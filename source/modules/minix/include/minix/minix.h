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
    /// Minix is a simple library that provides consistent 
    /// translations of influx message to mqtt message and 
    /// vice versa

    namespace minix
    {
        /// Converts a mqtt::Message into influx::Message.
        /// Returns ERC::FAILURE upon error
        ERC get_influx_msg_from(mqtt::Message this_msg, influx::Message& into_this);

        /// Converts a influx::Message into mqtt::Message.
        /// Returns ERC::FAILURE upon error
        ERC get_mqtt_msg_from(influx::Message this_msg, mqtt::Message& into_this);
    }
}