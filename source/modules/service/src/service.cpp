// standard includes
// ..


// internal includes
#include "service/service.h"


// module includes
// ..


// thirdparty includes
// ..



namespace felidae
{

    Service::Service(void)
    {}


    Service::~Service(void)
    {}


    ERC Service::assign_task(Task_t task)
    {
        ERC status = ERC::SUCCESS;

        if(task != nullptr)
            m_task = task;
        else
            status = ERC::NULLPTR_RECV;

        return status;
    }


    ERC Service::remove_task(void)
    {
        ERC status = ERC::SUCCESS;

        if(!this->is_running())
            m_task = nullptr;
        else
            status = ERC::FAILURE;

        return status;
    }


    ERC Service::start(void)
    {
        ERC status = ERC::SUCCESS;

        // ..

        return status;
    }


    ERC Service::stop(bool force)
    {
        ERC status = ERC::SUCCESS;

        // ..

        return status;
    }


    bool Service::is_running(void) const
    {
        return !m_service_thread.joinable();
    }

}   // namespace felidae