// standard includes
#include <memory>

// internal includes
#include "engine/engine.h"

// module includes
#include "influx/client.h"
#include "memdb/memdb.h"
#include "mqtt/client.h"

// third party includes
// ..



namespace felidae
{
	Engine::Engine()
	{
		m_core = std::make_unique<Core>();
	}

	Engine::~Engine()
	{}


	ERC Engine::start(void)
	{
		auto status = ERC::SUCCESS;
		// ..
		return status;
	}

	ERC Engine::stop(void)
	{
		auto status = ERC::SUCCESS;
		// ..
		return status;
	}

	bool Engine::is_running(void)
	{
		return m_core->is_running();
	}
}