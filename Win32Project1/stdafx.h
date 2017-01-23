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
void TexInit();
extern DWORD glTexAdd,*glTex2DAdd, Base;
extern HANDLE mProc;
extern bool ReTex;
extern std::string SYSTEMPATH,localePath;
extern float Old1, Old2;
BYTE* CharAnalysis972(BYTE* str);
void msgmgr(int type, char* msg, ...),SetBack972(), GetWidthXYOFF972();
BOOL WriteAdd(DWORD OffSet, BYTE *Code, size_t Size);
BOOL ReadAdd(DWORD OffSet, BYTE *Code, size_t Size);
//void CharXY();
BYTE* CharAnalysis(BYTE* str);
void CharAna();
BOOL SEMain(int mode);
extern HMODULE hModule2, DLL;
typedef struct {
	BYTE *DATA;
	long fmt = 0;
	long W;
	long H;
	long B;
}PNGDATA;
int LoadPNG(const char *filepath, PNGDATA *IMAGE);

//extern DWORD *ReAdd;
extern void *RV, *RV2 , *TexEnd;
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
	float Width = 12;
};
BOOL GetFileVersion(Version *Ver, HMODULE *hModle);
extern char *Pstr[8];
extern bool INITED, Is980;
extern SYSTEMTIME sys_time;
void DrawTexture();
class PageInfo {
public:

