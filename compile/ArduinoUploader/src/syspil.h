/*******************************************************************
* Process Platform Independent Layer
* Distributed under GPLv3 license
* Copyright (c) 2005-11 Stanley Huang <stanleyhuangyc@gmail.com>
* All rights reserved.
*******************************************************************/

#ifndef _SYSPIL_H_
#define _SYSPIL_H_

#ifdef SYS_MINGW
#ifndef WIN32
#define WIN32
#endif
#endif

#ifdef WIN32
#include <windows.h>
#include <io.h>

#define snprintf _snprintf

#else
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/select.h>

#if !defined(O_BINARY)
#define O_BINARY 0
#endif
#define HAVE_PTHREAD
#endif //WIN32

#ifdef HAVE_PTHREAD
#include <pthread.h>
#endif

#ifdef WIN32

#define ssize_t size_t
#define socklen_t int
#ifndef HAVE_PTHREAD
typedef HANDLE pthread_t;
typedef HANDLE pthread_mutex_t;
#endif

typedef DWORD (WINAPI *PFNGetProcessId)(HANDLE hProcess);
#define DD
#else

#define closesocket close
#ifndef MAX_PATH
#define MAX_PATH 256
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

typedef int SOCKET;
typedef unsigned int DWORD;
typedef unsigned short int WORD;
typedef unsigned char BYTE;
typedef int BOOL;
#define DD printf("%s, %s(%d)\n", __FILE__,__FUNCTION__ , __LINE__)
#endif //WIN32
typedef unsigned char OCTET;

#define SHELL_NOREDIRECT 1
#define SHELL_SHOWWINDOW 2
#define SHELL_NOWAIT 4

#ifdef WIN32
#define msleep(ms) (Sleep(ms))
#define PATH_DELIMITER '\\'
#else
#define msleep(ms) (usleep(ms<<10))
#define PATH_DELIMITER '/'
#define _strdup strdup
#define stricmp strcasecmp
#endif

#ifdef __cplusplus
extern "C" {
#endif

int InitSocket();
void UninitSocket();
char *GetTimeString();
int ThreadCreate(pthread_t *pth, void* (*start_routine)(void*), void* arg);
int ThreadKill(pthread_t pth);
int ThreadWait(pthread_t pth, int timeout, void** ret);
void MutexCreate(pthread_mutex_t* mutex);
void MutexDestroy(pthread_mutex_t* mutex);
void MutexLock(pthread_mutex_t* mutex);
void MutexUnlock(pthread_mutex_t* mutex);
int ReadDir(const char* pchDir, char* pchFileNameBuf);
int IsFileExist(const char* filename);
int IsDir(const char* pchName);

#ifndef WIN32
unsigned int GetTickCount();
#endif

#ifdef __cplusplus
}
#endif

#endif
