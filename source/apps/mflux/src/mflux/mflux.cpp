// standard includes
// ..

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
        Engine(){}
        ~Engine(){}
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
        fmt::print("Mflux running");
        return ERC::SUCCESS;
    }


    bool Mflux::process_command_line(int argc, char* argv[])
    {
        return true;
    }


    bool Mflux::init_logging(void)
    {
        return true;
    }
}