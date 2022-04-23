// preprocessor flags
#pragma once


// standard includes
#include <chrono>								// Library to deal with data time
#include <cstdint>								// Gives uint64_t and other data int types
#include <map>									// Map data structure (key, value) pairs
#include <string>								// String data structure
#include <variant>								// Type-safe union data structure


// internal includes
// ..


// module includes
#include "errorcodes/errorcodes.h"


// thirdparty includes
#include "spdlog/fmt/fmt.h"


// forward references
// ..



namespace felidae
{
	namespace influx
	{
		/// This data structure represents a common influx payload
		/// that is sent over or received from the Influx database
		/// A serialized payload looks like this:
		/// 
		/// cpu_z,sub_id=JTGM,user_id=TLM0201 celsius=73.97038159354763,cost=0.48445310567793615,precipitation=35.23103248356096 1642002847244005
		///
		/// Here we have 4 parameters to consider, these are:
		/// Measure   : The name of the measurement, here it is 'cpu_z'
		/// Tag Set   : The tags of the measurement, here they are 'sub_id' and 'user_id'
		/// Field Set : The fields of the measurement, here they are 'celsius', 'cost' and 'precipitation'
		/// Timestamp : The timestamp when the measurement is made in microseconds (default) since epoch.
		///
		/// * Tag name and tag values are always a string
		/// * Field name is always a string but field value can be
		///   a bool, an int, a decimal (double) or a string
		/// * Whenever an object of this data structure is made, it
		///   assigns itself a timestamp in microseconds since epoch
		///   However this can be overwritten using set_timestamp()
		///   and set_timestamp_precision()
	
		class Message
		{
			// These are the data types permitted in influx payload
			// as a field value
			using value_t = std::variant<bool, int64_t, double, std::string>;

		public:

			// This publicly available data-type denotes the timestamp
			// precision type for Influx Message.
			enum class TimeStamp_t : uint16_t
			{
				nanoseconds = 0,
				microseconds,
				milliseconds,
				seconds
			};
		
		public:

			Message(void)
			{
				m_timestamp = std::to_string(std::chrono::system_clock::now().time_since_epoch() / std::chrono::microseconds(1));
				m_timestamp_precision = TimeStamp_t::microseconds;
			}

			~Message(void){}

			/// Get name of measurement, if exists
			inline std::string get_measure(void) const;

			/// Set name of measurement or overwrite existing one
			inline ERC set_measure(std::string measure_name);

			/// Get a tag value for a tag in this measurement
			inline std::string get_tag_value(std::string tag_key) const;

			/// Set a tag value for an existing tag in this measurment
			inline ERC set_tag_value(std::string tag_key, std::string tag_val);

			/// Add a new tag to this measurement
			inline ERC add_tag_set(std::string tag_key, std::string tag_val);

			/// Remove an existing tag from this measurement
			inline ERC remove_tag_set(std::string tag_key);

			/// Get a field value for a field in this measurement
			inline std::string get_field_value(std::string field_key) const;

			/// Set a field value for an existing field in this measurment
			inline ERC set_field_value(std::string field_key, value_t field_val);

			/// Add a new field to this measurement
			inline ERC add_field_set(std::string field_key, value_t field_val);

			/// Remove an existing field from this measurement
			inline ERC remove_field_set(std::string field_key);

			/// Get the timestamp of this measurement
			inline std::string get_timestamp(void) const;

			/// Update the timestamp of this measurement
			inline ERC set_timestamp(std::string timestamp);

			/// Get the timestamp precision of this measurement
			inline std::string get_timestamp_precision(void) const;

			/// Set the timestamp precision of this measurement
			inline ERC set_timestamp_precision(TimeStamp_t timestamp_precision);

			/// Serialize this measurement
			inline std::string dump(void) const;

			// TODO - define parse()
			// static inline ERC parse(std::string msg) const;

			/// Clear all existing measurements
			inline void clear(void);

		private:

			std::string m_measure;
			std::map<std::string, std::string> m_tags;
			std::map<std::string, value_t> m_fields;
			std::string m_timestamp;
			TimeStamp_t m_timestamp_precision;
		};



		// Definitions
		// ------------------------------------------------

		std::string Message::get_measure(void) const
		{
			return m_measure;
		}



		ERC Message::set_measure(std::string measure_name)
		{
			auto status = ERC::FAILURE;

			if (measure_name.length() > 0)
			{
				m_measure = measure_name;
				status = ERC::SUCCESS;
			}

			return status;
		}



		std::string Message::get_tag_value(std::string tag_key) const
		{
			std::string tag_value = "";

			if (m_tags.find(tag_key) != m_tags.end())
			{
				tag_value = m_tags.at(tag_key);
			}

			return tag_value;
		}



