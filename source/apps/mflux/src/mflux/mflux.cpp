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
            fmt::print("Starting {}", m_name);

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
            fmt::print("\nStopping {}", m_name);

        return status;
    }


    ERC Mflux::process_command_line(int argc, char* argv[])
    {
        ERC status = ERC::SUCCESS;

        CLI::App parser;

        parser.add_option("--config", m_config_file, "JSON file containing mflux configurations")->required()->option_text("<filename>");
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

        // Parse config file and get log directory. Assume currently logdir 
        std::string log_dir = "./logs";

        if (!std::filesystem::exists(log_dir))
        {
            if (!std::filesystem::create_directories(log_dir))
            {
                std::cerr << fmt::format("ERROR : Unable to create log dir '{}'", log_dir);
                status = ERC::FAILURE;
            }
        }

        if (status == ERC::SUCCESS)
        {
            // Setup sinks for logger
            std::vector<spdlog::sink_ptr> sinks;
        }

        return status;
    }
}
