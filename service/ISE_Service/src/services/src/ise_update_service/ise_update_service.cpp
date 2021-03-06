#include "ise_update_service.h"
#include "ise_service_msg.h"
#include "ise_service_manager.h"

namespace ise_service
{
    using namespace ise_common;

    CIseUpdateService::CIseUpdateService():CIseServiceBase(ISE_UPDATE_SERVICE_ID,"CIseUpdateService")
    {
        ISE_INFO_TRACE("This is ISE Update Service...");
    }

    CIseUpdateService::~CIseUpdateService()
    {
        ISE_INFO_TRACE("This is ISE Update Service distruct...");
    }

    ISE_BOOL CIseUpdateService::OnInit()
    {

        ISE_INFO_TRACE("CIseUpdateService initialized!");
        return ISE_TRUE;
    }

    ISE_VOID CIseUpdateService::OnUninit()
    {

        ISE_INFO_TRACE("CIseUpdateService un-initialized!");
    }

    ISE_VOID CIseUpdateService::OnMessage(const ISE_MSG_HEAD *pIseMsg)
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
        qDebug()<<__FUNCTION__<<"CIseUpdateService msg------:"<<pMsgHead1->str;
        delete pMsgHead1;
    }

}
