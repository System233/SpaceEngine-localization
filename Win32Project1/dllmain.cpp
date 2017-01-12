// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#pragma comment (lib, "Version.lib")   
DWORD Base=0;
WCHAR *Type[2] = { L"Config",L"PNG" };
char *ResPath[7] = { "chs-font1.png","chs-font2.png","chs-font3.png","chs-menu.png","CN-font.png","chs-gui.cfg","CN-font.cfg" };
int ResId[7] = { IDB_PNG1,IDB_PNG2,IDB_PNG3,IDB_PNG4,IDB_PNG5,IDR_CONFIG1,IDR_CONFIG2 };//IDR_CONFIG
char ConfigFilePath[256] = "System/Config.ini";
DWORD* FunAdd = 0;
DWORD FunAdd980[6] = {
	0x1FF4E0,//映射
	0X1FFA73,//坐标
	0x1FFA91,//偏移
	0x1FF958,//宽1
	0x1FFA64,//宽2&坐标
	0x198DA5//0x198DD2//980call
};
DWORD FunAdd974[6] = {
//SpaceEngine.exe+1F41C8 - F3 0F10 44 96 5C      - movss xmm0,[esi+edx*4+5C] 不明 可能是字宽
	0x1ECBA0,//映射
	0x1ED117,// 坐标
	0x1ED135,// 偏移
	0x1ECFFF,// 极其相似 字宽1
	0x1ED0FA,// 字宽2
	0x18AC15//TEST
};
/*
DWORD RetAdd = (DWORD)hModule2 + 0x1FFA9A;
void *RV = (void*)((DWORD)hModule2 + 0X3B48F4);
void *RV2 = (void*)((DWORD)hModule2 + 0x472F90);
*/
DWORD *ReAdd,
	ReAdd980[3] = {
	0x1FFA9A,
	0X3B48F4,
	0x472F90
},ReAdd974[3] = {
	0x1ED13E,
	0x390DD4,
	0x44D350

},StartAdd[2] = {
	0X407E64,
	0x3E10B8
},LstrAdd[2] = {
	0X4AD788,
	0x489F78
}, BackWidth[2] = {//背景宽
	0x20705C,//980
	0x1F41C8//974

},glAdd[2] = {
	0x36A2BC,//980
	0x34A2B8//974
},TexInitAdd[2] = {
	0x3E310,//0x03F590,//980
	0x5C2A0//974未测试<<<<<<<<<<<<<<<<<<<<<=============
};
char SYSTEMPATH[MAX_PATH];
//bool Is980 = false;
DWORD glTexAdd = 0, *glTex2DAdd = 0, sBackWidth = 0;
int *start = 0;// = (int*)((DWORD)hModule2 + 0X407E64);//974 0x3E10B8 
//char *Lstr = 0;//(char*)((DWORD)hModule2 + 0X4AD788), tmp[3] = { 0 };//974 0x489F78
DWORD ThreadId = 0;
void *XYOAW, *GCW, *BackFun, *TexEnd;
//bool INITED = false;
bool CanRun = false;
HMODULE hModule2 = 0,DLL=0;
SEL WCharAdd;
BYTE WID[8] = { 0 };
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
//	std::ofstream A("A.txt", std::ios::app);
	
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:{
		hModule2 = GetModuleHandle(NULL);
		GetModuleFileNameA(hModule2, SYSTEMPATH, MAX_PATH);
		//msgmgr(0, "SYSTEMPATH A:%s", SYSTEMPATH);
		*strrchr(SYSTEMPATH, '\\')=0;
		*strrchr(SYSTEMPATH, '\\') = 0;
		int A = 0;
		//char *P;
		while (SYSTEMPATH[A] != 0&&A<MAX_PATH) {
			if (SYSTEMPATH[A] == '\\')SYSTEMPATH[A] = '/';
			A++;
		}
		//msgmgr(0, "SYSTEMPATH A:%s", SYSTEMPATH);
		DLL = hModule;
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Start, NULL, NULL, &ThreadId);

	}break;
	case DLL_THREAD_ATTACH:break;
	case DLL_THREAD_DETACH:break;
	case DLL_PROCESS_DETACH:
		if (CanRun) {
			SEMain(2);
		}
//		Dlog(0, "	STOP...");
		break;
	}
