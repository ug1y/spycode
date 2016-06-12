#ifndef _SERVICE_H_
#define _SERVICE_H_

#include "hook.h"

int InitService();
void ServiceMain(int argc, char** argv);
void ControlHandler(DWORD request);


#endif // _SERVICE_H_