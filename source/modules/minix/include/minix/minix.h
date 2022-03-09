// preprocessor flags
#pragma once

// standard includes
// ..

// internal includes
// ..

// module includes
#include "errorcodes/errorcodes.h"
#include "influx/message.h"
#include "mqtt/message.h"

// thirdparty includes
// ..

// forward references
// ..



namespace felidae
{
    namespace minix
    {
        ERC get_influx_msg(void);

        ERC get_mqtt_msg(void);
    }
}