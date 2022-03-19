// standard includes
#include <memory>
#include <thread>


// internal includes
#include "core/core.h"


// module includes
#include  "configurator/configurator.h"
#include "errorcodes/errorcodes.h"
#include "minix/minix.h"


// third party includes
#include "spdlog/spdlog.h"



namespace felidae
{
	Core::Core()
	{}

	Core::~Core()
	{}


	ERC Core::start(std::shared_ptr<MemDB> p_buffer)
	{
		auto status = ERC::SUCCESS;
		
		if (!this->is_running())
		{
			spdlog::debug("{} starting", SELF_NAME);

			m_pBuffer = p_buffer;

			if (m_pBuffer == nullptr)
				status = ERC::NULLPTR_RECV;

			if (status == ERC::SUCCESS)
				m_worker = std::thread(s_job_wrapper, this);

			if (this->is_running())
				spdlog::info("{} started", SELF_NAME);
			else
				spdlog::error("{} failed to start with code {}", SELF_NAME, status);
		}

		return status;
	}


	ERC Core::stop(void)
	{
		auto status = ERC::SUCCESS;
		
		if (this->is_running())
		{
			spdlog::debug("{} stopping", SELF_NAME);

			m_signalled_stop.exchange(true);
			m_worker.join();

			spdlog::info("{} stopped", SELF_NAME);
		}

		return status;
	}


	bool Core::is_running(void)
	{
		return m_worker.joinable();
	}


	void Core::m_actual_job()
	{
		auto status = ERC::SUCCESS;

		auto inbox_name = Configurator::get_mqtt_inbox_name();
		auto outbox_name = Configurator::get_influx_outbox_name();

		DBitem dbitem;
		mqtt::Message mqtt_msg;
		influx::Message influx_msg;

		m_signalled_stop.exchange(false);

		while(!m_signalled_stop)
		{
			// wait for a message
			if (!m_pBuffer->is_empty(inbox_name))
			{
				// Pull the DBitem from the inbox buffer
				status = m_pBuffer->pop(inbox_name, dbitem);

				// Get the message from the DBitem
				if(status == ERC::SUCCESS)
					status = dbitem.get<mqtt::Message>(mqtt_msg);

				// Convert the message to an influx message
				if (status == ERC::SUCCESS)
					status = minix::get_influx_msg_from(mqtt_msg, influx_msg);

				// Overwrite the DBitem with the influx message
				if (status == ERC::SUCCESS)
					status = dbitem.set<influx::Message>(influx_msg);

				// Push the DBitem to the outbox buffer
				if (status == ERC::SUCCESS)
					status = m_pBuffer->push(outbox_name, dbitem);

				// if (status != ERC::SUCCESS)
				//	 m_pDb->push(inbox_name, dbitem);
			}
		}
	}

	void Core::s_job_wrapper(void* instance)
	{
		Core* self_instance = (Core*)instance;
		self_instance->m_actual_job();					// This thread blocks here
	}
}