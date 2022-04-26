// preprocessor flags
#pragma once


// standard includes
#include <atomic>
#include <map>
#include <memory>
#include <thread>


// internal includes
#include "message.h"
#include "subscription.h"


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

			// ---------------------- PUBLIC METHODS --------------------------
			// The following methods are public interface for MQTT client.
			// Detailed info on usage and functioning of each public method is
			// written for it.
			// ----------------------------------------------------------------

			// TODO - remove dependency on mosquitto_message, use mqtt::Message instead
			
			/// On message callback type for mqtt client. Use this type for defining
			/// function pointers that are required as a callback parameter type in 
			/// subscribe() method for client. 
			using msg_callback_t = std::function<void(const struct mosquitto_message*)>;
			
			Client(void);
			~Client(void);


			/// Connect to MQTT broker. This is a blocking call.
			///
			/// client_name - name of mqtt client. Should be a non-empty string.
			/// is_clean - set to true to instruct the broker to clean all messages and subscriptions on disconnect, false to instruct it to keep them.
			/// host - set the host address of broker to connect to. Defaults to 'localhost'.
			/// port - set the port number of broker to connect to. Defaults to 1883.
			/// username - set the username for connection authentication. Defaults to empty string specifying no authentication
			/// password - set the password for connection authentication. Defaults to empty string specifying no authentication
			/// timeout_s - the number of seconds after which the broker should send a PING message to the client if no other messages have been exchanged in that time.
			///
			/// return ERC.SUCCESS - on success
			/// return ERC.MEMORY_ALLOCATION_FAILED - if client fails to initialize mosquitto lib or instance
			/// return ERC.FAILURE - if input is invalid
			ERC connect(
				std::string client_name,
				bool is_clean = true,
				std::string host = "localhost", 
				int port = 1883, 
				std::string username = "", 
				std::string password = "", 
				int timeout_s = 60);


			/// Disconnects from an MQTT broker. This is blocking call.
			///
			/// return ERC.SUCCESS - on success
			/// return ERC.FAILURE - on failure
			ERC disconnect(void);


			/// Returns connection status between client and broker.
			///
			/// return TRUE if client is connected to broker
			/// return FALSE if client is not connected to broker
			bool is_connected(void);

			// TODO - define publish()
			/// Publish a message to MQTT broker on a specified topic.
			ERC publish(void);


			/// Subscribe to a MQTT topic on the MQTT broker. Requires client
			/// to be connected with the broker. Specify an optional callback
			/// function that'll be invoked whenever a new message is received
			/// on the subscribed topic.
			///
			/// topic - subscription topic string in MQTT specified format. Should be a non-empty string
			/// qos - quality of service level for subscription. Ranges from 0 to 2
			/// retain - whether to retain the messages on reconnection for this subscription topic
			/// callback - callback function that'll be invoked whenever a new message is received on the subscribed topic, defaults to nullptr.
			///
			/// return ERC.SUCCESS - on success
			/// return ERC.FAILURE - on failure
			ERC subscribe(
				std::string topic,
				uint8_t qos = 0,
				bool retain = false,
				msg_callback_t callback = nullptr
			);


			// TODO - define subscribe()
			// ERC subscribe(Subscription sub_obj);


			/// Unsubscribe from a MQTT topic on the MQTT broker. Requires client to be connected with the broker and subscribed to the topic.
			///
			/// topic - subscription topic string in MQTT specified format. Should be a non-empty string
			///
			/// return ERC.SUCCESS - on success
			/// return ERC.FAILURE - on failure
			ERC unsubscribe(std::string topic);


			// NOTE - The following three methods are going to be depreciated 
			// in future releases of mflux as they increase module coupling.
			// They'll be replaced by a separate unit local to mflux that
			// uses this client class to make a service. This will enable this
			// client class to be used by other projects seamlessly.
			
			/// A tailored function for mflux that handles the pushing of incoming mqtt messages into and from mqtt buffer.
			/// This is a non-blocking call, as it starts the service worker on a separate thread.
			///
			/// p_config - pointer to configuration object containing valid MQTT attributes
			/// p_buffer - pointer to memdb object. This is the object that will be used to store incoming mqtt messages.
			///
			/// return ERC.SUCCESS - on success
			/// return ERC.FAILURE - on failure
			ERC start_service(std::shared_ptr<Configurator> p_config, std::shared_ptr<MemDB> p_buffer);
			
			/// A tailored function for mflux that stops the service worker gracefully.
			/// This is a blocking call that waits for the worker thread to exit.
			///
			/// return ERC.SUCCESS - on success
			/// return ERC.FAILURE - on failure
			ERC stop_service(void);
			
			/// Returns runtime status of the service worker.
			///
			/// return TRUE if service worker is running
			/// return FALSE if service worker is not running
			bool is_running(void);


		private: 
			
			// --------------------- PRIVATE METHODS --------------------------
			// The following methods are internal implementation of mqtt client
			// and aren't going to be used directly or needed to be understood
			// by the general end user. From a developer's view however, the 
			// code is available to view. But it is advised to be careful while
			// doing any customization.
			// ----------------------------------------------------------------

			// Initialize mosquitto library and create a mosquitto instance.
			//
			// client_name - name of mqtt client. Should be a non-empty string.
			// is_clean - set to true to instruct the broker to clean all messages and subscriptions on disconnect, false to instruct it to keep them.
			// username - set the username for connection authentication. Defaults to empty string specifying no authentication
			// password - set the password for connection authentication. Defaults to empty string specifying no authentication
			//
			// return ERC.SUCCESS - on success
			// return ERC.MEMORY_ALLOCATION_FAILED - if client fails to initialize mosquitto lib or instance
			// return ERC.FAILURE - if input is invalid
			ERC i_initialize(
				std::string client_name,
				bool is_clean, 
				std::string username, 
				std::string password
			);

			// NOTE - The following two internal methods are going to be depre-
			// ciated in future releases of mflux as they are internal impleme-
			// ntations of the mqtt::start_service() and mqtt::stop_service()

			// A static service wrapper (thread support) an an actual service
			// worker. This service worker does the actual job that
			// mqtt::start_service() initiates.
			//
			// p_instance - pointer to mqtt client instance (this)
			static void si_service_wrapper(void* p_instance);
			void i_actual_job(void);

			// Mosquitto loop starters and stoppers. Supports cross-platform
			// (WIN32 & LIN) mosquitto loop controllers that are required for
			// optimal functioning of mosquitto callbacks and other runtime
			// library functions.
			ERC i_start_network_monitor(void);
			ERC i_stop_network_monitor(void);

			// A static network monitor wrapper (thread support) and an actual
			// monitor method that loops over the network, scanning for any 
			// events and callbacks. The i_actual_monitor() provides the cross-
			// platform support for mosquitto_loop that network monitor starters
			// and stoppers advertise.
			//
			// p_instance - pointer to mqtt client instance (this)
			static void si_network_monitor_wrapper(void* p_instance);
			void i_actual_monitor(void);

			// A static on connect wrapper (thread support) and an actual
			// on_connect callback. This callback will be executed whenever
			// the client connects or reconnects to the broker.
			static void si_on_connect_wrapper(mosquitto* p_mosq, void* p_obj, int status);
			void i_on_connect_callback(void* p_instance, int status);

			// A static on disconnect wrapper (thread support) and an actual
			// on_disconnect callback. This callback will be executed whenever
			// the client disconnects from the broker.
			static void si_on_disconnect_wrapper(mosquitto* p_mosq, void* p_obj, int status);
			void i_on_disconnect_callback(void* p_instance, int status);

			// A static on subscribe wrapper (thread support) and an actual
			// on_subscribe callback. This callback will be executed whenever
			// the client makes a successful subscription on the broker.
			static void si_on_subscribe_wrapper(mosquitto* p_mosq, void* p_obj, int mid, int qos_count, const int* p_granted_qos);
			void i_on_subscribe_callback(void* p_instance, int mid, int qos_count, const int* granted_qos);

			// A static on unsubscribe wrapper (thread support) and an actual
			// on_unsubscribe callback. This callback will be executed whenever
			// the client makes a successful unsubscription on the broker.
			static void si_on_unsubscribe_wrapper(mosquitto* p_mosq, void* p_obj, int mid);
			void i_on_unsubscribe_callback(void* p_instance, int mid);

			// A static on message wrapper (thread support) and an actual
			// on_message callback. This callback will be executed whenever
			// the client receives a message on a existing subscription. 
			// On receiving a new message the on_message callback method
			// searches for custom callbacks in callback table for the topic
			// message is received on. The callback table here is set using
			// client::subscribe(). If the callback method finds a custom action
			// then it is executed else, the default log action is performed.
			static void si_on_message_wrapper(mosquitto* p_mosq,  void* p_obj, const mosquitto_message* p_msg);
			void i_on_message_callback(const mosquitto_message* p_msg);

			// A static on publish wrapper (thread support) and an actual 
			// on_publish callback. This callback will be executed whenever
			// the client makes a successful publication on the broker.
			static void si_on_publish_wrapper(mosquitto* p_mosq, void* p_obj, int mid);
			void i_on_publish_callback(void* p_instance, int mid);

		private:

			static constexpr const char* SELF_NAME = "MQTT  ";

			std::atomic_bool m_signalled_stop;
			std::thread m_worker;

			std::shared_ptr<Configurator> m_pConfig;
			std::shared_ptr<MemDB> m_pBuffer;

			std::atomic_bool m_is_monitoring;
			std::thread m_monitor_thread;

			// BUG: The program seem to only work when this unused variable is declared
			std::map<std::string, msg_callback_t> void_callback;

			// mosquitto attributes
			mosquitto* m_pMosq;

			bool m_is_mosq_initialized;
			bool m_is_mosq_connected;
		};
	}
}