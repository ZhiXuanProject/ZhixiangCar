#include "ise_thread.h"
#include "ise_debug.h"
#include <assert.h>

namespace ise_common
{
    CIseThread::CIseThread()
    {
        m_ThreadId        = ISE_NONE;
        m_strThreadName   = "Ise Thread";
        m_ThreadPrio      = ISE_NORMAL;
        m_TheadRoutine    = ISE_NULL;
        m_pThreadParam    = ISE_NULL;
        m_bMessageQueue   = ISE_FALSE;
        m_pMessageQueue   = ISE_NULL;
    }

    CIseThread::CIseThread(std::string thread_name)
    {
        m_ThreadId        = ISE_NONE;
        m_strThreadName   = thread_name;
        m_ThreadPrio      = ISE_NORMAL;
        m_TheadRoutine    = ISE_NULL;
        m_pThreadParam    = ISE_NULL;
        m_bMessageQueue   = ISE_FALSE;
        m_pMessageQueue   = ISE_NULL;
    }

    CIseThread::~CIseThread()
    {
        WaitForDead();
    }

    ISE_BOOL CIseThread::Create(IseThreadRT routine, ISE_VOID *pParam, ISE_BOOL bMessageQueue, ISEThreadPrio prio)
    {
        m_TheadRoutine     = routine;
        m_pThreadParam     = pParam;
        m_bMessageQueue    = bMessageQueue;
        m_ThreadPrio       = prio;

        return InitThread();
    }

    ISE_BOOL CIseThread::Create(IseThreadRT routine, ISE_VOID *pParam, ISE_BOOL bMessageQueue)
    {
        m_TheadRoutine     = routine;
        m_pThreadParam     = pParam;
        m_bMessageQueue    = bMessageQueue;
        m_ThreadPrio       = ISE_NORMAL;

        return InitThread();
    }

    ISE_BOOL CIseThread::Create(IseThreadRT routine, ISE_VOID *pParam)
    {
        m_TheadRoutine     = routine;
        m_pThreadParam     = pParam;
        m_bMessageQueue    = ISE_FALSE;
        m_ThreadPrio       = ISE_NORMAL;

        return InitThread();
    }

    ISE_BOOL CIseThread::InitThread()
    {
        assert(m_TheadRoutine);

        if(m_ThreadId != ISE_NONE)
        {
            ISE_ERROR_TRACE("Thread %s has been created already! Close it before create a new one!", m_strThreadName.c_str());
            return ISE_FALSE;
        }

        if(m_bMessageQueue)
        {
            if(m_pMessageQueue != ISE_NULL)
            {
                ISE_ERROR_TRACE("Message Queue for thead %s has been created!", m_strThreadName.c_str());
                return ISE_FALSE;
            }

            m_pMessageQueue = new CIseQueue<ISE_MSG_HEAD *>();
            if(m_pMessageQueue == ISE_NULL)
            {
                ISE_ERROR_TRACE("Message Queue for thead %s create failed!", m_strThreadName.c_str());
                return ISE_FALSE;
            }
        }

        if( m_ThreadPrio != ISE_NORMAL )
        {
            pthread_attr_t     attr;
            struct sched_param schParam;
            pthread_attr_init( &attr );
            pthread_attr_setschedpolicy( &attr, SCHED_RR );
            switch( m_ThreadPrio )
            {
            case ISE_LOWEST:
                schParam.sched_priority = sched_get_priority_min( SCHED_RR );
                break;
            case ISE_LOW:
                schParam.sched_priority = sched_get_priority_min( SCHED_RR ) +
                                          ( sched_get_priority_max( SCHED_RR ) - sched_get_priority_min( SCHED_RR ) ) / 4;
                break;
            case ISE_HIGH:
                schParam.sched_priority = sched_get_priority_max( SCHED_RR ) -
                                          ( sched_get_priority_max( SCHED_RR ) - sched_get_priority_min( SCHED_RR ) ) / 4;
                break;
            case ISE_HIGHEST:
                schParam.sched_priority = sched_get_priority_max( SCHED_RR );
                break;
            default:
                assert( ISE_FALSE );
            }
            pthread_attr_setschedparam( &attr, &schParam );
            if( pthread_create( &m_ThreadId, &attr, m_TheadRoutine, m_pThreadParam ) != 0)
            {
                m_ThreadId = ISE_NONE;
            }

            pthread_attr_destroy( &attr );
        }
        else
        {
            if( pthread_create( &m_ThreadId, ISE_NULL, m_TheadRoutine, m_pThreadParam ) )
            {
                m_ThreadId = ISE_NONE;
            }
        }

        if(m_ThreadId == ISE_NONE)
        {
            ISE_ERROR_TRACE("Thread %s create failed!", m_strThreadName.c_str());

            if(m_bMessageQueue && (m_pMessageQueue != ISE_NULL))
            {
                delete m_pMessageQueue;
                m_pMessageQueue  = ISE_NULL;
            }

            return ISE_FALSE;
        }

        ISE_INFO_TRACE("Therad %s created!", m_strThreadName.c_str());
        return ISE_TRUE;
    }

