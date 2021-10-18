#ifndef __ISE_THREAD_H__
#define __ISE_THREAD_H__

#include "ise_utils.h"
#include "ise_debug.h"
#include "ise_queue.h"

namespace ise_common
{
    /*Thread Routine define*/
    typedef void *(*IseThreadRT)(void *pParam);

    typedef enum _IseThreadPriority
    {
        ISE_LOWEST = 1,
        ISE_LOW,
        ISE_NORMAL,
        ISE_HIGH,
        ISE_HIGHEST
    } ISEThreadPrio;

    class CIseThread
    {
    public:
        CIseThread();
        CIseThread(std::string thread_name);
        ~CIseThread();
    
    public:
        ISE_BOOL                         Create(IseThreadRT routine, ISE_VOID *pParam, ISE_BOOL bMessageQueue, ISEThreadPrio prio);
        ISE_BOOL                         Create(IseThreadRT routine, ISE_VOID *pParam, ISE_BOOL bMessageQueue);
        ISE_BOOL                         Create(IseThreadRT routine, ISE_VOID *pParam);
        ISE_VOID                         Close();
        ISE_VOID                         WaitForDead();
        ISE_BOOL                         GetThreadMessage(IseMessage &msg, ISE_UINT32 wait_time_ms = ISEOSPER_INFINITE);
        ISE_BOOL                         HaveThreadMessage();
        ISE_BOOL                         SendThreadMessage(const IseMessage msg);

        std::string                      GetThreadName();

    private:
        ISE_BOOL                         InitThread();
 
    private:
        pthread_t                       m_ThreadId;
        std::string                     m_strThreadName;
        ISEThreadPrio                   m_ThreadPrio;
        IseThreadRT                     m_TheadRoutine;
        ISE_VOID                       *m_pThreadParam;
        ISE_BOOL                        m_bMessageQueue;
        CIseQueue<IseMessage>          *m_pMessageQueue;
    };
}

#endif  /*__ISE_THREAD_H__*/
