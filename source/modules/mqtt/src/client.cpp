// standard includes
#include <memory>


// internal includes
#include "mqtt/client.h"
#include "mqtt/message.h"


// module includes
// ..


// thirdparty includes
#include "mosquitto.h"
#include "spdlog/spdlog.h"



namespace felidae
{
	namespace mqtt
	{
		// Static / Global attributes declaration
		// TODO : Docs, it is a patch work
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
		{}


		ERC Client::connect(
			std::string client_id,
			bool is_clean,
			std::string host, 
			int port, 
			std::string username, 
			std::string password, 
			int timeout_s)
		{
			auto status = ERC::SUCCESS;

			// initialize mosquitto library
			if(!m_is_mosq_initialized)
				status = this->i_initialize(client_id, is_clean, username, password);

			// connect async to mqtt
			if (status == ERC::SUCCESS)
			{
				if(!m_is_mosq_connected)
					status = (ERC)(mosquitto_connect_async(m_pMosq, host.c_str(), port, timeout_s));

				if(status == ERC::SUCCESS)
					status = (ERC)(mosquitto_reconnect_async(m_pMosq));
			}

			// update connecton flag
			if(status == ERC::SUCCESS)
				m_is_mosq_connected = true;

			return status;
		}

		ERC Client::disconnect(void)
		{
			auto status = ERC::SUCCESS;

			// ..

			return status;
		}

		bool Client::is_connected(void)
		{
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
			auto status = ERC::SUCCESS;

			status = (ERC)(mosquitto_subscribe(m_pMosq, nullptr, topic.c_str(), (int)qos));

			if(status == ERC::SUCCESS)
			{
				if(callback != nullptr)
				{
					g_on_msg_callback_table[topic] = callback;
					spdlog::debug("{} subscribed to topic '{}' with callback", SELF_NAME, topic);
				}
				else
				{
					spdlog::debug("{} subscribed to topic '{}' w/o callback", SELF_NAME, topic);
				}
			}
			else
			{
				spdlog::warn("{} failed to subscribe to topic '{}'", SELF_NAME, topic);
			}

			return status;
		}

		ERC Client::unsubscribe(void)
		{
			auto status = ERC::SUCCESS;

			// ..

			return status;
		}


		ERC Client::start_service(std::shared_ptr<Configurator> p_config, std::shared_ptr<MemDB> p_buffer)
		{
			auto status = ERC::SUCCESS;

			if (!this->is_running())
			{
				spdlog::debug("{} service starting", SELF_NAME);

				m_pConfig = p_config;
				m_pBuffer = p_buffer;

				if ((m_pConfig == nullptr) || (m_pBuffer == nullptr))
					status = ERC::NULLPTR_RECV;

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

				// set network monitor
				if(status == ERC::SUCCESS)
					status = this->start_network_monitor();

				// subscribe to topics (TODO : Add break when subscribe fails)
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
					m_worker = std::thread(s_service_wrapper, this);

				if (this->is_running())
					status = ERC::SUCCESS;

				if (status == ERC::SUCCESS)
					spdlog::info("{} service started", SELF_NAME);
				else
					spdlog::error("{} service failed to start with code {}", SELF_NAME, status);
			}

			return status;
		}

