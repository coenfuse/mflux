// standard includes
// ..

// internal includes
#include "influx/client.h"

// module includes
// ..

// thirdparty includes
// cinflux



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


		ERC Client::start_service(void)
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