// preprocessor flags
#pragma once

// standard includes
#include <string>

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
		class Message
		{
		public:

			Message(void){}
			~Message(void){}

			std::string dump(){}
			ERC parse(std::string msg){}
		};
	}
}