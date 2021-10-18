#include "ise_update_service.h"

namespace ise_service
{
    using namespace ise_common;

    CIseUpdateService::CIseUpdateService()
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
        if(pIseMsg->service_id != ISE_UPDATE_SERVICE_ID)
        {
            ISE_WARN_TRACE("Unexpected service id 0x%04X", pIseMsg->service_id);
            return;
        }

        ISE_INFO_TRACE("Received Message: service ID = 0x%04X", pIseMsg->service_id);
    }

	ISE_VOID CIseUpdateService::Run()
    {
        ISE_INFO_TRACE("Enter ISE map service thread");
		CIseUpdateService *pIseUpdateService = CIseUpdateService::GetInstance();
        while(ISE_TRUE)
        {
            ISE_MSG_HEAD * pServiceMsg = ISE_NULL;
            if(pIseUpdateService->m_UpdateMessageQueue.pop(pServiceMsg, ISE_INFINITE))
            {
                ISE_INFO_TRACE("ISE update Service Thread: Handle Message with service num: 0x%04X", pServiceMsg->service_id);

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

	//This interface is called by serviceManager, put message into the queue
    ISE_BOOL CIseUpdateService::SendIseServiceMsg(ISE_MSG_HEAD *pServiceMsg)
    {
		ISE_INFO_TRACE("SendIseServiceMsg called service num: 0x%04X", pServiceMsg->service_id);
        m_UpdateMessageQueue.push(pServiceMsg);
        return ISE_TRUE;
    }

}