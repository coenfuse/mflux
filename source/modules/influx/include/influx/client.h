// preprocessor flags
#pragma once

// standard includes
// ..

// internal includes
// ..

// module includes
#include "errorcodes/errorcodes.h"

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

			ERC start_service(void);
			ERC stop_service(void);
			bool is_running(void);
		};
	}
}