//	DEBUG.close();
	return TRUE;
}
//void *PglTexAdd = 0;
char *localePath = 0;
char *Msg[] = { "Info" ,"Error" ,"Warning" ,"Debug" ,"Null" };
BOOL isone = TRUE;
//0 Info 1 Error 2 Warning 3 Debug 没卵用的错误输出.......
void msgmgr(int type, char* msg, ...) {

	char str[2048], *str2 = new char[3072];
	va_list vlArgs;
	va_start(vlArgs, msg);
	vsnprintf_s(str, 2048, msg, vlArgs);
	va_end(vlArgs);
	GetLocalTime(&sys_time);
	
	std::ofstream A("SE-Localization.log", std::ios::app);
	if (isone) {
		snprintf(str2, 3072, "[TIME] %04d-%02d-%02d %02d:%02d:%02d\n------------------------------------", sys_time.wYear, sys_time.wMonth, sys_time.wDay, sys_time.wHour, sys_time.wMinute, sys_time.wSecond);
		A << str2;
		isone = FALSE;
	}
	snprintf(str2, 3072, "%02d:%02d:%02d [%s] %s\n", sys_time.wHour, sys_time.wMinute, sys_time.wSecond, Msg[type], str);

	A << str2;
	delete[] str2;
	A.close();

}
void GetError(int d) {
	DWORD Err = GetLastError();
	if (Err != 0) {
		char ErrInfo[256], ERR[512];
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, Err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), ErrInfo, 256, NULL);
		snprintf(ERR, 512, "位置:%d 错误(0x%X):%s", d, Err, ErrInfo);
		MessageBoxA(0, ERR, "Error", MB_OK);
		msgmgr(1, ERR);
		SetLastError(0);
	}


}
void Start() {
	DWORD  sStartAdd = 0,sTexAdd = 0;
	mProc = GetCurrentProcess();
	Version Ver;
	hModule2 = GetModuleHandle(NULL);
	Base = DWORD(hModule2);
	if (GetFileVersion(&Ver, &hModule2)) {
		if (Ver.HM == 0 && Ver.LM == 9 && Ver.HL == 8 && Ver.LL == 0) {
			//Is980=
			CanRun = true;
			FunAdd = FunAdd980;
			ReAdd = ReAdd980;
			XYOAW = GetCharXYOffAndWid;
			GCW = GetWidth980;
			sTexAdd = TexInitAdd[0];
			//TexCall = (void*)(Base + 0x16B76C);
			BackFun = SetBackWid980;
			sBackWidth = BackWidth[0];
			sStartAdd = StartAdd[0];
			//sglAdd = glAdd[0];
			localePath = "data/locale/";
			//				DEBUG << "执行980";
		}
		if (Ver.HM == 0 && Ver.LM == 9 && Ver.HL == 7 && Ver.LL == 4) {
			/*
			RE0 = (void*)(Base + ReAdd974[0]);
			RE1 = (void*)(Base + ReAdd974[1]);
			RE2 = (void*)(Base + ReAdd974[2]);*/
			ReAdd = ReAdd974;

			CanRun = true;
			FunAdd = FunAdd974;
			XYOAW = GetCharXYOW974;
			GCW = GetWidth974;

			BackFun = SetBackWid980;//974上测试
			sBackWidth = BackWidth[1];
			sTexAdd = TexInitAdd[1];
			sStartAdd = StartAdd[1];
			//sglAdd = glAdd[1];
			localePath = "locale/";

			//			DEBUG << "执行974";
		}
	}
	
	if (CanRun){
		if (!CharADD.MainInit())return;
		RE0 = (void*)(Base + ReAdd[0]);
		RE1 = (void*)(Base + ReAdd[1]);
		RE2 = (void*)(Base + ReAdd[2]);
		TexEnd = (void*)(Base + sTexAdd);
		//glTex2DAdd = (DWORD*)(Base + sglAdd);
		start = (int*)(Base + sStartAdd);
	//	PglTexAdd = glTex2D;
		SEMain(0);
		SEMain(1);
		/*if (SEMain(0))
		{
			if (SEMain(1)) {
		/*	DWORD dwTemp = 0, dwOldProtect;
			if (!VirtualProtectEx(mProc, glTex2DAdd, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect))GetError(0);
			glTexAdd = *glTex2DAdd;//glTex2DAdd;
			*glTex2DAdd = (DWORD)PglTexAdd;
			if (!VirtualProtectEx(mProc, glTex2DAdd, 4, dwOldProtect, &dwTemp))GetError(1);
			}
		}*/
	}


}
//函数 偏移 存储
void GetCode(void* Fun, DWORD OffSet, BYTE *Code) {
	DWORD CODE = (DWORD)Fun - ((DWORD)hModule2 + OffSet)-5;
	BYTE* P = (BYTE*)&CODE;
	for (int i = 0;i < 4;i++) {
		Code[i+1] = P[i];
	}
}

