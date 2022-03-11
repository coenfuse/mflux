// preprocessor flags
#pragma once

// standard includes
#include <memory>

// internal includes
// ..

// module includes
#include "configurator/configurator.h"
#include "errorcodes/errorcodes.h"
#include "memdb/memdb.h"

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

			ERC start_service(std::shared_ptr<Configurator> p_config, std::shared_ptr<MemDB> p_buffer);
			ERC stop_service(void);
			bool is_running(void);
		};
	}
}