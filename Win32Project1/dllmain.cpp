// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "标头.h"
#pragma comment (lib, "Version.lib")   
DWORD Base=0;
WCHAR *Type[2] = { L"Config",L"PNG" };
//char *ResPath[7] = { "chs-font1.png","chs-font2.png","chs-font3.png","chs-menu.png","chs-font.png","chs-gui.cfg","chs-font.cfg" };
//int ResId[7] = { IDB_PNG1,IDB_PNG2,IDB_PNG3,IDB_PNG4,IDB_PNG5,IDR_CONFIG1,IDR_CONFIG2 };//IDR_CONFIG
char ConfigFilePath[256] = "System/Config.ini";
DWORD* FunAdd = 0;
DWORD FunAdd980[7] = {
	0x1FF4E0,//映射
	0X1FFA73,//坐标
	0x1FFA91,//偏移
	0x1FF958,//宽1
	0x1FFA64,//宽2&坐标
	0x160C34,//0x198DA5,//0x198DD2//980call
	0x20705C//BACKW
};//12作废
DWORD FunAdd972[4] = {
	0x1F0970,//START
	0x1F0C5B,//XYO
	0x1F80F6,//BACKW
	0x1A4605//Call
};
DWORD FunAdd974[7] = {
//SpaceEngine.exe+1F41C8 - F3 0F10 44 96 5C      - movss xmm0,[esi+edx*4+5C] 不明 可能是字宽
	0x1ECBA0,//映射
	0x1ED117,// 坐标
	0x1ED135,// 偏移
	0x1ECFFF,// 极其相似 字宽1
	0x1ED0FA,// 字宽2
	0x155614,//0x18AC15,//TESTCALL
	0x1F41C8//BACKW
};
/*
DWORD RetAdd = (DWORD)hModule2 + 0x1FFA9A;
void *RV = (void*)((DWORD)hModule2 + 0X3B48F4);
void *RV2 = (void*)((DWORD)hModule2 + 0x472F90);
*/
double sewid971 = 16;
DWORD *ReAdd,
	ReAdd980[3] = {
	0x1FFA9A,
	0X3B48F4,
	0x472F90
},ReAdd974[3] = {
	0x1ED13E,
	0x390DD4,
	0x44D350

}, ReAdd972[3] = {
	0X39B098,
	0x39BF40,
	0x1F0CB9

}, ReAdd971[3] = {
	0x2B80B0,0x2B82E0,0x163418

}, ReAdd970[3] = {
	0x272660,0x272440,0x14A19F

}, ReAdd973[3] = {
	0x3B6CB0,0x3B7C68,0x201BC9

},
StartAdd[4] = {
	0X407E64,
	0x3E10B8,
	0x3E0160,
	0x3FD980//973
},BackWidth[2] = {//背景宽
	0x20705C,//980
	0x1F41C8//974

},TexInitAdd[3] = {
	0x3EE00,//0x3E310,//0x03F590,//980
	0x5D220,//0x5C2A0,call SpaceEngine.exe+5D220

	0x5D1D0//972

};
std::string SYSTEMPATH;
std::string LOGPATH;
//bool Is980 = false;
DWORD glTexAdd = 0, *glTex2DAdd = 0, sBackWidth = 0;
int *start = 0;// = (int*)((DWORD)hModule2 + 0X407E64);//974 0x3E10B8 
//char *Lstr = 0;//(char*)((DWORD)hModule2 + 0X4AD788), tmp[3] = { 0 };//974 0x489F78
DWORD ThreadId = 0;
void *XYOAW, *GCW, *BackFun, *TexEnd;//继续调用
//bool INITED = false;
bool CanRun = false;
HMODULE hModule2 = 0,DLL=0;
SEL WCharAdd;
BYTE WID[256] = {0};
RWMEM RwMem;
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{

	
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:{
		char SP[MAX_PATH];
		hModule2 = GetModuleHandle(NULL);
		GetModuleFileNameA(hModule2, SP, MAX_PATH);
		//msgmgr(0, "SYSTEMPATH A:%s", SYSTEMPATH);
		*strrchr(SP, '\\')=0;
		*strrchr(SP, '\\') = 0;

		int A = 0;
		//char *P;
		while (SP[A] != 0&&A<MAX_PATH) {
			if (SP[A] == '\\')SP[A] = '/';
			A++;
		}
		//msgmgr(0, "SYSTEMPATH A:%s", SYSTEMPATH);
		SYSTEMPATH=LOGPATH = SP;
		LOGPATH += "/SE-Localization.log";
		//std::ofstream AA("AAA.log");
		//AA <<"AAAAA:"<< LOGPATH;
		//AA.close();
		//std::ofstream AA(LOGPATH, std::ios::app);
		//AA << "AAAA:"<< LOGPATH<<" AAA:"<< SYSTEMPATH;
		//AA.close();
		//float AF = 0.0f;
	//	msgmgr(0, "DLLMAINSTART ");
		DLL = hModule;
		Start();

	}break;
	case DLL_THREAD_ATTACH:break;
	case DLL_THREAD_DETACH:break;
	case DLL_PROCESS_DETACH:
		if (CanRun) {
			//SEMain(2);
			while (!res.empty()) {
				RES* P=res.front();
				res.erase(res.begin());
				delete P;
			}
			RwMem.End();
		}
//		Dlog(0, "	STOP...");
		break;
	}