BYTE CharMapCode[6] = { 0X90 }, CharMapOld[6], 
CharXYCode[7] = { 0X90 }, CharXYOld[7],
CharOFFCode[9] = { 0X90 }, CharOFFOld[9],
CharWid1Code[6] = {0x90}, CharWid1Old[6],
CharWid2Code[6] = { 0x90 }, CharWid2Old[6],//宽2&坐标
BackWidCode[6] = {0x90}, BackWidOld[6],
TexCode[5] = {0x90},TexCodeOld[5];//背景

bool RunOnce1 = true;
BOOL SEMain(int mode) {
	switch (mode)
	{
	case 0: {
		if(ReadAdd(FunAdd[0], CharMapOld, 6))
			//ReadAdd(FunAdd[1], CharXYOld, 7);
			//ReadAdd(FunAdd[2], CharOFFOld, 9);;
			if(ReadAdd(FunAdd[3], CharWid1Old, 6))
				if(ReadAdd(FunAdd[4], CharWid2Old, 6))
					if (ReadAdd(sBackWidth, BackWidOld, 6))
						if(ReadAdd(TexInitAdd[0],TexCodeOld,5)) {;//读背景宽
		GetCode(BackFun, sBackWidth, BackWidCode);//汇编码
		GetCode(CharAna, FunAdd[0], CharMapCode);
		//GetCode(GetCharXY, FunAdd[1], CharXYCode);
		//GetCode(GetCharOff, FunAdd[2], CharOFFCode);
		//GetCode(GetWidth1, FunAdd[3], CharWid1Code);
		GetCode(GCW, FunAdd[3], CharWid1Code);
		GetCode(XYOAW, FunAdd[4], CharWid2Code);
		GetCode(TexInit, FunAdd[5], TexCode);
		
	//	GetCode(GetCharXYOffAndWid, FunAdd[4], CharWid2Code);
		TexCode[0]=CharMapCode[0] = CharXYCode[0] = CharOFFCode[0]= CharWid1Code[0]= BackWidCode[0] = 0XE8;//call
		CharMapCode[5] = 
			CharXYCode[5] = CharXYCode[6] = 
			CharOFFCode[5] = CharOFFCode[6] = CharOFFCode[7] = CharOFFCode[8] =
			CharWid1Code[5] = CharWid2Code[5]=
			BackWidCode[5] = 0x90;//nop
			CharWid2Code[0] = 0XE9;
		//	GetError(11);
			return TRUE;
		}
	}break;
	case 1: {

		if (WriteAdd(FunAdd[0], CharMapCode, 6))
			//WriteAdd(FunAdd[1], CharXYCode, 7);
		//	WriteAdd(FunAdd[2], CharOFFCode, 9);
			if (WriteAdd(FunAdd[3], CharWid1Code, 6))
				if (WriteAdd(FunAdd[4], CharWid2Code, 6))
					if (WriteAdd(sBackWidth, BackWidCode, 6))
						if(WriteAdd(FunAdd[5], TexCode, 5))return TRUE;
			//GetError(12);
	}break;
	case 2: {
		if (WriteAdd(FunAdd[0], CharMapOld, 6))
			//	WriteAdd(FunAdd[1], CharXYOld, 7);
			//	WriteAdd(FunAdd[2], CharOFFOld, 9);
			if (WriteAdd(FunAdd[3], CharWid1Old, 6))
				if (WriteAdd(FunAdd[4], CharWid2Old, 6))
					if (WriteAdd(sBackWidth, BackWidOld, 6))
						if (WriteAdd(FunAdd[5], TexCodeOld, 5))return TRUE;
		
	}break;
	}
	GetError(13);
	return FALSE;
}
BOOL GetFileVersion(Version *Ver,HMODULE *hModle)
{
	
	DWORD VerSize,dwHandle;
	TCHAR strFile[256];
	//printf("信息:");
	GetModuleFileName(*hModle, strFile, sizeof(strFile)/2);
	VerSize = GetFileVersionInfoSize(strFile, &dwHandle);
	
	if (VerSize == 0)
		return FALSE;
	TCHAR *lpdata = new TCHAR[VerSize];
	if (lpdata == 0)return FALSE;
	if (GetFileVersionInfo(strFile, 0, VerSize, lpdata))
	{
		//printf("信息2");
		VS_FIXEDFILEINFO * pInfo=0;
		unsigned int nInfoLen;

		if (VerQueryValue(lpdata, L"\\", (LPVOID*)&pInfo, &nInfoLen))
		{
			Ver->HM = HIWORD(pInfo->dwFileVersionMS);
			Ver->LM = LOWORD(pInfo->dwFileVersionMS);
			Ver->HL = HIWORD(pInfo->dwFileVersionLS);
			Ver->LL = LOWORD(pInfo->dwFileVersionLS);

			delete[] lpdata;
			return TRUE;
		}
	}
	delete[] lpdata;
	return FALSE;
}



