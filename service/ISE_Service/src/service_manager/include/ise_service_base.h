#ifndef __ISE_SERVICE_BASE_H__
#define __ISE_SERVICE_BASE_H__

#include "ise_common.h"
#include "ise_message_base.h"
#include <memory>

namespace ise_service
{
    using namespace ise_common;
    class CIseServiceBase
    {
    public:
        CIseServiceBase();
        ~CIseServiceBase();
    
    public:
        ISE_BOOL               Init(ISE_UINT16 service_id, string service_name);
        ISE_VOID               Uninit();
    
    public:
        string                 GetServiceName();
        ISE_UINT16             GetServiceId();

    protected:
        virtual ISE_BOOL       OnInit()                                     = 0;
        virtual ISE_VOID       OnUninit()                                   = 0;
    
    public:
        virtual ISE_VOID       OnMessage(const ISE_MSG_HEAD *pServiceMsg);
		virtual ISE_VOID       Run();
	private:
		static ISE_VOID        *ServiceThreadProc(ISE_VOID *pParam);
		ISE_BOOL               InitServiceThread();

    private:
		CIseThread            *m_pServiceThread;
        ISE_UINT16            m_uServiceId;
        string                m_strServiceName;

        ISE_BOOL              m_bInitFlag;
        CIseSectionLock       m_InitFlagLock;

        ISE_BOOL              m_bEnableFlag;
    };

	typedef std::shared_ptr<CIseServiceBase>      CIseServicePtr;
}

#endif  /*__ISE_SERVICE_BASE_H__*/