//	DEBUG.close();
	return TRUE;
}
//void *PglTexAdd = 0;
std::string localePath;
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
//WCHAR *Type[2] = { L"Config",L"PNG" };
char *ResName[7] = { "chs-font1.png","chs-font2.png","chs-font3.png","chs-menu.png","chs-font.png","chs-gui.cfg","chs-font.cfg" };
int ResId[8] = { IDB_PNG1,IDB_PNG2,IDB_PNG3,IDB_PNG4,IDB_PNG5,IDR_CONFIG1,IDR_CONFIG2 ,IDB_PNG6 };//IDR_CONFIG
std::vector<RES*> res;
DWORD *FloatAdd = 0, FloatAdd973[2] = {
	0x3B6D98,
	 0x3B6CB0
}, FloatAdd972[2] = {
	0x39B180,
	0x39B098
}, *DoubleAdd = 0, DoubleAdd971[3] = {
	0x2B80B0,0x2B82E0, 0x2B82F0
}, DoubleAdd970[3] = {
	0x272440,0x272660,0x272670
};
void  CharAna972();
void Start() {
	DWORD  sStartAdd = 0, sTexAdd = 0;//Tick
	mProc = GetCurrentProcess();
	Version Ver;
	hModule2 = GetModuleHandle(NULL);
	Base = DWORD(hModule2);
	if (GetFileVersion(&Ver, &hModule2)) {
	//	msgmgr(3, "V:%d,%d,%d,%d", Ver.HM ,Ver.LM,Ver.HL,Ver.LL);
		if (Ver.HM == 0 && Ver.LM == 9 && Ver.HL == 8 && Ver.LL == 0) {
			CanRun = true;
			ReAdd = ReAdd980;
			sTexAdd = TexInitAdd[0];
			sStartAdd = StartAdd[0];
			localePath = "data/locale";
			res.push_back(new RES(Type[1], ResName[0],localePath, ResId[0]));
			res.push_back(new RES(Type[1], ResName[1], localePath, ResId[1]));
			res.push_back(new RES(Type[1], ResName[2], localePath, ResId[2]));
			res.push_back(new RES(Type[1], ResName[4], localePath, ResId[4]));
			res.push_back(new RES(Type[0], ResName[5], localePath, IDR_GUI980));
			RwMem.Add(CharAna, FunAdd980[0], 0xE8, 6);
			RwMem.Add(GetWidth980, FunAdd980[3], 0xE8, 6);
			RwMem.Add(GetCharXYOffAndWid, FunAdd980[4], 0xE9, 6);
			RwMem.Add(TexInit, FunAdd980[5], 0xE8,5);
			RwMem.Add(SetBackWid980, FunAdd980[6], 0xE8, 6);
			//				DEBUG << "执行980";
		}
		else if (Ver.HM == 0 && Ver.LM == 9 && Ver.HL == 7 && Ver.LL == 4) {
			ReAdd = ReAdd974;
			CanRun = true;
			sTexAdd = TexInitAdd[1];
			sStartAdd = StartAdd[1];
			localePath = "locale";
			res.push_back(new RES(Type[1], ResName[0], localePath, ResId[0]));
			res.push_back(new RES(Type[1], ResName[1], localePath, ResId[1]));
			res.push_back(new RES(Type[1], ResName[2], localePath, ResId[2]));
			res.push_back(new RES(Type[1], ResName[4], localePath, ResId[4]));
			res.push_back(new RES(Type[0], ResName[5], localePath, IDR_GUI974));
			RwMem.Add(CharAna, FunAdd974[0], 0xE8, 6);
			RwMem.Add(GetWidth974, FunAdd974[3], 0xE8, 6);
			RwMem.Add(GetCharXYOW974, FunAdd974[4], 0xE9, 6);
			RwMem.Add(TexInit, FunAdd974[5], 0xE8, 5);
			RwMem.Add(SetBackWid980, FunAdd974[6], 0xE8, 6);
		}
		else if (Ver.HM == 0 && Ver.LM == 9 && Ver.HL == 7 && Ver.LL == 3) {

			ReAdd = ReAdd973;
			CanRun = true;
			FloatAdd = FloatAdd973;
			Old1 = *(float*)(Base + 0x3B6D98);
			Old2 = *(float*)(Base + 0x3B6CB0);
			sTexAdd = 0x46FD0;//SpaceEngine.exe+1B3DD5 - call SpaceEngine.exe+46FD0

			sStartAdd = 0x3FD980;//StartAdd[2];3B6D98
			localePath = "locale";
			res.push_back(new RES(Type[1], ResName[4], localePath, ResId[7]));
			res.push_back(new RES(Type[0], ResName[5], localePath, IDR_GUI973));
			RwMem.Add(CharAna972, 0x201880, 0xE8, 6);//SpaceEngine.exe+201880 

			RwMem.Add(SetAll973, 0x201B6B, 0xE9, 9);
			RwMem.Add(SetBack972, 0x209066, 0xE8, 9);
			RwMem.Add(TexInit, 0x1B3DD5, 0xE8, 5);

		}
		else if (Ver.HM == 0 && Ver.LM == 9 && Ver.HL == 7 && Ver.LL == 2) {
			
			ReAdd = ReAdd972;
			CanRun = true;
			FloatAdd = FloatAdd972;
			Old1 = *(float*)(Base + 0x39B180);
			Old2 = *(float*)(Base + 0x39B098);
			sTexAdd = TexInitAdd[2];
			sStartAdd = StartAdd[2];
			localePath = "locale";
			res.push_back(new RES(Type[1], ResName[4], localePath, ResId[7]));
			res.push_back(new RES(Type[0], ResName[5], localePath, IDR_GUI972));
			RwMem.Add(CharAna972, FunAdd972[0], 0xE8, 6);
			RwMem.Add(GetWidthXYOFF972, FunAdd972[1], 0xE9, 9);
		//	msgmgr(3, "SetBack972:%p TexInit:%p CharAna972:%p GetWidthXYOFF972:%p", SetBack972, TexInit,CharAna972, GetWidthXYOFF972);
			RwMem.Add(SetBack972, FunAdd972[2], 0xE8, 9);
			RwMem.Add(TexInit, FunAdd972[3], 0xE8, 5);

		}
		else if (Ver.HM == 0 && Ver.LM == 9 && Ver.HL == 7 && Ver.LL == 1) {

			
			ReAdd = ReAdd971;
			CanRun = true;
			DoubleAdd = DoubleAdd971;
			DOld1 = *(double*)(Base + 0x2B80B0);
			DOld2 = *(double*)(Base + 0x2B82E0);
			DOld3 = *(float*)(Base + 0x2B82F0);
			sTexAdd = 0x4530;
			sStartAdd = 0x2FC3B0;//2F0974;//StartAdd[2];
			localePath = "locale";
			res.push_back(new RES(Type[1], ResName[4], localePath, ResId[7]));
			res.push_back(new RES(Type[0], ResName[5], localePath, IDR_GUI971));
			RwMem.Add(CharAna971, 0x163180, 0xE8, 9);
			RwMem.Add(SetAll971, 0x1633BD, 0xE9, 7);
			RwMem.Add(SetBack971, 0x164BCB, 0xE8, 7);
			RwMem.Add(TexInit, 0x2321D9, 0xE8, 5);

		}
		else if (Ver.HM == 0 && Ver.LM == 9 && Ver.HL == 7 && Ver.LL == 0) {
			DoubleAdd = DoubleAdd970;
			ReAdd = ReAdd970;
			CanRun = true;
			DOld1 = *(double*)(Base + DoubleAdd970[0]);
			DOld2 = *(double*)(Base + DoubleAdd970[1]);
			DOld3 = *(float*)(Base + DoubleAdd970[2]);
			sTexAdd = 0x4AC0;
			sStartAdd = 0x2A4B00;//StartAdd[2];
			localePath = "locale";
			res.push_back(new RES(Type[1], ResName[4], localePath, ResId[7]));
			res.push_back(new RES(Type[0], ResName[5], localePath, IDR_GUI971));
			RwMem.Add(CharAna970, 0x149E50, 0xE8, 9);
			RwMem.Add(SetAll970, 0x14A144, 0xE9, 7);
			RwMem.Add(SetBack970, 0x14AB8E, 0xE8, 7);
			RwMem.Add(TexInit, 0x1FB840, 0xE8, 5);
			sewid971 = 15.0;

		}
	}
	else {
		msgmgr(1, "读取主程序异常");
	}

	if (CanRun) {
		//char *ResName[7] = { "chs-font1.png","chs-font2.png","chs-font3.png","chs-menu.png","chs-font.png","chs-gui.cfg","chs-font.cfg" };
		//int ResId[8] = { IDB_PNG1,IDB_PNG2,IDB_PNG3,IDB_PNG4,IDB_PNG5,IDR_CONFIG1,IDR_CONFIG2 ,IDB_PNG6 };//IDR_CONFIG
	
		res.push_back(new RES(Type[1], ResName[3], localePath, ResId[3]));
		
		res.push_back(new RES(Type[0], ResName[6], localePath, ResId[6]));
		//char PH[260];
		//snprintf(PH, 260, "%s/%s/%s", SYSTEMPATH.c_str(), localePath.c_str(), ResName[5]);
		//std::string Path = SYSTEMPATH + "/" + localePath + "/" + ResName[5];
		std::ifstream IF;
		IF.open(SYSTEMPATH + "/"+ConfigFilePath);

		if (!IF) {

			CharADD.InitAll();
		}
		else {
			IF.close();
			IF.open(SYSTEMPATH + "/" + localePath + "/" + ResName[5]);
				if (!IF) {
					CharADD.InitFile();
				}
				else IF.close();
		}
		
		
		RE0 = (void*)(Base + ReAdd[0]);
		RE1 = (void*)(Base + ReAdd[1]);
		RE2 = (void*)(Base + ReAdd[2]);
		TexEnd = (void*)(Base + sTexAdd);
		start = (int*)(Base + sStartAdd);
	//	msgmgr(0, "START");
		RwMem.Start();
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

bool RunOnce1 = true;
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



char *Msg[] = { "Info" ,"Error" ,"Warning" ,"Debug" ,"Null" };
BOOL isone = TRUE, IS2 = TRUE;
//0 Info 1 Error 2 Warning 3 Debug 没卵用的错误输出
void msgmgr(int type, char* msg, ...) {
	std::ofstream AA;
	char str[4096], *str2 = new char[5128];
	va_list vlArgs;
	va_start(vlArgs, msg);
	vsnprintf_s(str, 4096, msg, vlArgs);
	va_end(vlArgs);
	GetLocalTime(&sys_time);


	DWORD L = 0;
	if (isone) {
		FILE *fp;
		fopen_s(&fp, LOGPATH.c_str(), "rb");
		if (fp != NULL) {
			fseek(fp, 0, SEEK_END);
			L = ftell(fp);
			fclose(fp);
			AA.open(LOGPATH, L > 512 * 1024 ? std::ios::trunc : std::ios::app);
		}
		else {
			AA.open(LOGPATH);

		}


		snprintf(str2, 5128, "\nTIME %04d-%02d-%02d %02d:%02d:%02d\n --------------------------\n", sys_time.wYear, sys_time.wMonth, sys_time.wDay, sys_time.wHour, sys_time.wMinute, sys_time.wSecond);
		AA << str2;
		isone = FALSE;
	}

	else {
		AA.open(LOGPATH, std::ios::app);
	}
	snprintf(str2, 5128, "%02d:%02d:%02d.%03d [%s] %s\n", sys_time.wHour, sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds, Msg[type>3 ? 4 : type], str);

	AA << str2;

	AA.close();
	delete[] str2;
}
