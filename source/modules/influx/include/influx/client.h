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
	namespace influx
	{
		class Client
		{
		public:
			
			Client(void);
			~Client(void);

			ERC connect(void);
			ERC disconnect(void);
			bool is_connected(void);

			ERC get(void);
			ERC push(void);
			ERC pop(void);
			ERC remove(void);

			ERC start_service(std::shared_ptr<Configurator> p_config, std::shared_ptr<MemDB> p_buffer);
			ERC stop_service(void);
			bool is_running(void);
		};
	}
}