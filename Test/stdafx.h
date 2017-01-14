// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO:  在此处引用程序需要的其他头文件
#include <windows.h>
//#include <tchar.h>
//#include <iostream>
#include <vector>
#include <sstream> 
#include <fstream>
void TexInit();
extern DWORD glTexAdd, *glTex2DAdd, Base;
extern HANDLE mProc;
extern bool ReTex;
extern char *SYSTEMPATH;
void msgmgr(int type, char* msg, ...);
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
extern void *RV, *RV2, *TexEnd;
struct Version {
	int HM = 0;
	int LM = 0;
	int HL = 0;
	int LL = 0;

};

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
	OffSet* Page = 0;
	bool use = false;
};
extern char *localePath;
class CharD {
public:
	std::wstring Name, Value;
	CharD(std::wstring N, std::wstring V) {
		Name = N;
		Value = V;

	}
	void claer() {
		Name.clear();
		Value.clear();
	}


};
class wcscstr {
private:
	CHAR *str = 0;
	WCHAR *wstr = 0;
public:
	~wcscstr() {
		if (str) { delete[] str;str = NULL; }
		if (wstr) { delete[] wstr;wstr = 0; }
	}
	char* WcharToChar(const wchar_t *wc, size_t l)
	{
		if (str) { delete[] str;str = NULL; }
		if (l == NULL)l = wcslen(wc);
		int len = WideCharToMultiByte(CP_ACP, 0, wc, l, NULL, 0, NULL, NULL);
		str = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, wc, l, str, len, NULL, NULL);
		str[len] = '\0';
		return str;
	}

	wchar_t* CharToWchar(const char* c, size_t L)
	{
		if (wstr) { delete[] wstr;wstr = 0; }
		if (L == NULL)L = strlen(c);
		int len = MultiByteToWideChar(CP_ACP, 0, c, L, NULL, 0);
		wstr = new wchar_t[len + 1];
		MultiByteToWideChar(CP_ACP, 0, c, L, wstr, len);
		wstr[len] = '\0';
		return wstr;
	}
	wchar_t* AutoCharToWchar(const char* c)
	{
		if (wstr) { delete[] wstr;wstr = 0; }
		size_t L = strlen(c);
		int len = MultiByteToWideChar(CP_ACP, 0, c, L, NULL, 0);
		wstr = new wchar_t[len + 1];
		MultiByteToWideChar(CP_ACP, 0, c, L, wstr, len);
		wstr[len] = '\0';
		return wstr;
	}
};
class CharDef {
private:

	WCHAR *wstr = 0;
	wchar_t* CharToWchar(const char* c, size_t L)
	{
		if (wstr) { 
			msgmgr(3, "WSTR=>>");
			delete[] wstr;wstr = 0; 
			msgmgr(3, "WST<<<==");
		}
		msgmgr(3, "WST<<<==0");
		int len = MultiByteToWideChar(CP_ACP, 0, c, L, NULL, 0);
		msgmgr(3, "WST<<<==1");
		wstr = new wchar_t[len + 1];
		MultiByteToWideChar(CP_ACP, 0, c, L, wstr, len);
		msgmgr(3, "WST<<<==2");
		wstr[len] = '\0';
		return wstr;
	}
	void clear() {
		//		msgmgr(2, "清除");
		while (!str.empty()) {
			CharD* P;
			P = str.front();
			P->claer();
			delete P;
			str.erase(str.begin());


		};
		delete[] wstr;
		wstr = 0;

	}

public:
	std::vector<CharD*> str;
	void Initstr(char *Config) {
		clear();
		char *P1 = 0, *P2 = 0;
		size_t len = 0;
		if ((P1 = strstr(Config, "[STRDEF]") + 9) != 0) {
			//if ((P2 = strstr(Config, "[ENDDEF]")) == 0)else
			len = ((P2 = strstr(Config, "[ENDDEF]")) == 0) ? 0 : P2 - P1;
			if (len > 0) {
				msgmgr(3, "Initstring==>>>>L:%d",len);
				CharToWchar(P1, len);
				msgmgr(3, "Initstred");
				Init();

				return;
			}
			else {
				msgmgr(1, "字串定义未闭合");
			}
		};


	}
	void Init() {
		//	msgmgr(2, "初始化字串定义");
		DWORD i = 0, j = 0, k = 0;
		WCHAR P = 0;
		std::wstring TMPN, TMPV;
		bool st = false;
		wcscstr WA;
		while ((P = wstr[i]) != 0 && P != ';') {
			if (P == '=')j++;
			if (j == 0) {

				if (P != ' '&& P != '	' && !st)  st = true;
				else if ((P == ' ' || P == '	') && st) st = false;
				if (st&&P != '\r'&&P != '\n')TMPN.push_back(P);
			}
			else if (j == 1) {

				if (P == '"')k++;
				else if (k == 1 && P != '\r'&&P != '\n')TMPV.push_back(P);
				if (k == 2 || P == '\r' || P == '\n') {
					Add(TMPN.c_str(), TMPV.c_str());
					TMPN.clear();TMPV.clear();
					j = 0, k = 0;
					st = false;
				};
			}

			i++;
		}
		msgmgr(3, "Inited");
	}
	~CharDef() {
		clear();

	}

