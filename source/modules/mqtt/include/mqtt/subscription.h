// preprocessor flags
#pragma once

// standard includes
#include <cstdint>
#include <string>

// internal includes
// ..

// module includes
// ..

// thirdparty includes
// ..

// forward references
// ..



namespace felidae
{
	namespace mqtt
	{
		struct Subscription
        {
            std::string topic;
            uint8_t qos;
            bool retain;
        };
	}
}