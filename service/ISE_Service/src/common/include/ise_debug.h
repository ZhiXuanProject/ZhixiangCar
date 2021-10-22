#ifndef ISE_DEBUG_H
#define ISE_DEBUG_H

#include "ise_utils.h"
#include <execinfo.h>

/**
 * @brief If source code is in debug mode(ISE_DEBUG is enabled), this project will:
 *        1: Redirect the output to screen.
 *        2: Override the output leve to DEBUG.
 *
 *        It's strongly recommanded to follow the trace level rule strictly.
*/
namespace ise_common
{
    #define     ISE_SERVICE_DEBUG
	#define     LOG_FILE_NAME "IseServiceLog.txt"
    #ifdef      ISE_SERVICE_DEBUG
    #define     OVERRIDE_NODE_VERBOSITY_LEVEL
    #endif    /*ISE_SERVICE_DEBUG*/
    typedef enum _ISETraceType
    {
        ISE_DEBUG      = 0,
        ISE_INFO       = 1,
        ISE_WARN       = 2,
        ISE_ERROR      = 3,
        ISE_FATAL      = 4
    } ISETraceType;

    #define     USE_ISE_TRACE

    #ifdef  ISE_SERVICE_DEBUG
    #ifdef  USE_ISE_TRACE
    #define ISE_DEBUG_TRACE(_Format, ...)    ISE_TraceOut(ISE_DEBUG, __FILE__, __LINE__, _Format, ##__VA_ARGS__)
    #define ISE_INFO_TRACE(_Format, ...)     ISE_TraceOut(ISE_INFO, __FILE__, __LINE__, _Format, ##__VA_ARGS__)
    #define ISE_WARN_TRACE(_Format, ...)     ISE_TraceOut(ISE_WARN, __FILE__, __LINE__, _Format, ##__VA_ARGS__)
    #else
    #define ISE_DEBUG_TRACE(_Format, ...)    ROS_DEBUG(_Format, ##__VA_ARGS__)
    #define ISE_INFO_TRACE(_Format, ...)     ROS_INFO(_Format, ##__VA_ARGS__)
    #define ISE_WARN_TRACE(_Format, ...)     ROS_WARN(_Format, ##__VA_ARGS__)
    #endif

    #define ISE_ASSERT(_Expression, ...)     ( ( _Expression ) ? ( ( ISE_VOID )0 ) : \
                                              ISE_ASSERT_FAILED(#_Expression, ##__VA_ARGS__) )

    #define ISE_VERIFY(_Expression, ...)     ( ( _Expression ) ? ISE_TRUE : \
                                              ISE_VERIFY_FAILED(#_Expression, ##__VA_ARGS__) )

    #else   /*ISE_SERVICE_DEBUG*/
    #define ISE_DEBUG_TRACE(_Format, ...)    ((ISE_VOID)0)
    #define ISE_INFO_TRACE(_Format, ...)     ((ISE_VOID)0)
    #define ISE_WARN_TRACE(_Format, ...)     ((ISE_VOID)0)

    #define ISE_ASSERT( _Expression, ... )   ( ( ISE_VOID )0 )
    #define ISE_VERIFY( _Expression, ... )   ( ( ISE_VOID ) ( _Expression ) )
    #endif  /*ISE_SERVICE_DEBUG*/

    /*ERROR and FATAL trace MUST output in any cases!*/
    #ifdef  USE_ISE_TRACE
    #define ISE_ERROR_TRACE(_Format, ...)     ISE_TraceOut(ISE_ERROR, __FILE__, __LINE__, _Format, ##__VA_ARGS__)
    #define ISE_FATAL_TRACE(_Format, ...)     ISE_TraceOut(ISE_FATAL, __FILE__, __LINE__, _Format, ##__VA_ARGS__)
    #else
    #define ISE_ERROR_TRACE(_Format, ...)    ROS_ERROR(_Format, ##__VA_ARGS__)
    #define ISE_FATAL_TRACE(_Format, ...)    ROS_FATAL(_Format, ##__VA_ARGS__)
    #endif

    //#define ISE_ERROR_TRACE(_Format, ...)    printf(_Format, ##__VA_ARGS__); printf("\r\n")
    //#define ISE_FATAL_TRACE(_Format, ...)    printf(_Format, ##__VA_ARGS__); printf("\r\n")

    ISE_VOID ISE_ASSERT_FAILED(const ISE_CHAR *expression, ...);

    ISE_BOOL ISE_VERIFY_FAILED(const ISE_CHAR *expression, ...);

    ISE_VOID SetDebugLevel(ISETraceType level);

    ISETraceType GetDebugLevel();

    ISE_VOID DumpCallStack();

    ISE_VOID DebugSignalHandler(ISE_INT singal);

    ISE_VOID ISE_DEBUG_INIT(std::string strDebugLevel);

#ifdef USE_ISE_TRACE
    ISE_VOID ISE_TraceOut(ISETraceType type, const ISE_CHAR *file_path, ISE_INT lineNo, const ISE_CHAR *format, ...);	
#endif
}


#endif  /*__ISE_DEBUG_H__*/
