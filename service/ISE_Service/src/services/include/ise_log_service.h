#ifndef ISE_LOG_SERVICE_H
#define ISE_LOG_SERVICE_H

#include "ise_service_base.h"

namespace ise_service
{
    class CIseLogService : public CIseServiceBase, public CSingleton<CIseLogService>
    {
    public:
        CIseLogService();
        virtual ~CIseLogService();

    /*Overrided functions*/
    protected:
        ISE_BOOL       OnInit();
        ISE_VOID       OnUninit();

    public:
        virtual ISE_VOID       OnMessage(const ISE_MSG_HEAD *pPepMsg);

	private:
        ise_common::CIseQueue<ISE_MSG_HEAD *>          m_LogMessageQueue;
    };
}

#endif  /*__ISE_LOG_SERVICE_H__*/
