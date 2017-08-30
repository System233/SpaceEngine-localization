// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "Define.h"
DWORD Base=0;
std::wstring SYSTEMROOT;// "System/Config.json";
MD5 md5;
LPCSTR Lang;
LPCWSTR localePath;
double sewid971 = 16;
DWORD *FunAdd = 0, *ReAdd,
ReAdd980[3] = {
0x1FFA9A,0x3B48F4,0x472F90
}, ReAdd974[3] = {
	0x1ED13E,0x390DD4,0x44D350
}, ReAdd974RC2[3] = {
	0x1FE65E ,//SpaceEngine.exe+1FE65E 
	0x3ABB74,//mulss xmm5,[SpaceEngine.exe + 3ABB74]{ [0.00] }
	0x469530//mov ecx,SpaceEngine.exe+469530 { [000004B0] }
}, ReAdd974RC3[3] = {
	0x1FEB3A  ,//SpaceEngine.exe+1FEB3A 
	0x3B2B34,//mulss xmm5,[SpaceEngine.exe+3B2B34] { [0.00] }
	0x471300//mov ecx,SpaceEngine.exe+471300 { [000004B0] }
}, ReAdd972[3] = {
	0X39B098,0x39BF40,0x1F0CB9
}, ReAdd971[3] = {
	0x2B80B0,0x2B82E0,0x163418
}, ReAdd970[3] = {
	0x272660,0x272440,0x14A19F
}, ReAdd973[3] = {
	0x3B6CB0,0x3B7C68,0x201BC9
}, ReAdd980e[3] = {
	0x20DE9A,//SpaceEngine.exe+20DE9A - movaps xmm4,xmm6
	0x3BDC00,//SpaceEngine.exe+20DE6A - mulss xmm5,[SpaceEngine.exe+3BDC00] { [0.00] }
	0x4D6B10//SpaceEngine.exe+20DE7A - mov ecx,SpaceEngine.exe+4D6B10 { [000004B0] }
},glTexAdd = 0, *glTex2DAdd = 0, sBackWidth = 0;
size_t *start = 0, maxLogSize(128<<10);
void *TexEnd(0);
bool runtime_check(false);
Hook mHook;

DWORD *FloatAdd = 0, 
	FloatAdd973[2] = {0x3B6D98, 0x3B6CB0}, 
	FloatAdd972[2] = {0x39B180,0x39B098}, 
	*DoubleAdd = 0, 
	DoubleAdd971[3] = {0x2B80B0,0x2B82E0, 0x2B82F0}, 
	DoubleAdd970[3] = {0x272440,0x272660,0x272670};



BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: {
		DWORD  sStartAdd = 0, sTexAdd = 0, //sWidAdd=0,sTABWid=0,sUWid=NULL,
			sLang(0);//Timer TexCheck WidStrcut
		mProc = GetCurrentProcess();
		HMODULE exeModule = GetModuleHandle(NULL);
		Base = DWORD(exeModule);
		//size_t len = GetModuleFileNameW(hModule, (LPWSTR)SYSTEMROOT.data(), NULL);
		SYSTEMROOT.resize(MAX_PATH);
		GetModuleFileNameW(exeModule, (LPWSTR)SYSTEMROOT.data(), MAX_PATH);
		//CloseHandle(exeModule);
		SYSTEMROOT.reserve();
		std::ifstream sModule(SYSTEMROOT, std::ios::binary);
		if (sModule) {
			std::stringstream ss;
			ss << sModule.rdbuf();
			const std::string &SEData = ss.str();
			md5.GenerateMD5((BYTE*)SEData.c_str(), SEData.size());
			sModule.close();
			runtime_check = true;
			if (md5 == "03D1FDE3675AF345D20F263EB253984D") {//980E
				ReAdd = ReAdd980e;
				sTexAdd = 0x43160;
				sStartAdd = 0x461910;
				localePath = L"data/locale";
				sLang = 0x513C18;
				mHook.Add(CharAna, 0x20D8E0, 0xE8, 6);
				mHook.Add(TexInit, 0x16FFA1, 0xE8, 5);
				mHook.Add(GetWidth980, 0x20DD58, 0xE8, 6);		//SpaceEngine.exe+20DD58 - mulss xmm4,[esi+eax*4+5C]
				mHook.Add(GetCharXYOffAndWid, 0x20DE64, 0xE9, 6);	//SpaceEngine.exe+20DE64 - movss xmm5,[esi+edx*4+5C]
				mHook.Add(TexInit, 0x16FFA1, 0xE8, 5);
				mHook.Add(SetBackWid980, 0x2153DC, 0xE8, 6);//SpaceEngine.exe+2153DC - movss xmm0,[esi+edx*4+5C]

			}
			else if (md5 == "2A6C6DF6FEDEF93A09B2640C5AD735BE") {//980
				ReAdd = ReAdd980;
				sTexAdd = 0x3EE00;
				sStartAdd = 0x407E64;
				localePath = L"data/locale";
				sLang = 0x4AD788;
				IRETADD = (void*)(Base + 0x3F3BA);
				mHook.Add(CharAna, 0x1FF4E0, 0xE8, 6);
				mHook.Add(GetWidth980, 0x1FF958, 0xE8, 6);
				mHook.Add(GetCharXYOffAndWid, 0x1FFA64, 0xE9, 6);
				mHook.Add(TexInit, 0x160C34, 0xE8, 5);
				mHook.Add(SetBackWid980, 0x20705C, 0xE8, 6);

			}
			else if (md5 == "B495D5CA0CA6DACE5DEC3C967405D9EA") {//974 RC1
																 //MD5：B495D5CA0CA6DACE5DEC3C967405D9EA
				ReAdd = ReAdd974;
				sTexAdd = 0x5D220;
				sStartAdd = 0x3E10B8;
				localePath = L"locale";
				sLang = 0x489F78;
				mHook.Add(CharAna, 0x1ECBA0, 0xE8, 6);
				mHook.Add(GetWidth974, 0x1ECFFF, 0xE8, 6);
				mHook.Add(GetCharXYOW974, 0x1ED0FA, 0xE9, 6);
				mHook.Add(TexInit, 0x155614, 0xE8, 5);
				mHook.Add(SetBackWid980, 0x1F41C8, 0xE8, 6);
			}
			else if (md5 == "F239BC8DFB544608BCED4B369C27DCD8") {//974 RC2
																 //MD5：F239BC8DFB544608BCED4B369C27DCD8
				ReAdd = ReAdd974RC2;
				sTexAdd = 0x45440;//SpaceEngine.exe+1647B4 - call SpaceEngine.exe+45440
				sLang = 0x4A60E8;
				sStartAdd = 0x3FE7AC;//SpaceEngine.exe+3FE7AC
				localePath = L"data/locale";
				mHook.Add(CharAna, 0x1FE0C0, 0xE8, 6);//SpaceEngine.exe+1FE0C0 
				mHook.Add(GetWidth974, 0x1FE51F, 0xE8, 6);//SpaceEngine.exe+1FE51F 
				mHook.Add(GetCharXYOW974, 0x1FE61A, 0xE9, 6);//SpaceEngine.exe+1FE61A 
				mHook.Add(TexInit, 0x1647B4, 0xE8, 5);
				mHook.Add(SetBackWid980, 0x205CC8, 0xE8, 6);//SpaceEngine.exe+205CC8 
			}
			else if (md5 == "174EE0924E76036B7C177160E9752614") {//974 RC3
																 //MD5：174EE0924E76036B7C177160E9752614
				ReAdd = ReAdd974RC3;
				sTexAdd = 0x3E710;//SpaceEngine.exe+1647B4 - call SpaceEngine.exe+45440
				sLang = 0x4AB568;
				sStartAdd = 0x405C88;//SpaceEngine.exe+405C88
				localePath = L"data/locale";
				mHook.Add(CharAna, 0x1FE580, 0xE8, 6);//SpaceEngine.exe+1FE580 
				mHook.Add(GetWidth980, 0x1FE9F8, 0xE8, 6);//SpaceEngine.exe+1FE9F8 - F3 0F59 64 86 5C      - mulss xmm4,[esi+eax*4+5C]
				mHook.Add(GetXYOW974RC3, 0x1FEB04, 0xE9, 6);//SpaceEngine.exe+1FEB04 
				mHook.Add(TexInit, 0x15FC04, 0xE8, 5);//SpaceEngine.exe+15FC04 - call SpaceEngine.exe+3E710
				mHook.Add(SetBackWid980, 0x20611C, 0xE8, 6);//SpaceEngine.exe+20611C - movss xmm0,[esi+edx*4+5C]
			}
			else if (md5 == "A003AEF8F41389600BFD6831A0212A7C") {//973
																 //MD5：A003AEF8F41389600BFD6831A0212A7C
				ReAdd = ReAdd973;
				FloatAdd = FloatAdd973;
				Old1 = *(float*)(Base + 0x3B6D98);
				Old2 = *(float*)(Base + 0x3B6CB0);
				sTexAdd = 0x46FD0;//SpaceEngine.exe+1B3DD5 - call SpaceEngine.exe+46FD0
				sLang = 0x4C12D8;
				sStartAdd = 0x3FD980;//StartAdd[2];3B6D98
				localePath = L"locale";
				mHook.Add(CharAna972, 0x201880, 0xE8, 6);//SpaceEngine.exe+201880 
				mHook.Add(SetAll973, 0x201B6B, 0xE9, 9);
				mHook.Add(SetBack972, 0x209066, 0xE8, 9);
				mHook.Add(TexInit, 0x1B3DD5, 0xE8, 5);

			}
			else if (md5 == "CF969C362A5FFCA9E132B318BDCA5043") {//972
																 //MD5：CF969C362A5FFCA9E132B318BDCA5043
				ReAdd = ReAdd972;
				FloatAdd = FloatAdd972;
				Old1 = *(float*)(Base + 0x39B180);
				Old2 = *(float*)(Base + 0x39B098);
				sTexAdd = 0x5D1D0;
				sStartAdd = 0x3E0160;
				sLang = 0x4A0AF8;
				localePath = L"locale";
				mHook.Add(CharAna972, 0x1F0970, 0xE8, 6);
				mHook.Add(GetWidthXYOFF972, 0x1F0C5B, 0xE9, 9);
				mHook.Add(SetBack972, 0x1F80F6, 0xE8, 9);
				mHook.Add(TexInit, 0x1A4605, 0xE8, 5);

			}
			else if (md5 == "51F74355E759302FE68A8FF3DFB8681C") {//971
																 //MD5：51F74355E759302FE68A8FF3DFB8681C
				ReAdd = ReAdd971;
				DoubleAdd = DoubleAdd971;
				DOld1 = *(double*)(Base + 0x2B80B0);
				DOld2 = *(double*)(Base + 0x2B82E0);
				DOld3 = *(float*)(Base + 0x2B82F0);
				sTexAdd = 0x4530;
				sLang = 0x37686C;
				sStartAdd = 0x2FC3B0;//2F0974;//StartAdd[2];
				localePath = L"locale";
				mHook.Add(CharAna971, 0x163180, 0xE8, 9);
				mHook.Add(SetAll971, 0x1633BD, 0xE9, 7);
				mHook.Add(SetBack971, 0x164BCB, 0xE8, 7);
				mHook.Add(TexInit, 0x2321D9, 0xE8, 5);

			}
			else if (md5 == "DE13DEEFDD2400DA2BF557740397377A") {//970
																 //MD5：DE13DEEFDD2400DA2BF557740397377A
				DoubleAdd = DoubleAdd970;
				ReAdd = ReAdd970;
				sLang = 0x322540;
				DOld1 = *(double*)(Base + DoubleAdd970[0]);
				DOld2 = *(double*)(Base + DoubleAdd970[1]);
				DOld3 = *(float*)(Base + DoubleAdd970[2]);
				sTexAdd = 0x4AC0;
				sStartAdd = 0x2A4B00;;
				localePath = L"locale";
				mHook.Add(CharAna970, 0x149E50, 0xE8, 9);
				mHook.Add(SetAll970, 0x14A144, 0xE9, 7);
				mHook.Add(SetBack970, 0x14AB8E, 0xE8, 7);
				mHook.Add(TexInit, 0x1FB840, 0xE8, 5);
				sewid971 = 15.0;
			}
			else runtime_check = false;
		}
		else openErr(SYSTEMROOT);
		for (auto &ch : SYSTEMROOT)if (ch == '\\')ch = '/';
		SYSTEMROOT.erase(SYSTEMROOT.rfind('/', SYSTEMROOT.rfind('/') - 1) + 1);
		if (runtime_check) {
			RE0 = (void*)(Base + ReAdd[0]);
			RE1 = (void*)(Base + ReAdd[1]);
			RE2 = (void*)(Base + ReAdd[2]);
			TexEnd = (void*)(Base + sTexAdd);
			start = (size_t*)(Base + sStartAdd);
			Lang = (LPSTR)(Base + sLang);
			mHook.HookAll();
		}


	
	}; break;
	case DLL_THREAD_ATTACH:break;
	case DLL_THREAD_DETACH:break;
	case DLL_PROCESS_DETACH:
		if (runtime_check)mHook.unHookAll();
		if (wngCnt || errCnt)msgmgr(MsgType::Info,L"Warning:%d Error:%d",wngCnt, errCnt);
		break;
	}
	return TRUE;
}