// standard includes
#include <iostream>


// internal includes
#include "influx/client.h"
#include "influx/message.h"


// module includes
// ..


// thirdparty includes
// #include "cinflux/cinflux.h"
#include "fmt/format.h"
#include "httplib/httplib.h"
#include "spdlog/spdlog.h"


namespace felidae
{
	namespace influx
	{
		
		Client::Client(void):
			m_pBuffer(nullptr),
			m_pConfig(nullptr),
			m_signalled_stop(true),
			m_pHTTP_cli(nullptr)
		{}

		Client::~Client(void)
		{}


		ERC Client::connect(std::string host, uint16_t port, std::string token)
		{
			auto status = ERC::SUCCESS;
			int httpres = 0;

			m_pHTTP_cli = std::make_shared<httplib::Client>(host, port);
			m_token = token;

			if (m_pHTTP_cli == nullptr)
				status = ERC::MEMORY_ALLOCATION_FAILED;

			if (status == ERC::SUCCESS)
				httpres = m_pHTTP_cli->Get("/ping")->status;

			if(httpres != 204)
				status = ERC::FAILURE;
				
			if(status == ERC::SUCCESS)
				m_pHTTP_cli->set_keep_alive(true);

			if (status == ERC::SUCCESS)
				spdlog::info("{} remote connect success at {}:{}", SELF_NAME, host, port);
			else
				spdlog::error("{} remote connect failure at {}:{} with HTTP code {}", SELF_NAME, host, port, httpres);

			return status;
		}

		ERC Client::disconnect(void)
		{
			auto status = ERC::SUCCESS;

			m_pHTTP_cli->set_keep_alive(false);
			m_pHTTP_cli.reset();

			return status;
		}

		bool Client::is_connected(void)
		{
			auto status = false;

			if (m_pHTTP_cli != nullptr)
			{
				if(m_pHTTP_cli->Get("/ping")->status == 204)
					status = true;
			}

			return status;
		}

		/*
		ERC Client::query(std::string org_name, std::string bucket, std::string flux_query)
		{
			auto status = ERC::SUCCESS;
			
			// ..

			return status;
		}
		*/

		ERC Client::write(std::string org, std::string bucket, Message data)
		{
			auto status = ERC::FAILURE;

			if(this->is_connected())
			{
				// Update write path
				auto path = fmt::format(
					"/api/v2/write?org={}&bucket={}&precision={}", 
					org, 
					bucket, 
					data.get_timestamp_precision()
				);

				// Update write headers
				httplib::Headers headers = {
					{"Authorization", fmt::format("Token {}", m_token)},
					{"Content-Type", "text/plain; charset=utf-8"},
					{"Accept", "application/json"}
				};

				// Write using HTTP POST
				auto res = m_pHTTP_cli->Post(
					path.c_str(), 
					headers, 
					data.dump().c_str(), 
					data.dump().length(), 
					"text/plain"
				);

				// Analyse response
				if(res->status == 204)
				{
					spdlog::info("{} write success", SELF_NAME);
					status = ERC::SUCCESS;
				}
				else
				{
					spdlog::warn(
						"{} write failure with HTTP code {}:{} for data {}",
						SELF_NAME, 
						res->status, 
						res->body,
						data.dump()
						);
				}
			}

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
						m_pConfig->get_influx_host(), 
						m_pConfig->get_influx_port(), 
						m_pConfig->get_influx_db_auth_key());

				if (status == ERC::SUCCESS)
					m_worker = std::thread(si_service_wrapper, this);

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

				this->disconnect();

				if(this->is_running())
					status = ERC::FAILURE;

				if(status == ERC::SUCCESS)
					spdlog::info("{} service stopped", SELF_NAME);
				else
					spdlog::error("{} service failed to stop with code {}", SELF_NAME, status);
			}

			return status;
		}

		bool Client::is_running(void)
		{
			return m_worker.joinable();
		}



		// PRIVATE DEFINIIIONS

		void Client::i_actual_job(void)
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
					if (status == ERC::SUCCESS)
						status = this->write(
							m_pConfig->get_influx_org_name(),
							m_pConfig->get_influx_db_name(),
							influx_msg);
				}

				// Take a breath for while
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}

		void Client::si_service_wrapper(void* p_instance)
		{
			// Thread blocks here
			static_cast<Client*>(p_instance)->i_actual_job();
		}
	}
}