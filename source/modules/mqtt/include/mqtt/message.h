// preprocessor flags
#pragma once

// standard includes
#include <string>

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
	namespace mqtt
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