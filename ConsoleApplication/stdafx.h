// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"
#include "Windows.h"
#include <vector>
#include <stdio.h>
#include <tchar.h>
#include <sstream> 
#include <fstream>
#include <string>
#include <algorithm>
#include "resource.h"
struct STA{
	wchar_t ID[1];
	char *str;
};
// TODO:  在此处引用程序需要的其他头文件
/*
struct OffSet {
	int Off = 0;
	int Width = 12;
};

struct PageInfo {
	char *File;
	int OffSetX = 0;
	int OffSetY = 0;
	int PX = 0;
	int PY = 0;
	bool use = false;
};
*/
struct WChar {
	bool use = false;
	BYTE str[2] = { 0 };
	BYTE ID = 0;
	long Size = 0;
	int UseSize = 0;
};

void TEST(char* In, char*Out);
class SEL {
	const char* ConfigFile = "Config.ini";
	char *Pstr[9] = { "File","1","2","3","4","5","6","7","DEF" };
	wchar_t *WPstr[9] = { L"File",L"1",L"2",L"3",L"4",L"5",L"6",L"7",L"DEF" };
public:


	BOOL WMainInit() {
		//	char line[4096];
		//	wprintf(L"开始");
		FILE *fp;
		fopen_s(&fp, ConfigFile, "rb"); // 读取当前文件mian.c

		if (fp == NULL) {
			//printf("配置文件不存在!\n");
			fopen_s(&fp, ConfigFile, "wb+");
			HRSRC hRsrc = FindResource(NULL, MAKEINTRESOURCE(IDR_CONFIG1), L"Config");
			HGLOBAL hGlobal = LoadResource(NULL, hRsrc);
			DWORD dwSize = SizeofResource(NULL, hRsrc);
			LPVOID pBuffer = LockResource(hGlobal);
			fwrite(pBuffer, 1, dwSize, fp);
			fclose(fp);
			printf("已创建字符配置文件\n");
			fopen_s(&fp, ConfigFile, "rb");
			//return;
		}
		if (fp == NULL)return FALSE;
		fseek(fp, 0, SEEK_END);

		unsigned int len = ftell(fp) / 2;
		wchar_t* Config = new wchar_t[len];

		//把指针移动到文件开头 因为我们一开始把指针移动到结尾，如果不移动回来 会出错
		rewind(fp);
		//跳过unicode标志位 0xfeff
		//	fread(Config, 2, 1, fp);
		fseek(fp, 2L, SEEK_SET);

		//size_t SIZE = 
		fread(Config, sizeof(wchar_t), len - 1, fp);
		//	printf("%X %X", Config[0], Config[1]);
		Config[len - 1] = 0;
		//	int tick = 0;
		//wchar_t* Config[81920] = { 0 };
		//	BYTE Buf[1];
		//size_t SIZE = fread(Config, sizeof(char), 81920, fp);
		//	int i = 0;
		bool Incom = false, Inread = false, begin = false;
		//char str[8192];
		std::wstring str;
		wchar_t *ps;//, *ps2;
		for (int P = 0;P < 9;P++) {
			if ((ps = WGetConfig(P, Config)) != 0) {
				Inread = true;
			}
			else {
				continue;
			}
			printf("读取配置:Page%s...", Pstr[P]);
			int s = 0;// s2 = 0;
			while (Inread) {
				if (ps[s] == '/'&&ps[s + 1] == '/') {
					Incom = true;
					s++, s++;
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
					//		printf("结束");
					begin = Inread = false;
					str.push_back('\0');
					//wchar_t *TMP = new wchar_t[str.size()];
					//		printf("\n复制副本 Size:%d str:\n %p", str.size(), str.c_str(), TMP);
					//wcscpy_s(TMP, str.size(), str.c_str());
					//printf("%X %X :%X %X",str[0],str[1], TMP[0], TMP[1]);
					Init(P, str.c_str());
					str.clear();
					printf("  完成\n\n");
					break;
				}
				if (begin) {
					//	printf("复制");
					str = str + ps[s];
				}
				s++;
			}

		}
		return TRUE;
	}
	//bool Inread = false;int PageId = 0;