	bool Add(std::wstring N, std::wstring V) {
		wcscstr WA, WB;
		//msgmgr(3, "Add :N:%s:V:%s", WA.WcharToChar(N.c_str(), N.size()), WB.WcharToChar(V.c_str(), V.size()));
		if (Find(N) == NULL) {
			str.push_back(new CharD(N, V));
			//	msgmgr(3, "添加 :N:%s:V:%s", WA.WcharToChar(N.c_str(), N.size()), WB.WcharToChar(V.c_str(), V.size()));
			return true;
		}

		msgmgr(2, "重定义:%s=%s", WA.WcharToChar(N.c_str(), N.size()), WB.WcharToChar(V.c_str(), V.size()));
		return false;
	}
	CharD* Find(std::wstring A) {//operator =
		wcscstr WA, WB;
		//	msgmgr(3, "查找 N:%s", WA.WcharToChar(A.c_str(), A.size()));
		for (std::vector<CharD*>::const_iterator i = str.begin();i != str.end();i++) {

			if ((*i)->Name.compare(A) == 0) {
				//		msgmgr(3, "找到 FN:%s:FV:%s", WA.WcharToChar((*i)->Name.c_str(), (*i)->Name.size()), WB.WcharToChar((*i)->Value.c_str(), (*i)->Value.size()));
				return *i;
			}
			//	else { msgmgr(1, "判断不相等:[%s]:[%s]", WA.WcharToChar((*i)->Name.c_str(), (*i)->Name.size()),WB.WcharToChar(A.c_str(),A.size())); }
		}
		return NULL;
	}


};
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
	CharDef CD;
	wchar_t *WPstr[8] = { L"1",L"2",L"3",L"4",L"5",L"6",L"7",L"DEF" };
	void Init(int ID, const wchar_t* str) {
		int C = 0;
		//	msgmgr(0, "ID:%d", ID);
		size_t size = wcslen(str);
		unsigned int i = 0;
		while (i<size) {
			if (str[i] == '\r' || str[i] == '\n' || str[i] == ' ') {//XD XA
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
				msgmgr(2, "%X->%X:%X str:%d 重复 PID:%d size:%d", C, WT->ID, WT->str[1], str[i], ID, size);
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
		wchar_t *str = wcsstr(AC->wstr, L"=") + 1, P = 0;
		int size = AC->size;
		BYTE *CON = AC->str;
		wcscstr WA, WB;


		int i = 0, T = 0, j = 0, Ti = 0;
		if ((AC->Add = wcstol(AC->wstr, 0, 16)) != 0) {
			if (str != NULL&&CON != NULL) {

				//	msgmgr(3, "START[%d]",size);
				//	msgmgr(3, "ST字串:%s", WA.WcharToChar(AC->wstr, 0));
				while (i < size && (P = str[i++]) != ';')if (P == '"')Ti++;
				i = 0;


				if (Ti == 2)
					while (str[i] != 0 && (P = str[i]) != ';') {

						if (P == '"') {
							j++, i++;
							continue;
						}

						if (j == 1) {
							CON[T] = BYTE(P);
							if (Wstr[P].str[1] == 0) {
								CON[T] = '#';
								char *P2 = WA.WcharToChar(&P, 1);
								if (nullstr.find(P2) == std::string::npos)nullstr += P2;

							}
							else
								if (Wstr[P].str[0] == 0) {
									CON[T] = Wstr[P].str[1];
								}
								else {
									CON[T++] = Wstr[P].str[0];
									CON[T] = Wstr[P].str[1];
								}
								T++;
						}
						if (j == 2)break;
						i++;
					}

				else if (Ti == 0) {
					bool st = false;
					std::wstring ws;
					DWORD R = 0;
					while ((P = str[i++]) != ';'&&P != 0) {
						if ((P == ' ' || P == '	') && st)break;
						else if (P != ' '&& P != '	' && !st)st = true;
						if (st&&P != '\r'&&P != '\n')ws.push_back(P);
					}
					//msgmgr(3, "GETwsTMP:[%s]", WA.WcharToChar(ws.c_str(), ws.size()));
					CharD *CP;
					if ((CP = CD.Find(ws.c_str())) != NULL) {
						const WCHAR *P2 = CP->Value.c_str();

						//	msgmgr(3, "C:%s,P2V:%s", WA.WcharToChar(CP->Name.c_str(), CP->Name.size()),WB.WcharToChar(P2, CP->Value.size()));
						while ((P = P2[R++]) != 0) {
							CON[T] = BYTE(P);
							if (Wstr[P].str[1] == 0) {
								CON[T] = '#';
								char *P3 = WA.WcharToChar(&P, 1);
								if (nullstr.find(P3) == std::string::npos)nullstr += P3;
							}
							else if (Wstr[P].str[0] == 0)CON[T] = Wstr[P].str[1];
							else {
								CON[T++] = Wstr[P].str[0];
								CON[T] = Wstr[P].str[1];
							}
							T++;

						}

					}
					else {
						msgmgr(1, "翻译错误 字串[%s]未定义", WA.WcharToChar(ws.c_str(), ws.size()));
						AC->Add = 0;
					};

				}
				else if (Ti) {
					msgmgr(1, "翻译错误 请检查引号是否成对出现 字串[%d]:%s ", size, WA.WcharToChar(AC->wstr, 0));
					AC->Add = 0;
				}
			}
			else {
				msgmgr(1, "翻译错误 格式不正确或内存不足 字串[%d]:%s ", size, WA.WcharToChar(AC->wstr, 0));
				AC->Add = 0;
			}
		}
		CON[T] = 0;
		//wprintf(L"WAdd:%s\n", Add);

		//msgmgr(3, "33字串[%d]:%s Add:0x%X T:%d", size, WA.WcharToChar(AC->wstr, 0),AC->Add,T);
		AC->size = T;
		//	msgmgr(3, "Ti:%d AC->Add:%X 字串[%d]:%s ==>>>[T:%d]", Ti, AC->Add,size, WcharToChar(str, size),T);
		return TRUE;
	}

	std::string nullstr;

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
					s += 2;
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
		msgmgr(3, "WMainInited");
		CD.Initstr(Conf);
		msgmgr(3, "Initstr->>>>>");
		WStart();
		msgmgr(3, "WStart->>>>>");
		return TRUE;
	}
	//bool Inread = false;int PageId = 0;





	BOOL WStart() {

		WCHAR *str = 0, Versum[20];
		std::wstring wstrTMP;
		size_t len = 0, i = 0;
		Version Ver;
		GetFileVersion(&Ver, &hModule2);
		wcscstr WA;
		/*	for (std::vector<CharD*>::const_iterator i = CD.str.begin();i != CD.str.end();i++) {

		msgmgr(2, "列表:[%s]:[%s]", WA.WcharToChar((*i)->Name.c_str(), (*i)->Name.size()),WA.WcharToChar((*i)->Value.c_str(), (*i)->Value.size()));
		}*/
		int l1 = wsprintf(Versum, L"[Start:%d%d%d%d]", Ver.HM, Ver.LM, Ver.HL, Ver.LL);
		str = wcsstr(wstr, Versum) + l1;
		wsprintf(Versum, L"[End:%d%d%d%d]", Ver.HM, Ver.LM, Ver.HL, Ver.LL);
		//strend= wcsstr(wstr, Versum);

		if ((len = (wcsstr(wstr, Versum) - str)) == 0)return FALSE;
		//msgmgr(3, "调试 str:%p len:%d", str,len);
		//	msgmgr(3, "调试:%s", WA.WcharToChar(wstr, len/2));
		while (i < len) {
			wstrTMP.push_back(str[i]);
			if (str[i] == '\r' || str[i] == '\n' || str[i] == ';') {

				Addchar AC;
				AC.str = new BYTE[wstrTMP.size() * 2];
				AC.wstr = (WCHAR*)wstrTMP.c_str();
				AC.size = wstrTMP.size();
				//msgmgr(3, "调试 TMP:%s J:%d", WA.WcharToChar(TMP, j), j);
				GetInfo(&AC);
				if (AC.Add != 0) {
					BYTE *P = (BYTE*)(Base + AC.Add);
					//msgmgr(3, "写地址:0x%08p Add:0x%08X", P,AC.Add);
					//memcpy(P, AC.str, AC.size);
					//P[AC.size] = 0;
					/*
					int k = 0;
					for (k = 0;AC.str[k] != 0 && k < 15;k++)  P[k] = AC.str[k];
					P[k] = 0;*/
				}
				wstrTMP.clear();
				delete[] AC.str;


			}
			i++;
		}
		if (nullstr.size()) {
			msgmgr(2, "以下字符未配置:%s", nullstr.c_str());
			nullstr.clear();
		}
		delete[] wstr;
		msgmgr(3, "WStarted");
		return TRUE;

	}
};
void GetError(int d);
extern SEL WCharAdd;
extern WCHAR *Type[2];
extern char *ResPath[7], *ConfigFilePath;
extern int ResId[7];//IDR_CONFIG

