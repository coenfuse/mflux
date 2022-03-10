// standard includes
// ..

// internal includes
#include "memdb/memdb.h"

// module includes
// ..

// thirdparty includes
// ..



namespace felidae
{
    MemDB::MemDB(void)
    {}

    MemDB::~MemDB(void)
    {}


    ERC MemDB::push(std::string column_name, DBitem item)
    {
        auto status = ERC::SUCCESS;
        // ..
        return status;
    }

    ERC MemDB::pop(std::string column_name, DBitem& pop_into)
    {
        auto status = ERC::SUCCESS;
        // ..
        return status;
    }

    bool MemDB::is_empty(void)
    {
        auto status = true;
        // ..
        return status;
    }

    bool MemDB::is_empty(std::string column_name)
    {
        auto status = true;
        // ..
        return status;
    }

    ERC MemDB::purge(std::string column_name)
    {
        auto status = ERC::SUCCESS;
        // ..
        return status;
    }

    ERC MemDB::drop(void)
    {
        auto status = ERC::SUCCESS;
        // ..
        return status;
    }
}