#ifndef ISE_DBUS_SERVICE_H
#define ISE_DBUS_SERVICE_H

#include "ise_common.h"
#include "ise_service_base.h"

namespace ise_service
{
    class CIseDbusService : public CIseServiceBase, public CSingleton<CIseDbusService>
    {
    public:
        CIseDbusService();
        ~CIseDbusService();

    /*Overrided functions*/
    protected:
        ISE_BOOL       OnInit();
        ISE_VOID       OnUninit();

    public:
        virtual ISE_VOID       OnMessage(const ISE_MSG_HEAD *pPepMsg);
    };
}

#endif  /*__ISE_DBUS_SERVICE_H__*/
