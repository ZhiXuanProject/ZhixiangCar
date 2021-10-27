#include "ise_service_manager.h"
#include <unistd.h>
#include<string.h>
#include <QCoreApplication>


bool nameMatch(const char *name1, const char *name2)
{
    if (0==strcmp(name1, name2))
        return true;
    return false;
}

int main(int argc, char** argv)
{
    QCoreApplication app(argc,argv);
	//set log level from outside
	if(argc < 2)
	{
        ise_common::ISE_DEBUG_INIT("debug");
	}
	else
	{

		if(nameMatch(argv[1], "debug") || nameMatch(argv[1], "info") || nameMatch(argv[1], "warn")
			|| nameMatch(argv[1], "error") || nameMatch(argv[1], "fatal"))
		{
            ise_common::ISE_DEBUG_INIT(argv[1]);
		}
		else
		{
            ise_common::ISE_DEBUG_INIT("debug");
		}
	}

    ISE_INFO_TRACE("Starting up ISE services....");
    ise_service::CIseServiceManager *pServiceManager = ise_service::CIseServiceManager::GetInstance();
    ISE_ASSERT(pServiceManager, "Failed to get service manager!");
    ISE_ASSERT(pServiceManager->Init(), "Fail to initialize ISE service Manager!");
    ISE_INFO_TRACE("ISE Service Manager initialized!");

    return app.exec();
}
