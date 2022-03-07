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

        bool process_command_line(int argc, char* argv[]);
        bool init_logging(void);

        private:

        std::string m_config_file = "";
        bool m_is_logging_to_std = false;
        bool m_is_verbose = false;

        std::string m_name = app_NAME;
        std::string m_version = app_VERSION;
        std::string m_description = app_DESCRIPTION;

        std::unique_ptr<felidae::Engine> m_engine;
    };
}