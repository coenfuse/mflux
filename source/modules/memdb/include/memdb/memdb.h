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
	namespace influx
	{
		class MemDB
		{
		public:
			
			MemDB(void);
			~MemDB(void);

			ERC push();
		    ERC pop();
		    ERC fetch();
		    bool isEmpty();			            // The database
		    bool isEmpty(std::string key);		// A column
		    ERC purge();				        // A column
		    ERC drop();				            // The database
		};
	}
}