// standard includes
#include <chrono>
#include <thread>

// internal includes
#include "mflux/mflux.h"

// module includes
// ..

// third party includes
#include "fmt/format.h"



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

        // ..

        return status;
    }


    ERC Mflux::init_logging(void)
    {
        ERC status = ERC::SUCCESS;

        // ..

        return status;
    }
}
