// preprocessor flags
#pragma once


// standard includes
#include <atomic>
#include <memory>
#include <thread>


// internal includes
#include "message.h"


// module includes
#include "configurator/configurator.h"
#include "errorcodes/errorcodes.h"
#include "memdb/memdb.h"


// forward references
namespace httplib { class Client; }



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

			// ------------------------ PUBLIC METHODS ------------------------
			// The following methods are the public interface for Influx client
			// Detailed info on usage and functioning of each public method is
			// written on top of it.
			// ----------------------------------------------------------------
			
			Client(void);
			~Client(void);


			/// Connect to InfluxDB remote instance on HTTP protocol.
			/// This is a blocking call.
			/// 
			/// host - set the host address of remote instance to connect to.
			/// port - set the port number of host to access remote instance.
			/// token - set the token to perform API operatios on remote.
			///
			/// return ERC.SUCCESS - on success
			/// return ERC.MEMORY_ALLOCATION_FAILED - if client failed to init 
			///		   HTTP client (usually due to malformed host or port value)
			/// return ERC.FAILURE - if remote doesn't respond to ping request 
			ERC connect(
				std::string host, 
				uint16_t port, 
				std::string token
			);
			

			/// Disconnects from InfluxDB remote instance. Deallocates the HTTP 
			/// access point. This is a blocking call.
			///
			/// return ERC.SUCCESS - on success (always)
			ERC disconnect(void);
			

			/// Returns connection status between Influx Client and remote DB.
			/// It sends ping request to the remote DB over HTTP channel.
			/// This is a blocking call.
			///
			/// return TRUE - if remote responds on ping req with 204
			/// return FALSE - otherwise
			bool is_connected(void);

			
			// TODO - define query()
			// ERC query(std::string org_name, std::string bucket, std::string flux_query);
			

			/// Write a data point/message to data bucket in an organization
			/// that must be present on the  InfluxDB remote. Requires client
			/// to be connected to remote. This is a blocking call.
			///
			/// org_name - organization name (not ID) which carries the bucket
			/// bucket - bucket name to write the data into.
			/// data - influx::Message object containing data that is to be written
			///
			/// return ERC.SUCCESS - if remote responds on write req with 204
			/// return ERC.FAILURE - otherwise
			/// 
			/// NOTE - The log messages provide detailed info on HTTP response
			///        in case of an error.
			ERC write(
				std::string org_name,
				std::string bucket,
				Message data
			);

			
			// NOTE - The following three methods are going to be depreciated
			// in future releases of mflux as they increase module coupling.
			// They'll be replaced by a separate unit local to mflux that uses
			// this client class to make a service. This will enable this client
			// class to be used by other apps/projects seamlessly without
			// unnecessary long dependency chain.

			/// A tailored function for mflux that handles the writing of
			/// outgoing influx messages. This is a non-blocking call as it starts
			/// the service worked on a separate thread.
			///
			/// p_config - pointer to configuration object containing valid Influx
			///            attributes
			/// p_buffer - pointer to memdb object. This is the object that
			///            stores Influx messages awaiting to be written to
			///		 	   remote. This service pulls messages from this buffer.
			///
			/// return ERC.SUCCESS - on success
			/// return ERC.FAILURE - on failure in starting up service
			ERC start_service(
				std::shared_ptr<Configurator> p_config, 
				std::shared_ptr<MemDB> p_buffer
			);
			
			/// A tailored function for mflux that stops the service worker
			/// gracefully. This is a blocking call that waits for the worker
			/// thread to exit.
			///
			/// return ERC.SUCCESS - on success
			/// return ERC.FAILURE - on failure
			ERC stop_service(void);
			
			/// Returns runtime status of the service worker
			///
			/// return TRUE if service worker is running
			/// return FALSE if service worker is not running
			bool is_running(void);

		private:
			
			// ----------------------- PRIVATE METHODS ------------------------
			// The following methods are the public interface for Influx client
			// Detailed info on usage and functioning of each public method is
			// written on top of it.
			// ----------------------------------------------------------------

			// NOTE - The following two internal methods are going to be depre-
			// ciated in future releases of mflux as they are internal impleme-
			// ntations of the influx::start_service() and influx::stop_service()

			// A static service wrapper (for thread support) on the actual
			// service worker. That service worker does the actual job that
			// influx::start_service() initiates.
			//
			// p_instance - pointer to influx client instance (this)
			static void si_service_wrapper(void* p_instance);
			void i_actual_job(void);

		private:
			
			static constexpr const char* SELF_NAME = "INFLUX";

			std::atomic<bool> m_signalled_stop;
			std::thread m_worker;

			std::shared_ptr<Configurator> m_pConfig;
			std::shared_ptr<MemDB> m_pBuffer;

			// TODO : remove cinflux params
			std::shared_ptr<httplib::Client> m_pHTTP_cli;
			std::string m_host;
			uint16_t m_port;
			std::string m_token;
		};
	}
}