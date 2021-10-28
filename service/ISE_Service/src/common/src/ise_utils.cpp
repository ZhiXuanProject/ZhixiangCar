#include "ise_utils.h"
#include "ise_debug.h"
#include <assert.h>
#include <string.h>

#include <QDebug>

namespace ise_common
{
    CIseEvent::CIseEvent() : m_bSignaled(ISE_FALSE), m_strEventName("Ise Event")
    {
        m_pCond = (pthread_cond_t *)malloc(sizeof(pthread_cond_t));
        ISE_ASSERT(m_pCond, "CIseEvent: Event allocate failed!");

        m_pMutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
        ISE_ASSERT(m_pMutex, "CIseEvent: pthread_mutex_t allocate failed!"); 

        ISE_ASSERT(pthread_mutex_init( m_pMutex, ISE_NULL ) == 0, "CIseEvent: Mutex initialzie failed!");
        ISE_DEBUG_TRACE("CIseEvent: Mutex initialized. %p", m_pMutex);

        pthread_condattr_t attr;
        pthread_condattr_init( &attr );
        pthread_condattr_setclock( &attr, CLOCK_MONOTONIC );
        ISE_ASSERT( pthread_cond_init( m_pCond, &attr ) == 0, "CIseEvent: cond initialize failed!" );
        pthread_condattr_destroy( &attr );
        ISE_DEBUG_TRACE("CIseEvent: Cond initialized. %p", m_pCond);
    }

    CIseEvent::CIseEvent(std::string event_name) :m_bSignaled(ISE_FALSE), m_strEventName(event_name)
    {
        m_pCond = (pthread_cond_t *)malloc(sizeof(pthread_cond_t));
        ISE_ASSERT(m_pCond, "CIseEvent: Event allocate failed!");

        m_pMutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
        ISE_ASSERT(m_pMutex, "CIseEvent: pthread_mutex_t allocate failed!"); 

        ISE_ASSERT(pthread_mutex_init( m_pMutex, ISE_NULL ) == 0, "CIseEvent: Mutex initialzie failed!");
        ISE_DEBUG_TRACE("CIseEvent: Mutex initialized. %p", m_pMutex);

        pthread_condattr_t attr;
        pthread_condattr_init( &attr );
        pthread_condattr_setclock( &attr, CLOCK_MONOTONIC );
        ISE_ASSERT( pthread_cond_init( m_pCond, &attr ) == 0, "CIseEvent: cond initialize failed!" );
        pthread_condattr_destroy( &attr );
        ISE_DEBUG_TRACE("CIseEvent: Event initialized. %p", m_pCond);
    }

    CIseEvent::~CIseEvent()
    {
        if(m_pMutex)
        {
            ISE_DEBUG_TRACE("CIseEvent: Mutex destroy... %p", m_pMutex);
            pthread_mutex_destroy(m_pMutex);

            free(m_pMutex);
            m_pMutex = ISE_NULL;
        }

        if(m_pCond)
        {
            ISE_DEBUG_TRACE("CIseEvent: Event destroy... %p", m_pCond);
            pthread_cond_destroy(m_pCond);
            
            free(m_pCond);
            m_pCond = ISE_NULL;
        }
    }

    ISE_VOID CIseEvent::Signal()
    {
        ISE_ASSERT(m_pMutex, "Invalid CIseEvent mutex!");
        ISE_ASSERT(m_pCond, "Invalid CIseEvent event");

        ISE_DEBUG_TRACE("CIseEvent: Singal Event %p", m_pCond);
        pthread_mutex_lock( m_pMutex );
        m_bSignaled = ISE_TRUE;
        pthread_cond_signal( m_pCond );
        pthread_mutex_unlock(m_pMutex);
        ISE_DEBUG_TRACE("CIseEvent: Event signaled %p.", m_pCond);
    }

    ISE_VOID CIseEvent::Reset()
    {
        ISE_ASSERT(m_pMutex, "Invalid CIseEvent mutex!");
        ISE_ASSERT(m_pCond, "Invalid CIseEvent event");

        ISE_DEBUG_TRACE("CIseEvent: Reseting Event %p", m_pCond);
        pthread_mutex_lock( m_pMutex );
        m_bSignaled = ISE_FALSE;
        pthread_mutex_unlock( m_pMutex );
    }

