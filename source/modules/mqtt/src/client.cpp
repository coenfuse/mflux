// standard includes
// ..


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
		
		Client::Client(void):
			m_signalled_stop(true),
			m_pBuffer(nullptr),
			m_pConfig(nullptr),
			m_pMosq(nullptr),
			m_is_mosq_initialized(false)
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
			int timeout_s = 60)
		{
			auto status = ERC::SUCCESS;

			// initialize mosquitto library
			if(!m_is_mosq_initialized)
				this->initialize();

			// connect async to mqtt

			// set reconnection thread

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
			auto status = true;

			// ..

			return status;
		}


		ERC Client::publish(void)
		{
			auto status = ERC::SUCCESS;
			
			// ..

			return status;
		}

		ERC Client::subscribe(
			std::string topic,
			int qos = 0,
			bool retain = false,
			std::function<void(void)> callback = nullptr
		)
		{
			auto status = ERC::SUCCESS;

			// ..

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
					status = ERC::SUCCESS;

				// subscribe to topics
				if(status == ERC::SUCCESS)
					for (auto subscription : m_pConfig->get_mqtt_sub_list())
						status = this->subscribe(
							subscription.get_topic(), 
							subscription.get_qos(), 
							subscription.get_to_retain()
						);

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

				m_signalled_stop.exchange(true);
				m_worker.join();

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

		ERC Client::initialize(void)
		{
			auto status = ERC::SUCCESS;

			if(mosquitto_lib_init() != MOSQ_ERR_SUCCESS)
				status = ERC::MEMORY_ALLOCATION_FAILED;
			
			// create mosquitto instance
			m_pMosq = mosquitto_new(nullptr, true, nullptr);

			// set mosquitto credentials

			// set mosquitto callbacks

			// update initialization flag

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
				srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

				mqtt_msg.set_topic("BASSAI");
				mqtt_msg.set_qos(rand() % 3);
				mqtt_msg.set_to_retain(rand() % 2);
				mqtt_msg.set_payload(fmt::format("{}", rand() % 99));

				dbitem.set<Message>(mqtt_msg);

				m_pBuffer->push(buffer_name, dbitem);
				
				spdlog::trace("Sent     {} payload: {} qos: {} retention: {}", mqtt_msg.get_topic(), mqtt_msg.get_payload(), mqtt_msg.get_qos(), mqtt_msg.get_to_retain());

				// Take a break for a while
				std::this_thread::sleep_for(std::chrono::seconds(3));
			}
		}
		
		void Client::s_service_wrapper(void* instance)
		{
			Client* self_instance = (Client*)instance;
			self_instance->i_actual_job();						// This thread blocks here
		}
	}
}