// preprocessor flags
#pragma once


// standard includes
#include <map>
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
	class DBitem
	{
	public:

		DBitem()
		{}

		~DBitem()
		{}

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
		
		using value_t = std::variant<influx::Message, mqtt::Message>;
		value_t m_value;
	};



	class MemDB
	{
	public:
			
		MemDB(void);
		~MemDB(void);

		// Push a DB item into a DB column
		ERC push(std::string column_name, DBitem item);
		
		// Pop a DB item from a DB column
		ERC pop(std::string column_name, DBitem& pop_into);

		// Check if the database is empty
		bool is_empty(void);

		// Check if a DB column is empty
		bool is_empty(std::string column_name);

		// Purge a database column
		ERC purge(std::string column_name);

		// Drop the database
		ERC drop(void);

	private:

		bool column_exists(std::string column_name);

	private:

		using data_column_t = std::queue<DBitem>;

		std::map<std::string, data_column_t> m_db;
	};
}