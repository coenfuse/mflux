// preprocessor flags
#pragma once


// standard includes
#include <atomic>
#include <map>
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
struct mosquitto;
struct mosquitto_message;



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
			ERC connect(
				std::string client_id,
				bool is_clean,
				std::string host, 
				int port, 
				std::string username, 
				std::string password, 
				int timeout_s = 60);

			// TODO : Docs
			ERC disconnect(void);
			
			// TODO : Docs
			bool is_connected(void);

			
			// TODO : Docs
			ERC publish(void);
			
			// TODO : Docs
			ERC subscribe(
				std::string topic,
				int qos = 0,
				bool retain = false,
				std::function<void(void)> callback = nullptr
			);
			
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
			ERC initialize(void);

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

			// mosquitto attributes
			mosquitto* m_pMosq;

			bool m_is_mosq_initialized;
		};
	}
}