// preprocessor flags
#pragma once


// standard includes
#include <atomic>
#include <memory>
#include <thread>


// internal includes
// ..


// module includes
#include  "configurator/configurator.h"
#include "errorcodes/errorcodes.h"
#include "memdb/memdb.h"


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

		ERC start(std::shared_ptr<MemDB> p_db);
		ERC stop(void);

		bool is_running(void);

	private:

		static void s_job_wrapper(void* instance);
		void m_actual_job(void);

	private:

		std::shared_ptr<felidae::MemDB> m_pDb = nullptr;
		
		std::atomic<bool> m_running = false;
		std::thread m_worker;
	};
}