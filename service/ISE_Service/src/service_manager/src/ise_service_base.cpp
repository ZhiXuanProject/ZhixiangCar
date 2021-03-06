#include "ise_service_base.h"
#include <QThread>

namespace ise_service
{
    using namespace ise_common;
    CIseServiceBase::CIseServiceBase(ISE_UINT16 service_id , std::string service_name)
    {
        m_uServiceId     = service_id;
        m_strServiceName = service_name;
        m_bInitFlag     = ISE_FALSE;
        m_bEnableFlag   = ISE_FALSE;
    }

    CIseServiceBase::~CIseServiceBase()
    {
        m_uServiceId     = 0;
        m_strServiceName = "Undefined Service";
        m_bInitFlag     = ISE_FALSE;
    }

    ISE_BOOL CIseServiceBase::Init(ISE_UINT16 service_id, std::string service_name)
    {
    	ISE_INFO_TRACE("CIseServiceBase::Init called!");
        CIseLocker locker(m_InitFlagLock);

        if(m_bInitFlag == ISE_TRUE || m_bEnableFlag == ISE_TRUE)
        {
            ISE_INFO_TRACE("service %s has already initialized,no need to initialize again.", service_name.c_str());
            return ISE_TRUE;
        }

        if(service_id < 0)
        {
            ISE_WARN_TRACE("Invalid service id(%d) for initialize!", service_id);
            return ISE_FALSE;
        }

        m_uServiceId     = service_id;
        m_strServiceName = service_name;

        if(InitServiceThread() == ISE_FALSE)
        {
            ISE_WARN_TRACE("Service %s initialize Thread failed!", m_strServiceName.c_str());
            return ISE_FALSE;
        }

        if(OnInit() == ISE_TRUE)
        {
            m_bInitFlag     = ISE_TRUE;
            m_bEnableFlag   = ISE_TRUE;  /*Enabled by default*/
            ISE_INFO_TRACE("Service %s initialized!", m_strServiceName.c_str());
            return ISE_TRUE;
        }
        else
        {
            ISE_WARN_TRACE("Service %s initialize failed!", m_strServiceName.c_str());
            return ISE_FALSE;
        }
    }

    ISE_VOID CIseServiceBase::Uninit()
    {
        CIseLocker locker(m_InitFlagLock);

        OnUninit();

        m_bInitFlag     = ISE_FALSE;
        m_bEnableFlag   = ISE_FALSE;
        if(m_pServiceThread != ISE_NULL)
        {
            /*Shutdown the ervice thread....*/
            m_pServiceThread->Close();
            delete m_pServiceThread;
            m_pServiceThread = ISE_NULL;
        }
    }

    std::string CIseServiceBase::GetServiceName()
    {
        return m_strServiceName;
    }

    ISE_UINT16 CIseServiceBase::GetServiceId()
    {
        return m_uServiceId;
    }

	ISE_BOOL CIseServiceBase::InitServiceThread()
	{
		ISE_INFO_TRACE("InitServiceThread called!");
        /*Initialize the service thread*/
        m_pServiceThread = new ise_common::CIseThread("Service Thread");
        if(!m_pServiceThread)
        {
            ISE_ERROR_TRACE("Object m_pServiceThread allocate failed!");
            return ISE_FALSE;
        }

        if(m_pServiceThread->Create(ServiceThreadProc, this, ISE_TRUE) == ISE_FALSE)
        {
            ISE_ERROR_TRACE("Service Thread create failed!");
            return ISE_FALSE;
        }

        return ISE_TRUE;
	}

	ISE_VOID *CIseServiceBase::ServiceThreadProc(ISE_VOID *pParam)
    {
        ISE_INFO_TRACE("ServiceThread called!");
        while(ISE_TRUE)
        {
            ISE_MSG_HEAD *pServiceMsg = nullptr;
            if(nullptr != pParam)
			{
                CIseServiceBase* pServiceBase = static_cast<CIseServiceBase*>(pParam);
                if(pServiceBase->m_pServiceThread->GetThreadMessage(pServiceMsg) == ISE_TRUE)
				{
                    pServiceBase->OnMessage(pServiceMsg);
                }
			}
        }
    }

	ISE_BOOL CIseServiceBase::SendIseServiceMsg(ISE_MSG_HEAD* pServiceMsg)
	{
        if(!m_pServiceThread)
        {
            if(Init(m_uServiceId,m_strServiceName) == ISE_FALSE)
            {
                ISE_FATAL_TRACE("CIseServiceBase Init failed!");
                return ISE_FALSE;
            }
        }

        //ISE_INFO_TRACE("SendIseServiceMsg called!");
		m_pServiceThread->SendThreadMessage(pServiceMsg);
        return ISE_TRUE;
	}
}
