/*
*  文件名：KeyBoardHook.c
*  用途：键盘钩子的演示程序
*  编程环境：WinXP SP2+CL 8.0
*  完成日期： 2006.3   Ver 0.01
*  作者： 88250
*  联系方式： E-mail: DL88250@gmail.com  QQ:845765
*/

#define _WIN32_WINNT 0x0400

#include <stdio.h>

#include <stdlib.h>

#include <windows.h>

#include <Psapi.h>


#pragma comment (lib,"Psapi.lib")
#pragma comment(lib, "User32.lib")


DWORD g_tid =0;

HHOOK g_hook =0;



BOOL CALLBACK con_handler(DWORD g_tid)
{
	PostThreadMessage(g_tid, WM_QUIT, 0, 0);
	return TRUE;	
}



LRESULT CALLBACK kb_proc(int code, WPARAM w, LPARAM l)
{
    PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)l;
	
	if (code==HC_ACTION && w==WM_KEYDOWN)
	{
		HWND hWnd = GetForegroundWindow();
		if (hWnd != INVALID_HANDLE_VALUE)
		{ 
			char name[100]={0};
			char text[100]={0};
			char path[100]={0};
			int n = GetClassName(hWnd, name, 100);
			int m = GetWindowText(hWnd, text, 100);
			DWORD pid;
			GetWindowThreadProcessId(hWnd,&pid);
			HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
			GetModuleFileNameEx(handle,NULL,path,100);
			printf("[%ld] %s %d,%s; %d,%s =>%x\n", pid,path,n,name,m,text,p->vkCode);
		}
		if(GetAsyncKeyState(VK_CAPITAL))
		{
			printf("CapsLk\n");
		}
		if(p->vkCode==0x43 && GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_CONTROL) )
		{
			printf("Ctrl + c\n");
		}
		if(GetAsyncKeyState(VK_MENU))
		{
			printf("Alt\n");
		}
		if(GetAsyncKeyState(VK_SHIFT))
		{
			printf("Shift\n");
		}
		//GetKeyState
		//GetAsyncKeyState
	}
/*
	if (((w == WM_KEYDOWN) && ((GetKeyState(VK_CAPITAL) &1) || (GetKeyState(VK_SHIFT) &1))) 
		&& (((p->vkCode >64) && (p->vkCode <91)) || ((p->asdasdvkCode >47) && (p->vkCode <58)))){
        printf("You press %c ", p->vkCode);
    }else if ((w == WM_KEYDOWN) && ((p->vkCode >64) && (p->vkCode <91))){
        printf("You press %c ", p->vkCode +32);  
    }else if ((w == WM_KEYDOWN) && ((p->vkCode >47) && (p->vkCode <58))){
        printf("You press %c ", p->vkCode);   
    }
	*/
	return CallNextHookEx(g_hook, code, w, l);
}



int main (void)
{
    MSG msg;
    g_tid = GetCurrentThreadId();
    SetConsoleCtrlHandler(&con_handler, TRUE);
    g_hook = SetWindowsHookEx(WH_KEYBOARD_LL, &kb_proc, GetModuleHandle(NULL),0);
	while (GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(g_hook);
	return 0;
}



