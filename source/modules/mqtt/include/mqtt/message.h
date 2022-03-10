// preprocessor flags
#pragma once

// standard includes
#include <string>

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
		class Message
		{
		public:

			Message(void){}
			~Message(void){}

			inline void set_topic(std::string topic);
			inline void set_payload(std::string payload);
			inline void set_qos(uint8_t qos);
			inline void set_to_retain(bool retain_status);

			inline std::string get_topic(void);
			inline std::string get_payload(void);
			inline uint8_t get_qos(void);
			inline bool get_to_retain(void);

			inline std::string dump();
			inline ERC parse(std::string msg);

		private:

			std::string m_topic;
			std::string m_payload;
			uint8_t m_qos = 0;
			bool m_to_retain = false;
		};



		// Definitions
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

		std::string Message::get_topic(void)
		{
			return m_topic;
		}

		std::string Message::get_payload(void)
		{
			return m_payload;
		}

		uint8_t Message::get_qos(void)
		{
			return m_qos;
		}

		bool Message::get_to_retain(void)
		{
			return m_to_retain;
		}

		std::string Message::dump(void)
		{
			auto mqtt_msg_dump = "";

			// TODO : MQTT msg serialization

			return mqtt_msg_dump;
		}

		ERC Message::parse(std::string msg)
		{
			auto status = ERC::SUCCESS;

			// TODO : MQTT msg deserialization

			return status;
		}
	}
}