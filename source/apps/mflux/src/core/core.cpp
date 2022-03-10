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
// ..



namespace felidae
{
	Core::Core()
	{}

	Core::~Core()
	{}


	ERC Core::start(std::shared_ptr<MemDB> p_db)
	{
		auto status = ERC::SUCCESS;
		
		if (!this->is_running())
		{
			m_pDb = p_db;

			if (m_pDb == nullptr)
				status = ERC::NULLPTR_RECV;

			if (status == ERC::SUCCESS)
				m_worker = std::thread(s_job_wrapper, this);

			if (this->is_running())
				status = ERC::SUCCESS;
		}

		return status;
	}


	ERC Core::stop(void)
	{
		auto status = ERC::SUCCESS;
		
		if (this->is_running())
		{
			m_signalled_stop.exchange(true);
			m_worker.join();
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
			if (!m_pDb->is_empty(inbox_name))
			{
				status = m_pDb->pop(inbox_name, dbitem);

				if(status == ERC::SUCCESS)
					status = dbitem.get<mqtt::Message>(mqtt_msg);

				if (status == ERC::SUCCESS)
					status = minix::get_influx_msg_from(mqtt_msg, influx_msg);

				if (status == ERC::SUCCESS)
					status = dbitem.set<influx::Message>(influx_msg);

				if (status == ERC::SUCCESS)
					status = m_pDb->push(outbox_name, dbitem);

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