// preprocessor flags
#pragma once

// standard includes
#include <string>
#include <memory>

// internal includes
#include "app-config.h"
#include "engine/engine.h"

// module includes
#include "configurator/configurator.h"
#include "errorcodes/errorcodes.h"

// thirdparty includes
// ..

// forward references
// ..



namespace felidae
{
    class Mflux
    {
    public:

        Mflux(void);
        ~Mflux(void);
        ERC start(int argc, char* argv[]);
        void stop(void);
        
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

        bool m_signalled_stop = false;
    };
}