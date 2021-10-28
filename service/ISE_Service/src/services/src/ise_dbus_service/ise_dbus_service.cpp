#include "ise_dbus_service.h"
#include "vehiclebusproxy.h"
#include "ise_service_msg.h"
#include "ise_service_manager.h"
#include <QDebug>

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

    CIseDbusService::CIseDbusService():CIseServiceBase(ISE_DBUS_SERVICE_ID,"CIseDbusService")
    {
        ISE_INFO_TRACE("This is ISE dbus Service...");
    }

    CIseDbusService::~CIseDbusService()
    {
        ISE_INFO_TRACE("This is ISE dbus Service distruct...");
    }

    ISE_BOOL CIseDbusService::OnInit()
    {
        //初始化dbus
        VehicleDbusProxy::getInstance()->initBus();

        ISE_INFO_TRACE("CIseDbusService initialized!");
        return ISE_TRUE;
    }

    ISE_VOID CIseDbusService::OnUninit()
    {

        ISE_INFO_TRACE("CIseDbusService un-initialized!");
    }

    ISE_VOID CIseDbusService::OnMessage(const ISE_MSG_HEAD *pIseMsg)
    {
        ISE_INFO_TRACE("Received Message: message ID = 0x%04X", pIseMsg->msg_id);
        ISE_MSG_HEAD *pMsgHead = const_cast<ISE_MSG_HEAD *>(pIseMsg);
        switch (pMsgHead->msg_id) {
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
        //ISE_INFO_TRACE("CIseDbusService msg------:%s", pMsgHead1->str.toUtf8().data());
        qDebug()<<__FUNCTION__<<"CIseDbusService msg------:"<<pMsgHead1->str;
        delete pMsgHead1;
    }

}