class CharAdd {
private:
	void Err(int ID, int err) {
		msgmgr(1, "读取块:Page%s->%X %d 时出现异常", Pstr[ID], err / 2, err);

	}

	void InitChar(int ID, char* str) {
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
		if (str_list2.size() != 512)  Err(ID, str_list2.size() / 2);
		while (str_list2.size() > i) {

			if (str_list2.size() < i + 1)  Err(ID, i);
			TMP[k].Off = float(atof(str_list2[i++].c_str()));

			TMP[k].Width = float(atof(str_list2[i++].c_str()));
			k++;

		};

	};
	void SetPage(char *str) {
		unsigned int i = 0;
		std::vector<std::string> str_list;
		std::string str2 = "";
		bool st = false;
		while (str[i] != '\0') {
			if (str[i] == '{') {
				i++;continue;
			}
			else if (str[i] == '\n' || str[i] == '\r' || str[i] == '	') {
				str[i] = ' ';
			}
			if (str[i] != ' ')st = true;
			if (str[i] == ',' || str[i] == '}' || str[i + 1] == '\0') {
				str_list.push_back(str2);
				//	msgmgr(3, "SETPAGE:%s", str2.c_str());
				str2 = "";
				st = false;
			}
			else if (st) {
				str2.push_back(str[i]);
				//	str2+=str[i];
			}
			i++;
		}


		unsigned int A = 0;
		BYTE PID1 = 0;
		int TMP = 0;
		while (A < str_list.size()) {

			if (A + 2 > str_list.size())Err(0, A);
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
			//	const char *CP= str_list[A++].c_str();
			//	int AA = 0;
			//while (CP[AA++] != 0|| CP[AA] == ' '|| CP[AA] == '	');
			Page[PID1].File = str_list[A++].c_str();
		}

	}

