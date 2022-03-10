// standard includes
// ..

// internal includes
#include "memdb/memdb.h"

// module includes
// ..

// thirdparty includes
// ..


// TODO : Implement thread safe operations

namespace felidae
{
    // PUBLIC METHODS

    MemDB::MemDB(void)
    {}

    MemDB::~MemDB(void)
    {}


    ERC MemDB::push(std::string column_name, DBitem item)
    {
        auto status = ERC::SUCCESS;
        
        if (column_exists(column_name))
        {
            // TODO : Lock the thread
            
            m_db.at(column_name).push(item);

            // TODO : Unlock the thread
        }

        return status;
    }

    ERC MemDB::pop(std::string column_name, DBitem& pop_into)
    {
        auto status = ERC::SUCCESS;
        
        if (column_exists(column_name))
        {
            // TODO : Lock the thread
            
            pop_into = m_db.at(column_name).front();
            m_db.at(column_name).pop();

            // TODO : Unlock the thread
        }

        return status;
    }

    bool MemDB::is_empty(void)
    {
        return m_db.empty();
    }

    bool MemDB::is_empty(std::string column_name)
    {
        // Check existence of column and then check if it's empty
        if (column_exists(column_name))
            return m_db.at(column_name).empty();
        
        // No column exists, logically empty
        return true;
    }

    ERC MemDB::purge(std::string column_name)
    {
        auto status = ERC::SUCCESS;
        
        if (column_exists(column_name))
        {
            while (!m_db.at(column_name).empty())
                m_db.at(column_name).pop();
        }

        return status;
    }

    ERC MemDB::drop(void)
    {
        auto status = ERC::SUCCESS;
        
        m_db.clear();

        if (!m_db.empty())
            status = ERC::FAILURE;

        return status;
    }

    // PRIVATE METHODS

    bool MemDB::column_exists(std::string column_name)
    {
        return (m_db.find(column_name) != m_db.end());
    }
}