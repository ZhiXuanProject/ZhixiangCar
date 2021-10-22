#include "ise_service_manager.h"
#include "ise_can_service.h"
#include "ise_service_msg.h"

namespace ise_service
{
    using namespace ise_common;
    extern ISE_BOOL ExtSendIseServiceMsg(ISE_UINT16 service_id, ISE_MSG_HEAD *pServiceMsg);
    CIseCanService::CIseCanService()
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
        ISE_CAN_COMMAND *pMsgHead = new ISE_CAN_COMMAND();
        pMsgHead->reserved = 99;
        SendIseServiceMsg(pMsgHead);
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
        ISE_CAN_COMMAND *pMsgHead1 = static_cast<ISE_CAN_COMMAND *>(pMsgHead);
        //delete pServiceMsg;
        delete pMsgHead1;
    }
}
