// // preprocessor flags
#pragma once

// standard includes
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

// other includes
#include "errorcodes/errorcodes.h"
#include "json/json.hpp"

// forward references
namespace felidae
{
    namespace MQTT
    {
        class Message;
    }
}



namespace felidae
{
    class Configurator
    {
    public:

        Configurator(std::string file_path);
        ~Configurator();

        // General global level configurations
        std::string get_logdir(void);
        uint16_t get_log_level(void);
        
        // Watchdog configurations
        bool is_watchdog_on(void);
        uint16_t get_watchdog_log_level(void);
        uint16_t get_watchdog_timeout_s(void);
        std::string get_watchdog_command(void);

        // MQTT configurations
        bool is_mqtt_on(void);
        uint16_t get_mqtt_log_level(void);
        std::string get_mqtt_client_name(void);
        bool is_mqtt_clean(void);
        std::string get_mqtt_host(void);
        uint16_t get_mqtt_port(void);
        uint16_t get_mqtt_timeout_s(void);
        std::string get_mqtt_username(void);
        std::string get_mqtt_password(void);
        std::vector<MQTT::Message> get_mqtt_sub_list(void);

        // Influx configurations
        bool is_influx_on(void);
        uint16_t get_influx_log_level(void);
        std::string get_influx_client_name(void);
        std::string get_influx_host(void);
        uint16_t get_influx_port(void);
        uint16_t get_influx_timeout_s(void);
        std::string get_influx_org_name(void);
        std::string get_influx_db_name(void);
        std::string get_influx_db_username(void);
        std::string get_influx_db_password(void);
        std::string get_influx_db_auth_key(void);

        // Buffer configurations
        std::string get_mqtt_inbox_name(void);
        std::string get_mqtt_outbox_name(void);
        std::string get_influx_inbox_name(void);
        std::string get_influx_outbox_name(void);

    private:

        nlohmann::json m_config_json;
    };
}