// standard includes
#include <memory>


// internal includes
#include "mqtt/client.h"
#include "mqtt/message.h"


// module includes
// ..


// thirdparty includes
#ifdef WIN32 
	#include "mosquitto/mosquitto.h"
#else
	#include "mosquitto.h"
#endif
#include "spdlog/spdlog.h"



namespace felidae
{
	namespace mqtt
	{
		// PATCH - globally available variable that stores on_message callbacks
		// Its a map object with a string key (topic name) and a callback value.
		// The client fails to function as required when this variable is set
		// as an attribute to client. Tested in both static and non-static style.
		std::map<std::string, Client::msg_callback_t> g_on_msg_callback_table = {};

		Client::Client(void):
			m_signalled_stop(true),
			m_pBuffer(nullptr),
			m_pConfig(nullptr),
			m_pMosq(nullptr),
			m_is_mosq_initialized(false),
			m_is_mosq_connected(false)
		{}

		Client::~Client(void)
		{
			mosquitto_lib_cleanup();
		}


		ERC Client::connect(
			std::string client_name,
			bool is_clean,
			std::string host, 
			int port, 
			std::string username, 
			std::string password, 
			int timeout_s)
		{
			auto status  = ERC::SUCCESS;
			int mosq_erc = MOSQ_ERR_SUCCESS;

			// initialize mosquitto library
			if(!m_is_mosq_initialized)
				status = this->i_initialize(client_name, is_clean, username, password);

			// connect asynchronously to mqtt
			if (status == ERC::SUCCESS)
			{
				spdlog::debug("{} connecting to {}:{}", SELF_NAME, host, port);

				if(!m_is_mosq_connected)
					mosq_erc = mosquitto_connect_async(m_pMosq, host.c_str(), port, timeout_s);

				if(mosq_erc == MOSQ_ERR_SUCCESS)
					mosq_erc = mosquitto_reconnect_async(m_pMosq);

				if(mosq_erc != MOSQ_ERR_SUCCESS)
					status = ERC::FAILURE;
			}	

			// start mosquitto network monitor
			if(status == ERC::SUCCESS)
				status = i_start_network_monitor();

			// NOTE - The network monitor should ideally be started post-init and pre-connect,
			// but doing so causes a little delay in callbacks invocations. Starting
			// monitor post connection resolves the issue surprisingly.

			// update connecton flag. There must be some other reliable way of knowing connection status.
			if(status == ERC::SUCCESS)
				m_is_mosq_connected = true;

			return status;
		}

		ERC Client::disconnect(void)
		{
			auto status  = ERC::SUCCESS;
			int mosq_erc = MOSQ_ERR_SUCCESS;

			// check connection status before disconnection
			if(this->is_connected())
			{
				mosq_erc = mosquitto_disconnect(m_pMosq);

				// set client status
				if (mosq_erc != MOSQ_ERR_SUCCESS)
					status = ERC::FAILURE;
				
				// update connection flag
				if(status == ERC::SUCCESS)
					m_is_mosq_connected = false;

				// stop mosquitto network monitor
				if(status == ERC::SUCCESS)
					status = i_stop_network_monitor();

				// destroy mosquitto instance and update init flag
				if (status == ERC::SUCCESS)
				{
					mosquitto_destroy(m_pMosq);
					m_is_mosq_initialized = false;
				}

				// log
				if (!m_is_mosq_initialized)
					spdlog::debug("{} mosq init clear success", SELF_NAME);
				else
					spdlog::error("{} mosq init clear failure with code {}", SELF_NAME, status);				
			}

			return status;
		}

		bool Client::is_connected(void)
		{
			// TODO - Try using a PING mechanism to ensure connection status
			// instead of relying on an unreliable boolean attribute
			return m_is_mosq_connected;
		}


		ERC Client::publish(void)
		{
			auto status = ERC::SUCCESS;
			
			// ..

			return status;
		}

