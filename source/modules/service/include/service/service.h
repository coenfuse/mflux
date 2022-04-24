// preprocessor flags
#pragma once


// standard includes
#include <atomic>
#include <functional>
#include <memory>
#include <thread>


// internal includes
// ..


// module includes
#include <errorcodes/errorcodes.h>


// thirdparty includes
// ..


// forward references
// ..



namespace felidae
{
    // TODO - Docs
    class Service
    {
        public:

        Service(void);
        ~Service(void);

        // --------------------------------------------------------------------
        //
        // --------------------------------------------------------------------

        // TODO - Docs
        using Task_t = std::function<void(void)>;

        // TODO - Docs
        ERC assign_task(Task_t task);
        
        // TODO - Docs
        ERC remove_task(void);

        // TODO - Docs
        ERC start(void);

        // TODO - Docs
        ERC stop(bool force = false);

        // TODO - Docs
        bool is_running(void) const;

        private:

        // --------------------------------------------------------------------
        // 
        // --------------------------------------------------------------------

        // TODO - Docs
        static void si_task_wrapper(void* p_instance);
        
        // TODO - Docs
        void i_job(void);

        private:

        std::thread m_service_thread;
        std::atomic<bool> m_signalled_stop;
        Task_t m_task;
    
    }; // class Service

}   // namespace felidae