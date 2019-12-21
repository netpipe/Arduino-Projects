#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "httppil.h"
#include "httpapi.h"
#include "processpil.h"

#define MAX_LIBS 64
#define MAX_LIBNAME 128

#define SUCCESS 0
#define ERROR_GENERIC -1
#define ERROR_BUILD_SKETCH -2
#define ERROR_BUILD_LIB -3
#define ERROR_LINK -4

#define SOURCE_OK 0
#define SOURCE_HEX 1
#define SOURCE_ERROR -1

#define BUILDER_VERSION "0.0.2"

SHELL_PARAM proc;

char libs[MAX_LIBS][MAX_LIBNAME] = {0};

int GenSourceFiles(const char* srcfile, const char* sketch)
{
    FILE* fp;
    int len;
	const char *p;
	int numlibs = 0;

    len = strlen(sketch);

	printf("Analyzing sketch (%d bytes) ...", len);

    fp = fopen(srcfile, "w");
    fprintf(fp, "#include <Arduino.h>\n%s", sketch);
    fclose(fp);

	// parsing reference libraries
	printf("done\nLibraries:");
	p = sketch;
	libs[0][0] = 0;
	while ((p = strstr(p, "#include"))) {
		char *q;
		q = strchr(p, '<');
		if (!q) strchr(p, '\"');
		if (q) {
			p = q + 1;
			q = strchr(p, '.');
			if (q) {
				int l = q - p;
				strncpy(libs[numlibs], p, min(l, MAX_LIBNAME - 1));
				printf(" [%s]", libs[numlibs]);
				if (++numlibs == MAX_LIBS) break;
				libs[numlibs][0] = 0;
			} else {
				break;
			}
		} else {
			break;
		}
	}
	printf("\n\n");

    return SOURCE_OK;
}

int run(const char* cmd)
{
#ifdef _DEBUG
	printf("[COMMAND LINE] %s\n", cmd);
#endif
	if (ShellExec(&proc, cmd))
		return -1;

	ShellWait(&proc, -1);
	ShellClean(&proc);

	return 0;
}

typedef struct {
	const char* name;
	const char* mcu;
	const char* variant;
	int baudrate;
	const char* corefile;
	unsigned int count;
} BOARD_CONFIG;

BOARD_CONFIG boards[] = {
	{"Arduino Uno", "atmega328p", "standard", 115200, "core328.a"},
	{"Arduino Duemilanove (328)", "atmega328p", "standard", 57600, "core328.a"},
	{"Arduino Duemilanove (168)", "atmega168", "standard", 19200, "core168.a"},
	{"Arduino Nano (328)", "atmega328p", "eightanaloginputs", 57600, "core328nano.a"},
	{"Arduino Nano (168)", "atmega168", "eightanaloginputs", 19200, "core168nano.a"},
	{"Arduino Mini (328)", "atmega328p", "eightanaloginputs", 57600, "core328nano.a"},
	{"Arduino Mini (168)", "atmega168", "eightanaloginputs", 19200, "core168nano.a"},
	{"Arduino Pro Mini (328)", "atmega328p", "standard", 57600, "core328.a"},
	{"Arduino Pro Mini (168)", "atmega168p", "standard", 19200, "core168.a"},
	{"Arduino Mega 2560/ADK", "atmega2560", "mega", 57600, "core2560.a"},
	{"Arduino Mega", "atmega1280", "mega", 57600, "core1280.a"},
};

#define BOARD_COUNT (sizeof(boards) / sizeof(boards[0]))

static char srcfile[128];
static unsigned int count = 0;
static unsigned int fail = 0;
static char *appdir = "./";
#ifdef WIN32
static char* avrpath = "avr/bin/";
#else
static char* avrpath = "/usr/bin/";
#endif