		ERC Client::subscribe(
			std::string topic,
			uint8_t qos,
			bool retain,
			msg_callback_t callback
		)
		{
			auto status  = ERC::SUCCESS;
			int mosq_erc = MOSQ_ERR_SUCCESS;

			mosq_erc = mosquitto_subscribe(m_pMosq, nullptr, topic.c_str(), (int)qos);

			if (mosq_erc != MOSQ_ERR_SUCCESS)
				status = ERC::FAILURE;

			if(status == ERC::SUCCESS)
			{
				if(callback != nullptr)
				{
					g_on_msg_callback_table[topic] = callback;
					spdlog::debug("{} subscribe success to topic:{} qos:{} [C]", SELF_NAME, topic, qos);
				}
				else
				{
					spdlog::debug("{} subscribe success to topic:{} qos:{}", SELF_NAME, topic, qos);
				}
			}
			else
			{
				spdlog::warn("{} subscribe failure to topic '{}' with MOSQ_ERR_CODE {}", SELF_NAME, topic, mosq_erc);
			}

			return status;
		}

		ERC Client::unsubscribe(std::string topic)
		{
			auto status  = ERC::SUCCESS;
			int mosq_erc = MOSQ_ERR_NOT_FOUND;

			// Check connection
			if (this->is_connected())
			{
				bool subscription_exists = false;

				// Find if this subscription exists in callback table
				if (g_on_msg_callback_table.find(topic) != g_on_msg_callback_table.end())
					subscription_exists = true;

				// Unsubscribe if subscription exists, else do nothing
				if (subscription_exists)
					mosq_erc = mosquitto_unsubscribe(m_pMosq, nullptr, topic.c_str());

				// remove subscription from callback table
				if (mosq_erc == MOSQ_ERR_SUCCESS)
					g_on_msg_callback_table.erase(topic);
				else
					status = ERC::FAILURE;					// means, unsubscription failed

				// log
				if(status == ERC::SUCCESS)
					spdlog::debug("{} unsubscribe success from topic '{}'", SELF_NAME, topic);
				else
					spdlog::warn("{} unsubscribe failure from topic '{}' with MOSQ_ERR_CODE {}", SELF_NAME, topic, mosq_erc);
			}

			return status;
		}


		ERC Client::start_service(std::shared_ptr<Configurator> p_config, std::shared_ptr<MemDB> p_buffer)
		{
			auto status = ERC::SUCCESS;

			if (!this->is_running())
			{
				spdlog::trace("{} service starting", SELF_NAME);

				// allocate config and buffer pointer copies
				m_pConfig = p_config;
				m_pBuffer = p_buffer;

				if ((m_pConfig == nullptr) || (m_pBuffer == nullptr))
					status = ERC::NULLPTR_RECV;

				// connect to broker
				if(status == ERC::SUCCESS)
					status = this->connect(
						m_pConfig->get_mqtt_client_name(),
						m_pConfig->is_mqtt_clean(),
						m_pConfig->get_mqtt_host(),
						m_pConfig->get_mqtt_port(),
						m_pConfig->get_mqtt_username(),
						m_pConfig->get_mqtt_password(),
						m_pConfig->get_mqtt_timeout_s()
					);

				// subscribe to topics
				// TODO - Add break when subscribe fails
				if(status == ERC::SUCCESS)
					for (auto subscription : m_pConfig->get_mqtt_sub_list())
						status = this->subscribe(
							subscription.get_topic(), 
							subscription.get_qos(), 
							subscription.get_to_retain(),
							[&](const mosquitto_message* msg)
							{
								// get mqtt inbox name from configurator
								auto inbox_name = m_pConfig->get_mqtt_inbox_name();

								// convert Message from mosquitto_message
								Message msg_obj;
								auto payload = (std::string)(const char*)msg->payload;

								msg_obj.set_to_retain(false);
								msg_obj.set_payload(payload);
								msg_obj.set_topic(msg->topic);
								msg_obj.set_qos(msg->qos);

								spdlog::trace("{} processing received msg with topic: {} payload: {} qos: {} retention: {}", 
									SELF_NAME,
									msg_obj.get_topic(), 
									msg_obj.get_payload(), 
									msg_obj.get_qos(), 
									msg_obj.get_to_retain()
								);

								// create a db item with message
								DBitem dbitem;
								dbitem.set<Message>(msg_obj);

								// push db item to buffer
								m_pBuffer->push(inbox_name, dbitem);
							}
						);

				// start service
				if (status == ERC::SUCCESS)
					m_worker = std::thread(si_service_wrapper, this);

				if (this->is_running())
					status = ERC::SUCCESS;

				if (status == ERC::SUCCESS)
					spdlog::debug("{} service start success", SELF_NAME);
				else
					spdlog::error("{} service start failure with code {}", SELF_NAME, status);
			}

			return status;
		}