    ISE_VOID CIseThread::Close()
    {
        if(m_ThreadId == ISE_NONE)
        {
            ISE_ERROR_TRACE("Thread %s close failed! NOT created yet!", m_strThreadName.c_str());
            return;
        }

        pthread_detach(m_ThreadId);
        m_ThreadId = ISE_NONE;

        if(m_bMessageQueue && m_pMessageQueue != ISE_NULL)
        {
            delete m_pMessageQueue;
            m_pMessageQueue = ISE_NULL;
        }
    }

    ISE_VOID CIseThread::WaitForDead()
    {
        if(m_ThreadId == ISE_NONE)
        {
            //ISE_ERROR_TRACE("Thread %s close failed! NOT created yet!", m_strThreadName.c_str());
            return;
        }

        ISE_VOID   *pThreadResult;
        pthread_join( m_ThreadId, &pThreadResult );
        m_ThreadId = ISE_NONE;

        if(m_bMessageQueue && m_pMessageQueue != ISE_NULL)
        {
            delete m_pMessageQueue;
            m_pMessageQueue = ISE_NULL;
        }
    }

    ISE_BOOL CIseThread::GetThreadMessage(ISE_MSG_HEAD *&msg, ISE_UINT32 wait_time_ms)
    {
        assert(m_ThreadId);

        if((m_bMessageQueue == ISE_FALSE) || (m_pMessageQueue == ISE_NULL))
        {
            ISE_ERROR_TRACE("Messaging for thread %s is NOT support or NOT initialized!", m_strThreadName.c_str());
            return ISE_FALSE;
        }

        return m_pMessageQueue->pop(msg, wait_time_ms);
    }

    ISE_BOOL CIseThread::HaveThreadMessage()
    {
        assert(m_ThreadId);

        if((m_bMessageQueue == ISE_FALSE) || (m_pMessageQueue == ISE_NULL))
        {
            ISE_ERROR_TRACE("Messaging for thread %s is NOT support or NOT initialized!", m_strThreadName.c_str());
            return ISE_FALSE;
        }

        return !(m_pMessageQueue->is_empty());
    }

    ISE_BOOL CIseThread::SendThreadMessage(ISE_MSG_HEAD *msg)
    {
        assert(m_ThreadId);

        if((m_bMessageQueue == ISE_FALSE) || (m_pMessageQueue == ISE_NULL))
        {
            ISE_ERROR_TRACE("Messaging for thread %s is NOT support or NOT initialized!", m_strThreadName.c_str());
            return ISE_FALSE;
        }

        m_pMessageQueue->push(msg);
        return ISE_TRUE;
    }

    std::string CIseThread::GetThreadName()
    {
        return m_strThreadName;
    }
}
