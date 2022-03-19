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
    /// The main Mflux application class. Internally, it
    /// doesn't do much itself. It uses Engine and Core
    /// classes to do the actual operation by defined usage
    /// of modules and other units. Logically, Mflux class
    /// serves as a shell for its internal components. This
    /// shell exposes minimal interface to its users through
    /// which they can edit or configure its operations as
    /// required.

    class Mflux
    {
    public:

        Mflux(void);
        ~Mflux(void);

        /// Starts the Mflux application with incoming command
        /// line arguments
        ERC start(int argc, char* argv[]);

        /// Stop the Mflux application if running
        void stop(void);

    private:

        /// Process the cmd args and set the basic configuration
        ERC process_command_line(int argc, char* argv[]);

        /// Define logging parameters for Mflux that are then followed
        /// throughout the application
        ERC init_logging(void);

    private:

        static constexpr const char* SELF_NAME = "MFLUX ";

        bool m_is_logging_to_std = false;
        bool m_is_verbose = false;

        std::string m_name = app_NAME;
        std::string m_version = app_VERSION;

        std::shared_ptr<felidae::Configurator> m_config = nullptr;
        std::unique_ptr<felidae::Engine> m_engine = nullptr;

        bool m_signalled_stop = false;
    };
}