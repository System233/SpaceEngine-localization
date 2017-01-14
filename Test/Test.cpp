// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

SEL WCharAdd;
std::string LOGPATH;
char *Msg[] = { "Info" ,"Error" ,"Warning" ,"Debug" ,"Null" };
BOOL isone = TRUE;
//0 Info 1 Error 2 Warning 3 Debug 没卵用的错误输出.......
void msgmgr(int type, char* msg, ...) {

	char str[2048];
	va_list vlArgs;
	va_start(vlArgs, msg);
	vsnprintf_s(str, 2048, msg, vlArgs);
	va_end(vlArgs);
	GetLocalTime(&sys_time);
	printf("%02d:%02d:%02d.%03d [%s] %s\n", sys_time.wHour, sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds, Msg[type>3 ? 4 : type], str);
	

}
void GetError(int d) {
	DWORD Err = GetLastError();
	if (Err != 0) {
		char ErrInfo[256], ERR[512];
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, Err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), ErrInfo, 256, NULL);
		snprintf(ERR, 512, "位置:%d 错误(0x%X):%s", d, Err, ErrInfo);
	//	MessageBoxA(0, ERR, "Error", MB_OK);
		msgmgr(1, ERR);
		SetLastError(0);
	}


}
SYSTEMTIME sys_time;
DWORD Base = 0;
HMODULE hModule2=0, DLL=0;
WCHAR *Type[2] = { L"Config",L"PNG" };
BYTE WID[8] = { 0 };
char *Pstr[8] = { "File","1","2","3","4","5","6","7" };
int ResId[7] = { 0 };//IDR_CONFIG
char * SYSTEMPATH = "";
char * localePath = "";
char *ResPath[7] = { "chs-font1.png","chs-font2.png","chs-font3.png","chs-menu.png","CN-font.png","chs-gui.cfg","CN-font.cfg" };
char *ConfigFilePath = "Config2.ini";
BOOL GetFileVersion(Version *Ver, HMODULE *hModle) {
	Ver->HM = 0, Ver->LM = 9, Ver->HL = 8, Ver->LL = 0;
	return TRUE;
};
CharAdd CharADD;
int main()
{
	
	printf("START2\n");
	for(int i=0;i<100;i++){
	msgmgr(3, "\nSTART[%d]\n",i);
	CharADD.MainInit();
	}
	system("pause");
	for (int i = 0;i<100;i++) {
		msgmgr(3, "\nSTART[%d]\n", i);
		CharADD.MainInit();
	}
    return 0;
}

