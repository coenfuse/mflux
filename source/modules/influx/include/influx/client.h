// preprocessor flags
#pragma once

// standard includes
#include <atomic>
#include <memory>
#include <thread>

// internal includes
// ..

// module includes
#include "configurator/configurator.h"
#include "errorcodes/errorcodes.h"
#include "memdb/memdb.h"

// thirdparty includes
// ..

// forward references
// ..



namespace felidae
{
	namespace influx
	{
		// TODO : Docs

		class Client
		{
		public:
			
			Client(void);
			~Client(void);

			// TODO : Docs
			ERC connect(void);
			
			// TODO : Docs
			ERC disconnect(void);
			
			// TODO : Docs
			bool is_connected(void);

			
			// TODO : Docs
			ERC get(void);
			
			// TODO : Docs
			ERC push(void);
			
			// TODO : Docs
			ERC pop(void);
			
			// TODO : Docs
			ERC remove(void);

			
			// TODO : Docs
			ERC start_service(std::shared_ptr<Configurator> p_config, std::shared_ptr<MemDB> p_buffer);
			
			// TODO : Docs
			ERC stop_service(void);
			
			// TODO : Docs
			bool is_running(void);

		private:
			
			// TODO : Docs
			static void s_service_wrapper(void* instance);
			
			// TODO : Docs
			void m_actual_job(void);

		private:

			std::atomic_bool m_signalled_stop = true;
			std::thread m_worker;

			std::shared_ptr<Configurator> m_pConfig;
			std::shared_ptr<MemDB> m_pBuffer;
		};
	}
}