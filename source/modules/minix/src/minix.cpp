// standard includes
// ..


// internal includes
#include "minix/minix.h"
#include "conv/converters.h"


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

            if(this_msg.get_topic().empty())
                status = ERC::FAILURE;

            if(status == ERC::SUCCESS)
            {
                auto converter = M2I_conv.find(this_msg.get_topic());

                if(converter == M2I_conv.end())
                    status = ERC::FAILURE;
                else
                    status = converter->second(this_msg, into_this);
            }
            
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