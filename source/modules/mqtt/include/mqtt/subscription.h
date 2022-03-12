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

            /// TODO : Docs
            inline std::string get_topic(void) const;

            /// TODO : Docs
            inline ERC set_topic(std::string topic);

            /// TODO : Docs
            inline uint8_t get_qos(void) const;

            /// TODO : Docs
            inline ERC set_qos(uint8_t qos);

            // TODO : Docs
            inline bool get_to_retain(void) const;

            // TODO : Docs
            inline void set_to_retain(bool to_retain);

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