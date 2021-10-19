#include "ise_service_manager.h"
#include "ise_service_msg.h"

#include "ise_can_service.h"
#include "ise_dbus_service.h"
#include "ise_udp_service.h"
#include "ise_log_service.h"
#include "ise_map_service.h"
#include "ise_media_service.h"
#include "ise_update_service.h"
#include "ise_web_scribe_service.h"

namespace ise_service
{
    using namespace ise_common;
    using namespace std;

    CIseServiceManager::CIseServiceManager()
    {
        /*DO NOTHING*/
    }
    
    CIseServiceManager::~CIseServiceManager()
    {
        /*DO NOTHING*/
    }

    ISE_BOOL CIseServiceManager::Init()
    {
		 //create can service and init it
         CIseServicePtr pIseCanService = static_cast<CIseServicePtr>(CIseCanService::GetInstance());
         if(pIseCanService == ISE_NULL)
         {
             ISE_ERROR_TRACE("Can Service create failed!");
             return false;
         }
         if(pIseCanService->Init((ISE_UINT16)ISE_CAN_SERVICE_ID, "CIseCanService") == ISE_FALSE)
         {
             ISE_ERROR_TRACE("Can Service initialize failed!");
             return false;
         }
		m_ServiceMap.insert(map<ISE_UINT16, CIseServicePtr>::value_type(ISE_CAN_SERVICE_ID, pIseCanService));

		//create DBUS service and init it
         CIseServicePtr pIseDbusService = static_cast<CIseServicePtr>(CIseDbusService::GetInstance());
         if(pIseDbusService == ISE_NULL)
         {
             ISE_ERROR_TRACE("DBUS Service create failed!");
             return false;
         }
         if(pIseDbusService->Init((ISE_UINT16)ISE_DBUS_SERVICE_ID, "CIseDbusService") == ISE_FALSE)
         {
             ISE_ERROR_TRACE("DBUS Service initialize failed!");
             return false;
         }
		m_ServiceMap.insert(map<ISE_UINT16, CIseServicePtr>::value_type(ISE_DBUS_SERVICE_ID, pIseDbusService));

		//create UDP service and init it
         CIseServicePtr pIseUdpService = static_cast<CIseServicePtr>(CIseUdpService::GetInstance());
         if(pIseUdpService == ISE_NULL)
         {
             ISE_ERROR_TRACE("UDP Service create failed!");
             return false;
         }
         if(pIseUdpService->Init((ISE_UINT16)ISE_UDP_SERVICE_ID, "CIseUdpService") == ISE_FALSE)
         {
             ISE_ERROR_TRACE("UDP Service initialize failed!");
             return false;
         }
		m_ServiceMap.insert(map<ISE_UINT16, CIseServicePtr>::value_type(ISE_UDP_SERVICE_ID, pIseUdpService));

		//create ISE log service and init it
         CIseServicePtr pIseLogService = static_cast<CIseServicePtr>(CIseLogService::GetInstance());
         if(pIseLogService == ISE_NULL)
         {
             ISE_ERROR_TRACE("ISE log Service create failed!");
             return false;
         }
         if(pIseLogService->Init((ISE_UINT16)ISE_LOG_SERVICE_ID, "CIseLogService") == ISE_FALSE)
         {
             ISE_ERROR_TRACE("ISE log Service initialize failed!");
             return false;
         }
		m_ServiceMap.insert(map<ISE_UINT16, CIseServicePtr>::value_type(ISE_LOG_SERVICE_ID, pIseLogService));

		//create ISE map service and init it
         CIseServicePtr pIseMapService = static_cast<CIseServicePtr>(CIseMapService::GetInstance());
         if(pIseMapService == ISE_NULL)
         {
             ISE_ERROR_TRACE("ISE map Service create failed!");
             return false;
         }
         if(pIseMapService->Init((ISE_UINT16)ISE_MAP_SERVICE_ID, "CIseMapService") == ISE_FALSE)
         {
             ISE_ERROR_TRACE("ISE map Service initialize failed!");
             return false;
         }
		m_ServiceMap.insert(map<ISE_UINT16, CIseServicePtr>::value_type(ISE_MAP_SERVICE_ID, pIseMapService));

		//create ISE media service and init it
         CIseServicePtr pIseMeidaService = static_cast<CIseServicePtr>(CIseMediaService::GetInstance());
         if(pIseMeidaService == ISE_NULL)
         {
             ISE_ERROR_TRACE("ISE media Service create failed!");
             return false;
         }
         if(pIseMeidaService->Init((ISE_UINT16)ISE_MEDIA_SERVICE_ID, "CIseMeidaService") == ISE_FALSE)
         {
             ISE_ERROR_TRACE("ISE media Service initialize failed!");
             return false;
         }
		m_ServiceMap.insert(map<ISE_UINT16, CIseServicePtr>::value_type(ISE_MEDIA_SERVICE_ID, pIseMeidaService));

		//create ISE update service and init it
         CIseServicePtr pIseUpdateService = static_cast<CIseServicePtr>(CIseUpdateService::GetInstance());
         if(pIseUpdateService == ISE_NULL)
         {
             ISE_ERROR_TRACE("ISE update Service create failed!");
             return false;
         }
         if(pIseUpdateService->Init((ISE_UINT16)ISE_UPDATE_SERVICE_ID, "CIseUpdateService") == ISE_FALSE)
         {
             ISE_ERROR_TRACE("ISE update Service initialize failed!");
             return false;
         }
		m_ServiceMap.insert(map<ISE_UINT16, CIseServicePtr>::value_type(ISE_UPDATE_SERVICE_ID, pIseUpdateService));

		//create ISE web_scrib service and init it
         CIseServicePtr pIseWebScribeService = static_cast<CIseServicePtr>(CIseWebScribeService::GetInstance());
         if(pIseWebScribeService == ISE_NULL)
         {
             ISE_ERROR_TRACE("ISE web_scribe Service create failed!");
             return false;
         }
         if(pIseWebScribeService->Init((ISE_UINT16)ISE_WEB_SCRIBE_SERVICE_ID, "CIseWebScribeService") == ISE_FALSE)
         {
             ISE_ERROR_TRACE("ISE web_scribe Service initialize failed!");
             return false;
         }
		m_ServiceMap.insert(map<ISE_UINT16, CIseServicePtr>::value_type(ISE_WEB_SCRIBE_SERVICE_ID, pIseWebScribeService));

		ISE_INFO_TRACE("Initialzing Service Manager Thread...");
        if(InitServiceManagerThread() == ISE_FALSE)
        {
            ISE_ERROR_TRACE("Service Manager initialize failed!");
            goto ERROR_LINE;
        }

        return ISE_TRUE;

    ERROR_LINE:
        if(m_pServiceManagerThread != nullptr)
        {
            /*Shutdown the thread....*/
            m_pServiceManagerThread->Close();
            delete m_pServiceManagerThread;
            m_pServiceManagerThread = ISE_NULL;
        }

        return ISE_FALSE;
    }

