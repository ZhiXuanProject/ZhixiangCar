#ifndef __ISE_UTILS_H__
#define __ISE_UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#include <vector>
#include <queue>
#include <string>
#include <sys/types.h>
#include "ise_singleton.h"

namespace ise_common
{
    typedef char                 ISE_CHAR;       /* Size should be 1 byte. */
    typedef unsigned char        ISE_BYTE;       /* Size should be 1 byte. */
    typedef signed char          ISE_INT8;       /* Size should be 1 bytes. */
    typedef unsigned char        ISE_UINT8;      /* Size should be 1 bytes. */
    typedef signed short         ISE_INT16;      /* Size should be 2 bytes. */
    typedef unsigned short       ISE_UINT16;     /* Size should be 2 bytes. */
    typedef signed long          ISE_INT32;      /* Size should be 4 bytes. */
    typedef unsigned long        ISE_UINT32;     /* Size should be 4 bytes. */
    typedef signed long long     ISE_INT64;      /* Size should be 8 bytes. */
    typedef unsigned long long   ISE_UINT64;     /* Size should be 8 bytes. */
    typedef signed int           ISE_INT;        /* Size depends on compiler. */
    typedef unsigned int         ISE_UINT;       /* Size depends on compiler. */
    typedef ISE_INT64            ISE_INT_PTR;    /* Size depends on target platform, current is for 64bit. */
    typedef ISE_UINT64           ISE_UINT_PTR;   /* Size depends on target platform, current is for 64bit. */
    typedef float                ISE_FLOAT;      /* Size should be 4 bytes. */
    typedef double               ISE_DOUBLE;     /* Size should be 8 bytes. */

    typedef ISE_INT64             ISE_TIME;
    typedef void                  ISE_VOID;
    typedef ISE_INT               ISE_BOOL;
    typedef ISE_UINT32            ISE_SIZE;

    #define ISE_NONE              0
    #define ISE_NULL              NULL
    #define ISE_TRUE              1
    #define ISE_FALSE             0
    #define ISE_INFINITE          ( ( ISE_SIZE )~0 )
    #define ISE_INVALID_TIME      ( ( ISE_TIME )~0 )

    #define ISE_COUNT_OF( _Array ) ( sizeof( _Array ) / sizeof( ( _Array )[0] ) )

    #define                      ISEOSPER_INFINITE          ( ( unsigned long )~0 )
    #define                      ISE_EMPTY_STRING           ""

    #define                      ISE_UNUSED(param)          (void)param

    typedef ISE_INT               ISE_HSOCKET;
    #define ISE_INVALID_SOCKET    ( ( ISE_HSOCKET )~0 )
    #define ISE_SD_BOTH           SHUT_RDWR
    #define ISE_SD_RECEIVE        SHUT_RD
    #define ISE_SD_SEND           SHUT_WR

    #define _ISE_ALIGN( N )       __attribute__((aligned( N )))
    #define _ISE_PACKED           __attribute__((packed))

//#define ISE_BIG_ENDIAN_TYPE
#if defined( ISE_BIG_ENDIAN_TYPE )  /* Big endian */
    #define ISE_MAKE16WORD( _Low, _High ) ((ISE_UINT16)(((ISE_UINT8)(((ISE_UINT)( _High )) & 0xFF)) | ((ISE_UINT16)((ISE_UINT8)(((ISE_UINT)( _Low )) & 0xFF))) << 8))
    #define ISE_LOBYTE( _Value )          ((ISE_UINT8)(((ISE_UINT16)( _Value ) >> 8) & 0xFF)) 
    #define ISE_HIBYTE( _Value )          ((ISE_UINT8)(((ISE_UINT16)( _Value )) & 0xFF)) 
#else
    #define ISE_MAKE16WORD( _Low, _High ) ((ISE_UINT16)(((ISE_UINT8)(((ISE_UINT)( _Low )) & 0xFF)) | ((ISE_UINT16)((ISE_UINT8)(((ISE_UINT)( _High )) & 0xFF))) << 8))
    #define ISE_LOBYTE( _Value )          ((ISE_UINT8)(((ISE_UINT16)( _Value )) & 0xFF)) 
    #define ISE_HIBYTE( _Value )          ((ISE_UINT8)(((ISE_UINT16)( _Value ) >> 8) & 0xFF)) 
#endif

    typedef struct _IseMessage
    {
        ISE_UINT32           op_code;
        ISE_UINT32           param;
        ISE_UINT32           extra_param;
        ISE_VOID            *p_extra_param;
    } IseMessage;

    /*Ise Thread Event*/
    class CIseEvent
    {
    public:
        CIseEvent(std::string event_name);
        CIseEvent();
        ~CIseEvent();

        //CIseEvent(const CIseEvent&) = delete;
        //CIseEvent& operator=(const CIseEvent&) = delete;

    public:
        ISE_VOID Signal();
        ISE_VOID Reset();
        ISE_BOOL Wait(unsigned long wait_time_ms /* = ISEOSPER_INFINITE*/);

    private:
        mutable pthread_cond_t  *m_pCond;
        mutable pthread_mutex_t *m_pMutex;
        ISE_BOOL                  m_bSignaled;
        std::string                   m_strEventName;
    };

    /*Ise Section Lock*/
    class CIseSectionLock
    {
    public:
        CIseSectionLock();
        ~CIseSectionLock();

        CIseSectionLock(const CIseSectionLock&);
        CIseSectionLock& operator=(const CIseSectionLock&);

    public:
        ISE_VOID                Enter();
        ISE_VOID                Leave();
        ISE_BOOL                TryEnter();

    private:
        mutable pthread_mutex_t  *m_pMutex;
    };

    class CIseLocker
    {
    public:
        CIseLocker() = delete;
        CIseLocker(CIseSectionLock &section_Lock);
        ~CIseLocker();
    
    public:
        ISE_VOID Lock();
        ISE_VOID Unlock();

    private:
        CIseSectionLock    &m_SectionLock;
        ISE_BOOL                 m_bLocked;
    };

} // namespace ise_common


#endif  /*__ISE_UTILS_H__*/
