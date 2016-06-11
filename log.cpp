/*
*  �ļ�����log.c
*  ��;�����̼�¼
*  ��̻�����Win10
*  ������ڣ� 2016.6   Ver 0.01
*  ���ߣ� yinhao
*  ��ϵ��ʽ�� E-mail: yinhao746746@163.com
*/

#include "log.h"

//��ȡ��ǰʱ�䣬��ʽ�����������2016/06/11-15:01:20
int logGetTime(char *ptime){
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	sprintf(ptime,"%04d/%02d/%02d-%02d:%02d:%02d",timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
	return strlen(ptime);
}

//��¼��ǰ������״̬
int logGetInfo(PLOG_STRU plog){
	HANDLE handle;
	HWND hWnd = GetForegroundWindow();	//��ȡ��ǰϵͳ�б������ǰ̨���ھ��
	if (hWnd != INVALID_HANDLE_VALUE){
		logGetTime(plog->time);			//��ʽ����ǰʱ��
		GetWindowText(hWnd, plog->text, TEXT_LEN);		//��ȡ����ڵı���text
		GetWindowThreadProcessId(hWnd,&plog->pid);		//��ȡ����ڵĽ���ID
		handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, plog->pid);		//ͨ������ID���Ҷ�Ӧ�ľ��handle
		GetModuleFileNameEx(handle,NULL,plog->path,PATH_LEN);		//�þ����ȡ��ǰ�����ִ��·��
		return 1;
	}
	return 0;
}

//��ӡ��ʽ����Ϣ��Ϊ��־���
void logPrintInfo(LOG_STRU log){
	char str[MAX_LOG];
	sprintf(str,"%s,%ld,%s,%s,%s",log.time,log.pid,log.path,log.text,log.sCode);
	printf("%s\n",str);
}