	wchar_t* WGetConfig(int ID, wchar_t* str) {
		wchar_t TMP[256];
		swprintf(TMP, 256, L"Page%s", WPstr[ID]);
		return wcsstr(str, TMP);
	}
	void Init(int ID,const wchar_t* str) {
		if (ID == 0) {
			SetPage(str);
			return;
		}
		

		int C = 0;
		size_t size = wcslen(str);
		unsigned int i = 0;
		while(i<size){
			if (str[i] == 0XD || str[i] == 0XA) {
				i++;
				continue;
			}
			if (str[i] == ' ') {
				i++;continue;
			}
			if ( str[i]=='?') {
		//		alc = true;
				i++;C++;continue;
			};
			WChar* WT = &Wstr[str[i]];
			if (WT->use&&str[i] !='?') {
				//printf(Pstr[WIDToID(WT->ID)]);
				printf("警告:%X->%X:%X str:%d 重复\n",C,WT->ID,WT->str[1], str[i]);
				
			}
			else {
				WT->use = true;
				WT->ID = WID[ID-1];
				WT->str[0] = ID==8?0:WID[ID-1];
				WT->str[1] = BYTE(C);
			}
			
			//printf("")
		//	C << ID << i << std::endl;
			i++, C++;// C++;
		
		}
		
	//	Start(ID, L"\"dwadDAWF\"  \"昵称自定义\"     ");
	}
	bool O = true;
	char* Start(wchar_t*str,int size) {
		
		if(wcsstr(str,L"FontConfig")|| wcsstr(str, L"FontTexture")){
//			int i = 0;
			return WcharToChar(str);
		/*	while (i < size&&str[i]!=0) {
				CON[i] = BYTE(str[i]);
				i++;*/
		//}
		//	return CON;
		}
		char *CON = new char[size * 2];
//		for (int a = 0;a < size;a++) {
//			printf("%X ", str[a]);
//		}
//		printf("\n");
		int i = 0,T=0,j=0;
		while (i < size&&str[i] != ';') {
			CON[T] = BYTE(str[i]);
			if (str[i] == '"') {
				j++;
				if (j == 3) {
					T++;i++;continue;
			}
			}
			if (j == 3) {
			//	printf("T:%d I:%d byte:%X %X\n",T,Wstr[str[i]].str[0], Wstr[str[i]].str[1]);
				if (Wstr[str[i]].str[1] == 0) {
					CON[T] = '#';
					if (Wstr[str[i]].Size == 0) { 
						STA S;
						S.str = WcharToCharOne(&str[i]);
						S.ID[0] = str[i];
						No.push_back(S); }
					Wstr[str[i]].Size++;
			//		printf("未找到 列:%d str:%s\n",i, WcharToCharOne(&str[i]));
				
					//No.push();
				}else 
				if (Wstr[str[i]].str[0] == 0) {
					CON[T] = Wstr[str[i]].str[1];
				}
				else {
				CON[T++] = Wstr[str[i]].str[0];
				CON[T] = Wstr[str[i]].str[1];
				Wstr[str[i]].UseSize++;
				}
			
				//
			}
			if (j == 4) {
			//	CON[T] = '"';
				j = 0;
			}

			
			i++;T++;
		}
		CON[T] = '\0';
		return CON;
		//CON[T - 2] = '"';
	/*	FILE* fp;
		char F[256];
		snprintf(F, 256, "%s.txt", Pstr[ID]);
		fopen_s(&fp, F, "wb");
		fwrite(CON, sizeof(char), T-1, fp);
		fclose(fp);*/
	}
	void SetPage(const wchar_t*str) {
		WChar* S = &Wstr[' '];
		S->use = true;
		S->ID = 0;
		S->str[0] = 0;
		S->str[1] = ' ';
		S = &Wstr['?'];
		S->use = true;
		S->ID = 0;
		S->str[0] = 0;
		S->str[1] = '?';
		int i = 0;
		wchar_t sum[256];
		int ID=0,j=0;
		//printf("\n");
		while ((sum[j++]=str[i++]) != '\0') {
			
			if (str[i] == ','|| str[i+1]=='\0') {
				//sum[ID - 1] = ' ';

				WID[ID] = BYTE(wcstol(sum, 0, 16));
				printf("\nPageID:0x%X", WID[ID]);
				
				ID++,i++,j=0;
			}
		}


	};
	int WIDToID(int ID) {
		for (int a = 1;a < 8;a++) {
			if (WID[a] == ID) {
				return a;
			}
		}
		return 0;
	}
	char* WcharToCharOne(wchar_t* wc)
	{
//		void Release();
//		int len = WideCharToMultiByte(CP_ACP, 0, wc, wcslen(wc), NULL, 0, NULL, NULL);
		char* m_char = new char[2+1];
		WideCharToMultiByte(CP_ACP, 0, wc, wcslen(wc), m_char, 2, NULL, NULL);
		m_char[2] = '\0';
		return m_char;
	}
	char* WcharToChar(wchar_t* wc)
	{

		int len = WideCharToMultiByte(CP_ACP, 0, wc, wcslen(wc), NULL, 0, NULL, NULL);
		char* m_char = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, wc, wcslen(wc), m_char, len, NULL, NULL);
		m_char[len] = '\0';
		return m_char;
	}
	BYTE WID[8] = { 0 };
