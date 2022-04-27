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

        if(m_task == nullptr)
            status = ERC::NULLPTR_RECV;

        if(status == ERC::SUCCESS)
            m_worker = std::thread(si_task_wrapper, this);

        if(!this->is_running())
            status = ERC::FAILURE;

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
        return !m_worker.joinable();
        // TODO - Use future and async 
        // https://stackoverflow.com/questions/9094422/how-to-check-if-a-stdthread-is-still-running
    }



    // ------------------------------------------------------------------------
    // 
    // ------------------------------------------------------------------------

    void Service::si_task_wrapper(void* p_instance)
    {
        // This thread blocks here
        static_cast<Service*>(p_instance)->i_job();
    }


    void Service::i_job(void)
    {
        m_signalled_stop.exchange(false);

        while(!m_signalled_stop)
            m_task();
    }

}   // namespace felidae