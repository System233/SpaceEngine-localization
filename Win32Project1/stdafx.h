// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once
#define  PNG_BYTES_TO_CHECK 4
#include "targetver.h"
#define DEFASM __declspec(naked) 
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>
#include <png.h>
#include "resource.h"
//#include <tchar.h>
//#include <iostream>
#include <vector>
#include <sstream> 
#include <fstream>
extern DWORD glTexAdd,*glTex2DAdd, Base;
extern HANDLE mProc;
extern bool ReTex;
void glTex2D();
void msgmgr(int type, char* msg, ...);
BOOL WriteAdd(DWORD OffSet, BYTE *Code, size_t Size);
BOOL ReadAdd(DWORD OffSet, BYTE *Code, size_t Size);
//void CharXY();
BYTE* CharAnalysis(BYTE* str);
void CharAna();
BOOL SEMain(int mode);
extern HMODULE hModule2, DLL;
typedef struct {
	BYTE *DATA;
	long W;
	long H;
	long B;
}PNGDATA;
int LoadPNG(const char *filepath, PNGDATA *IMAGE);

//extern DWORD *ReAdd;
extern void *RV, *RV2 ;
struct Version {
	int HM = 0;
	int LM = 0;
	int HL = 0;
	int LL = 0;

};
BOOL GetFileVersion(Version *Ver, HMODULE *hModle);

extern BYTE STR[8192];
struct OffSet {
	float Off = 0.0;
	float Width = 12.5;
};
BOOL GetFileVersion(Version *Ver, HMODULE *hModle);
extern char *Pstr[8];
extern bool INITED, Is980;
extern SYSTEMTIME sys_time;
void DrawTexture();
struct PageInfo {
	std::string File;
	//BYTE PageId[1];
	int OffSetX = 0;
	int OffSetY = 0;
	int PX = 0;
	int PY = 0;
	OffSet* Page=0;
	bool use = false;
};
extern char *localePath;
//void Dlog(int type, char* msg, ...);
//extern Version Ver;
struct WChar {
	bool use = false;
	BYTE str[2] = { 0 };
	BYTE ID = 0;
	long Size = 0;
	int UseSize = 0;
};
struct Addchar {
	DWORD Add = 0;
	BYTE *str = 0;
	wchar_t* wstr = 0;
	int size = 0;
};
extern BYTE WID[8];

class SEL {
	wchar_t *WPstr[8] = { L"1",L"2",L"3",L"4",L"5",L"6",L"7",L"DEF" };
	void Init(int ID, const wchar_t* str) {
		int C = 0;
	//	msgmgr(0, "ID:%d", ID);
		size_t size = wcslen(str);
		unsigned int i = 0;
		while (i<size) {
			if (str[i] == '\r' || str[i] == '\n'|| str[i] == ' ') {//XD XA
				i++;
				continue;
			}
			if (str[i] == '?') {
				//		alc = true;
				i++;C++;continue;
			};
			WChar* WT = &Wstr[str[i]];
			if (WT->use&&str[i] != '?') {
				//printf(Pstr[WIDToID(WT->ID)]);
				msgmgr(2, "%X->%X:%X str:%d 重复 PID:%d size:%d", C, WT->ID, WT->str[1], str[i],ID, size);
			//	printf();

			}
			else {
				WT->use = true;
				WT->ID = WID[ID];
				WT->str[0] = ID == 7 ? 0 : WID[ID];
				WT->str[1] = BYTE(C);
			}

			i++; C++;// C++;

		}

	}
	wchar_t* WGetConfig(int ID, wchar_t* str) {
		wchar_t TMP[256];
		swprintf(TMP, 256, L"PageChar%s", WPstr[ID]);
		return wcsstr(str, TMP);
	}


	WChar Wstr[65535];
	WCHAR *wstr = 0;

