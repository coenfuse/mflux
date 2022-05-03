// preprocessor flags
#pragma once


// standard includes
#include <functional>
#include <map>


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

    // Converter methods declaration
    // Documentation format: <TYPE> <ID>

    // Valid TYPEs are:
    // I2M - Influx to MQTT
    // M2I - MQTT to Influx

    // Valid IDs are:
    // BASSAI - MFlux's MQTT endpoint for M2I communication
    // MFLUX_DEBUG - Debug topic used for Mflux development

    /// [M2I] MFLUX_DEBUG
    ERC m2i_mflux_debug(
        mqtt::Message this_msg,
        influx::Message &into_this);

    /// [M2I] BASSAI
    ERC m2i_BASSAI(
        mqtt::Message this_msg,
        influx::Message &into_this);

    // Contains list of converter functions indexed by unique id in a single map
    // object. This allows instant access to required converter for received msg type

    // [M2I] MQTT to INFLUX converter access table
    static std::map<
        std::string,
        std::function<ERC(mqtt::Message, influx::Message &)>>
        M2I_conv = {
            {"BASSAI", m2i_BASSAI},
            {"mflux_debug", m2i_mflux_debug}

            // ..
    };

    // [I2M] INFLUX to MQTT converter access table
    /*
    std::map<
        std::string,
        std::function<ERC(mqtt::Message, influx::Message&)>
        > I2M_conv;
    */

} // namespace felidae