int build(int index, char* sketch)
{
#ifdef WIN32
	const char* workdir = getenv("TEMP");
#else
	const char* workdir = "/var/tmp";
#endif

    char cmd[1024];
	char *p;
	int ret = ERROR_GENERIC;

	BOARD_CONFIG* board = boards;

	if (index == 0) {
		printf("Automatic board detection not yet implemented.\n");
		return -1;
	}
	if (index > BOARD_COUNT) {
		printf("Invalid board number specified.\n");
		return -1;
	}
	board = boards + index - 1;
	printf("Board: %s (MCU: %s, Baudrate: %d)\n\n", board->name, board->mcu, board->baudrate);
	board->count++;

    if (!workdir || !*workdir)
        workdir = ".";

    memset(&proc, 0, sizeof(proc));

    do {
		int i;
        // generate main cpp file
        sprintf(srcfile, "%s/sketch%08d.cpp", workdir, count);

		sprintf(cmd, "%s.hex", srcfile);
		remove(cmd);

        if (GenSourceFiles(srcfile, sketch) != 0) {
            printf("Invalid sketch\n");
            break;
        }

		printf("Compiling ...\n");
        p = cmd + sprintf(cmd, "%savr-g++ -c -g -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=%s -DF_CPU=16000000L -MMD -DARDUINO=101 -I%sarduino/hardware/arduino/cores/arduino -I%sarduino/hardware/arduino/variants/%s",
            avrpath, board->mcu, appdir, appdir,
			board->variant);
		for (i = 0; i < MAX_LIBS && libs[i][0]; i++) {
			p += sprintf(p, " -I%sarduino/libraries/%s", appdir, libs[i]);
		}
		sprintf(p, " %s -o %s.o", srcfile, srcfile);
        if (run(cmd) != 0) {
            printf("Error\n");
            break;
        }
		sprintf(cmd, "%s.o", srcfile);
		if (!IsFileExist(cmd)) {
			ret = ERROR_BUILD_SKETCH;
			break;
		}
		sprintf(cmd, "%s.d", srcfile);
		remove(cmd);

		for (i = 0; i < MAX_LIBS && libs[i][0]; i++) {
			sprintf(cmd, "%sarduino/libraries/%s/%s.cpp", appdir, libs[i], libs[i]);
			if (!IsFileExist(cmd)) {
				ret = ERROR_BUILD_LIB;
				break;
			}
			printf("Compiling [%s] ...\n", libs[i]);
			p = cmd + sprintf(cmd, "%savr-g++ -c -g -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=%s -DF_CPU=16000000L -MMD -DARDUINO=101 -I%sarduino/hardware/arduino/cores/arduino -I%sarduino/hardware/arduino/variants/%s",
				avrpath, board->mcu, appdir, appdir,
				board->variant);
			p += sprintf(p, " -I%sarduino/libraries/%s", appdir, libs[i]);
			sprintf(p, " %sarduino/libraries/%s/%s.cpp -o %s/%s.o", appdir, libs[i], libs[i], workdir, libs[i]);
			if (run(cmd) != 0) {
				printf("Error\n");
				break;
			}
			sprintf(cmd, "%s/%s.o", workdir, libs[i]);
			if (!IsFileExist(cmd)) {
				ret = ERROR_BUILD_LIB;
				break;
			}
		}
		if (ret == ERROR_BUILD_LIB)
			break;

		printf("Linking with %s ...\n", board->corefile);
		p = cmd + sprintf(cmd, "%savr-gcc -Wl,--gc-sections -mmcu=%s -lm %s.o",
			avrpath, board->mcu, srcfile);
		for (i = 0; i < MAX_LIBS && libs[i][0]; i++) {
			p += sprintf(p, " %s/%s.o", workdir, libs[i]);
		}
		p += sprintf(p, " %scores/%s -o %s.elf", appdir, board->corefile, srcfile);
        if (run(cmd) != 0) {
            printf("error\n");
            break;
        }
		sprintf(cmd, "%s.elf", srcfile);
		if (!IsFileExist(cmd)) {
			ret = ERROR_LINK;
			break;
		}

		printf("Generating HEX file ...\n");
		sprintf(cmd, "%savr-objcopy -O ihex -R .eeprom %s.elf %s.hex",
			avrpath, srcfile, srcfile);
        if (run(cmd) != 0) {
            printf("Error generating HEX file for %s\n", sketch);
            break;
        }

		sprintf(cmd, "%s.o", srcfile);
		remove(cmd);
		sprintf(cmd, "%s.elf", srcfile);
		remove(cmd);

		sprintf(cmd, "%s.hex", srcfile);
		if (!IsFileExist(cmd)) {
			ret = ERROR_LINK;
			break;
		}
    	ret = SUCCESS;
    } while(0);
	count++;
	if (ret == SUCCESS) {
		return count;
	} else {
		fail++;
		return ret;
	}
}

int uhBuildStats(UrlHandlerParam* param)
{
	HttpStats *stats = &((HttpParam*)param->hp)->stats;
	char *p = param->pucBuffer;
	int len = 0;
	int i;

	len = sprintf(p, "var builder_ver=\"%s\";var stats_uptime=%u;var stats_requests=%u;var stats_total_builds=%u;var stats_error_builds=%u;\n",
		BUILDER_VERSION, (unsigned int)(time(NULL) - stats->startTime), stats->reqCount, count, fail);
	len += sprintf(p + len, "var stats_board_used=new Array(");
	for (i = 0; i < BOARD_COUNT; i++) {
		len += sprintf(p + len, "%d,", boards[i].count);	
	}
	len += sprintf(p + len - 1, ");") - 1;
	param->dataBytes = len;
	param->fileType=HTTPFILETYPE_JS;
	return FLAG_DATA_RAW;
}

int uhBuildSketch(UrlHandlerParam* param)
{
	int board = mwGetVarValueInt(param->pxVars, "board", 0);
	char* sketch = mwGetVarValue(param->pxVars, "sketch", 0);
	int ret = -1;
	if (!sketch) {
		sketch = param->pucPayload;
	}
	if (board && sketch) {
#ifdef _DEBUG
		printf("[Sketch]\n%s\n", sketch);
#endif
		ret  = build(board, sketch);
	}
	if (ret >= 0) {
		strcat(srcfile, ".hex");
#ifdef WIN32
		param->hs->fd = open(srcfile, O_RDONLY|O_BINARY);
#else
		param->hs->fd = open(srcfile, O_RDONLY);
#endif
		param->fileType = HTTPFILETYPE_HEX;
		return FLAG_DATA_FD;
	} else {
		switch (ret) {
		case ERROR_BUILD_SKETCH:
			param->dataBytes = sprintf(param->pucBuffer, "%s", "Erroring compiling sketch. Please check your code.");
			break;
		case ERROR_BUILD_LIB: {
			int i;
			char *p;
			p = param->pucBuffer + sprintf(param->pucBuffer, "%s", "Erroring compiling library.\nThe following libraries are referenced but not supported yet:\n");
			for (i = 0; i < MAX_LIBS && libs[i][0]; i++) {
				char buf[MAX_LIBNAME];
				sprintf(buf, "%sarduino/libraries/%s/%s.cpp", appdir, libs[i], libs[i]);
				if (!IsFileExist(buf)) {
					p += sprintf(p, " %s\n", libs[i]);
				}
			}
			param->dataBytes = p - param->pucBuffer;
			} break;
		case ERROR_LINK:
			param->dataBytes = sprintf(param->pucBuffer, "%s", "Erroring linking.");
			break;
		default:
			param->dataBytes = sprintf(param->pucBuffer, "%s", "Generic error.");
		}
	}
	param->fileType=HTTPFILETYPE_TEXT;
	return FLAG_DATA_RAW;
}