/*	WChar IDToW(int ID) {
		switch (ID) {
		case 1:break;
		case 2:
		case 3:
		}

	}*/
	WChar Wstr[65535];
	std::vector<STA> No;

};
#include<TlHelp32.h>  
class ReadAdd {
	DWORD Base=0;
	DWORD GetBase(DWORD Pid)
	{
		
		HANDLE phSnapshot;
		hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Pid);
		MODULEENTRY32 me32;
		phSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, Pid);
		if (phSnapshot == INVALID_HANDLE_VALUE)return false;
		me32.dwSize = sizeof(MODULEENTRY32);
		if (!Module32First(phSnapshot, &me32))return false;
		
		do
		{
			if (me32.th32ProcessID == Pid)
			{
				Base = (DWORD)me32.modBaseAddr;
				break;
			}
		} while (Module32Next(phSnapshot, &me32));

		CloseHandle(phSnapshot);
		if (Base != 0)return Base;
		return false;
	}
	size_t ReadMem(DWORD OF,char *p) {
		size_t l = 0;
		char *p2 = p;
		if(p!=0){
		DWORD LP = Base + OF;
		while(l<256&&ReadProcessMemory(hProc, (LPVOID)LP++, p2, 1, 0)&&*(p2++)!=0)l++;
		p[l] = 0;
		}
		return l;
	}
	HANDLE hProc = 0;
public:
	~ReadAdd() {
		CloseHandle(hProc);
	}
	ReadAdd(char *Path, char*Out, char *F,DWORD PID) {
		std::ifstream IF(Path);
		char str[256],str2[256],str3[512];
		GetBase(PID);
		if (hProc == NULL) return;
		std::ofstream OF(Out);
		while(IF.getline(str,256)){
			size_t L = 0;
			DWORD LP=strtol(str, 0, 16);
			if (L = ReadMem(LP, str2)) {
				snprintf(str3, 512, F, LP, str2);
				printf("%s\n", str3);
				OF << str3 << std::endl;

			}
			
			//ReadProcessMemory(hProc, (LPVOID)(Base+strtol(str,0,16)), PVOID pvBufferLocal, DWORD dwSize, PDWORD pdwNumBytesRead);
		
		}
		IF.close();
		OF.close();
	}


};