/*************************************************************************
* AVRDUDE Deamon
* Distributed under GPL v2.0
* Copyright (c) 2012 Stanley Huang <stanleyhuangyc@gmail.com>
* All rights reserved.
*************************************************************************/

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "httppil.h"
#include "httpapi.h"
#include "processpil.h"
#include "revision.h"

HttpParam httpParam;

static SHELL_PARAM shell = {0};

DWORD GetUniqueNum()
{
#ifdef WIN32
	return GetCurrentProcessId();
#else
	return (DWORD)time(NULL);
#endif
}

int Invoke(const char* port, const char* mcu, int baudrate, const char* type)
{
#ifdef WIN32
	const char* workdir = getenv("TEMP");
#else
	const char* workdir = "/var/tmp";
#endif
	char cmd[256];
	DWORD exitcode = 0;
	snprintf(cmd, sizeof(cmd), "AVRDUDE.dll -C avrduded.conf -V -p%s -carduino -P\\\\.\\%s -b%d -D -U%s:w:\"%s/sketch%x.hex\":i",
		mcu, port, baudrate, type, workdir, GetUniqueNum());
	if (ShellExec(&shell, cmd) == -1) {
		printf("Error invoking AVRDUDE\n");
		ShellClean(&shell);
		return -1;
	}
	ShellWait(&shell, 60000);
#ifdef WIN32
	GetExitCodeProcess(shell.piProcInfo.hProcess, &exitcode);
#endif
	ShellClean(&shell);
	return exitcode;
}

int HexUploadCallback(HttpMultipart *pxMP, char *poData, size_t dwDataChunkSize)
{
#ifdef WIN32
	const char* workdir = getenv("TEMP");
#else
	const char* workdir = "/var/tmp";
#endif

  // Do nothing with the data
	FILE* fp = pxMP->pxCallBackData;
	if (!poData) {
		// to cleanup
		if (fp) {
			fclose(fp);
			pxMP->pxCallBackData = NULL;
		}
		return 0;
	}
	if (!fp) {
		char filename[256];
		if (poData[0] != ':') {
			// invalid hex file
			return -1;
		}
        snprintf(filename, sizeof(filename), "%s/sketch%x.hex", workdir, GetUniqueNum());
		fp = fopen(filename, "wb");
		pxMP->pxCallBackData = fp;
	}
	if (!fp) return -1;
	fwrite(poData, 1, dwDataChunkSize, fp);
	if (pxMP->oFileuploadStatus & HTTPUPLOAD_LASTCHUNK) {
		int i;
		char* port = "COM1";
		char* mcu = "atmega328p";
		char* type = "flash";
		int baudrate = 57600;

		fclose(fp);
		pxMP->pxCallBackData = NULL;
		// invoke avrdude
		for (i = 0; i < pxMP->pp.iNumParams; i++) {
			if (!strcmp(pxMP->pp.stParams[i].pchParamName, "port")) {
				port = pxMP->pp.stParams[i].pchParamValue;
			} else if (!strcmp(pxMP->pp.stParams[i].pchParamName, "mcu")) {
				mcu = pxMP->pp.stParams[i].pchParamValue;
			} else if (!strcmp(pxMP->pp.stParams[i].pchParamName, "baudrate")) {
				baudrate = atoi(pxMP->pp.stParams[i].pchParamValue);
			} else if (!strcmp(pxMP->pp.stParams[i].pchParamName, "type")) {
				type = pxMP->pp.stParams[i].pchParamValue;
			}
		}
		i = Invoke(port, mcu, baudrate, type);
		printf("AVRDUDE return code: %d\n", i);
	}
	return 0;
}

int uhUploadHex(UrlHandlerParam* param)
{
#ifdef WIN32
	const char* workdir = getenv("TEMP");
#else
	const char* workdir = "/var/tmp";
#endif
	int baudrate = mwGetVarValueInt(param->pxVars, "baudrate", 57600);
	char* hex = mwGetVarValue(param->pxVars, "hex", 0);
	char* port = mwGetVarValue(param->pxVars, "port", "COM1");
	char* mcu = mwGetVarValue(param->pxVars, "mcu", "atmega328p");
	char* type = mwGetVarValue(param->pxVars, "type", "flash");
	char filename[256];
	FILE* fp;
	int ret;

	if (!hex) {
		hex = param->pucPayload;
	}

	if (!hex) return 0;

	if (hex[0] != ':') {
		// invalid hex file
		return 0;
	}

    snprintf(filename, sizeof(filename), "%s/sketch%x.hex", workdir, GetUniqueNum());
	fp = fopen(filename, "wb");
	if (!fp) return 0;
	fwrite(hex, 1, strlen(hex), fp);
	fclose(fp);
	ret = Invoke(port, mcu, baudrate, type);
	remove(filename);
	param->dataBytes = sprintf(param->pucBuffer, "%s", ret == 0 ? "Uploading successfully completed" : "Uploading failed");
	param->fileType=HTTPFILETYPE_TEXT;
	return FLAG_DATA_RAW;
}