	BOOL GetInfo(Addchar *AC) {
		wchar_t *str = AC->wstr, Add[16];
		int size = AC->size;
		BYTE *CON = AC->str;
		int s = 0;
		if (CON == NULL)return 0;
		int i = 0, T = 0, j = 0;
		while (i<size&&str[i] != ';') {

			if (str[i] == '"') {
				j++,i++;
				continue;
			}
			if (j == 1 && s<16)Add[s++] = str[i];
			if (j == 3) {
				CON[T] = BYTE(str[i]);
				if (Wstr[str[i]].str[1] == 0) {
					CON[T] = '#';
				}
				else
					if (Wstr[str[i]].str[0] == 0) {
						CON[T] = Wstr[str[i]].str[1];
					}
					else {
						CON[T++] = Wstr[str[i]].str[0];
						CON[T] = Wstr[str[i]].str[1];
						//Wstr[str[i]].UseSize++;
					}
					T++;
					//
			}
			if (j == 4)j = 0;



			i++;
		}

		Add[s] = CON[T] = 0;
		//wprintf(L"WAdd:%s\n", Add);
		AC->Add = wcstol(Add, 0, 16);

		AC->size = T;
		return TRUE;
	}
public:

	BOOL WMainInit(CHAR *Conf) {
		memset(Wstr, 0, sizeof(Wstr));
		int wlen = MultiByteToWideChar(CP_ACP, 0, Conf, -1, NULL, 0);
		wstr = new WCHAR[wlen];
		MultiByteToWideChar(CP_ACP, 0, Conf, -1, wstr, wlen);
		if (wstr == NULL)return FALSE;
		bool Incom = false, Inread = false, begin = false;
		std::wstring str;
		wchar_t *ps;//, *ps2;

		for (int P = 0;P < 8;P++) {
			if ((ps = WGetConfig(P, wstr)) != 0) {
				Inread = true;
			}
			else {
				continue;
			}
			int s = 0;// s2 = 0;
			while (Inread) {
				if (!Incom&&ps[s] == '/'&&ps[s + 1] == '/') {
					Incom = true;
					s+=2;
					continue;
				}
				if (Incom) {
					if (ps[s] == '\n' || ps[s] == '\r') {
						Incom = false;
					}
					s++;
					continue;

				}
				if (ps[s] == '{') {

					begin = true;
					s++;
					continue;
				}
				if (ps[s] == '}') {
					begin = Inread = false;
					str.push_back('\0');
					Init(P, str.c_str());
					str.clear();
					break;
				}
				if (begin) {
					str = str + ps[s];
				}
				s++;
			}

		}
		return TRUE;
	}
	//bool Inread = false;int PageId = 0;





	BOOL Start() {
		WCHAR *str = 0,TMP[1024], Versum[20];
		size_t len=0, i = 0, j = 0;
		Version Ver;
		GetFileVersion(&Ver, &hModule2);
		wsprintf(Versum,L"[Start:%d%d%d%d]", Ver.HM, Ver.LM, Ver.HL, Ver.LL);
		str = wcsstr(wstr, Versum);
		wsprintf(Versum, L"[End:%d%d%d%d]", Ver.HM, Ver.LM, Ver.HL, Ver.LL);
		//strend= wcsstr(wstr, Versum);
		if ((len = (wcsstr(wstr, Versum) - str)) == 0)return FALSE;
		while (i <len) {
			TMP[j] = str[i];;
			if (str[i] == '\r' || str[i] == '\n'||  i >= len) {
				if(j!=0){
				Addchar AC;
				AC.str = new BYTE[j * 2];
				AC.wstr = TMP;
				AC.size = j;
				
				GetInfo(&AC);
				if (AC.Add != 0) {
					
					BYTE *P = (BYTE*)(Base + AC.Add);
					int k = 0;
					for (k = 0;AC.str[k] != 0 && k < 15;k++)  P[k] = AC.str[k];
					P[k] = 0;
				}
				delete[] AC.str;
				j = 0, i++;
				continue;
				}
			}
			i++, j++;
		}
		
		delete[] wstr;
		return TRUE;

	}
};
extern SEL WCharAdd;
class CharAdd {
private:
	WCHAR *Type[2] = { L"Config",L"PNG" };
	char *ResPath[7] = { "chs-font1.png","chs-font2.png","chs-font3.png","chs-menu.png","CN-font.png","chs-gui.cfg","CN-font.cfg" };
	int ResId[7] = { IDB_PNG1,IDB_PNG2,IDB_PNG3,IDB_PNG4,IDB_PNG5,IDR_CONFIG1,IDR_CONFIG2 };//IDR_CONFIG
	char ConfigFilePath[256] = "System/Config.ini";

