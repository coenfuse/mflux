// preprocessor flags
#pragma once


// standard includes
#include <map>
#include <mutex>
#include <queue>
#include <string>
#include <variant>


// internal includes
// ..


// module includes
#include "errorcodes/errorcodes.h"
#include "influx/message.h"
#include "mqtt/message.h"


// thirdparty includes
// ..


// forward references
// ..



namespace felidae
{

	/// DBitem is the class that will be stored inside the
	/// MemDB class object. It is a wrapper around templated
	/// datatypes that a user would like to store in MemDB.
	/// Currently, a DBitem could store either an influx::Message
	/// object or mqtt::Message object.
	/// This coupling with mqtt and influx module isn't
	/// desirable and thus will be removed in the future. Then
	/// DBitem will store an array of fundamental data types
	/// like strings, bool, int, float, etc. Which in turn
	/// would enable MemDB to be used in any scenario and
	/// not only Mflux's specific use case.

	class DBitem
	{
	public:

		DBitem()
		{}

		~DBitem()
		{}

		/// Copies the data from the DBitem for the specified
		/// datatype if exists. Otherwise returns ERC::FAILURE
		template <typename T>
		inline ERC get(T& copy_into)
		{
			auto status = ERC::FAILURE;

			if (std::holds_alternative<T>(m_value))
			{
				copy_into = std::get<T>(m_value);
				status = ERC::SUCCESS;
			}

			return status;
		}

		/// Sets the DBitem value with the specified data type.
		/// Currently allowed datatypes are influx::Message and
		/// mqtt::Message
		template <typename T>
		inline ERC set(T value)
		{
			auto status = ERC::SUCCESS;

			try
			{
				m_value = value;
			}
			catch (...)
			{
				status = ERC::EXCEPTION;
			}

			return status;
		}

	private:
		
		// TODO : Remove this dependency on Influx and MQTT asap!
		using value_t = std::variant<influx::Message, mqtt::Message>;
		value_t m_value;
	};


	/// In memory key value database featuring basic push-pop
	/// operations. It is used as a buffer for load balancing
	/// asynchronous operations of mqttclient and influxclient

	class MemDB
	{
	public:
			
		MemDB(void);
		~MemDB(void);

		/// Push a DB item into a DB column
		ERC push(std::string column_name, DBitem item);
		
		/// Pop a DB item from a DB column
		ERC pop(std::string column_name, DBitem& pop_into);

		/// Check if the database is empty
		bool is_empty(void);

		/// Check if a DB column is empty
		bool is_empty(std::string column_name);

		/// Purge a database column
		ERC purge(std::string column_name);

		/// Drop the database
		ERC drop(void);

	private:

		/// Checks whether a data colum already exists in the DB or not
		bool column_exists(std::string column_name);

	private:

		std::mutex m_mtx;

		using data_column_t = std::queue<DBitem>;
		std::map<std::string, data_column_t> m_db;
	};
}