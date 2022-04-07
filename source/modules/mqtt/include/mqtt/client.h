// preprocessor flags
#pragma once


// standard includes
#include <atomic>
#include <map>
#include <memory>
#include <thread>


// internal includes
#include "message.h"


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

			// TODO : Docs and remove dependency on mosquitto_message, use mqtt::Message instead
			using msg_callback_t = std::function<void(const struct mosquitto_message*)>;
			
			Client(void);
			~Client(void);

			// TODO : Docs
			ERC connect(
				std::string client_id,
				bool is_clean = true,
				std::string host = "localhost", 
				int port = 1883, 
				std::string username = "", 
				std::string password = "", 
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
				uint8_t qos = 0,
				bool retain = false,
				msg_callback_t callback = nullptr
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
			ERC i_initialize(
				std::string client_id,
				bool is_clean, 
				std::string username, 
				std::string password
			);

			// TODO : Docs
			static void s_service_wrapper(void* instance);
			void i_actual_job(void);

			// TODO : Docs
			ERC start_network_monitor(void);
			ERC stop_network_monitor(void);
			static void s_network_monitor_wrapper(void* instance);
			void i_actual_monitor(void);

			// TODO : Docs
			static void s_on_connect_wrapper(mosquitto* instance, void* obj, int status);
			void i_on_connect_callback(void* instance, int status);

			// TODO : Docs
			static void s_on_disconnect_wrapper(mosquitto* instance, void* obj, int status);
			void i_on_disconnect_callback(void* instance, int status);

			// TODO : Docs
			static void s_on_subscribe_wrapper(mosquitto* instance, void* obj, int mid, int qos, const int* granted_qos);
			void i_on_subscribe_callback(void* instance, int mid, int qos, const int* granted_qos);

			// TODO : Docs
			static void s_on_unsubscribe_wrapper(mosquitto* instance, void* obj, int mid);
			void i_on_unsubscribe_callback(void* instance, int mid);

			// TODO : Docs
			static void s_on_message_wrapper(mosquitto* instance,  void* obj, const mosquitto_message* msg);
			void i_on_message_callback(const mosquitto_message* msg);

			// TODO : Docs
			static void s_on_publish_wrapper(mosquitto* instance, void* obj, int mid);
			void i_on_publish_callback(void* instance, int mid);

		private:

			static constexpr const char* SELF_NAME = "MQTT  ";

			std::atomic_bool m_signalled_stop;
			std::thread m_worker;

			std::shared_ptr<Configurator> m_pConfig;
			std::shared_ptr<MemDB> m_pBuffer;

			std::atomic_bool m_is_monitoring;
			std::thread m_monitor_thread;

			// BUG : The program seem to only work when this 
			// unused variable is declared
			std::map<std::string, msg_callback_t> void_callback;

			// mosquitto attributes
			mosquitto* m_pMosq;

			bool m_is_mosq_initialized;
			bool m_is_mosq_connected;
		};
	}
}