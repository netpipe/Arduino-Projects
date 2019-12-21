/*************************************************************************
* ArduGate HTTP-to-Serial Gateway
* Distributed under GPL v2.0
* Copyright (c) 2012 Stanley Huang <stanleyhuangyc@gmail.com>
* All rights reserved.
*************************************************************************/

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "httppil.h"
#include "httpapi.h"
#include "revision.h"

#define AG_VER_MAJOR 0
#define AG_VER_MINOR 1

int uhSerial(UrlHandlerParam* param);
int uhBuildSketch(UrlHandlerParam* param);
int uhBuildStats(UrlHandlerParam* param);
int uhUploadHex(UrlHandlerParam* param);

UrlHandler urlHandlerList[]={
	{"serial", uhSerial, NULL},
	{"build", uhBuildSketch, NULL},
	{"upload", uhUploadHex, NULL},
	{"stats.js", uhBuildStats, NULL},
	{NULL},
};

HttpParam httpParam;

void Shutdown()
{
	//shutdown server
	mwServerShutdown(&httpParam);
	UninitSocket();
}

char* GetLocalAddrString()
{
	// get local ip address
	struct sockaddr_in sock;
	char hostname[128];
	struct hostent * lpHost;
	gethostname(hostname, 128);
	lpHost = gethostbyname(hostname);
	memcpy(&(sock.sin_addr), (void*)lpHost->h_addr_list[0], lpHost->h_length);
	return inet_ntoa(sock.sin_addr);
}

int AppQuit(int arg) {
	static int quitting = 0;
	if (quitting) return 0;
	quitting = 1;
	if (arg) printf("\nCaught signal (%d). ArduGate shutting down...\n",arg);
	Shutdown();
	return 0;
}

void GetFullPath(char* buffer, char* argv0, char* path)
{
	char* p = strrchr(argv0, '/');
	if (!p) p = strrchr(argv0, '\\');
	if (!p) {
		strcpy(buffer, path);
	} else {
		int l = p - argv0 + 1;
		memcpy(buffer, argv0, l);
		strcpy(buffer + l, path);
	}
}

int main(int argc,char* argv[])
{
	printf("ArduGate Version %d.%d (built on %s) <www.arduinodev.com>\nWritten by Stanley Huang <stanleyhuangyc@gmail.com> Distributed under GPLv2\n\n",
        AG_VER_MAJOR, AG_VER_MINOR, __DATE__);

#ifdef WIN32
	SetConsoleCtrlHandler( (PHANDLER_ROUTINE) AppQuit, TRUE );
#else
	signal(SIGINT, (void *) AppQuit);
	signal(SIGTERM, (void *) AppQuit);
	signal(SIGPIPE, SIG_IGN);
#endif

	//fill in default settings
	mwInitParam(&httpParam);
	httpParam.maxClients = 32;
	httpParam.httpPort = 8880;
	GetFullPath(httpParam.pchWebPath, argv[0], "htdocs");
	httpParam.pxUrlHandler = urlHandlerList;
	httpParam.tmSocketExpireTime = 180;

	//parsing command line arguments
	InitSocket();

    printf("Host: http://%s:%d\n", GetLocalAddrString(), httpParam.httpPort);
    printf("Root: %s\n\n",httpParam.pchWebPath);

    //start server
    if (mwServerStart(&httpParam)) {
        printf("ArduGate is unable to bind on port\n", httpParam.httpPort);
    } else {
        printf("ArduGate is running\n");
        mwHttpLoop(&httpParam);
    }

	Shutdown();
	return 0;
}
////////////////////////////// END OF FILE //////////////////////////////
