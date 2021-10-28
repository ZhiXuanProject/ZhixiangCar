#include "ise_service_manager.h"
#include "ise_can_service.h"
#include "ise_service_msg.h"
#include <QDebug>


extern ISE_BOOL ExtSendIseServiceMsg(ISE_MSG_HEAD* pServiceMsg);

namespace ise_service
{
    extern ISE_BOOL ExtSendIseServiceMsg(ISE_UINT16 service_id, ISE_MSG_HEAD *pServiceMsg);
    CIseCanService::CIseCanService():CIseServiceBase(ISE_CAN_SERVICE_ID,"CIseCanService")
    {
        ISE_INFO_TRACE("This is ISE Can Service...");
    }

    CIseCanService::~CIseCanService()
    {
        ISE_INFO_TRACE("This is ISE Can Service distruct...");
    }

    ISE_BOOL CIseCanService::OnInit()
    {
        ISE_INFO_TRACE("CIseCanService initialized!");
		//Call the SendIseServiceMsg to start OnMessage to handle internal messag for first time
        //ISE_UINT8 msg_len   = 100;
        //ISE_UINT8 *pMsgBuff = new ISE_UINT8[msg_len + 1];
        //pMsgBuff[0] = msg_len;
        //pMsgBuff[1] = 88;
        //pMsgBuff[2] = 78;
        //ISE_MSG_HEAD *pMsgHead = new(pMsgBuff) ISE_MSG_HEAD();
        //demo
        for(int i = 0 ; i < 1000;i++)
        {
            canTestDemo * demo =  new canTestDemo(MESSAGE_ID_STATION_MANAGER);
            demo->speed = i;
            demo->str = "a"+QString::number(i);
            //发送给自己基类队列
            SendIseServiceMsg(dynamic_cast<ISE_MSG_HEAD*>(demo));
        }

        for(int j = 0 ; j< 1000 ;j++)
        {
            canTestDemo * demo =  new canTestDemo(MESSAGE_ID_STATION_MANAGER);
            demo->speed = j;
            demo->str = "b"+QString::number(j);
            //全局发送，可任意发送给其他线程
            ExtSendIseServiceMsg(ISE_DBUS_SERVICE_ID,dynamic_cast<ISE_MSG_HEAD*>(demo));
        }

        for(int j = 0 ; j< 1000 ;j++)
        {
            canTestDemo * demo =  new canTestDemo(MESSAGE_ID_STATION_MANAGER);
            demo->speed = j;
            demo->str = "c"+QString::number(j);
            //全局发送，可任意发送给其他线程
            ExtSendIseServiceMsg(ISE_UDP_SERVICE_ID,dynamic_cast<ISE_MSG_HEAD*>(demo));
        }

        for(int j = 0 ; j< 1000 ;j++)
        {
            canTestDemo * demo =  new canTestDemo(MESSAGE_ID_STATION_MANAGER);
            demo->speed = j;
            demo->str = "d"+QString::number(j);
            //全局发送，可任意发送给其他线程
            ExtSendIseServiceMsg(ISE_UPDATE_SERVICE_ID,dynamic_cast<ISE_MSG_HEAD*>(demo));
        }

        for(int j = 0 ; j< 1000 ;j++)
        {
            canTestDemo * demo =  new canTestDemo(MESSAGE_ID_STATION_MANAGER);
            demo->speed = j;
            demo->str = "e"+QString::number(j);
            //全局发送，可任意发送给其他线程
            ExtSendIseServiceMsg(ISE_MEDIA_SERVICE_ID,dynamic_cast<ISE_MSG_HEAD*>(demo));
        }

        for(int j = 0 ; j< 1000 ;j++)
        {
            canTestDemo * demo =  new canTestDemo(MESSAGE_ID_STATION_MANAGER);
            demo->speed = j;
            demo->str = "f"+QString::number(j);
            //全局发送，可任意发送给其他线程
            ExtSendIseServiceMsg(ISE_WEB_SCRIBE_SERVICE_ID,dynamic_cast<ISE_MSG_HEAD*>(demo));
        }

        for(int j = 0 ; j< 1000 ;j++)
        {
            canTestDemo * demo =  new canTestDemo(MESSAGE_ID_STATION_MANAGER);
            demo->speed = j;
            demo->str = "g"+QString::number(j);
            //全局发送，可任意发送给其他线程
            ExtSendIseServiceMsg(ISE_LOG_SERVICE_ID,dynamic_cast<ISE_MSG_HEAD*>(demo));
        }

        for(int j = 0 ; j< 1000 ;j++)
        {
            canTestDemo * demo =  new canTestDemo(MESSAGE_ID_STATION_MANAGER);
            demo->speed = j;
            demo->str = "g"+QString::number(j);
            //全局发送，可任意发送给其他线程
            ExtSendIseServiceMsg(ISE_MAP_SERVICE_ID,dynamic_cast<ISE_MSG_HEAD*>(demo));
        }
        return ISE_TRUE;
    }

    ISE_VOID CIseCanService::OnUninit()
    {

        ISE_INFO_TRACE("CIseCanService un-initialized!");
    }

    ISE_VOID CIseCanService::OnMessage(const ISE_MSG_HEAD *pServiceMsg)
    {
        ISE_INFO_TRACE("Received Message: message ID = 0x%04X", pServiceMsg->msg_id);
        ISE_MSG_HEAD *pMsgHead = const_cast<ISE_MSG_HEAD *>(pServiceMsg);
        switch (pServiceMsg->msg_id) {
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
        qDebug()<<__FUNCTION__<<"CIseCanService msg------:"<<pMsgHead1->str;
        delete pMsgHead1;
    }
}
