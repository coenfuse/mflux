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
	Engine::Engine(void)
	{
		m_pInflux_sc = std::make_unique<influx::Client>();
		m_pMqtt_sc = std::make_unique<mqtt::Client>();
		m_pCore = std::make_unique<Core>();

		m_pBuffer = std::make_shared<MemDB>();
	}

	Engine::~Engine(void)
	{}


	ERC Engine::start(std::shared_ptr<Configurator> p_config)
	{
		auto status = ERC::SUCCESS;

		if (!this->is_running())
		{
			if ((p_config == nullptr) || (m_pCore == nullptr) || (m_pBuffer == nullptr) || (m_pInflux_sc == nullptr) || (m_pMqtt_sc == nullptr))
				status = ERC::MEMORY_ALLOCATION_FAILED;

			if (status == ERC::SUCCESS)
				status = m_pMqtt_sc->start_service(p_config);

			if (status == ERC::SUCCESS)
				status = m_pInflux_sc->start_service(p_config);

			if (status == ERC::SUCCESS)
				status = m_pCore->start(m_pBuffer);
		}

		return status;
	}

	ERC Engine::stop(void)
	{
		auto status = ERC::SUCCESS;
		
		if (this->is_running())
		{
			status = m_pCore->stop();

			if (status == ERC::SUCCESS)
				status = m_pInflux_sc->stop_service();

			if (status == ERC::SUCCESS)
				status = m_pMqtt_sc->stop_service();
		}

		return status;
	}

	bool Engine::is_running(void)
	{
		// The engine is marked as running if any of its
		// inner module is found to be running
		return ( m_pInflux_sc->is_running() || m_pMqtt_sc->is_running() || m_pCore->is_running() );
	}
}