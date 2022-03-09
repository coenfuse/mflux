// preprocessor flags
#pragma once

// standard includes
#include <memory>

// internal includes
// ..

// module includes
#include  "configurator/configurator.h"
#include "errorcodes/errorcodes.h"

// third party includes
// ..

// forward references
// ..


namespace felidae
{
	class Core
	{
	public:

		Core();
		~Core();

		ERC start(void);
		ERC stop(void);

		bool is_running(void);

	private:

		void m_job(void);

	private:

		bool m_is_running = false;
	};
}