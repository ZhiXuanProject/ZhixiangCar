#include "ise_debug.h"

#ifdef  UNW_LOCAL_ONLY
extern "C"
{
#include <libunwind.h>
}
#endif

#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <assert.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdarg.h>
#include <fstream>
#include <limits.h>



namespace ise_common
{
    #define MAX_TIMESTAMP_LEN    64
    #define MAX_FILENAME_LEN     128
    #define MAX_FORMAT_LEN       128
    #define MAX_LOG_LEN          512

    using namespace std;

    typedef enum
    {
        ISE_TCOLOR_DEFAULT = 0,
        ISE_TCOLOR_RED     = 31,
        ISE_TCOLOR_BLUE    = 34,
        ISE_TCOLOR_GREEN   = 32,
        ISE_TCOLOR_WHITE   = 37,
        ISE_TCOLOR_YELLOW  = 33
    } ISE_CONSOLE_COLOR;

#ifdef USE_ISE_TRACE
    pthread_mutex_t  debug_level_lock;
#endif /*USE_ISE_TRACE*/
    ISETraceType      debug_level = ISE_DEBUG;

	static ISE_VOID GetLogFilePath(ISE_CHAR* szPath)  
    {  
        getcwd(szPath, MAX_FILENAME_LEN);  
        strcat(szPath,"/");  
        strcat(szPath,LOG_FILE_NAME);
    }  
    static ISE_VOID SetConsoleTextColor(ISE_CONSOLE_COLOR color)
    {
        printf("\e[%dm", (int)(color));
    }

    static ISE_VOID ResetConsoleTextColor()
    {
        printf("\033[0m");
    }

    static ISE_INT GetFileName(const ISE_CHAR *pFilePath, ISE_CHAR *pFileName)
    {
        ISE_CHAR  *pFile = const_cast<ISE_CHAR  *>(pFilePath);
        ISE_CHAR  *pName = strrchr(pFile,'/');
        if(pName == ISE_NULL)
        {
            return 0;
        }

        pName = pName + 1;
        if(strlen(pName) <= 0)
        {
            return 0;
        }

        memcpy(pFileName, pName, strlen(pName));
        return strlen(pName);
    }

    static ISE_INT GetTimeStamp(ISE_CHAR *pTimeStamp)
    {
        time_t     now;
        struct tm *tm_now;

        time(&now);
        tm_now = localtime(&now);

        struct timeval tv;
        gettimeofday(&tv, NULL);
        ISE_INT64 time_ms = tv.tv_usec/1000;

        return snprintf(pTimeStamp, MAX_TIMESTAMP_LEN, "[%d-%02d-%02d %02d:%02d:%02d %03lld]",
                        tm_now->tm_year + 1900,
                        tm_now->tm_mon + 1,
                        tm_now->tm_mday,
                        tm_now->tm_hour,
                        tm_now->tm_min,
                        tm_now->tm_sec,
                        time_ms);
    }

    ISE_VOID ISE_ASSERT_FAILED(const ISE_CHAR *expression, ...)
    {
        assert(expression);

        ISE_ERROR_TRACE("ASSERT FAILED! Expression: %s!", expression);

        va_list args;
        va_start( args, expression );

        const ISE_CHAR *format = va_arg( args, const ISE_CHAR* );
        if(format && (strcmp( format, "" ) != 0) )
            ISE_ERROR_TRACE(format, args);

        va_end( args );

        DumpCallStack();

        assert(ISE_FALSE);
    }

