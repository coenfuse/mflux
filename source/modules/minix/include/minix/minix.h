// preprocessor flags
#pragma once

// standard includes
// ..

// module includes
#include "errorcodes/errorcodes.h"

// thirdparty includes
// ..

// forward references
// influx message
// mqtt message



namespace felidae
{
    namespace minix
    {
        ERC get_influx_msg(void);

        ERC get_mqtt_msg(void);
    }
}