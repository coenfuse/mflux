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
		/// Provides a consistent interface for operations such 
		/// as connect(), publish(), get() etc using the influxdb-cxx
		/// library that communicates with InfluxDB (this will be
		/// later replaced with cinflux library). This client 
		/// also provides an additional functionality of 
		/// start_service() and stop_service() functions that are
		/// tailor made for mflux handling the pushing and 
		/// publishing of incoming and outgoing influx messages 
		/// into and from mflux buffer.

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
			
			static constexpr const char* SELF_NAME = "INFLUX";

			std::atomic_bool m_signalled_stop = true;
			std::thread m_worker;

			std::shared_ptr<Configurator> m_pConfig;
			std::shared_ptr<MemDB> m_pBuffer;
		};
	}
}