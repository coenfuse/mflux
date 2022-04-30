// standard includes
#include <algorithm>
#include <exception>
#include <iostream>
#include <string>


// internal includes
#include "converters.h"


// module includes
// ..


// thirdparty includes
#include "json/json.hpp"
#include "spdlog/spdlog.h"



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
        mqtt::Message mqtt_msg,
        influx::Message &influx_msg)
    {
        auto status = ERC::SUCCESS;

        try
        {
            using namespace std;
            using namespace nlohmann;

            json payload = json::parse(mqtt_msg.get_payload());
            string data = payload["DATA"].at(0).at(4);

            string temp1_str = data.substr(6,4);
            int64_t temp1 = stoi(temp1_str, nullptr, 16);

            string temp2_str = data.substr(10,4);
            int64_t temp2 = stoi(temp2_str, nullptr, 16);

            string watt_str = data.substr(30,4);
            int64_t watt = stoi(watt_str, nullptr, 16);

            string channel_name = payload["DATA"].at(0).at(0);
            replace(channel_name.begin(), channel_name.end(), ' ', '_');
            
            string channel_code = payload["DATA"].at(0).at(1);
            int channel_num = stoi(channel_code, nullptr, 16);

            influx_msg.clear();

            if(channel_num == 1)
            {
                influx_msg.set_measure("Measurement");
                influx_msg.add_tag_set("Channel", channel_name);
                influx_msg.add_tag_set("Channel_Code", channel_code);
                influx_msg.add_field_set("CProd1", temp1);
                influx_msg.add_field_set("CProd2", temp2);
                influx_msg.add_field_set("CLoad", watt);
            }
            else if(channel_num == 2)
            {
                influx_msg.set_measure("Measurement");
                influx_msg.add_tag_set("Channel", channel_name);
                influx_msg.add_tag_set("Channel_Code", channel_code);
                influx_msg.add_field_set("Temprature", temp1);
            }
            else
                status = ERC::FAILURE;
        }
        catch(std::exception& e)
        {
            spdlog::error(
                "MINIX : Exception '{}' in M2I conv. for payload '{}'",
                e.what(), 
                mqtt_msg.get_payload());
                
            status = ERC::EXCEPTION;
        }

        return status;
    }
}