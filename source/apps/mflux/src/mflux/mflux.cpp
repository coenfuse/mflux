// standard includes
#include <chrono>
#include <thread>
#include <vector>

// internal includes
#include "mflux/mflux.h"

// module includes
// ..

// third party includes
#include "CLI/CLI.hpp"
#include "fmt/format.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"



namespace felidae
{
    class Engine
    {
    public:
        Engine(std::string config_file){}
        ~Engine(){}

        ERC start(void) { return ERC::SUCCESS; }
        ERC stop(void) { return ERC::SUCCESS; }
        bool is_running(void) { return false; }
    };
}


namespace felidae
{
    Mflux::Mflux(void)
    {}


    Mflux::~Mflux(void)
    {}


    ERC Mflux::run(int argc, char* argv[])
    {
        ERC status = ERC::SUCCESS;

        if (status == ERC::SUCCESS)
            status = process_command_line(argc, argv);

        if (status == ERC::SUCCESS)
            status = init_logging();

        if (status == ERC::SUCCESS)
            spdlog::info("Starting {}", m_name);

        if (status == ERC::SUCCESS)
            m_engine = std::make_unique<felidae::Engine>(m_config_file);

        if (m_engine == nullptr)
            status = ERC::MEMORY_ALLOCATION_FAILED;

        if (status == ERC::SUCCESS)
            status = m_engine->start();

        if (status == ERC::SUCCESS)
        {
            while (m_engine->is_running())
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        if (status == ERC::SUCCESS)
            status = m_engine->stop();

        if (status == ERC::SUCCESS)
            spdlog::info("Stopping {}", m_name);

        return status;
    }


    ERC Mflux::process_command_line(int argc, char* argv[])
    {
        ERC status = ERC::SUCCESS;

        CLI::App parser;

        parser.add_option("--config", m_config_file, "JSON file containing mflux configurations")->required()->option_text("<filename>");
        parser.add_option("--logdir", m_logdir, "Path to store the generated runtime logs")->required()->option_text("<path>");
        parser.add_flag("--stdout", m_is_logging_to_std, "Whether to display the log on console");
        parser.add_flag("-v", m_is_verbose, "Increase verbosity of log 'if' being displayed");

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

        return status;
    }


    ERC Mflux::init_logging(void)
    {
        ERC status = ERC::SUCCESS;

        if (!std::filesystem::exists(m_logdir))
        {
            if (!std::filesystem::create_directories(m_logdir))
            {
                std::cerr << fmt::format("ERROR : Unable to create log dir '{}'", m_logdir);
                status = ERC::FAILURE;
            }
        }

        if (status == ERC::SUCCESS)
        {
            std::vector<spdlog::sink_ptr> sinks;

            // Add rotating file logging sink - Max file size of 10MB and max of 10 log files
            auto log_file = fmt::format("{}/{}.log", m_logdir, m_name);
            auto pFileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(log_file, 1048576 * 10, 10);
            sinks.push_back(pFileSink);

            // Add stdout sink if enabled
            if (m_is_logging_to_std)
            {
                auto pStdoutSink = std::make_shared<spdlog::sinks::stdout_sink_mt>();
                sinks.push_back(pStdoutSink);
            }

            // Create a logger with the sinks
            auto pLogger = std::make_shared<spdlog::logger>("mflux", sinks.begin(), sinks.end());

            // Register and set as default
            spdlog::register_logger(pLogger);
            spdlog::set_default_logger(pLogger);

            // Set the default log level to info
            if (m_is_logging_to_std && m_is_verbose)
                spdlog::set_level(spdlog::level::debug);
            else
                spdlog::set_level(spdlog::level::info);


            // Set pattern and flushing
            spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e UTC] [%L] %v", spdlog::pattern_time_type::utc);
            spdlog::flush_on(spdlog::level::trace);
        }

        return status;
    }
}
