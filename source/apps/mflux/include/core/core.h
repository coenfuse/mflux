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
	// TODO : Docs

	class Core
	{
	public:

		Core();
		~Core();

		// TODO : Docs
		ERC start(std::shared_ptr<MemDB> p_buffer);
		
		// TODO : Docs
		ERC stop(void);

		// TODO : Docs
		bool is_running(void);

	private:

		// TODO : Docs
		static void s_job_wrapper(void* instance);
		
		// TODO : Docs
		void m_actual_job(void);

	private:

		static constexpr const char* SELF_NAME = "CORE";
		
		std::shared_ptr<felidae::MemDB> m_pBuffer = nullptr;
		
		std::atomic_bool m_signalled_stop = true;
		std::thread m_worker;
	};
}