	BOOL WriteRes(int ID, int t, const char *Path) {

					
		msgmgr(1, "写出资源 ID:%d TYPE:%d Path:%s", ID, t, Path);
		return TRUE;
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
		//char CPath[MAX_PATH];
	//	snprintf(CPath, MAX_PATH, "%s/%s", SYSTEMPATH, ConfigFilePath);
		fopen_s(&fp, ConfigFilePath, "rb+");
		if (fp == NULL) {
			msgmgr(3, "配置文件初始化:%s:%s:%s", ConfigFilePath, SYSTEMPATH, ConfigFilePath);
			if (!WriteRes(0, 0, ConfigFilePath)) {
				GetError(15);
				return FALSE;
			};//错误标记15;
			  //	fclose(fp);
			InitFile();
			fopen_s(&fp, ConfigFilePath, "rb+");
		}
		if (fp == NULL) {
			GetError(14);
			return FALSE;
		};//错误标记14
		fseek(fp, 0L, SEEK_END);
		DWORD FileSize = ftell(fp);
		fseek(fp, 0L, SEEK_SET);
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
			//	char *str=new char[256];
			char Tstr[256];
			size_t Size = snprintf(Tstr, 256, NeedInit>1 ? "\n%s: %s\n" : "%s: %s\n", Verstr, Versum);
			fwrite(Tstr, sizeof(char), Size, fp);
			//delete[] str;
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
		//msgmgr(3, "------------------");
		msgmgr(3, "MainInited");
		WCharAdd.WMainInit(Config);
		msgmgr(3, "ALLInited");
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
		char FPATH[MAX_PATH];
		for (int i = 0;i < 7;i++) {
			snprintf(FPATH, MAX_PATH, "%s/%s/%s", SYSTEMPATH, localePath, ResPath[i]);
			WriteRes(ResId[i], i > 4 ? 0 : 1, FPATH);
		}

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