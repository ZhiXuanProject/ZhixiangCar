#include "ise_service_manager.h"
#include <unistd.h>
#include<string.h>
#include <QCoreApplication>
 
using namespace ise_common;
using namespace ise_service;

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
		ISE_DEBUG_INIT("debug");
	}
	else
	{
		if(nameMatch(argv[1], "debug") || nameMatch(argv[1], "info") || nameMatch(argv[1], "warn")
			|| nameMatch(argv[1], "error") || nameMatch(argv[1], "fatal"))
		{
			ISE_DEBUG_INIT(argv[1]);
		}
		else
		{
			ISE_DEBUG_INIT("debug");
		}
	}

    ISE_INFO_TRACE("Starting up ISE services....");
    CIseServiceManager *pServiceManager = CIseServiceManager::GetInstance();
    ISE_ASSERT(pServiceManager, "Failed to get service manager!");
    ISE_ASSERT(pServiceManager->Init(), "Fail to initialize ISE service Manager!");
    ISE_INFO_TRACE("ISE Service Manager initialized!");

    return app.exec();
}
