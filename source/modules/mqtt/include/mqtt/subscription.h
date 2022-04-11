// preprocessor flags
#pragma once

// standard includes
#include <cstdint>
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
        class Subscription
        {
        public:

            Subscription(){}
            ~Subscription(){}

            /// Get the topic name of the subscription object
            inline std::string get_topic(void) const;

            /// Set a topic name for this subscription object.
            ///
            /// topic - subscription topic string in MQTT specified format. Should be a non-empty string
            ///
            /// return ERC.SUCCESS - on success
            /// return ERC.FAILURE - on invalid topic input
            inline ERC set_topic(std::string topic);

            /// Get the QOS (Quality of service) value of the subcription object
            ///
            /// return unsigned int ranging from 0 to 2
            inline uint8_t get_qos(void) const;

            /// Set the QOS (Quality of service) value of the subscription object.
            /// 
            /// qos - quality of service level for subscription. Ranges from 0 to 2
            ///
            /// return ERC.SUCCESS - on success
            /// return ERC.FAILURE - on invalid QOS value
            inline ERC set_qos(uint8_t qos);

            /// Get retention status for this subscription object.
            ///
            /// return TRUE if message retention for this subscription is ON
            /// return FALSE if message retention for this subscription is OFF
            inline bool get_to_retain(void) const;

            /// Set retention status for this subscription object.
            ///
            /// to_retain - whether to retain the messages on reconnection for this subscription topic
            inline void set_to_retain(bool to_retain);

            // TODO - define get_callback()
            // inline void get_callback();

            // TODO - define set_callback()
            // inline void set_callback();

        private:

            std::string m_topic = "";
            uint8_t m_qos = 0;
            bool m_retain = false;
        };



        // PUBLIC DEFINITIONS
        // ------------------------------------------------

        std::string Subscription::get_topic(void) const
        {
            return m_topic;
        }

        ERC Subscription::set_topic(std::string topic)
        {
            auto status = ERC::SUCCESS;

            if (topic.length() > 0)
                m_topic = topic;
            else
                status = ERC::FAILURE;

            return status;
        }

        uint8_t Subscription::get_qos(void) const
        {
            return m_qos;
        }

        ERC Subscription::set_qos(uint8_t qos)
        {
            auto status = ERC::SUCCESS;

            if (qos < 3)
                m_qos = qos;
            else
                status = ERC::FAILURE;

            return status;
        }

        bool Subscription::get_to_retain(void) const
        {
            return m_retain;
        }

        void Subscription::set_to_retain(bool to_retain)
        {
            m_retain = to_retain;
        }
	}
}