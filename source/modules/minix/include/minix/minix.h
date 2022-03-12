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
        // TODO : Docs
        ERC get_influx_msg_from(mqtt::Message this_msg, influx::Message& into_this);

        // TODO : Docs
        ERC get_mqtt_msg_from(influx::Message this_msg, mqtt::Message& into_this);
    }
}