	void Init() {
		if (Page != 0)delete[] Page;
		Page = 0;
		OffSetX = OffSetY = PX = PY = ID = PID = 0;
		File.clear();
		use = false;
	}
	PageInfo() {
		Init();
	};
	PageInfo(BYTE I,BYTE PI,int X,int Y,int OX,int OY,std::string F) {
		OffSetX = OX, OffSetY = OY, PX = X, PY = Y, ID = I,PID=PI, File = F;
	};
	~PageInfo() {
		Init();
	}
	std::string File;
	//BYTE PageId[1];
	int OffSetX = 0;
	int OffSetY = 0;
	int PX = 0;
	int PY = 0;
	BYTE PID = 0;// 页映射ID
	BYTE ID=0;//页序号ID 
	OffSet* Page=0;
	bool use = false;
};


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
	CHAR *str=0;
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
		if(L==NULL)L = strlen(c);
		int len = MultiByteToWideChar(CP_ACP, 0, c, L, NULL, 0);
		wstr = new wchar_t[len + 1];
		MultiByteToWideChar(CP_ACP, 0, c, L, wstr, len);
		wstr[len] = '\0';
		return wstr;
	}
	wchar_t* AutoCharToWchar(const char* c)
	{
		if (wstr) { delete[] wstr;wstr = 0; }
		size_t L=strlen(c);
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
		if (wstr) { delete[] wstr;wstr = 0; }
		int len = MultiByteToWideChar(CP_ACP, 0, c, L, NULL, 0);
		wstr = new wchar_t[len + 1];
		MultiByteToWideChar(CP_ACP, 0, c, L, wstr, len);
		wstr[len] = '\0';
		return wstr;
	}
	void clear() {
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
		 if ((P1 = strstr(Config, "[STRDEF]")+8) != 0) {
			 len = ((P2 = strstr(Config, "[ENDDEF]")) == 0) ? 0 : P2 - P1;
			 if (len > 0) {
				 CharToWchar(P1, len);
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
		DWORD i = 0,j=0,k=0;
		WCHAR P = 0;
		std::wstring TMPN, TMPV;
		bool st = false;
		wcscstr WA;
		while ((P = wstr[i]) != 0 && P != ';') {
			if (P == '=')j++;
			if (j == 0) {
				
				if (P != ' '&& P != '	'&& !st)  st = true;
				else if ((P == ' '|| P == '	') && st) st = false;
				if (st&&P != '\r'&&P != '\n')TMPN.push_back(P);
			}
			else if (j==1) { 
				
				if (P == '"')k++;
				else if (k == 1&& P != '\r'&&P != '\n')TMPV.push_back(P);
				if (k == 2 || P == '\r' || P == '\n') {
					Add(TMPN.c_str(), TMPV.c_str());
					TMPN.clear();TMPV.clear();
					j = 0, k = 0;
					st = false;
				};
			}
			
			i++;
		}
	}
	~CharDef() {
		clear();

	}
	
	bool Add(std::wstring N, std::wstring V) {
		
		if (Find(N)==NULL) {
			str.push_back(new CharD(N, V));
			return true;
		}
		wcscstr WA, WB;
		msgmgr(2, "重定义:%s=%s", WA.WcharToChar(N.c_str(), N.size()), WB.WcharToChar(V.c_str(), V.size()));
		return false;
	}
	CharD* Find(std::wstring A) {//operator =
		for (std::vector<CharD*>::const_iterator i = str.begin();i != str.end();i++){
			
			if ((*i)->Name.compare(A) == 0) { 
				return *i; }
		}
		return NULL;
	}


};
struct WChar {
	bool use = false;
	BYTE str[2] = { 0 };//页ID XY
	BYTE ID = 0;//页ID
	long Size = 0;
	int UseSize = 0;
};
struct Addchar {
	DWORD Add = 0;
	BYTE *str = 0;
	wchar_t* wstr = 0;
	int size = 0;
};
extern BYTE WID[256];
class MEMADD {
	void GetCode() {
		DWORD CODE = (DWORD)Fun - ((DWORD)hModule2 + Offset) - 5;
		BYTE* P = (BYTE*)&CODE;
		for (int i = 0;i < 4;i++) {
			Code[i + 1] = P[i];
		}
	}
public:
	DWORD Offset = 0;
	LPVOID Fun = 0;
	BYTE *Code = 0, *CodeOld = 0;
	size_t Size = 0;
	BYTE Method = 0xE8;
	bool sted = false;
	MEMADD(LPVOID F, DWORD Of, BYTE Met, size_t s) {
		Offset = Of, Fun = F, Method = Met, Size = s;
		Code = new BYTE[s], CodeOld = new BYTE[s];
		ReadAdd(Offset, CodeOld, Size);
		GetCode();
		for (size_t i = 5;i < Size;i++)Code[i] = 0x90;
		Code[0] = Method;
	}
	~MEMADD() {
		End();
		if (Code)delete[] Code;
		if (CodeOld)delete[] CodeOld;
		Code = CodeOld = 0;

	}
	void Start() {
		if (!sted) {
			WriteAdd(Offset, Code, Size);

			sted = true;
		}
	}
	void End() {
		if (sted) {

			WriteAdd(Offset, CodeOld, Size);

			sted = false;
		}
	}
};
class RWMEM {
	std::vector<MEMADD*> MA;
public:
	void Add(LPVOID Fun, DWORD Offset, BYTE Met, size_t s) {
		MA.push_back(new MEMADD(Fun, Offset, Met, s));
	};
	~RWMEM() {
		while (!MA.empty()) {
			MEMADD *P = MA.front();
			P->End();
			MA.erase(MA.begin());
			if (P != 0)delete P;

		}
	}
	void Start() {
		for (std::vector<MEMADD*>::iterator i = MA.begin();i != MA.end();i++) {

			(*i)->Start();
			
		}



	}
	void End() {
		for (std::vector<MEMADD*>::iterator i = MA.begin();i != MA.end();i++) {
			(*i)->End();
			

		}
	}

};

class RES {

public:

	std::string Name, Path;
	std::wstring Type;
	DWORD Id = 0;

	RES(std::wstring TYPE, std::string NAME, std::string PATH, DWORD ID) {
		Name = NAME, Type = TYPE, Id = ID, Path = SYSTEMPATH + "/" + PATH + "/" + Name;
	}
};
extern std::vector<RES*> res;
class SEL {
	CharDef CD;
	void Init(int ID, std::wstring* ws) {
		
		int C = 0;
		const wchar_t *str = ws->c_str();
		size_t size = ws->size(),i = 0;
		while (i<size) {
			if (str[i] == '\r' || str[i] == '\n'|| str[i] == ' ') {//XD XA
				i++;
				continue;
			}
			if (str[i] == '?') {
				//		alc = true;
				i++;C++;continue;
			};
			if (str[i] == 0)break;
			WChar* WT = &Wstr[str[i]];
			if (WT->use&&str[i] != '?') {
				msgmgr(2, "%X->%X:%X str:%d 重复 PID:%d size:%d", C, WT->ID, WT->str[1], str[i],ID, size);

			}
			else {
				WT->use = true;
				WT->ID = WID[ID];
				WT->str[0] = ID? WID[ID] :0 ;
				WT->str[1] = BYTE(C);
			}

			i++; C++;// C++;

		}

	}
	wchar_t* WGetConfig(int ID, wchar_t* str) {
		wchar_t TMP[32];
		if(ID)swprintf(TMP, 256, L"PageChar%d", ID);//WPstr[ID]
		else return wcsstr(str, L"PageCharDEF");
		return wcsstr(str, TMP);
	}

	
	WChar Wstr[65535];
	WCHAR *wstr = 0;
	
	BOOL GetInfo(Addchar *AC) {
		wchar_t *str = wcsstr(AC->wstr, L"=")+1, P=0;
		int size = AC->size;
		BYTE *CON = AC->str;
		wcscstr WA, WB;
		

		int i = 0, T = 0, j = 0, Ti = 0;
		AC->Add = wcstol(AC->wstr, 0, 16);
		if(AC->Add){
		if (str != NULL&&CON != NULL) {
			
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
			while ((P = str[i++]) != ';'&&P!=0) {
					if ((P == ' ' || P == '	') && st)break;
					else if (P != ' '&& P != '	'&& !st)st = true;
					if (st&&P != '\r'&&P != '\n')ws.push_back(P);
			}
			CharD *CP;
			if ((CP = CD.Find(ws.c_str())) != NULL) {
				const WCHAR *P2 = CP->Value.c_str();
				
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
		CON[T] = 0;
		}
		else {
			msgmgr(1, "翻译错误 格式不正确或内存不足 字串[%d]:%s ", size, WA.WcharToChar(AC->wstr, 0));
			AC->Add = 0;
		}
		}
		
		AC->size = T;
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
		
		std::wstring str;
		wchar_t *ps;//, *ps2;

		for (int P = 0;P < 256;P++) {
			ps = WGetConfig(P, wstr);
			if (ps) {
				int s = 0;// s2 = 0;
				bool Incom = false, begin = false;
				while (s < 10240) {
					if (!Incom&&ps[s] == '/'&&ps[s + 1] == '/') {
						Incom = true;
						s += 2;
						continue;
					}
					if (Incom) {
						if (ps[s] == '\n' || ps[s] == '\r')Incom = false;
						s++;
						continue;

					}
					if (ps[s] == '{') {

						begin = true;
						s++;
						continue;
					}
					if (ps[s] == '}') {
						begin = false;
						//str.push_back('\0');
						Init(P, &str);
						str.clear();
						break;
					}
					if (begin) {
						str.push_back(ps[s]);
					}
					s++;
				}
			}
		}
		CD.Initstr(Conf);
		WStart();
		return TRUE;
	}




	BOOL WStart() {
	
		WCHAR *str = 0,Versum[20];
		std::wstring wstrTMP;
		size_t len = 0, i = 0;
		Version Ver;
		GetFileVersion(&Ver, &hModule2);
		wcscstr WA;
		int l1=wsprintf(Versum, L"[Start:%d%d%d%d]", Ver.HM, Ver.LM, Ver.HL, Ver.LL);
		if ((str = wcsstr(wstr, Versum)) == 0)return FALSE;
			str+= l1;
		wsprintf(Versum, L"[End:%d%d%d%d]", Ver.HM, Ver.LM, Ver.HL, Ver.LL);
		if ((len = (wcsstr(wstr, Versum) - str)) <= 0)return FALSE;
		while (i < len&&str[i]!=0) {
			wstrTMP.push_back(str[i]);
			if (str[i] == '\r' || str[i] == '\n' || str[i] == ';'|| str[i]==0) {
				
					Addchar AC;
					AC.str = new BYTE[wstrTMP.size() * 2];
					AC.wstr = (WCHAR*)wstrTMP.c_str();
					AC.size = wstrTMP.size();
					GetInfo(&AC);
					if (AC.Add != 0) {
						BYTE *P = (BYTE*)(Base + AC.Add);
						memcpy(P, AC.str, AC.size);
						P[AC.size] = 0;
					}
					wstrTMP.clear();
					delete[] AC.str;
				
				
			}
			i++;
		}
		if (nullstr.size()){msgmgr(2, "以下字符未配置:%s", nullstr.c_str());
		nullstr.clear();
	}
		delete[] wstr;
		return TRUE;

	}
};
void GetError(int d);
extern SEL WCharAdd;
extern WCHAR *Type[2];
extern char *ResName[7], ConfigFilePath[256] ;
extern int ResId[8];//IDR_CONFIG
class CharAdd {
private:
	void Err(int ID,int err) {
		msgmgr(1, "读取块:Page%d->%X %d 时出现异常", ID, err / 2, err);

	}

	void InitChar(int ID, std::string* str) {
			if (ID == 0) {
				SetPage(str->c_str());return;
			}
			OffSet* TMP = GetPage(ID);
			if (TMP == 0)return;
			
			//std::string str2 = str;
			std::vector<std::string> str_list2;
			std::string buf;
			std::stringstream A(str->c_str());
			size_t k = 0;
			bool of = false;
			while (A >> buf) {
				of = !of;
				if(of)
				TMP[k].Off = float(atof(buf.c_str())) / 256.0f;//<<<<<<<<<<<<<<<<<<<<2017019
				else
				TMP[k++].Width = float(atof(buf.c_str()));
				buf.clear();

			
			
			}

	};
	void SetPage(const char *str) {
		unsigned int i = 0;
		std::vector<std::string> str_list;
		std::string str2;
		bool st = false;
		while (str[i] != '\0') {
			if (str[i] == '{'|| str[i] == '\n' || str[i] == '\r' || str[i] == '	') {
				i++;continue;
			}
			if (str[i] != ' ')st = true;
			if (str[i] == ',' || str[i] == '}' || str[i + 1] == '\0') {
				str_list.push_back(str2);
				str2.clear();
				st = false;
			}
			else if(st){
				str2.push_back(str[i]);
			}
			i++;
		}

		str_list.push_back(str2);
		unsigned int A = 0;
		BYTE PID1 = 0;
		int TMP = 1;
		while (A < str_list.size()) {

			if (A + 2 > str_list.size()) { Err(0, A);break; }//超界访问
			PID1 = BYTE(strtol(str_list[A++].c_str(), NULL, 16));
			if (TMP < 4) {
				Page[PID1].OffSetX = 16 * TMP;
				Page[PID1].PX = 256 * TMP;
				Page[PID1].PY = 512;
				Page[PID1].OffSetY = 0;
			}
			else {
				Page[PID1].OffSetX = 16 * (TMP%4);
				Page[PID1].OffSetY = 16*(TMP/4);
				Page[PID1].PX = 256 * (TMP % 4);;
				Page[PID1].PY = 512 + 256 * (TMP / 4) ;
			}
			if (PID1 != 0) {
				Page[PID1].use = true;
				Page[PID1].Page = new OffSet[256];//GetPage(TMP + 1);
			}
			
			
			Page[PID1].ID = BYTE(TMP);
			Page[PID1].PID = PID1;
			TMP++;
			Page[PID1].File = str_list[A++];
		}

	}
	
	BOOL WriteRes(RES* R) {
		const WCHAR*Ty = R->Type.c_str();
		const CHAR *Path = R->Path.c_str();
		DWORD ID = R->Id;
		HRSRC hRsrc = FindResource(DLL, MAKEINTRESOURCE(ID), Ty);
		if (hRsrc != NULL) {
			HGLOBAL hGlobal = LoadResource(DLL, hRsrc);
			if (hGlobal != NULL) {
				LPVOID pBuffer = LockResource(hGlobal);
				DWORD dwSize = SizeofResource(DLL, hRsrc);
				FILE *fp;
				fopen_s(&fp, Path, "wb+");
				
				if (fp != 0) {
					msgmgr(3, "写出资源 ID:%d Path:%s", ID, Path);
					fwrite(pBuffer, sizeof(BYTE), dwSize, fp);
					fclose(fp);
					return TRUE;
				}
				
			}
		}
		msgmgr(1, "写出资源失败 ID:%d Path:%s", ID,  Path);
		GetError(16);
		return FALSE;
	}
	char* GetConfig(int ID, char* str) {
		char TMP[256];
		if(ID)snprintf(TMP, 256, "Page%d", ID);
		else return strstr(str, "PageFile");//, "PageFile");
		return strstr(str, TMP);
	}
public:
	BOOL InitAll() {
		msgmgr(3, "配置文件初始化");
		RES R(Type[0], "Config.ini", "System", IDR_CONFIG);
		if (!WriteRes(&R)) {
			GetError(17);
			return FALSE;
		};//错误标记15;
		InitFile();
		return TRUE;
	};
	void Clear() {
		for (int i = 0;i < 256;i++)if (Page[i].use) {
			Page[i].Init();

		}

	}
	BOOL MainInit() {
		Clear();
		FILE *fp;
		std::string CPath= SYSTEMPATH+"/"+ConfigFilePath;
		fopen_s(&fp, CPath.c_str(), "rb+");
		if (fp == NULL) {
			InitAll();
			fopen_s(&fp, CPath.c_str(), "rb+");
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
			char sum[16];
			snprintf(sum, 16, "%d", i);
			if (strcmp(sum, Versum) != 0) {
				fseek(fp, strstr(Config, Verstr) - Config, SEEK_SET);
				NeedInit = 1;
			}
		}
		else {
			fseek(fp, strrchr(Config, '}') - Config + 1, SEEK_SET);
			NeedInit = 2;
		}
		if (NeedInit) {
			char Tstr[256];
			size_t Size = snprintf(Tstr, 256, NeedInit>1 ? "\n%s: %s\n" : "%s: %s\n", Verstr, Versum);
			fwrite(Tstr, sizeof(char), Size, fp);
			InitFile();
		}
		fclose(fp);
		std::string str;
		char *ps = 0;
		for (int P = 0;P < 256;P++) {
			ps = GetConfig(P, Config);
			if (ps) {
				bool Incom = false, begin = false;
				int s = 0;
				while (s < 10240) {
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
						begin = false;
						InitChar(P, &str);
						str.clear();
						break;
					}
					if (begin) {
						str = str + ps[s];

					}
					s++;
				}
			}
		}
		for (int i = 0;i < 256;i++) WID[Page[i].ID] = Page[i].PID;
		WCharAdd.WMainInit(Config);
		delete[] Config;
		return TRUE;
	}

	
	OffSet* GetPage(int ID) {
		
		for (int i = 0;i < 256;i++)if (Page[i].ID == ID&&Page[i].use)return Page[i].Page;
		return 0;
	}

	


	void InitFile() {
	for(std::vector<RES*>::iterator i=res.begin();i!=res.end();i++)
			
			WriteRes(*i);

	}

	PageInfo Page[256];

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

