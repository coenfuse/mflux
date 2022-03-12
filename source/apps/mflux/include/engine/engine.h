// preprocessor flags
#pragma once


// standard includes
#include <memory>


// internal includes
#include "core/core.h"


// module includes
#include  "configurator/configurator.h"
#include "errorcodes/errorcodes.h"
#include "influx/client.h"
#include "memdb/memdb.h"
#include "mqtt/client.h"


// third party includes
// ..


// forward references
// ..



namespace felidae
{
	// TODO : Docs

	class Engine
	{
	public:

		Engine();
		~Engine();

		// TODO : Docs
		ERC start(std::shared_ptr<Configurator> p_config);
		
		// TODO : Docs
		ERC stop(void);

		// TODO : Docs
		bool is_running(void);

	private:

		// The following object pointers will not be updated and shared further
		std::unique_ptr<Core> m_pCore = nullptr;
		std::unique_ptr<mqtt::Client> m_pMqtt_sc = nullptr;
		std::unique_ptr<influx::Client> m_pInflux_sc = nullptr;

		// These object pointers will be updated and shared further
		std::shared_ptr<MemDB> m_pBuffer = nullptr;
	};
}