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
    // TODO : Docs

    class Mflux
    {
    public:

        Mflux(void);
        ~Mflux(void);
        
        // TODO : Docs
        ERC start(int argc, char* argv[]);
        
        // TODO : Docs
        void stop(void);
        
    private:

        // TODO : Docs
        ERC process_command_line(int argc, char* argv[]);
    
        // TODO : Docs
        ERC init_logging(void);

    private:

		static constexpr const char* SELF_NAME = "MFLUX";

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