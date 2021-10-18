#ifndef __ISE_SERVICE_MSG_H__
#define __ISE_SERVICE_MSG_H__

#include "ise_message_base.h"

namespace ise_service
{
	enum IseServiceID
	{
		ISE_SERVICE_ID_UNKNOWN = -1,
		ISE_CAN_SERVICE_ID,
		ISE_DBUS_SERVICE_ID,
		ISE_UDP_SERVICE_ID,
		ISE_USB_SERVICE_ID,
		ISE_UPDATE_SERVICE_ID,
		ISE_MEDIA_SERVICE_ID,
		ISE_WEB_SCRIBE_SERVICE_ID,
		ISE_LOG_SERVICE_ID,
		ISE_MAP_SERVICE_ID,
		AMP_SRVICE_ID_MAX
	};
	
	enum IseMessageType
	{
		ISE_MESSAGE_UNKNOWN = -1,
		ISE_SWTICH_LIGHT,
		ISE_ADJUST_VOLUME,
		ISE_SWTICH_AIR,
		ISE_SWTICH_MUSIC,
		ISE_EXPORT_LOG,
		AMP_MESSAGE_MAX
	};


    struct _ISE_ALIGN( 1 ) _ISE_PACKED ISE_CAN_COMMAND  : public ISE_MSG_HEAD
    {
        ISE_UINT8             reserved;

    public:
        ISE_CAN_COMMAND() : ISE_MSG_HEAD(ISE_CAN_SERVICE_ID, ISE_SWTICH_LIGHT, sizeof(*this))
        {
            /*DO NOTHING*/
        }
    };
}

#endif  /*__ISE_SERVICE_MSG_H__*/
