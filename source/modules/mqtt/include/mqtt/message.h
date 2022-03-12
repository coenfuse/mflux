// preprocessor flags
#pragma once

// standard includes
#include <string>								// String data structure

// internal includes
// ..

// module includes
#include "errorcodes/errorcodes.h"

// thirdparty includes
// ..

// forward references
// ..



namespace felidae
{
	namespace mqtt
	{
		/// This data structure represents a common mqtt payload
		/// that is sent over or received from the mqtt network
		///
		/// Here we have 4 parameters to consider, these are:
		/// Topic     : The MQTT topic this message has been or going to be published to.
		/// Payload   : The actual payload of this MQTT message.
		/// QOS       : The QOS (Quality-of-Service) number of this message.
		/// Retention : The retention status of this MQTT message.
		///
		/// * An MQTT topic doesn't have to be single topic, it
		///   can be nested topic as well, e.g : home/room1/temp/
		/// * The payload can be any alphanumeric string of any
		///	  length.
		/// * The QOS number determines the transmission quality that
		///   must be ensured during transfer of this message. Valid
		///   QOS values are 0, 1 and 2 only.
		/// * The retention status is a boolean parameter that
		///   tells whether to retain this message on MQTT
		///   broker or not

		class Message
		{
		public:

			Message(void){}
			~Message(void){}
			
			/// Get the publish topic for this MQTT message
			inline std::string get_topic(void) const;

			/// Set the publish topic for this MQTT message
			inline void set_topic(std::string topic);
			
			/// Get the string payload for this MQTT message
			inline std::string get_payload(void) const;
			
			/// Set the string payload for this MQTT message
			inline void set_payload(std::string payload);

			/// Get this MQTT message's QOS
			inline uint8_t get_qos(void) const;

			/// Set this MQTT message's QOS
			inline void set_qos(uint8_t qos);
			
			/// Get the retention status of this MQTT message
			inline bool get_to_retain(void) const;

			/// Set the retention status of this MQTT message
			inline void set_to_retain(bool retain_status);

			// TODO : mqtt::Message::dump()
			// inline std::string dump() const;
			
			// TODO : mqtt::Message::parse()
			// static inline ERC parse(std::string msg) const;

		private:

			std::string m_topic;
			std::string m_payload;
			uint8_t m_qos = 0;
			bool m_to_retain = false;
		};



		// Definitions
		// ------------------------------------------------------

		void Message::set_topic(std::string topic)
		{
			if (!topic.empty())
				m_topic = topic;
		}

		void Message::set_payload(std::string payload)
		{
			m_payload = payload;
		}

		void Message::set_qos(uint8_t qos)
		{
			const uint8_t MAX_QOS = 2;

			if (qos <= MAX_QOS)
				m_qos = qos;
			else
				m_qos = MAX_QOS;
		}

		void Message::set_to_retain(bool retain_status)
		{
			m_to_retain = retain_status;
		}

		std::string Message::get_topic(void) const
		{
			return m_topic;
		}

		std::string Message::get_payload(void) const
		{
			return m_payload;
		}

		uint8_t Message::get_qos(void) const
		{
			return m_qos;
		}

		bool Message::get_to_retain(void) const
		{
			return m_to_retain;
		}

		/*
		std::string Message::dump(void) const
		{
			auto mqtt_msg_dump = "";

			return mqtt_msg_dump;
		}
		*/

		/*
		ERC Message::parse(std::string msg) const
		{
			auto status = ERC::SUCCESS;

			return status;
		}
		*/
	}
}