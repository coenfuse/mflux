// // preprocessor flags
#pragma once

// standard includes
#include <string>
#include <memory>

// other includes
#include "app-config.h"
#include "errorcodes/errorcodes.h"

// forward references
namespace felidae
{
    class Configurator;
    class Engine;
}



namespace felidae
{
    class Mflux
    {
    public:

        Mflux(void);
        ~Mflux(void);
        ERC run(int argc, char* argv[]);

        
    private:

        ERC process_command_line(int argc, char* argv[]);
        ERC init_logging(void);


    private:

        bool m_is_logging_to_std = false;
        bool m_is_verbose = false;

        std::string m_name = app_NAME;
        std::string m_version = app_VERSION;
        std::string m_description = app_DESCRIPTION;

        std::shared_ptr<felidae::Configurator> m_config = nullptr;
        std::unique_ptr<felidae::Engine> m_engine = nullptr;
    };
}