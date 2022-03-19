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
	/// Actual logic of the mflux application. Core contains
	/// two functions, core::start() and core::stop(). It has
	/// sole responsibility of pulling in messages that are 
	/// awaiting translation from the memdb buffer. Converting
	/// them into target message using minux module and pushing
	/// them back into memdb outbox buffer where they await 
	/// transmission by an appropriate client.

	class Core
	{
	public:

		Core();
		~Core();

		/// Start the core thread. Requires MemDB type buffer ptr
		/// to pull and push processed data.
		ERC start(std::shared_ptr<MemDB> p_buffer);
		
		/// Stop the core thread if running
		ERC stop(void);

		/// Check the running status of core thread
		bool is_running(void);

	private:

		/// Static wrapper on actual job. This wrapper will be
		/// called into a thread and will be blocked till the
		/// life-cycle of actual job function
		static void s_job_wrapper(void* instance);
		
		/// The actual function that does job of this core class.
		/// It will run in an infinite loop until signalled to
		/// stop by the calling Core::stop(void)
		void m_actual_job(void);

	private:

		static constexpr const char* SELF_NAME = "CORE  ";
		
		std::shared_ptr<felidae::MemDB> m_pBuffer = nullptr;
		
		std::atomic_bool m_signalled_stop = true;
		std::thread m_worker;
	};
}