		ERC Client::stop_service(void)
		{
			auto status = ERC::SUCCESS;

			if (this->is_running())
			{
				spdlog::trace("{} service stopping", SELF_NAME);

				// stop service
				m_signalled_stop.exchange(true);
				m_worker.join();												// Wait to stop and join

				// unsubscribe from topics
				if(status == ERC::SUCCESS)
					for (auto subscription : m_pConfig->get_mqtt_sub_list())
						status = this->unsubscribe(subscription.get_topic());

				// disconnect from broker
				if(status == ERC::SUCCESS)
					status = this->disconnect();

				// deallocate config and buffer pointers copies
				if(status == ERC::SUCCESS)
				{
					m_pConfig = nullptr;
					m_pBuffer = nullptr;
				}

				// log
				if (status == ERC::SUCCESS)
					spdlog::debug("{} service stop success", SELF_NAME);
				else
					spdlog::error("{} service failed to stop with code {}", SELF_NAME, status);
			}

			return status;
		}

		bool Client::is_running(void)
		{
			return m_worker.joinable();
		}



		// PRIVATE DEFINITIONS
		// ------------------------------------------------------

		ERC Client::i_initialize(
			std::string client_name,
			bool is_clean,
			std::string username, 
			std::string password)
		{
			auto status  = ERC::SUCCESS;
			int mosq_erc = MOSQ_ERR_SUCCESS;

			spdlog::trace("{} mosq initializing", SELF_NAME);

			if(mosquitto_lib_init() != MOSQ_ERR_SUCCESS)
				status = ERC::MEMORY_ALLOCATION_FAILED;
			
			// allocate new mosquitto instance
			if (status == ERC::SUCCESS)
				m_pMosq = mosquitto_new(client_name.c_str(), is_clean, nullptr);
			
			// check allocation status
			if (m_pMosq == nullptr)
				status = ERC::MEMORY_ALLOCATION_FAILED;

			// set mosquitto credentials
			if (status == ERC::SUCCESS)
				mosq_erc = mosquitto_username_pw_set(m_pMosq, username.c_str(), password.c_str());

			// update status
			if (mosq_erc != MOSQ_ERR_SUCCESS)
				status = ERC::FAILURE;

			// set mosquitto callbacks
			if (status == ERC::SUCCESS)
			{
				//mosquitto_threaded_set(m_pMosq, this);
				mosquitto_message_callback_set(m_pMosq, si_on_message_wrapper);
				mosquitto_publish_callback_set(m_pMosq, si_on_publish_wrapper);
				mosquitto_connect_callback_set(m_pMosq, si_on_connect_wrapper);
				mosquitto_disconnect_callback_set(m_pMosq, si_on_disconnect_wrapper);
				mosquitto_subscribe_callback_set(m_pMosq, si_on_subscribe_wrapper);
				mosquitto_unsubscribe_callback_set(m_pMosq, si_on_unsubscribe_wrapper);
			}

			// update initialization flag
			if (status == ERC::SUCCESS)
				m_is_mosq_initialized = true;

			// log
			if (m_is_mosq_initialized)
				spdlog::debug("{} mosq init success", SELF_NAME);
			else
				spdlog::error("{} mosq init failure with MOSQ_ERR_CODE {}", SELF_NAME, mosq_erc);

			return status;
		}

