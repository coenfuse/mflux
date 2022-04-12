// standard includes
#include <chrono>
#include <thread>
#include <vector>


// internal includes
#include "mflux/mflux.h"


// module includes
#include "configurator/configurator.h"


// third party includes
#include "CLI/CLI.hpp"
#include "fmt/format.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"



namespace felidae
{
    Mflux::Mflux(void)
    {}


    Mflux::~Mflux(void)
    {}


    ERC Mflux::start(int argc, char* argv[])
    {
        ERC status = ERC::SUCCESS;

        if (status == ERC::SUCCESS)
            status = process_command_line(argc, argv);

        if (status == ERC::SUCCESS)
            status = init_logging();

        if (status == ERC::SUCCESS)
            spdlog::debug("{} starting", SELF_NAME);

        if (status == ERC::SUCCESS)
            m_engine = std::make_unique<felidae::Engine>();

        if (m_engine == nullptr)
            status = ERC::MEMORY_ALLOCATION_FAILED;

        if (status == ERC::SUCCESS)
            status = m_engine->start(m_config);

        if (status == ERC::SUCCESS)
        {
            spdlog::info("{} running", SELF_NAME);
            
            while (m_engine->is_running() && !m_signalled_stop)
                std::this_thread::sleep_for(std::chrono::milliseconds(100));

            spdlog::debug("{} stopping", SELF_NAME);
        }
        
        if (m_engine != nullptr)
            status = m_engine->stop();

        if (status == ERC::SUCCESS)
            spdlog::info("{} stopped", SELF_NAME);

        return status;
    }


    void Mflux::stop(void)
    {
        this->m_signalled_stop = true;
    }


    ERC Mflux::process_command_line(int argc, char* argv[])
    {
        ERC status = ERC::SUCCESS;

        CLI::App parser;
        std::string config_file;

        parser.add_option("--config", config_file, "JSON file containing mflux configurations")->required()->option_text("<filename>");
        parser.add_flag("--stdout", m_is_logging_to_std, "Whether to display the log on console");
        parser.add_flag("-v", m_is_verbose, "Increase verbosity of console log, if enabled");

        try
        {
            parser.parse(argc, argv);
        }
        catch (const CLI::ParseError& e)
        {
            status = ERC::EXCEPTION;

            fmt::print("ERROR: {}\n\n", e.what());
            fmt::print("{} v{} (c) 2022-2023 Felidae Systems Inc.\n\n", m_name, m_version);
            fmt::print(parser.help());
        }

        if(!config_file.empty())
            m_config = std::make_shared<felidae::Configurator>(config_file);

        if (m_config == nullptr)
            status = ERC::MEMORY_ALLOCATION_FAILED;

        return status;
    }


    ERC Mflux::init_logging(void)
    {
        ERC status = ERC::SUCCESS;

        auto logdir = m_config->get_logdir();

        if (!std::filesystem::exists(logdir))
        {
            if (!std::filesystem::create_directories(logdir))
            {
                spdlog::error("{} unable to create log dir {}", SELF_NAME, logdir);
                status = ERC::FAILURE;
            }
        }

        if (status == ERC::SUCCESS)
        {
            std::vector<spdlog::sink_ptr> sinks;

            // Setting console sink if enabled
            if (m_is_logging_to_std)
            {
                auto p_console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
                
                // Setting console log level
                if (m_is_verbose) 
                    p_console_sink->set_level(spdlog::level::debug);
                else 
                    p_console_sink->set_level(spdlog::level::info);

                // Adding console sink to sinks list
                sinks.push_back(p_console_sink);
            }

            // Setting file logger
            {
                auto log_file = fmt::format("{}/{}.log", logdir, m_name);

                // Add rotating file logging sink - Max file size of 10MB and max of 10 log files
                auto p_file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(log_file, 1048576 * 10, 10);

                // Setting file log level, typecasting uint16_t to spdlog_level_enum
                p_file_sink->set_level((spdlog::level::level_enum)m_config->get_log_level());
                
                // Adding file sink to sinks list
                sinks.push_back(p_file_sink);
            }

            // Creating a logger with the sinks
            auto p_logger = std::make_shared<spdlog::logger>("mflux_logger", sinks.begin(), sinks.end());

            spdlog::register_logger(p_logger);
            spdlog::set_default_logger(p_logger);

            spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e UTC] %^[%L]%$ %v", spdlog::pattern_time_type::utc);
            spdlog::flush_every(std::chrono::seconds(1));
            
            // Global log level ceiling for all sinks
            spdlog::set_level(spdlog::level::trace);
        }

        return status;
    }
}
