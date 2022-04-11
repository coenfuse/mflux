// standard includes
#include <csignal>
#include <iostream>


// internal includes
#include "mflux/mflux.h"


// module includes
#include "errorcodes/errorcodes.h"


// third party includes
#include "fmt/format.h"
#include "spdlog/spdlog.h"



// --------------------------------------------------------

static std::unique_ptr<felidae::Mflux> p_mflux;


// A simple wrapper to register all the signal handlers for
// this program. Using lambda functions, their definition
// is also mentioned here, given that they are within under
// 10 lines of code.

void setupSignalHandlers()
{
	// Abort termination triggered by abort call
	signal(SIGABRT, [](int signal)
		{
			spdlog::debug("SIGABRT received");
			p_mflux->stop();
		}
	);


	// Floating point exception
	signal(SIGFPE, [](int signal) {});
	

	// Interrupt
	signal(SIGINT, [](int signal)
		{
			spdlog::debug("SIGINT received");
			p_mflux->stop();
		}
	);


	// Illegal Instruction - Invalid function image
	signal(SIGILL, [](int signal) {});


	// Segment violation - Writing to illegal memory location
	signal(SIGSEGV, [](int signal) {});


	// Software termination signal from kill
	signal(SIGTERM, [](int signal) 
		{
			spdlog::debug("SIGTERM received");
			p_mflux->stop();
		}
	);


	// Ctrl-Break sequence
	// signal(SIGBREAK, [](int signal) {});
}


// TODO - Args class and parser
// TODO - Logging setup


// The entry point of the program

int main(int argc, char* argv[])
{
    auto status = felidae::ERC::SUCCESS;
    
    p_mflux = std::make_unique<felidae::Mflux>();

	if (p_mflux == nullptr)
		status = felidae::ERC::MEMORY_ALLOCATION_FAILED;
    
	if (status == felidae::ERC::SUCCESS)
	{
		try
		{
			setupSignalHandlers();
			status = p_mflux->start(argc, argv);
		}
		catch (std::exception &e)
		{
			spdlog::error("Exception {}", e.what());
			status = felidae::ERC::EXCEPTION;
		}
	}

	return static_cast<uint16_t>(status);
}