// standard includes
// ..

// internal includes
#include "memdb/memdb.h"

// module includes
// ..

// thirdparty includes
// ..

// forward references
// ..



namespace felidae
{
	namespace influx
	{
		MemDB::MemDB(void)
        {}

		MemDB::~MemDB(void)
        {}


		ERC MemDB::push()
        {
            auto status = ERC::SUCCESS;
            // ..
            return status;
        }

		ERC MemDB::pop()
        {
            auto status = ERC::SUCCESS;
            // ..
            return status;
        }

		ERC MemDB::fetch()
        {
            auto status = ERC::SUCCESS;
            // ..
            return status;
        }

		bool MemDB::isEmpty()
        {
            auto status = true;
            // ..
            return status;
        }
        
		bool MemDB::isEmpty(std::string key)
        {
            auto status = true;
            // ..
            return status;
        }
        
		ERC MemDB::purge()
        {
            auto status = ERC::SUCCESS;
            // ..
            return status;
        }
        
		ERC MemDB::drop()
        {
            auto status = ERC::SUCCESS;
            // ..
            return status;
        }
	}
}