    ISE_BOOL CIseEvent::Wait(ISE_UINT32 wait_time_ms)
    {
        ISE_ASSERT(m_pMutex, "Invalid CIseEvent mutex!");
        ISE_ASSERT(m_pCond, "Invalid CIseEvent event");

        ISE_DEBUG_TRACE("CIseEvent: Waiting for Event %p", m_pCond);
        ISE_BOOL    bWaited    = ISE_TRUE;

        pthread_mutex_lock( m_pMutex );
        if( wait_time_ms == ISE_INFINITE)
        {
            pthread_cond_wait( m_pCond, m_pMutex );
            if( !m_bSignaled )
            {
                ISE_WARN_TRACE("CIseEvent: ISE_INFINITE waited!");
            }
        }
        else
        {
            struct timespec waitTime;
            clock_gettime( CLOCK_MONOTONIC, &waitTime );
            if( wait_time_ms >= 1000 )
            {
                waitTime.tv_sec  += wait_time_ms / 1000;
                waitTime.tv_nsec += ( wait_time_ms % 1000 ) * 1000000LL;
            }
            else
            {
                waitTime.tv_nsec += wait_time_ms * 1000000LL;
            }

            while( waitTime.tv_nsec >= 1000000000LL )
            {
                waitTime.tv_nsec -= 1000000000LL;
                waitTime.tv_sec++;
            }

            if( !m_bSignaled )
            {
                bWaited = ( pthread_cond_timedwait( m_pCond, m_pMutex, &waitTime ) != ETIMEDOUT );
            }
        }

        if( !bWaited )
        {
            ISE_DEBUG_TRACE( "CIseEvent: Event Wait Failed %p", m_pCond );
        }
        else
        {
            ISE_DEBUG_TRACE( "CIseEvent: Event Waited %p", m_pCond );
        }

        m_bSignaled = ISE_FALSE;
        pthread_mutex_unlock(m_pMutex);

        return bWaited;
    }

    CIseSectionLock::CIseSectionLock()
    {
        m_pMutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
        ISE_ASSERT(m_pMutex, "CIseSectionLock: Section Lock create failed!"); 
        memset( m_pMutex, 0, sizeof( pthread_mutex_t ) );

        pthread_mutexattr_t attr;
        ISE_ASSERT(pthread_mutexattr_init( &attr ) == 0, "Lock ATTR Init failed!");
        pthread_mutexattr_settype( &attr, PTHREAD_MUTEX_RECURSIVE );

        ISE_ASSERT(pthread_mutex_init( m_pMutex, &attr ) == 0, "Section Lock Init Failed!");

        pthread_mutexattr_destroy( &attr );
        ISE_DEBUG_TRACE( "CIseSectionLock: Lock Created %p", m_pMutex );
    }

    CIseSectionLock::~CIseSectionLock()
    {
        ISE_DEBUG_TRACE("CIseSectionLock::~CIseSectionLock. %p>>", m_pMutex);
        if(m_pMutex)
        {
            pthread_mutex_destroy( m_pMutex );

            free(m_pMutex);
            m_pMutex = ISE_NULL;
        }
    }

    CIseSectionLock::CIseSectionLock(const CIseSectionLock& section_lock)
    {
        ISE_ASSERT(section_lock.m_pMutex, "Invalid Lock!");
        m_pMutex = section_lock.m_pMutex;
    }

    CIseSectionLock& CIseSectionLock::operator=(const CIseSectionLock& section_lock)
    {
        ISE_ASSERT(section_lock.m_pMutex, "Invalid Lock!");

        m_pMutex = section_lock.m_pMutex;
    }

    ISE_VOID CIseSectionLock::Enter()
    {
        //ISE_DEBUG_TRACE("CIseSectionLock::Enter %p>>", m_pMutex);
        ISE_ASSERT(m_pMutex, "Invalid Lock!");
        
        //ISE_DEBUG_TRACE("CIseSectionLock::Locking %p>>", m_pMutex);
        pthread_mutex_lock(m_pMutex);

        //ISE_DEBUG_TRACE("CIseSectionLock::Locked %p>>", m_pMutex);
    }

    ISE_VOID CIseSectionLock::Leave()
    {
        //ISE_DEBUG_TRACE("CIseSectionLock::Leaveing %p>>", m_pMutex);
        ISE_ASSERT(m_pMutex, "Invalid Lock!");

        pthread_mutex_unlock(m_pMutex);
        //ISE_DEBUG_TRACE("CIseSectionLock::Leaved %p>>", m_pMutex);
    }

    ISE_BOOL CIseSectionLock::TryEnter()
    {
        ISE_ASSERT(m_pMutex, "Invalid Lock!");

        if( pthread_mutex_trylock( m_pMutex ) == 0 )
        {
            return ISE_TRUE;
        }

        return ISE_FALSE;
    }

    CIseLocker::CIseLocker(CIseSectionLock &section_lock)
                   :m_SectionLock(section_lock)
    {
        m_bLocked = ISE_FALSE;

        Lock();
    }

    CIseLocker::~CIseLocker()
    {
        if(m_bLocked)
        {
            Unlock();
        }
    }

    ISE_VOID CIseLocker::Lock()
    {
        m_SectionLock.Enter();

        assert(m_bLocked == ISE_FALSE);
        m_bLocked = ISE_TRUE;
    }

    ISE_VOID CIseLocker::Unlock()
    {
        assert(m_bLocked == ISE_TRUE);
        m_bLocked = ISE_FALSE;
    
        m_SectionLock.Leave();
    }
}
