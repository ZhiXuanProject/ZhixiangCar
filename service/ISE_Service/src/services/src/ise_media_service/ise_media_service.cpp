#include "ise_media_service.h"
#include "ise_service_msg.h"
#include "ise_service_manager.h"

namespace ise_service
{
    using namespace ise_common;

    CIseMediaService::CIseMediaService():CIseServiceBase(ISE_MEDIA_SERVICE_ID,"CIseMediaService")
    {
        ISE_INFO_TRACE("This is ISE Media Service...");
    }

    CIseMediaService::~CIseMediaService()
    {
        ISE_INFO_TRACE("This is ISE Media Service distruct...");
    }

    ISE_BOOL CIseMediaService::OnInit()
    {

        ISE_INFO_TRACE("CIseMediaService initialized!");
        return ISE_TRUE;
    }

    ISE_VOID CIseMediaService::OnUninit()
    {

        ISE_INFO_TRACE("CIseMediaService un-initialized!");
    }

    ISE_VOID CIseMediaService::OnMessage(const ISE_MSG_HEAD *pIseMsg)
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
