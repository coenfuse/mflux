// standard includes
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
        mqtt::Message this_msg,
        influx::Message &into_this)
    {
        auto status = ERC::SUCCESS;

        into_this.clear();

        try
        {
            nlohmann::json payload = nlohmann::json::parse(this_msg.get_payload());
            std::string dataStr = payload["DATA"].at(0).at(4);

            // read 4 characters from index 6
            std::string temp1_str = dataStr.substr(6,4);
            int64_t temp1_num  = std::stoi(temp1_str, nullptr, 16);

            // read 4 characters from index 10
            std::string temp2_str = dataStr.substr(10,4);
            int64_t temp2_num  = std::stoi(temp2_str, nullptr, 16);

            // read 4 characters from index 30
            std::string watt_str = dataStr.substr(30,4);
            int64_t watt_int = std::stoi(watt_str, nullptr, 16);

            // normalize temprature values
            temp1_num = (temp2_num - 1) * 65536 + temp1_num;
            temp2_num = (temp2_num) * 65536 + temp1_num; 

            // fetch channel data // TODO - Remove white_space from Channel_Name
            std::string channel_name = payload["DATA"].at(0).at(0);
            std::string channel_str = payload["DATA"].at(0).at(1);
            int64_t channel_num = std::stoi(channel_str, nullptr, 16);

            // Prepare influx data set
            if(channel_num == 1)
            {
                into_this.set_measure("Measurement");
                into_this.add_tag_set("Channel", channel_name);
                into_this.add_tag_set("Channel_Number", channel_str);
                into_this.add_field_set("FF_CProd1", temp1_num);
                into_this.add_field_set("CProd2", temp2_num);
                into_this.add_field_set("CLoad", watt_int);
            }
            else if(channel_num == 2)
            {
                into_this.set_measure("Measurement");
                into_this.add_tag_set("Channel", channel_name);
                into_this.add_tag_set("Channel_Number", channel_str);
                into_this.add_field_set("FF2_Temprature", temp1_num);
            }
        }
        catch(std::exception& e)
        {
            spdlog::error(
                "MINIX : Exception '{}' in M2I conv. for payload '{}'",
                e.what(), 
                this_msg.get_payload());
                
            status = ERC::EXCEPTION;
        }

        return status;
    }
}