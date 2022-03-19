// standard includes
#include <iostream>


// internal includes
#include "influx/client.h"
#include "influx/message.h"


// module includes
// ..


// thirdparty includes
// cinflux
#include "spdlog/spdlog.h"


namespace felidae
{
	namespace influx
	{
		
		Client::Client(void)
		{}

		Client::~Client(void)
		{}


		ERC Client::connect(void)
		{
			auto status = ERC::SUCCESS;

			// ..

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


		ERC Client::get(void)
		{
			auto status = ERC::SUCCESS;
			
			// ..

			return status;
		}

		ERC Client::push(void)
		{
			auto status = ERC::SUCCESS;

			// ..

			return status;
		}

		ERC Client::pop(void)
		{
			auto status = ERC::SUCCESS;

			// ..

			return status;
		}

		ERC Client::remove(void)
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



		// PRIVATE DEFINIIIONS

		void Client::m_actual_job(void)
		{
			auto status = ERC::SUCCESS;

			auto buffer_name = Configurator::get_influx_outbox_name();
			Message influx_msg;
			DBitem dbitem;

			m_signalled_stop.exchange(false);

			while (!m_signalled_stop)
			{
				// wait for a message in influx outbox
				if (!m_pBuffer->is_empty(buffer_name))
				{
					// Pull the DBitem from the inbox buffer
					status = m_pBuffer->pop(buffer_name, dbitem);

					// Get the message from the DBitem
					if (status == ERC::SUCCESS)
						status = dbitem.get<influx::Message>(influx_msg);

					spdlog::trace("Received {}", influx_msg.dump());

					// Send it to Influx DB
					// if (status == ERC::SUCCESS)
					// 	status = this->push(influx_msg);
				}

				// Take a breath for while
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}

		void Client::s_service_wrapper(void* instance)
		{
			Client* self_instance = (Client*)instance;
			self_instance->m_actual_job();					// This thread blocks here
		}
	}
}