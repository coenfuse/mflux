// preprocessor flags
#pragma once


// standard includes
#include <cstdint>
#include <memory>
#include <string>
#include <vector>


// internal includes
// ..


// module includes
#include "errorcodes/errorcodes.h"
#include "mqtt/subscription.h"


// thirdparty includes
#include "json/json.hpp"


// forward references
// ..



namespace felidae
{
    /// A getter class that provides access to the config 
    /// parameters for units and modules running in mflux.
    /// It reads the config.json file passed via command
    /// line args and parses using the nlohmann::json lib.
    /// The config class is available to all the apps and 
    /// modules publicly.

    class Configurator
    {
    public:

        Configurator(std::string file_path);
        ~Configurator();


        /// Path to save the log file into
        std::string get_logdir(void) const;

        /// Log level to save the log file with
        uint16_t get_log_level(void) const;
        
        /// Whether to use watchdog or not
        bool is_watchdog_on(void) const;

        /// The logging level for watchdog
        uint16_t get_watchdog_log_level(void) const;

        /// The interval in seconds to check the watchdog
        uint16_t get_watchdog_timeout_s(void) const;

        /// The command to execute once watchdog is timed out
        std::string get_watchdog_command(void) const;


        /// Whether to use MQTT or not
        bool is_mqtt_on(void) const;

        /// The MQTT logging level
        uint16_t get_mqtt_log_level(void) const;

        /// The MQTT client name
        std::string get_mqtt_client_name(void) const;
        
        /// Whether to set a clean MQTT connection or not
        bool is_mqtt_clean(void) const;

        /// The MQTT server IP
        std::string get_mqtt_host(void) const;
        
        /// The MQTT server port
        uint16_t get_mqtt_port(void) const;
        
        /// The MQTT connection keepalive interval in seconds
        uint16_t get_mqtt_timeout_s(void) const;
        
        /// The MQTT username
        std::string get_mqtt_username(void) const;
        
        /// The MQTT password
        std::string get_mqtt_password(void) const;
        
        /// The MQTT topic(s) to subscribe to
        std::vector<mqtt::Subscription> get_mqtt_sub_list(void) const;

        
        /// Whether to use InfluxDB or not
        bool is_influx_on(void) const;
        
        /// The InfluxDB logging level
        uint16_t get_influx_log_level(void) const;
        
        /// The InfluxDB client name
        std::string get_influx_client_name(void) const;
        
        /// The InfluxDB server IP
        std::string get_influx_host(void) const;
        
        /// The InfluxDB server port
        uint16_t get_influx_port(void) const;
        
        /// The InfluxDB connection keepalive interval in seconds
        uint16_t get_influx_timeout_s(void) const;

        /// The InfluxDB database organization name
        std::string get_influx_org_name(void) const;

        /// The InfluxDB database name
        std::string get_influx_db_name(void) const;
        
        /// The InfluxDB username
        std::string get_influx_db_username(void) const;
        
        /// The InfluxDB password
        std::string get_influx_db_password(void) const;
        
        /// The InfluxDB database access key
        std::string get_influx_db_auth_key(void) const;


        /// Buffer name to store incoming MQTT messages into
        static std::string get_mqtt_inbox_name(void);

        /// Buffer name to store outgoing MQTT messages into
        static std::string get_mqtt_outbox_name(void);

        /// Buffer to store incoming InfluxDB messages into
        static std::string get_influx_inbox_name(void);

        /// Buffer to store outgoing InfluxDB messages into
        static std::string get_influx_outbox_name(void);

    private:

		static constexpr const char* SELF_NAME = "CONFIG";

        nlohmann::json m_config_json;
    };
}