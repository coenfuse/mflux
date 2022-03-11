// standard includes
// ..

// internal includes
#include "mqtt/client.h"

// module includes
// ..

// thirdparty includes
// mosquitto



namespace felidae
{
	namespace mqtt
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


		ERC Client::publish(void)
		{
			auto status = ERC::SUCCESS;
			
			// ..

			return status;
		}

		ERC Client::subscribe(void)
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

			// ..

			return status;
		}

		ERC Client::stop_service(void)
		{
			auto status = ERC::SUCCESS;

			// ..

			return status;
		}

		bool Client::is_running(void)
		{
			auto status = true;

			// ..

			return status;
		}
	}
}