    ISE_VOID CIseServiceManager::Uninit()
    {
        ISE_WARN_TRACE("Uninitializing the service...");
        map<ISE_UINT16, CIseServicePtr>::iterator iter;
        iter = m_ServiceMap.begin();
        while(iter != m_ServiceMap.end())
        {
            if(iter->second != nullptr)
            {
                CIseServicePtr pIseService = iter->second;
                pIseService->Uninit();
            }

            m_ServiceMap.erase(iter);
            iter++;
        }
		if(m_pServiceManagerThread != nullptr)
        {
            /*Shutdown the service manager thread....*/
            m_pServiceManagerThread->Close();
            delete m_pServiceManagerThread;
            m_pServiceManagerThread = ISE_NULL;
        }
    }

    ISE_VOID CIseServiceManager::OnMessage(const ISE_MSG_HEAD *pServiceMsg)
    {
        ISE_UINT16 service_id = pServiceMsg->service_id;
        CIseServicePtr pIseService = GetServiceInstance(service_id);
        if(pIseService == nullptr)
        {
            ISE_ERROR_TRACE("No Service(0x%04X) found!", service_id);
            return;
        }

        return pIseService->OnMessage(pServiceMsg);
    }

    CIseServicePtr CIseServiceManager::GetServiceInstance(ISE_UINT16 service_id)
    {
        std::map<ISE_UINT16, CIseServicePtr>::iterator it;
        it = m_ServiceMap.find(service_id);
        if(it == m_ServiceMap.end())
        {
            return nullptr;
        }

        return it->second;
    }
	
	ISE_BOOL CIseServiceManager::InitServiceManagerThread()
	{
        /*Initialize the service manager thread*/
        m_pServiceManagerThread = new CIseThread("Service Manager Thread");
        if(m_pServiceManagerThread == ISE_FALSE)
        {
            ISE_ERROR_TRACE("Object m_pServiceManagerThread allocate failed!");
            return ISE_FALSE;
        }

        if(m_pServiceManagerThread->Create(ServiceManagerThread, this, ISE_FALSE) == ISE_FALSE)
        {
            ISE_ERROR_TRACE("Service Manager Thread create failed!");
            return ISE_FALSE;
        }

        return ISE_TRUE;
	}

	ISE_VOID *CIseServiceManager::ServiceManagerThread(ISE_VOID *pParam)
    {
        CIseServiceManager *pServiceManager = CIseServiceManager::GetInstance();
        ISE_ASSERT(pServiceManager, "Fail to get Service Manager instance!");

        while(ISE_TRUE)
        {
            ISE_MSG_HEAD * pServiceMsg = ISE_NULL;
            if(pServiceManager->m_MessageQueue.pop(pServiceMsg, ISE_INFINITE))
            {
                ISE_INFO_TRACE("Service Manager Thread: Handle Message with service num: 0x%04X", pServiceMsg->service_id);

                if(pServiceMsg->service_id != ISE_SERVICE_ID_UNKNOWN)
                {
                    ISE_ERROR_TRACE("Invalid ISE Message! Ignore!!!!");
                    continue;
                }
				pServiceManager->OnMessage(pServiceMsg);
            }
            else
            {
                ISE_INFO_TRACE("Wait timeout. Continue to wait...");
            }
        }
    }

    ISE_BOOL CIseServiceManager::SendIseServiceMsg(ISE_MSG_HEAD *pServiceMsg)
    {
		ISE_INFO_TRACE("SendIseServiceMsg called service num: 0x%04X", pServiceMsg->service_id);
        m_MessageQueue.push(pServiceMsg);
        return ISE_TRUE;
    }
}
