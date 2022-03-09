// preprocessor flags
#pragma once

// standard includes
#include <map>
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
	class MemDB
	{
	public:
			
		MemDB(void);
		~MemDB(void);

		// Push a DB item into a DB column
		ERC push(std::string column_name);
		
		// Pop a DB item from a DB column
		ERC pop(std::string column_name);

		// Check if the database is empty
		bool is_empty(void);

		// Check if a DB column is empty
		bool is_empty(std::string column_name);

		// Purge a database column
		ERC purge(std::string column_name);

		// Drop the database
		ERC drop(void);
	};
}