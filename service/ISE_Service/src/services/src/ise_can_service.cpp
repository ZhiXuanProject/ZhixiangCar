#include "ise_service_manager.h"
#include "ise_can_service.h"
namespace ise_service
{
    using namespace ise_common;

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
        return ISE_TRUE;
    }

    ISE_VOID CIseCanService::OnUninit()
    {

        ISE_INFO_TRACE("CIseCanService un-initialized!");
    }

	//This interface is called by serviceManger, this message don't need to be running in new thread
    ISE_VOID CIseCanService::OnMessage(const ISE_MSG_HEAD *pServiceMsg)
    {
        if(pServiceMsg->service_id != ISE_CAN_SERVICE_ID)
        {
            ISE_WARN_TRACE("Unexpected service id 0x%04X", pServiceMsg->service_id);
            return;
        }

        ISE_INFO_TRACE("Received Message: service ID = 0x%04X", pServiceMsg->service_id);
    }

	ISE_VOID CIseCanService::Run()
    {
        ISE_INFO_TRACE("Enter Can service thread");
		CIseCanService *pIseCanService = CIseCanService::GetInstance();
        while(ISE_TRUE)
        {
            ISE_MSG_HEAD * pServiceMsg = ISE_NULL;
            if(pIseCanService->m_CanMessageQueue.pop(pServiceMsg, ISE_INFINITE))
            {
                ISE_INFO_TRACE("Can Service Thread: Handle Message with service num: 0x%04X", pServiceMsg->service_id);

                if(pServiceMsg->service_id != ISE_SERVICE_ID_UNKNOWN)
                {
                    ISE_ERROR_TRACE("Invalid ISE Message! Ignore!!!!");
                    continue;
                }
				//
				//To do something at here, if need other service to handle this message,please rebuild the 
				//serveceMsg with target service ID and filled it with new data then call the service manager interface
				//of OnMessage or SendIseServiceMsg.
				//
            }
            else
            {
                ISE_INFO_TRACE("Wait timeout. Continue to wait...");
            }
        }
    }

	//This interface is called by serviceManager, put the message into the queue
    ISE_BOOL CIseCanService::SendIseServiceMsg(ISE_MSG_HEAD *pServiceMsg)
    {
		ISE_INFO_TRACE("SendIseServiceMsg called service num: 0x%04X", pServiceMsg->service_id);
        m_CanMessageQueue.push(pServiceMsg);
        return ISE_TRUE;
    }
}