		void Client::i_actual_job(void)
		{
			auto status = ERC::SUCCESS;

			auto buffer_name = Configurator::get_mqtt_inbox_name();
			Message mqtt_msg;
			DBitem dbitem;

			m_signalled_stop.exchange(false);

			while (!m_signalled_stop)
			{
				/*
				srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

				mqtt_msg.set_topic("BASSAI");
				mqtt_msg.set_qos(rand() % 3);
				mqtt_msg.set_to_retain(rand() % 2);
				mqtt_msg.set_payload(fmt::format("{}", rand() % 99));

				dbitem.set<Message>(mqtt_msg);

				m_pBuffer->push(buffer_name, dbitem);
				
				spdlog::trace("Sent     {} payload: {} qos: {} retention: {}", mqtt_msg.get_topic(), mqtt_msg.get_payload(), mqtt_msg.get_qos(), mqtt_msg.get_to_retain());

				*/
				// Take a break for a while
				std::this_thread::sleep_for(std::chrono::seconds(3));
			}

			//return status;
		}

		ERC Client::i_start_network_monitor(void)
		{
			auto status  = ERC::SUCCESS;
			int mosq_erc = MOSQ_ERR_SUCCESS;

			if(!m_is_monitoring)
			{
				spdlog::trace("{} mosq loop starting", SELF_NAME);

				#ifdef WIN32
					m_is_monitoring.exchange(true);
					m_monitor_thread = std::thread(si_network_monitor_wrapper, this);
					
					std::this_thread::sleep_for(std::chrono::milliseconds(500));		// Wait to start up
					
					// BUG: If thread is joinable, it means it is not running. Hence, failure.
					// status = (m_monitor_thread.joinable()) ? ERC::FAILURE : ERC::SUCCESS;
				#else
					mosq_erc = mosquitto_loop_start(m_pMosq);
					std::this_thread::sleep_for(std::chrono::milliseconds(500));

					if (mosq_erc == MOSQ_ERR_SUCCESS)
						m_is_monitoring = true;
					else
						status = ERC::FAILURE;
				#endif
				
				if (status == ERC::SUCCESS)
					spdlog::debug("{} mosq loop start success", SELF_NAME);
				else
					spdlog::error("{} mosq loop start failure with MOSQ_ERR_CODE {}", SELF_NAME, mosq_erc);
			}

			return status;
		}

		ERC Client::i_stop_network_monitor(void)
		{
			auto status  = ERC::SUCCESS;
			int mosq_erc = MOSQ_ERR_SUCCESS;

			if(m_is_monitoring)
			{
				spdlog::trace("{} mosq loop stopping", SELF_NAME);

				#ifdef WIN32
					m_is_monitoring.exchange(false);
					m_monitor_thread.join();											// Wait to stop and join
				#else
					mosq_erc = mosquitto_loop_stop(m_pMosq, true);
					
					if (mosq_erc == MOSQ_ERR_SUCCESS)
						m_is_monitoring = false;
					else
						status = ERC::FAILURE;
				#endif

				if (status == ERC::SUCCESS)
					spdlog::debug("{} mosq loop stop success", SELF_NAME);
				else
					spdlog::error("{} mosq loop stop failure with MOSQ_ERR_CODE {}", SELF_NAME, mosq_erc);
			}

			return status;
		}

		void Client::i_actual_monitor(void)
		{
			while (m_is_monitoring)
				mosquitto_loop(m_pMosq, 100, 1);
		}