		ERC Message::set_tag_value(std::string tag_key, std::string tag_value)
		{
			auto status = ERC::FAILURE;

			if(m_tags.find(tag_key) != m_tags.end())
			{
				if (tag_value.length() > 0)
				{
					m_tags[tag_key] = tag_value;
					status = ERC::SUCCESS;
				}
			}

			return status;
		}



		ERC Message::add_tag_set(std::string tag_key, std::string tag_value)
		{
			auto status = ERC::FAILURE;

			if (tag_key.length() > 0 && tag_value.length() > 0)
			{
				auto new_tag_pair = std::pair<std::string, std::string>(tag_key, tag_value);

				m_tags.insert(new_tag_pair);
				status = ERC::SUCCESS;
			}

			return status;
		}



		ERC Message::remove_tag_set(std::string tag_key)
		{
			auto status = ERC::FAILURE;

			if (m_tags.find(tag_key) != m_tags.end())
			{
				m_tags.erase(tag_key);
				status = ERC::SUCCESS;
			}

			return status;
		}



		std::string Message::get_field_value(std::string field_key) const
		{
			std::string field_value = "";

			if (m_fields.find(field_key) != m_fields.end())
			{
				if (const bool* pval = std::get_if<bool>(&m_fields.at(field_key)))
				{
					field_value = std::to_string(*pval);
				}
				else if (const int64_t* pval = std::get_if<int64_t>(&m_fields.at(field_key)))
				{
					field_value = std::to_string(*pval);
				}
				else if (const double* pval = std::get_if<double>(&m_fields.at(field_key)))
				{
					field_value = std::to_string(*pval);
				}
				else if (const std::string* pval = std::get_if<std::string>(&m_fields.at(field_key)))
				{
					field_value = *pval;
				}

				//field_value = std::get<std::string>(m_fields[field_key]);
			}

			return field_value;
		}



		ERC Message::set_field_value(std::string field_key, value_t field_value)
		{
			auto status = ERC::FAILURE;

			if(m_fields.find(field_key) != m_fields.end())
			{
				m_fields[field_key] = field_value;
				status = ERC::SUCCESS;
			}

			return status;
		}



		ERC Message::add_field_set(std::string field_key, value_t field_value)
		{
			auto status = ERC::FAILURE;

			if (field_key.length() > 0)
			{
				auto new_field_pair = std::pair<std::string, value_t>(field_key, field_value);

				m_fields.insert(new_field_pair);
				status = ERC::SUCCESS;
			}

			return status;
		}



		ERC Message::remove_field_set(std::string field_key)
		{
			auto status = ERC::FAILURE;

			if (m_fields.find(field_key) != m_fields.end())
			{
				m_fields.erase(m_fields.find(field_key));
				status = ERC::SUCCESS;
			}

			return status;
		}



		std::string Message::get_timestamp(void) const
		{
			return m_timestamp;
		}



		ERC Message::set_timestamp(std::string timestamp)
		{
			auto status = ERC::FAILURE;

			if (timestamp.length() > 0)
			{
				m_timestamp = timestamp;
				status = ERC::SUCCESS;
			}

			return status;
		}



		std::string Message::get_timestamp_precision(void) const
		{
			switch(m_timestamp_precision)
			{
				case TimeStamp_t::nanoseconds : return "ns";
				break;
				
				case TimeStamp_t::microseconds : return "us";
				break;

				case TimeStamp_t::milliseconds : return "ms";
				break;

				case TimeStamp_t::seconds : return "s";
				break;

				default : return "null";
			}
		}



		ERC Message::set_timestamp_precision(Message::TimeStamp_t timestamp_prec)
		{
			m_timestamp_precision = timestamp_prec;
			return ERC::SUCCESS;
		}



		std::string Message::dump(void) const
		{
			std::string dump;

			// Adding measure
			dump += m_measure;

			// Adding tags
			for (auto tag_set : m_tags)
			{
				dump += fmt::format(",{}={}", tag_set.first, tag_set.second);
			}

			// Adding required space between tag_set and field_set
			dump.push_back(' ');

			// Adding fields
			for (auto field_set : m_fields)
			{
				auto key = field_set.first;
				auto value = this->get_field_value(key);

				dump += fmt::format("{}={},", key, value);
			}

			// Removing trailing comma from last field_set
			dump.pop_back();

			// Adding timestamp
			dump += fmt::format(" {}", m_timestamp);

			return dump;
		}


		/*
		ERC Message::parse(std::string to_parse)
		{
			ERC status = ERC::FAILURE;

			return status;
		}
		*/


		void Message::clear(void)
		{
			m_measure = "";
			m_tags.clear();
			m_fields.clear();
			m_timestamp = std::to_string(std::chrono::system_clock::now().time_since_epoch() / std::chrono::microseconds(1));
			m_timestamp_precision = TimeStamp_t::microseconds;
		}
	}
}