    ISE_BOOL ISE_VERIFY_FAILED(const ISE_CHAR *expression, ...)
    {
        assert(expression);

        ISE_ERROR_TRACE("Verify FAILED! Expression: %s!", expression);

        va_list args;
        va_start( args, expression );

        const ISE_CHAR *format = va_arg( args, const ISE_CHAR* );
        if(format && (strcmp( format, "" ) != 0) )
            ISE_ERROR_TRACE(format, args);

        va_end( args );

        return ISE_FALSE;
    }

#ifdef USE_ISE_TRACE
    ISE_VOID ISE_TraceOut(ISETraceType type, const ISE_CHAR *file_path, ISE_INT lineNo, const ISE_CHAR *format, ...)
    {
        ISE_CHAR          buf[MAX_LOG_LEN];
        ISE_CHAR          finalFormat[MAX_FORMAT_LEN];
        ISE_CHAR          fileName[MAX_FILENAME_LEN] = {'\0'};
        ISE_CHAR          timeStamp[MAX_TIMESTAMP_LEN] = {'\0'};
        const ISE_CHAR   *level_str     = "";
        ISE_CONSOLE_COLOR level_color   = ISE_TCOLOR_DEFAULT;
        //ISE_CHAR          file_name[32] = {'\0'};

        switch(type)
        {
            case ISE_DEBUG:
            {
                level_str   = "[DEBUG]";
                level_color = ISE_TCOLOR_GREEN;

                break;
            }
            case ISE_INFO:
            {
                level_str   = "[ INFO]";
                level_color = ISE_TCOLOR_GREEN;

                break;
            }
            case ISE_WARN:
            {
                level_str   = "[ WARN]";
                level_color = ISE_TCOLOR_YELLOW;

                break;
            }
            case ISE_ERROR:
            {
                level_str   = "[ERROR]";
                level_color = ISE_TCOLOR_RED;

                break;
            }
            case ISE_FATAL:
            {
                level_str   = "[FATAL]";
                level_color = ISE_TCOLOR_RED;

                break;
            }
            default:
            {
                level_str   = "[UNKNOW]";
                level_color = ISE_TCOLOR_WHITE;

                break;
            }
        }

        GetTimeStamp(timeStamp);

        ISE_INT len = GetFileName(file_path, fileName);
        if(len > 0)
        {
            snprintf(finalFormat, ISE_COUNT_OF( finalFormat ), "%s - %s %s(%d):%s", level_str, timeStamp, fileName, lineNo, format);
        }
        else
        {
            snprintf(finalFormat, ISE_COUNT_OF( finalFormat ), "%s - %s %s", level_str, timeStamp, format);
        }

        finalFormat[ ISE_COUNT_OF( finalFormat ) - 1 ] = '\0';

        va_list args;
        va_start( args, format );
        if( vsnprintf( buf, ISE_COUNT_OF( buf ), finalFormat, args ) != -1 )
        {
            buf[ ISE_COUNT_OF( buf ) - 1 ] = '\0';

            pthread_mutex_lock(&debug_level_lock);
            if(type >= debug_level)
            {
                SetConsoleTextColor(level_color);
                printf( "%s\r\n", buf );
                ResetConsoleTextColor();
				ISE_CHAR szPath[MAX_FILENAME_LEN] = {0};  
                GetLogFilePath(szPath);
                using namespace std;
				ofstream fout(szPath,ios::app);
				fout.seekp(ios::end);
				fout << buf <<endl;
				fout.close();
            }
            pthread_mutex_unlock(&debug_level_lock);

            fflush(stdout);
        }
    }
#endif

    ISE_VOID SetDebugLevel(ISETraceType level)
    {
#ifdef USE_ISE_TRACE
        pthread_mutex_lock(&debug_level_lock);
        if(debug_level != level)
        {
            debug_level = level;
            ISE_WARN_TRACE("Changing Debug output level to %d. PLEASE NOTE: debug level in ISE TRACE is global setting. ", level);
        }
        pthread_mutex_unlock(&debug_level_lock);
#endif /*USE_ISE_TRACE*/
    }

    ISETraceType GetDebugLevel()
    {
        ISETraceType level;
#ifdef USE_ISE_TRACE
        pthread_mutex_lock(&debug_level_lock);
#endif
        level = debug_level;
#ifdef USE_ISE_TRACE
        pthread_mutex_unlock(&debug_level_lock);
#endif

        return level;
    }