	void InitChar(int ID, char* str) {
		try {
			if (ID == 0) {
				SetPage(str);return;
			}
			OffSet* TMP = GetPage(ID);
			std::string str2 = str;
			std::vector<std::string> str_list2;
			std::string buf;
			std::stringstream A(str);
			while (A >> buf) {
				if (*buf.c_str() != ' ')
					str_list2.push_back(buf);
			}
			unsigned int i = 0, k = 0;
			if (str_list2.size() != 512)  throw int(str_list2.size() / 2);
			while (str_list2.size() > i) {

				if (str_list2.size() < i + 1)  throw int(i);
				TMP[k].Off = float(atof(str_list2[i++].c_str()));

				TMP[k].Width = float(atof(str_list2[i++].c_str()));
				k++;

			};
		}
		catch (int err) {
			msgmgr(1, "读取块:Page%s->%X %d 时出现异常", Pstr[ID], err / 2, err);
			/*CHAR TMP[1024];
			GetLocalTime(&sys_time);
			snprintf(TMP, 1024, "%02d:%02d:%02d.%03d	读取块:Page%s->%X %d 时出现异常", sys_time.wHour, sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds, Pstr[ID], err / 2, err);
			std::ofstream Dlllog("DllError.log", std::ios::app);
			Dlllog << TMP << std::endl;
			Dlllog.close();*/
			//Dlog(2, "读取块:Page%s->%X %d 时出现异常\n", Pstr[ID], err / 2, err);
			return;
		}

	};
	void SetPage(char *str) {
		unsigned int i = 0;
		std::vector<std::string> str_list;
		std::string str2 = "";
		while (str[i] != '\0') {
			if (str[i] == '{') {
				i++;continue;
			}
			else if (str[i] == '\n' || str[i] == '\r' || str[i] == '	') {
				str[i] = ' ';
				;
			}

			if (str[i] == ',' || str[i] == '}' || str[i + 1] == '\0') {
				str_list.push_back(str2);
				str2 = "";

			}
			else {
				str2 = str2 + str[i];

			}
			i++;
		}


		unsigned int A = 0;
		BYTE PID1 = 0;
		int TMP = 0;
		while (A < str_list.size()) {

			if (A + 2 > str_list.size())throw (int)A;
			PID1 = BYTE(strtol(str_list[A++].c_str(), NULL, 16));
			if (TMP < 3) {
				Page[PID1].OffSetX = 16 + 16 * TMP;
				Page[PID1].PX = 256 + 256 * TMP;
				Page[PID1].PY = 512;
				Page[PID1].OffSetY = 0;
			}
			else {
				Page[PID1].OffSetX = 16 * (TMP - 3);
				Page[PID1].OffSetY = 16;
				Page[PID1].PX = 256 * (TMP - 3);
				Page[PID1].PY = 512 + 256;
			}
			if (PID1 != 0) {
				Page[PID1].use = true;
			}
			Page[PID1].Page = GetPage(TMP + 1);
			PageId[TMP++] = PID1;
			Page[PID1].File = str_list[A++].c_str();
		}

	}
	BOOL WriteRes(int ID, int t, const char *str1, const char *str2) {
		char str[256];
		snprintf(str, 256, "%s%s", str1 == 0 ? "" : str1, str2);

		HRSRC hRsrc = FindResource(DLL, MAKEINTRESOURCE(ID), Type[t]);
		if (hRsrc != NULL) {
			HGLOBAL hGlobal = LoadResource(DLL, hRsrc);
			if (hGlobal != NULL) {
				LPVOID pBuffer = LockResource(hGlobal);
				DWORD dwSize = SizeofResource(DLL, hRsrc);
				FILE *fp;
				fopen_s(&fp, str, "wb+");
				if (fp != 0) {
					fwrite(pBuffer, sizeof(BYTE), dwSize, fp);
					fclose(fp);
					return TRUE;
				}
			}
		}
		return FALSE;
	}
	char* GetConfig(int ID, char* str) {
		char TMP[256];
		snprintf(TMP, 256, "Page%s", Pstr[ID]);
		return strstr(str, TMP);
	}
public:

