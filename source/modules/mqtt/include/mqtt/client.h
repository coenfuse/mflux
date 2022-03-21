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
	namespace mqtt
	{
		/// Provides a consistent interface for operations 
		/// such as connect(), publish(), on_message() etc
		/// using the mosquitto library that communicates 
		/// with an MQTT based broker. It also provides an 
		/// additional functionality of start_service() &
		/// stop_service() function that are tailor made 
		/// for mflux that handles the pushing and publishing
		/// of incoming and outgoing mqtt messages into and 
		/// from mqtt buffer.

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
			ERC publish(void);
			
			// TODO : Docs
			ERC subscribe(void);
			
			// TODO : Docs
			ERC unsubscribe(void);

			
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
			void i_actual_job(void);

		private:

			static constexpr const char* SELF_NAME = "MQTT  ";

			std::atomic_bool m_signalled_stop;
			std::thread m_worker;

			std::shared_ptr<Configurator> m_pConfig;
			std::shared_ptr<MemDB> m_pBuffer;
		};
	}
}