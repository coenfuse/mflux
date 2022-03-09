// standard includes
#include <memory>

// internal includes
#include "core/core.h"

// module includes
#include  "configurator/configurator.h"
#include "errorcodes/errorcodes.h"

// third party includes
// ..



namespace felidae
{
	Core::Core()
	{}

	Core::~Core()
	{}


	ERC Core::start(void)
	{
		auto status = ERC::SUCCESS;
		// ..
		return status;
	}

	ERC Core::stop(void)
	{
		auto status = ERC::SUCCESS;
		// ..
		return status;
	}

	bool Core::is_running(void)
	{
		return m_is_running;
	}

	void Core::m_job(void)
	{}
}