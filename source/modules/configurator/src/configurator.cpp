// standard includes
#include <chrono>
#include <fstream>
#include <thread>
#include <vector>

// internal includes
#include "configurator/configurator.h"

// module includes
#include "errorcodes/errorcodes.h"

// third party includes
#include "spdlog/spdlog.h"



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
        // TODO : Improve this, add logging.

        std::string json_raw;
        std::ifstream ifs(file_path);

        if (ifs.is_open())
        {
            std::string line;
            while (ifs.good())
            {
                std::getline(ifs, line);
                if (line.find("//") == std::string::npos)    // Ignore comments
                    json_raw.append(line);
            }
        }

        try
        {
            m_config_json = nlohmann::json::parse(json_raw);
        }
        catch (std::exception& e)
        {
            spdlog::error("Exception {}", e.what());
        }
    }

    Configurator::~Configurator()
    {}

    // General global level configurations
    std::string Configurator::get_logdir(void)
    {
        return m_config_json["log_dir"];
    }

    uint16_t Configurator::get_log_level(void)
    {
        auto log_lvl = m_config_json["log_level"];
        
        if ((log_lvl >= 0) && (log_lvl < 6))
            return log_lvl;
        else
            return 1;   // Default level is 1 (DEBUG)
    }
        
    // Watchdog configurations
    bool Configurator::is_watchdog_on(void)
    {
        return m_config_json["watchdog_on"];
    }

    uint16_t Configurator::get_watchdog_log_level(void)
    {
        return m_config_json["watchdog_log_level"];
    }
    
    uint16_t Configurator::get_watchdog_timeout_s(void)
    {
        return m_config_json["watchdog_timeout_s"];
    }
    
    std::string Configurator::get_watchdog_command(void)
    {
        return m_config_json["watchdog_command"];
    }
    

    // MQTT configurations
    bool Configurator::is_mqtt_on(void)
    {
        return m_config_json["mqtt_on"];
    }
    
    uint16_t Configurator::get_mqtt_log_level(void)
    {
        return m_config_json["mqtt_log_level"];
    }
    
    std::string Configurator::get_mqtt_client_name(void)
    {
        return m_config_json["mqtt_client_name"];
    }
    
    bool Configurator::is_mqtt_clean(void)
    {
        return m_config_json["mqtt_is_clean"];
    }
    
    std::string Configurator::get_mqtt_host(void)
    {
        return m_config_json["mqtt_host"];
    }
    
    uint16_t Configurator::get_mqtt_port(void)
    {
        return m_config_json["mqtt_port"];
    }
    
    uint16_t Configurator::get_mqtt_timeout_s(void)
    {
        return m_config_json["mqtt_timeout_s"];
    }
    
    std::string Configurator::get_mqtt_username(void)
    {
        return m_config_json["mqtt_username"];
    }
    
    std::string Configurator::get_mqtt_password(void)
    {
        return m_config_json["mqtt_password"];
    }
    
    std::vector<mqtt::Subscription> Configurator::get_mqtt_sub_list(void)
    {
        std::vector<mqtt::Subscription> sub_list;

        // TODO : Will be implemented once MQTT module is developed

        return sub_list;
    }
    

    // Influx configurations
    bool Configurator::is_influx_on(void)
    {
        return m_config_json["influx_on"];
    }
    
    uint16_t Configurator::get_influx_log_level(void)
    {
        return m_config_json["influx_log_level"];
    }
    
    std::string Configurator::get_influx_client_name(void)
    {
        return m_config_json["influx_client_name"];
    }
    
    std::string Configurator::get_influx_host(void)
    {
        return m_config_json["influx_host"];
    }
    
    uint16_t Configurator::get_influx_port(void)
    {
        return m_config_json["influx_port"];
    }
    
    uint16_t Configurator::get_influx_timeout_s(void)
    {
        return m_config_json["influx_timeout_s"];
    }
    
    std::string Configurator::get_influx_org_name(void)
    {
        return m_config_json["influx_org_name"];
    }
    
    std::string Configurator::get_influx_db_name(void)
    {
        return m_config_json["influx_db_name"];
    }
    
    std::string Configurator::get_influx_db_username(void)
    {
        return m_config_json["influx_db_username"];
    }
    
    std::string Configurator::get_influx_db_password(void)
    {
        return m_config_json["influx_db_password"];
    }
    
    std::string Configurator::get_influx_db_auth_key(void)
    {
        return m_config_json["influx_db_auth_key"];
    }
    

    // Buffer configurations
    std::string Configurator::get_mqtt_inbox_name(void)
    {
        return "mqttc_inbox";
    }
    
    std::string Configurator::get_mqtt_outbox_name(void)
    {
        return "mqttc_outbox";
    }
    
    std::string Configurator::get_influx_inbox_name(void)
    {
        return "influxc_inbox";
    }
    
    std::string Configurator::get_influx_outbox_name(void)
    {
        return "influxc_outbox";
    }
}