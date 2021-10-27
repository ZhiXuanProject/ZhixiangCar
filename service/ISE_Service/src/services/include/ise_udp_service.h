#ifndef ISE_UDP_SERVICE_H
#define ISE_UDP_SERVICE_H

#include "ise_common.h"
#include "ise_service_base.h"

namespace ise_service
{
    class CIseUdpService : public CIseServiceBase, public CSingleton<CIseUdpService>
    {
    public:
        CIseUdpService();
        ~CIseUdpService();

    /*Overrided functions*/
    protected:
        ISE_BOOL       OnInit();
        ISE_VOID       OnUninit();

    public:
        virtual ISE_VOID       OnMessage(const ISE_MSG_HEAD *pPepMsg);

    };
}

#endif  /*__ISE_DBUS_UDP_SERVICE_H__*/
