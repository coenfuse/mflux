// standard includes
#include <iostream>

// internal includes
#include "mflux/mflux.h"

// module includes
#include "errorcodes/errorcodes.h"

// third party includes
#include "fmt/format.h"



int main(int argc, char* argv[])
{
    felidae::ERC error_code = felidae::ERC::SUCCESS;
    
    std::unique_ptr<felidae::Mflux> p_Mflux = std::make_unique<felidae::Mflux>();
    try
    {
        error_code = p_Mflux->run(argc, argv);
    }
    catch (std::exception& e)
    {
        std::cerr << fmt::format("Exception in {}", e.what());
        error_code = felidae::ERC::EXCEPTION;
    }

    return static_cast<uint16_t>(error_code);
}