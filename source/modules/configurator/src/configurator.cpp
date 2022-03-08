// standard includes
#include <chrono>
#include <thread>
#include <vector>

// internal includes
#include "configurator/configurator.h"

// module includes
#include "errorcodes/errorcodes.h"
// mqtt message

// third party includes
#include "spdlog/spdlog.h"
#include "json/json.hpp"



namespace felidae
{
    namespace MQTT
    {
        class Message 
        {
        public:
            Message(void){}
            ~Message(void){}
        };
    }
}



namespace felidae
{
    Configurator::Configurator(std::string file_path)
    {
        spdlog::trace("Configurator working in trace");
        spdlog::debug("Configurator working in debug");
        spdlog::info("Configurator working in info");
    }

    Configurator::~Configurator()
    {}

    // General global level configurations
    std::string Configurator::get_logdir(void)
    {
        return "";
    }

    uint16_t Configurator::get_log_level(void)
    {
        return 0;
    }
        
    // Watchdog configurations
    bool Configurator::is_watchdog_on(void)
    {
        return true;
    }

    uint16_t Configurator::get_watchdog_log_level(void)
    {
        return 0;
    }
    
    uint16_t Configurator::get_watchdog_timeout_s(void)
    {
        return 0;
    }
    
    std::string Configurator::get_watchdog_command(void)
    {
        return "";
    }
    

    // MQTT configurations
    bool Configurator::is_mqtt_on(void)
    {
        return true;
    }
    
    uint16_t Configurator::get_mqtt_log_level(void)
    {
        return 0;
    }
    
    std::string Configurator::get_mqtt_client_name(void)
    {
        return "";
    }
    
    bool Configurator::is_mqtt_clean(void)
    {
        return true;
    }
    
    std::string Configurator::get_mqtt_host(void)
    {
        return "";
    }
    
    uint16_t Configurator::get_mqtt_port(void)
    {
        return 0;
    }
    
    uint16_t Configurator::get_mqtt_timeout_s(void)
    {
        return 0;
    }
    
    std::string Configurator::get_mqtt_username(void)
    {
        return "";
    }
    
    std::string Configurator::get_mqtt_password(void)
    {
        return "";
    }
    
    std::vector<MQTT::Message> Configurator::get_mqtt_sub_list(void)
    {
        std::vector<MQTT::Message> sub_list;
        return sub_list;
    }
    

    // Influx configurations
    bool Configurator::is_influx_on(void)
    {
        return true;
    }
    
    uint16_t Configurator::get_influx_log_level(void)
    {
        return 0;
    }
    
    std::string Configurator::get_influx_client_name(void)
    {
        return "";
    }
    
    std::string Configurator::get_influx_host(void)
    {
        return "";
    }
    
    uint16_t Configurator::get_influx_port(void)
    {
        return 0;
    }
    
    uint16_t Configurator::get_influx_timeout_s(void)
    {
        return 0;
    }
    
    std::string Configurator::get_influx_org_name(void)
    {
        return "";
    }
    
    std::string Configurator::get_influx_db_name(void)
    {
        return "";
    }
    
    std::string Configurator::get_influx_db_username(void)
    {
        return "";
    }
    
    std::string Configurator::get_influx_db_password(void)
    {
        return "";
    }
    
    std::string Configurator::get_influx_db_auth_key(void)
    {
        return "";
    }
    

    // Buffer configurations
    std::string Configurator::get_mqtt_inbox_name(void)
    {
        return "";
    }
    
    std::string Configurator::get_mqtt_outbox_name(void)
    {
        return "";
    }
    
    std::string Configurator::get_influx_inbox_name(void)
    {
        return "";
    }
    
    std::string Configurator::get_influx_outbox_name(void)
    {
        return "";
    }
}