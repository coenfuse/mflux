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
		m_pInfluxc = std::make_unique<influx::Client>();
		m_pMqttc = std::make_unique<mqtt::Client>();
		m_pCore = std::make_unique<Core>();

		m_pDb = std::make_shared<MemDB>();
	}

	Engine::~Engine(void)
	{}


	ERC Engine::start(std::shared_ptr<Configurator> p_config)
	{
		auto status = ERC::SUCCESS;

		if (!this->is_running())
		{
			m_pConfig = p_config;

			if ((m_pConfig == nullptr) || (m_pCore == nullptr) || (m_pDb == nullptr) || (m_pInfluxc == nullptr) || (m_pMqttc == nullptr))
				status = ERC::MEMORY_ALLOCATION_FAILED;

			if (status == ERC::SUCCESS)
				status = m_pMqttc->start_service();

			if (status == ERC::SUCCESS)
				status = m_pInfluxc->start_service();

			if (status == ERC::SUCCESS)
				status = m_pCore->start(m_pDb);
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
				status = m_pInfluxc->stop_service();

			if (status == ERC::SUCCESS)
				status = m_pMqttc->start_service();
		}

		return status;
	}

	bool Engine::is_running(void)
	{
		return m_pCore->is_running();
	}
}