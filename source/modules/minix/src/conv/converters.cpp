// standard includes
#include <iostream>

// internal includes
#include "converters.h"

// module includes
// ..

// thirdparty includes
// ..

namespace felidae
{
    ERC m2i_mflux_debug(
        mqtt::Message this_msg,
        influx::Message &into_this)
    {
        auto status = ERC::SUCCESS;
        
        into_this.clear();
            
        into_this.set_measure(this_msg.get_topic());
        into_this.add_tag_set("payload", this_msg.get_payload());
        into_this.add_field_set("retention", this_msg.get_to_retain());
        into_this.add_field_set("qos", (int64_t)this_msg.get_qos());
        into_this.set_timestamp_precision(influx::Message::TimeStamp_t::microseconds);

        return status;
    }

    ERC m2i_BASSAI(
        mqtt::Message this_msg,
        influx::Message &into_this)
    {
        auto status = ERC::SUCCESS;

        // ..

        return status;
    }
}