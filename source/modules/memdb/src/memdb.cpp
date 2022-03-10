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
            std::lock_guard<std::mutex> db_lock(m_mtx);
            m_db.at(column_name).push(item);

            // lock_guard automatically gets released
            // once we go out of its declaration scope.
            // Why not use pure mutex? Check
            // www.modernescpp.com/index.php/prefer-locks-to-mutexes
        }

        return status;
    }

    ERC MemDB::pop(std::string column_name, DBitem& pop_into)
    {
        auto status = ERC::SUCCESS;
        
        if (column_exists(column_name))
        {
            std::lock_guard<std::mutex> db_lock(m_mtx);
            
            pop_into = m_db.at(column_name).front();
            m_db.at(column_name).pop();
        }

        return status;
    }

    bool MemDB::is_empty(void)
    {
        return m_db.empty();
    }

    bool MemDB::is_empty(std::string column_name)
    {
        if (column_exists(column_name))
            return m_db.at(column_name).empty();
        
        // No column exists, logically empty
        return true;
    }

    ERC MemDB::purge(std::string column_name)
    {
        if (column_exists(column_name))
        {
            std::lock_guard<std::mutex> db_lock(m_mtx);

            while (!m_db.at(column_name).empty())
                m_db.at(column_name).pop();
        }

        // No column exists to purge, logically successful
        return ERC::SUCCESS;
    }

    ERC MemDB::drop(void)
    {
        auto status = ERC::SUCCESS;
        
        std::lock_guard<std::mutex> db_lock(m_mtx);
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