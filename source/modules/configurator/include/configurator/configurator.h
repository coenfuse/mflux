// // preprocessor flags
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
    class Configurator
    {
    public:

        Configurator(std::string file_path);
        ~Configurator();


        // Path to save the log file into
        std::string get_logdir(void);

        // Log level to save the log file with
        uint16_t get_log_level(void);
        
        // Whether to use watchdog or not
        bool is_watchdog_on(void);

        // The logging level for watchdog
        uint16_t get_watchdog_log_level(void);

        // The interval in seconds to check the watchdog
        uint16_t get_watchdog_timeout_s(void);

        // The command to execute once watchdog is timed out
        std::string get_watchdog_command(void);


        // Whether to use MQTT or not
        bool is_mqtt_on(void);

        // The MQTT logging level
        uint16_t get_mqtt_log_level(void);

        // The MQTT client name
        std::string get_mqtt_client_name(void);
        
        // Whether to set a clean MQTT connection or not
        bool is_mqtt_clean(void);

        // The MQTT server IP
        std::string get_mqtt_host(void);
        
        // The MQTT server port
        uint16_t get_mqtt_port(void);
        
        // The MQTT connection keepalive interval in seconds
        uint16_t get_mqtt_timeout_s(void);
        
        // The MQTT username
        std::string get_mqtt_username(void);
        
        // The MQTT password
        std::string get_mqtt_password(void);
        
        // The MQTT topic(s) to subscribe to
        std::vector<mqtt::Subscription> get_mqtt_sub_list(void);

        
        // Whether to use InfluxDB or not
        bool is_influx_on(void);
        
        // The InfluxDB logging level
        uint16_t get_influx_log_level(void);
        
        // The InfluxDB client name
        std::string get_influx_client_name(void);
        
        // The InfluxDB server IP
        std::string get_influx_host(void);
        
        // The InfluxDB server port
        uint16_t get_influx_port(void);
        
        // The InfluxDB connection keepalive interval in seconds
        uint16_t get_influx_timeout_s(void);

        // The InfluxDB database organization name
        std::string get_influx_org_name(void);

        // The InfluxDB database name
        std::string get_influx_db_name(void);
        
        // The InfluxDB username
        std::string get_influx_db_username(void);
        
        // The InfluxDB password
        std::string get_influx_db_password(void);
        
        // The InfluxDB database access key
        std::string get_influx_db_auth_key(void);


        // Buffer name to store incoming MQTT messages into
        static std::string get_mqtt_inbox_name(void);

        // Buffer name to store outgoing MQTT messages into
        static std::string get_mqtt_outbox_name(void);

        // Buffer to store incoming InfluxDB messages into
        static std::string get_influx_inbox_name(void);

        // Buffer to store outgoing InfluxDB messages into
        static std::string get_influx_outbox_name(void);

    private:

		static constexpr const char* SELF_NAME = "CONFIG";

        nlohmann::json m_config_json;
    };
}