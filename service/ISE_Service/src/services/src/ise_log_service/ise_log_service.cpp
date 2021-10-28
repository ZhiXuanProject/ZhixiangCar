#include "ise_service_msg.h"
#include "ise_log_service.h"
#include "ise_service_manager.h"

namespace ise_service
{
    CIseLogService::CIseLogService():CIseServiceBase(ISE_LOG_SERVICE_ID,"CIseLogService")
    {
        ISE_INFO_TRACE("This is ISE Log Service...");
    }

    CIseLogService::~CIseLogService()
    {
        ISE_INFO_TRACE("This is ISE Log Service distruct...");
    }

    ISE_BOOL CIseLogService::OnInit()
    {

        ISE_INFO_TRACE("CIseLogService initialized!");
        return ISE_TRUE;
    }

    ISE_VOID CIseLogService::OnUninit()
    {

        ISE_INFO_TRACE("CIseLogService un-initialized!");
    }

    ISE_VOID CIseLogService::OnMessage(const ISE_MSG_HEAD *pIseMsg)
    {
        ISE_INFO_TRACE("Received Message: message ID = 0x%04X", pIseMsg->msg_id);
        ISE_MSG_HEAD *pMsgHead = const_cast<ISE_MSG_HEAD *>(pIseMsg);
        switch (pIseMsg->msg_id) {
        case 1:
        {
            //强转
            break;
        }
        case 2:
        {
            //强转
            break;
        }
        default:
            break;
        }
        canTestDemo *pMsgHead1 = dynamic_cast<canTestDemo *>(pMsgHead);
        qDebug()<<__FUNCTION__<<"CIseMediaService msg------:"<<pMsgHead1->str;
        delete pMsgHead1;
    }

}