    ISE_VOID DumpCallStack()
    {
        SetConsoleTextColor(ISE_TCOLOR_RED);
#ifdef UNW_LOCAL_ONLY
        unw_cursor_t  cursor;
        unw_context_t context;

        //printf("==============================CALLSTACK START==============================\r\n");
        unw_getcontext(&context);
        unw_init_local(&cursor, &context);
        while(unw_step(&cursor) > 0)
        {
            unw_word_t offset;
            unw_word_t pc;

            unw_get_reg(&cursor, UNW_REG_IP, &pc);
            if(pc == 0)
            {
                break;
            }

            ISE_CHAR sym[256];
            if(unw_get_proc_name(&cursor, sym, sizeof(sym), &offset) == 0)
            {
                ISE_CHAR *namePtr = sym;
                ISE_INT   status;
                ISE_CHAR *demangled = abi::__cxa_demangle(sym, nullptr, nullptr, &status);
                if (status == 0) 
                {
                    namePtr = demangled;
                }
                printf("(%s+0x%lx)\r\n", namePtr, offset);
                printf("0x%lX: %s + 0x%lX\r\n", pc, namePtr, offset);
            }
            else
            {
                printf("0x%lX: \33[4munable to obtain symbol name!\033[0m\r\n", pc);
            }            
        }

        //ISE_ERROR_TRACE("==============================CALLSTACK  END==============================");
#else

        ISE_VOID *pSZStack[256] = {ISE_NULL};
        ISE_INT   stack_num     = backtrace( pSZStack, 256 );
        if(stack_num > 0)
        {
            ISE_CHAR** stack_trace = backtrace_symbols( pSZStack, stack_num );
            for ( int i = 0; i < stack_num; ++i ) 
            {
                fprintf( stderr, "%s\n", stack_trace[i] );
            }
            free(stack_trace);
        }
        else
        {
            fprintf( stderr, "no stack trace: %d", stack_num );
        }
#endif
        ResetConsoleTextColor();
    }

    ISE_VOID DebugSignalHandler(ISE_INT singal)
    {
        sleep(3);

        string strSingalReason;
        switch (singal)
        {
        case SIGSEGV:
            strSingalReason = "SEGMENT FAULT";
            break;
        case SIGABRT:
            strSingalReason = "SYSTEM ABORT";
        case SIGFPE:
            strSingalReason = "ISEOGRAM ERROR";
        case SIGSYS:
            strSingalReason = "SYSTE ERROR";
        case SIGBUS:
            strSingalReason = "BUS ERROR";
        case SIGILL:
            strSingalReason = "ILLEAGE COMMAND";
        default:
            return;
        }

        printf("===================%s===================\r\n", strSingalReason.c_str() );
        //fprintf( stderr, "===================%s===================\r\n", strSingalReason.c_str() );
        DumpCallStack();
        //fprintf( stderr, "Program Exiting....\r\n");
        sleep(3);
        exit(0);
    }

    ISE_VOID ISE_DEBUG_INIT(std::string strDebugLevel)
    {
        signal( SIGPIPE, SIG_IGN );

        signal( SIGSEGV, DebugSignalHandler );
        signal( SIGABRT, DebugSignalHandler );
        signal( SIGFPE,  DebugSignalHandler );
        signal( SIGSYS,  DebugSignalHandler );
        signal( SIGBUS,  DebugSignalHandler );
        signal( SIGILL,  DebugSignalHandler );

#ifdef USE_ISE_TRACE
        /*Initializing Debug Lock*/
        memset( &debug_level_lock, 0, sizeof( pthread_mutex_t ) );
        pthread_mutexattr_t attr;
        pthread_mutexattr_init( &attr );
        pthread_mutexattr_settype( &attr, PTHREAD_MUTEX_RECURSIVE );
        pthread_mutex_init( &debug_level_lock, &attr );
        pthread_mutexattr_destroy( &attr );
#endif /*USE_ISE_TRACE*/

        ISETraceType level = ISE_INFO;
        if(strDebugLevel.compare("debug") == 0)
        {
            level = ISE_DEBUG;
        }
        else if(strDebugLevel.compare("info") == 0)
        {
            level = ISE_INFO;
        }
        else if(strDebugLevel.compare("warn") == 0)
        {
            level = ISE_WARN;
        }
        else if(strDebugLevel.compare("error") == 0)
        {
            level = ISE_ERROR;
        }
        else if(strDebugLevel.compare("fatal") == 0)
        {
            level = ISE_FATAL;
        }

        SetDebugLevel(level);
    }
}
