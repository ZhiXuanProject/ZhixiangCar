#ifndef ISE_QUEUE_H
#define ISE_QUEUE_H

#include "ise_utils.h"
#include "ise_debug.h"

namespace ise_common
{
    template<typename T>
    class CIseQueue
    {
    private:
        CIseSectionLock     m_QueueLock;
        CIseEvent           m_QueueEvent;
        CIseEvent           m_QueueFullEvent;
        std::queue<T>       m_Queue;
        ISE_UINT32          m_MaxSize;
    
    public:
        CIseQueue()
        {
            //ISE_DEBUG_TRACE("CIseQueue::CIseQueue() >>");
            m_MaxSize = ISE_INFINITE;
        }

        CIseQueue(ISE_UINT max_size)
        {
            //ISE_DEBUG_TRACE("CIseQueue::CIseQueue() >>");
            if(max_size <= 1)
            {
                ISE_WARN_TRACE("Invalid queue size[%d]! Resize to infinite queue size!", max_size);
                m_MaxSize = ISE_INFINITE;
            }
            else
            {
                m_MaxSize = max_size;
            }
        }

        CIseQueue(const CIseQueue&) = delete;
        CIseQueue& operator=(const CIseQueue&) = delete;

        ~CIseQueue()
        {
            //ISE_DEBUG_TRACE("CIseQueue::~CIseQueue() >>");
        }
    
    public:
        ISE_VOID push(T data)
        {
            if(m_MaxSize == ISE_INFINITE)
            {
                CIseLocker locker(m_QueueLock);
                if(m_Queue.empty())
                {
                    m_Queue.push(data);
                    m_QueueEvent.Signal();
                }
                else
                {
                    m_Queue.push(data);
                }
            }
            else
            {
                if( queue_size() >= m_MaxSize)
                {
                    ISE_DEBUG_TRACE("Queue is full[max size = %ld]. Waiting for an empty slot...", m_MaxSize);
                    if(m_QueueFullEvent.Wait(1000) == ISE_FALSE)
                    {
                        ISE_ERROR_TRACE("Fail to wait for an empty signal!!!!");
                    }

                    CIseLocker locker(m_QueueLock);
                    m_Queue.push(data);
                }
            }
        }

        ISE_BOOL pop(T &data, ISE_UINT32 wait_time_ms)
        {
            if(is_empty())
            {
                if(m_QueueEvent.Wait(wait_time_ms) == ISE_FALSE)
                {
                    return ISE_FALSE;
                }

                CIseLocker locker(m_QueueLock);
                ISE_ASSERT(m_Queue.size() > 0, "Unexpected empty queue!");

                data = std::move(m_Queue.front());
                m_Queue.pop();

                return ISE_TRUE;
            }

            CIseLocker locker(m_QueueLock);

            if(m_MaxSize == ISE_INFINITE)
            {
                /*Infinite queue size. Push the data anyway.*/
                ISE_ASSERT(m_Queue.size() > 0, "Unexpected empty queue!");

                data = std::move(m_Queue.front());
                m_Queue.pop();
            }
            else
            {
                if(m_Queue.size() >= m_MaxSize)
                {
                    ISE_ASSERT(m_Queue.size() > 0, "Unexpected empty queue!");

                    data = std::move(m_Queue.front());
                    m_Queue.pop();
                    
                    /*The Queue is full, there might be someone waiting for an empty slot. Signal it.*/
                    m_QueueFullEvent.Signal();
                }
                else
                {
                    ISE_ASSERT(m_Queue.size() > 0, "Unexpected empty queue!");

                    data = std::move(m_Queue.front());
                    m_Queue.pop();
                }
            }
            
            return ISE_TRUE;
        }

        const T *pop(ISE_UINT32 wait_time_ms)
        {
            if(is_empty())
            {
                if(m_QueueEvent.Wait(wait_time_ms) == ISE_FALSE)
                {
                    return ISE_NULL;
                }

                ISE_DEBUG_TRACE("m_QueueEvent.Wait return TRUE.");

                CIseLocker locker(m_QueueLock);
                ISE_ASSERT(m_Queue.size() > 0, "Unexpected empty queue!");

                const T *pReturn = std::move(m_Queue.front());
                m_Queue.pop();

                return pReturn;
            }

            CIseLocker locker(m_QueueLock);

            if(m_MaxSize == ISE_INFINITE)
            {
                /*Infinite queue size. Push the data anyway.*/
                ISE_ASSERT(m_Queue.size() > 0, "Unexpected empty queue!");

                const T *pReturn = std::move(m_Queue.front());
                m_Queue.pop();

                return pReturn;
            }
            else
            {
                if(m_Queue.size() = m_MaxSize)
                {
                    ISE_ASSERT(m_Queue.size() > 0, "Unexpected empty queue!");

                    const T *pReturn = std::move(m_Queue.front());
                    m_Queue.pop();
                    
                    /*The Queue is full, there might be someone waiting for an empty slot. Signal it.*/
                    m_QueueFullEvent.Signal();

                    return pReturn;
                }
                else
                {
                    ISE_ASSERT(m_Queue.size() > 0, "Unexpected empty queue!");

                    const T *pReturn = std::move(m_Queue.front());
                    m_Queue.pop();

                    return pReturn;
                }
            }

            return ISE_NULL;
        }

        ISE_BOOL front(T *data)
        {
            if(is_empty())
            {
                return ISE_FALSE;
            }

            CIseLocker locker(m_QueueLock);
            data = m_Queue.front();
            return ISE_TRUE;
        }

        const T *front()
        {
            if(is_empty())
            {
                return ISE_NULL;
            }

            CIseLocker locker(m_QueueLock);
            return m_Queue.front();
        }

        ISE_BOOL try_pop(T *data)
        {
            if(is_empty())
            {
                return ISE_FALSE;
            }

            CIseLocker locker(m_QueueLock);
            data = m_Queue.front();
            m_Queue.pop();

            return ISE_TRUE;
        }

        const T *try_pop()
        {
            if(is_empty())
            {
                return ISE_NULL;
            }

            CIseLocker locker(m_QueueLock);
            const T *pReturn = m_Queue.front();
            m_Queue.pop();

            return pReturn;
        }

        ISE_BOOL is_empty()
        {
            CIseLocker locker(m_QueueLock);
            return m_Queue.empty();
        }

        ISE_UINT32 queue_size()
        {
            CIseLocker locker(m_QueueLock);
            return m_Queue.size();
        }

        ISE_VOID clear()
        {
            CIseLocker locker(m_QueueLock);

            std::queue<T> empty_queue;
            swap(empty_queue, m_Queue);
        }
    }; 
}

#endif  /*__ISE_QUEUE_H__*/