	BOOL MainInit() {
		FILE *fp;
		//AD=std::ofstream("A.txt", std::ios::app);
		fopen_s(&fp, ConfigFilePath, "rb+");
		if (fp == NULL) {
			WriteRes(IDR_CONFIG, 0, 0, ConfigFilePath);
			//	fclose(fp);
			InitFile();
			fopen_s(&fp, ConfigFilePath, "rb+");
		}
		fseek(fp, 0, SEEK_END);
		DWORD FileSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char *Config = new char[FileSize];
		if (Config == 0)return FALSE;
		fread(Config, sizeof(char), FileSize, fp);
		char *pVer = 0, Verstr[] = "LocalVersion", Versum[20];
		Version Ver;
		GetFileVersion(&Ver, &DLL);
		snprintf(Versum, 16, "%d%d%d%d", Ver.HM, Ver.LM, Ver.HL, Ver.LL);
		int NeedInit = 0;
		if ((pVer = strstr(Config, Verstr)) != 0) {
			int i = 0;
			while (pVer[0] != 0 && pVer[0] != '\n')if ((i = atoi(pVer++)) > 0)break;
			//if (i != 0) {
			char sum[16];
			snprintf(sum, 16, "%d", i);
			if (strcmp(sum, Versum) != 0) {
				fseek(fp, strstr(Config, Verstr) - Config, SEEK_SET);
				NeedInit = 1;
			}
			//}else {}
		}
		else {
			fseek(fp, strrchr(Config, '}') - Config + 1, SEEK_SET);
			NeedInit = 2;
		}
		if (NeedInit) {
			char str[256];
			size_t Size = snprintf(str, 256, NeedInit>1 ? "\n%s: %s\n" : "%s: %s\n", Verstr, Versum);
			fwrite(str, sizeof(char), Size, fp);
			InitFile();
		}
		fclose(fp);
		//version
		//	int i = 0;
		bool Incom = false, Inread = false, begin = false;
		std::string str;
		char *ps = 0;
		for (int P = 0;P < 8;P++) {
			if ((ps = GetConfig(P, Config)) != 0) {
				Inread = true;
			}
			else {
				continue;
			}

			int s = 0;//, s2 = 0;
			while (Inread) {
				if (ps[s] == '/' || ps[s] == ';') {
					Incom = true;
					s++;
					continue;

				}
				if (Incom) {
					if (ps[s] == '\n' || ps[s] == '\r') {
						Incom = false;
					}
					s++;
					continue;

				}
				if (ps[s] == '{') {
					begin = true;
					s++;
					continue;
				}
				if (ps[s] == '}') {
					;
					begin = Inread = false;
					str.push_back('\0');
					char *TMP = new char[str.size()];
					if (TMP == 0)  return FALSE; ;
					strcpy_s(TMP, str.size(), str.c_str());
					InitChar(P, TMP);
					delete[] TMP;
					str.clear();
					//				printf("\n完成");
					break;
				}
				if (begin) {
					str = str + ps[s];

				}
				s++;
			}

		}
		
		for (int i = 0;i < 8;i++) {
				WID[i] = PageId[i];
			}
	
		WCharAdd.WMainInit(Config);
		delete[] Config;
		return TRUE;
	}

	OffSet* GetPage(int ID) {

		switch (ID) {
		case 1:return Page1;break;
		case 2:return Page2;break;
		case 3:return Page3;break;
		case 4:return Page4;break;
		case 5:return Page5;break;
		case 6:return Page6;break;
		case 7:return Page7;break;
		default:return 0;break;
		}
	}
	//bool Inread=false;

	OffSet* PidToPage(int PID) {
		for (int i = 1;i < 8;i++) {
			if (PageId[i] == PID) {
				OffSet *PAGE = GetPage(i);
				return PAGE;
			}
		}
		return 0;
	}
	


	void InitFile() {
		for (int i = 0;i < 7;i++)
			WriteRes(ResId[i], i > 4 ? 0 : 1, localePath, ResPath[i]);

	}

	PageInfo Page[256];
	BYTE PageId[8] = { 0 };
	OffSet Page1[256];
	OffSet Page2[256];
	OffSet Page3[256];
	OffSet Page4[256];
	OffSet Page5[256];
	OffSet Page6[256];
	OffSet Page7[256];

};
class SEL;
extern CharAdd CharADD;
void GetCharXYOffAndWid(), GetWidth980();
extern DWORD *FunAdd,Base;
extern void* RE0, *RE1, *RE2;
void GetCharXYOW974();
void GetWidth974();
extern int *start;
void Start();
void SetBackWid980();