		ERC Client::stop_service(void)
		{
			auto status = ERC::SUCCESS;

			if (this->is_running())
			{
				spdlog::debug("{} service stopping", SELF_NAME);

				// stop service
				m_signalled_stop.exchange(true);
				m_worker.join();

				// unsubscribe from topics
				// ..

				// stop network monitor
				// ..

				// disconnect from broker
				// ..

				// deallocate config and buffer pointers
				// ..

				spdlog::info("{} service stopped", SELF_NAME);
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
			std::string client_id,
			bool is_clean,
			std::string username, 
			std::string password)
		{
			auto status = ERC::SUCCESS;

			if(mosquitto_lib_init() != MOSQ_ERR_SUCCESS)
				status = ERC::MEMORY_ALLOCATION_FAILED;
			
			// allocate new mosquitto instance
			if (status == ERC::SUCCESS)
				m_pMosq = mosquitto_new(client_id.c_str(), is_clean, nullptr);
			
			// check allocation status
			if (m_pMosq == nullptr)
				status = ERC::MEMORY_ALLOCATION_FAILED;

			// set mosquitto credentials
			if (status == ERC::SUCCESS)
			{
				auto uid_cstr = username.c_str();
				auto pwd_cstr = password.c_str();
				status = (ERC)(mosquitto_username_pw_set(m_pMosq, uid_cstr, pwd_cstr));
			}

			// set mosquitto callbacks
			if (status == ERC::SUCCESS)
			{
				mosquitto_message_callback_set(m_pMosq, s_on_message_wrapper);
				mosquitto_publish_callback_set(m_pMosq, s_on_publish_wrapper);
				mosquitto_connect_callback_set(m_pMosq, s_on_connect_wrapper);
				mosquitto_disconnect_callback_set(m_pMosq, s_on_disconnect_wrapper);
				mosquitto_subscribe_callback_set(m_pMosq, s_on_subscribe_wrapper);
				mosquitto_unsubscribe_callback_set(m_pMosq, s_on_unsubscribe_wrapper);
			}

			// update initialization flag
			if (status == ERC::SUCCESS)
				m_is_mosq_initialized = true;

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

		ERC Client::start_network_monitor(void)
		{
			ERC status = ERC::SUCCESS;

			if(!m_is_monitoring)
			{
				spdlog::debug("{} network monitor starting", SELF_NAME);

				m_monitor_thread = std::thread(s_network_monitor_wrapper, this);
				
				// Wait for monitor to start
				std::this_thread::sleep_for(std::chrono::seconds(1));
				m_is_monitoring = !m_monitor_thread.joinable();

				spdlog::debug("{} network monitor started", SELF_NAME);
			}

			return status;
		}

		void Client::i_actual_monitor(void)
		{
			spdlog::debug("{} started network monitoring", SELF_NAME);

			m_is_monitoring.exchange(true);

			// TODO : Remove this always on condition, use do-while instead?
			while(true)
			{
				mosquitto_loop(m_pMosq, 100, 1);
			}

			spdlog::debug("{} stopped network monitoring", SELF_NAME);

			// TODO : Consider usage of mosquitto_loop_forever() and 
			// mosquitto_loop_start() instead
		}

		void Client::i_on_connect_callback(void* instance, int status)
		{
			//if(custom_callback != nullptr)
			//	custom_callback(status);
			//else
				spdlog::debug("{} mosquitto connected", SELF_NAME);
		}

		void Client::i_on_disconnect_callback(void* instance, int status)
		{
			// TODO : Find a way to detect if disconnection was manual or
			// due to an error. Try reconnecting if the latter is true.
			spdlog::debug("{} mosquitto disconnected", SELF_NAME);
		}

		void Client::i_on_subscribe_callback(void* instance, int mid, int qos, const int* granted_qos)
		{
			//if(custom_callback != nullptr)
			//	custom_callback(status);
			//else
			spdlog::debug("{} mosquitto subscribed", SELF_NAME);
		}

		void Client::i_on_unsubscribe_callback(void* instance, int mid)
		{
			//if(custom_callback != nullptr)
			//	custom_callback(status);
			//else
			spdlog::debug("{} mosquitto unsubscribed", SELF_NAME);
		}

		void Client::i_on_publish_callback(void* instance, int mid)
		{
			//if(custom_callback != nullptr)
			//	custom_callback(status);
			//else
			spdlog::debug("{} mosquitto published a message", SELF_NAME);
		}

		void Client::i_on_message_callback(const mosquitto_message* msg)
		{
			// cache topic into a strig type
			auto topic = std::string(msg->topic);

			// log
			spdlog::debug("{} received a message from topic {}", SELF_NAME, topic);

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

		void Client::s_service_wrapper(void* instance)
		{
			Client* self_instance = (Client*)instance;
			self_instance->i_actual_job();						// This thread blocks here
		}

		void Client::s_network_monitor_wrapper(void* instance)
		{
			Client* self_instance = (Client*)instance;
			self_instance->i_actual_monitor();					// This thread blocks here
		}

		void Client::s_on_connect_wrapper(mosquitto* instance, void* obj, int status)
		{
			Client* self_instance = (Client*)instance;
			self_instance->i_on_connect_callback(instance, status);
		}

		void Client::s_on_disconnect_wrapper(mosquitto* instance, void* obj, int status)
		{
			Client* self_instance = (Client*)instance;
			self_instance->i_on_disconnect_callback(instance, status);
		}

		void Client::s_on_subscribe_wrapper(mosquitto* instance, void* obj, int mid, int qos, const int* granted_qos)
		{
			Client* self_instance = (Client*)instance;
			self_instance->i_on_subscribe_callback(instance, mid, qos, granted_qos);
		}

		void Client::s_on_unsubscribe_wrapper(mosquitto* instance, void* obj, int mid)
		{
			Client* self_instance = (Client*)instance;
			self_instance->i_on_unsubscribe_callback(instance, mid);
		}

		void Client::s_on_publish_wrapper(mosquitto* instance, void* obj, int mid)
		{
			auto self_ref = static_cast<Client*>(obj);
			self_ref->i_on_publish_callback(instance, mid);
		}

		void Client::s_on_message_wrapper(mosquitto* instance, void* obj, const mosquitto_message* msg)
		{
			auto self_ref = std::make_unique<Client>();
			self_ref->i_on_message_callback(msg);
		}

	}	// namespace mqtt

}	// namespace felidae