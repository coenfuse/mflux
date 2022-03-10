// standard includes
// ..

// internal includes
#include "minix/minix.h"

// module includes
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
        ERC get_influx_msg_from(mqtt::Message this_msg, influx::Message& into_this)
        {
            auto status = ERC::SUCCESS;
            // ..
            return status;
        }

        ERC get_mqtt_msg_from(influx::Message this_msg, mqtt::Message& into_this)
        {
            auto status = ERC::SUCCESS;
            // ..
            return status;
        }
    }
}