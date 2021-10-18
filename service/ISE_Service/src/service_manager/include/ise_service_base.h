#ifndef __ISE_SERVICE_BASE_H__
#define __ISE_SERVICE_BASE_H__

#include "ise_common.h"
#include "ise_message_base.h"
#include "ise_thread.h"
#include <memory>

namespace ise_service
{
    class CIseServiceBase
    {
    public:
        CIseServiceBase();
        virtual ~CIseServiceBase();
    
    public:
        ISE_BOOL               Init(ISE_UINT16 service_id, std::string service_name);
        ISE_VOID               Uninit();
    
    public:
        std::string                 GetServiceName();
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
        ise_common::CIseThread  *m_pServiceThread = nullptr;
        ISE_UINT16            m_uServiceId;
        std::string           m_strServiceName;

        ISE_BOOL              m_bInitFlag;
        CIseSectionLock       m_InitFlagLock;

        ISE_BOOL              m_bEnableFlag;
    };

	typedef std::shared_ptr<CIseServiceBase>      CIseServicePtr;
}

#endif  /*__ISE_SERVICE_BASE_H__*/
