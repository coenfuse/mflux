// preprocessor flags
#pragma once

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
	class Engine
	{
	public:

		Engine();
		~Engine();

		ERC start(void);
		ERC stop(void);

		bool is_running(void);

	private:

		std::unique_ptr<Core> m_core = nullptr;
	};
}