// preprocessor flags
#pragma once

// standard includes
#include <memory>

// internal includes
// ..

// module includes
#include "configurator/configurator.h"
#include "errorcodes/errorcodes.h"

// thirdparty includes
// ..

// forward references
// ..



namespace felidae
{
	namespace mqtt
	{
		class Client
		{
		public:
			
			Client(void);
			~Client(void);

			ERC connect(void);
			ERC disconnect(void);
			bool is_connected(void);

			ERC publish(void);
			ERC subscribe(void);
			ERC unsubscribe(void);

			ERC start_service(std::shared_ptr<Configurator> p_config);
			ERC stop_service(void);
			bool is_running(void);
		};
	}
}