		void Client::i_on_connect_callback(void* instance, int status)
		{
			if (status == MOSQ_ERR_SUCCESS)
				spdlog::debug("{} mosq connect success", SELF_NAME);
			else
				spdlog::error("{} mosq connect failure with MOSQ_ERR_CODE {}", SELF_NAME, status);
		}

		void Client::i_on_disconnect_callback(void* instance, int status)
		{
			// TODO - Find a way to detect if disconnection was manual or due to an error. Try reconnecting if the latter is true.
			if (status == MOSQ_ERR_SUCCESS)
				spdlog::debug("{} mosq disconnect success", SELF_NAME);
			else
				spdlog::error("{} mosq disconnect failure with MOSQ_ERR_CODE {}", SELF_NAME, status);
		}

		void Client::i_on_subscribe_callback(void* instance, int mid, int qos_count, const int* granted_qos)
		{
			spdlog::debug("{} mosq subs with mid {} and qos {}", SELF_NAME, mid, *granted_qos);
		}

		void Client::i_on_unsubscribe_callback(void* instance, int mid)
		{
			spdlog::debug("{} mosq unsub with mid {}", SELF_NAME, mid);
		}

		void Client::i_on_publish_callback(void* instance, int mid)
		{
			//if(custom_callback != nullptr)
			//	custom_callback(status);
			//else
			spdlog::debug("{} mosq sent msg with mid {}", SELF_NAME, mid);
		}

		void Client::i_on_message_callback(const mosquitto_message* msg)
		{
			// cache topic into a strig type
			auto topic = std::string(msg->topic);

			spdlog::debug("{} mosq recv msg with topic {}", SELF_NAME, topic);

			// search callback table for any callback actions
			if (g_on_msg_callback_table.find(topic) != g_on_msg_callback_table.end())
			{
				// retrieve custom callback action
				auto callback = g_on_msg_callback_table.at(std::string(msg->topic));
				
				// perform custom callback action if not null
				if (callback != nullptr)
					callback(msg);
			}
			else
			{
				// perform default action
				// ..
			}
		}



		// STATIC DEFINITIONS
		// ------------------------------------------------------

		void Client::si_service_wrapper(void* p_instance)
		{
			// Thread blocks here
			static_cast<Client*>(p_instance)->i_actual_job();
		}

		void Client::si_network_monitor_wrapper(void* p_instance)
		{
			// Thread blocks here
			static_cast<Client*>(p_instance)->i_actual_monitor();
		}

		void Client::si_on_connect_wrapper(mosquitto* p_mosq, void* p_obj, int status)
		{
			static_cast<Client*>(p_obj)->i_on_connect_callback(p_mosq, status);
		}

		void Client::si_on_disconnect_wrapper(mosquitto* p_mosq, void* p_obj, int status)
		{
			static_cast<Client*>(p_obj)->i_on_disconnect_callback(p_mosq, status);
		}

		void Client::si_on_subscribe_wrapper(mosquitto* p_mosq, void* p_obj, int mid, int qos_count, const int* p_granted_qos)
		{
			static_cast<Client*>(p_obj)->i_on_subscribe_callback(p_mosq, mid, qos_count, p_granted_qos);
		}

		void Client::si_on_unsubscribe_wrapper(mosquitto* p_mosq, void* p_obj, int mid)
		{
			static_cast<Client*>(p_obj)->i_on_unsubscribe_callback(p_mosq, mid);
		}

		void Client::si_on_publish_wrapper(mosquitto* p_mosq, void* p_obj, int mid)
		{
			static_cast<Client*>(p_obj)->i_on_publish_callback(p_mosq, mid);
		}

		void Client::si_on_message_wrapper(mosquitto* p_mosq, void* p_obj, const mosquitto_message* p_msg)
		{
			std::make_unique<Client>()->i_on_message_callback(p_msg);
			//static_cast<Client*>(p_obj)->i_on_message_callback(p_msg);
		}

	}	// namespace mqtt

}	// namespace felidae