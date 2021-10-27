#ifndef ISE_WEB_SCRIBE_SERVICE_H
#define ISE_WEB_SCRIBE_SERVICE_H

#include "ise_common.h"
#include "ise_service_base.h"

class AdvertisementInfo;
namespace ise_service
{
    class CIseWebSubscribeService : public CIseServiceBase, public CSingleton<CIseWebSubscribeService>
    {
    public:
        CIseWebSubscribeService();
        virtual ~CIseWebSubscribeService();

    /*Overrided functions*/
    protected:
        ISE_BOOL       OnInit();
        ISE_VOID       OnUninit();

    public:
        virtual ISE_VOID       OnMessage(const ISE_MSG_HEAD *pPepMsg);
    private:
        AdvertisementInfo* m_Advinfo = nullptr;
    };
}

#endif  /*__ISE_WEB_SCRIBE_SERVICE_H__*/
