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
		// TODO : Docs

		class Message
		{
		public:

			Message(void){}
			~Message(void){}
			
			// TODO : Docs
			inline std::string get_topic(void);

			// TODO : Docs
			inline void set_topic(std::string topic);
			
			// TODO : Docs
			inline std::string get_payload(void);
			
			// TODO : Docs
			inline void set_payload(std::string payload);

			// TODO : Docs
			inline uint8_t get_qos(void);

			// TODO : Docs
			inline void set_qos(uint8_t qos);
			
			// TODO : Docs
			inline bool get_to_retain(void);

			// TODO : Docs
			inline void set_to_retain(bool retain_status);

			// TODO : mqtt::Message::dump()
			// inline std::string dump();
			
			// TODO : Docs
			// static inline ERC parse(std::string msg);

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

		/*
		std::string Message::dump(void)
		{
			auto mqtt_msg_dump = "";

			return mqtt_msg_dump;
		}
		*/

		/*
		ERC Message::parse(std::string msg)
		{
			auto status = ERC::SUCCESS;

			return status;
		}
		*/
	}
}