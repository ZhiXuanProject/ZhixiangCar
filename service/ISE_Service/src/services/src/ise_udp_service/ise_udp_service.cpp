#include "ise_udp_service.h"
#include "ise_service_msg.h"
#include "ise_service_manager.h"

struct canTestDemo:public ISE_MSG_HEAD
{
    ISE_UINT speed;
    QString  str;
    canTestDemo(ISE_UINT8 messagID):ISE_MSG_HEAD(messagID,sizeof(canTestDemo))
    {
    }

    ~canTestDemo()
    {
    }
};

namespace ise_service
{
    using namespace ise_common;

    CIseUdpService::CIseUdpService():CIseServiceBase(ISE_UDP_SERVICE_ID,"CIseUdpService")
    {
        ISE_INFO_TRACE("This is ISE udp Service...");
    }

    CIseUdpService::~CIseUdpService()
    {
        ISE_INFO_TRACE("This is ISE udp Service distruct...");
    }

    ISE_BOOL CIseUdpService::OnInit()
    {

        ISE_INFO_TRACE("CIseUdpService initialized!");
        return ISE_TRUE;
    }

    ISE_VOID CIseUdpService::OnUninit()
    {

        ISE_INFO_TRACE("CIseUdpService un-initialized!");
    }

    ISE_VOID CIseUdpService::OnMessage(const ISE_MSG_HEAD *pIseMsg)
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
        qDebug()<<__FUNCTION__<<"CIseUdpService msg------:"<<pMsgHead1->str;
        delete pMsgHead1;
        //ISE_INFO_TRACE("Received Message: message ID = 0x%04X", pIseMsg->msg_id);
    }

}
