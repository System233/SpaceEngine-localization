// ConsoleApplication3.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#pragma comment (lib, "Version.lib")   
void TEST(char* In, char*In2, char*Out,int mode);
BOOL GetFileVersion()
{
	
	DWORD dwVerSize;
	DWORD dwHandle;
	TCHAR szFullPath[MAX_PATH];

	GetModuleFileName(NULL, szFullPath, MAX_PATH);
	//printf("��Ϣ:");
	dwVerSize = GetFileVersionInfoSize(szFullPath, &dwHandle);
	if (dwVerSize == 0)
		return FALSE;
	TCHAR *szVersionBuffer=new TCHAR[dwVerSize];
	if (GetFileVersionInfo(szFullPath, 0, dwVerSize, szVersionBuffer))
	{
		//printf("��Ϣ2");
		VS_FIXEDFILEINFO * pInfo;
		unsigned int nInfoLen;

		if (VerQueryValue(szVersionBuffer, _T("\\"), (void**)&pInfo, &nInfoLen))
		{

			printf(("�汾: %d.%d.%d.%d"),
				HIWORD(pInfo->dwFileVersionMS), LOWORD(pInfo->dwFileVersionMS),
				HIWORD(pInfo->dwFileVersionLS), LOWORD(pInfo->dwFileVersionLS));
			return TRUE;
		}
	}

	return FALSE;
}

SEL WCharAdd;
HANDLE hHandle;
void Color(WORD C) {
	SetConsoleTextAttribute(hHandle,C);
}
class GetOff {

public:
	GetOff(std::string Path, std::string O, std::string F) {
		std::ifstream IF(Path);
		std::string L;
		char Line[256],*str=new char[1024];
		int T = 0;
		std::ofstream OF(O);
		if(F.find("%s")!=std::string::npos)T=1;
		else if (F.find("%d") != std::string::npos|| F.find("%X") != std::string::npos)T = 2;
		while (IF.getline(Line, 256)) {
			L = Line;
			char *P = 0,*P2=0;
			if ((P = strstr(Line, "<Address>")) != 0) {
				P += 9;
				if ((P2 = strstr(Line, "</Address>")) != 0)*P2 = 0;
				
			
				if (T == 2) {
					if ((P = strstr(Line, "+")) != 0) { P += 1; 
					snprintf(str, 1024, F.c_str(), strtol(P,0,16));
					printf(" %s\n", str);
					OF << str << std::endl;
					}

				}
				else {
					snprintf(str, 1024, F.c_str(), P);
					printf(" %s\n", str);
					OF << str << std::endl;
				}
				
				
			}

		}
		delete[] str;
	};

};
int main(int argc, char *argv[])
{
	hHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	Color(0xB);
	printf("\n [SpaceEngine ���������� 1.0.0.7]\n\n");
	Color(0x7);
	if (argc == 3) {
		printf("[����ģʽ]\n");
		WCharAdd.WMainInit();
		TEST(argv[1], argv[2]);
	}
	else if (argc==5) {
		
		if(strcmp(argv[1],"-A")==0){
			printf("[�ų�������]\n");
			WCharAdd.WMainInit();
			TEST(argv[2], argv[3],argv[4],0);
	}else{
		printf("[��ȡ�ڴ�ģʽ]\n");
		ReadAdd RA(argv[1], argv[2], argv[3],atoi(argv[4]));
		}
	
	}
	else if (argc==4) {
		if(strstr(argv[3],"%")!=0){ printf("[��ȡCEXMLģʽ]\n"); 
		GetOff GF(argv[1], argv[2], argv[3]);
		}
		else { 
			printf("[�ų�ģʽ]\n");
			TEST(argv[1], argv[2], argv[3],1); }

	}
	else {
		
		Color(0XA);
		printf("\n�÷�:	�Զ�����: %s [�����ļ�]  [����ļ�]\n	�ų�����: %s [-A] [�����ļ�] [�ų��б��ļ�] [����ļ�]\n	��ȡSE�ڴ�: %s [ƫ���б��ļ�] [����ļ�] [�����ʽ] [PID] \n	CE XML��ʽ��ַ���� %s [�����ļ�] [����ļ�] [�����ʽ]", argv[0], argv[0], argv[0], argv[0]);
		Color(0xC);
		printf("\n [����ģʽ] �����ļ�����ʹ��Unicode����,���ڴ���FontConfig\\FontTexture�ַ����лᱻ����,���Կ��н�β.\n");
		Color(0x7);
		printf("\n ����Ŀ¼����ҪConfig.ini�ַ������ļ� �����������Զ�����\n ����һ��һ��\n Ҫ���ƵĻ������UE��[�û����а�(ctrl+����)]ȥ����,ϵͳ���а���ƻ�����\n ������ˣ���ʱһЩ������Ȼ�ᱻ�ƻ�,�����м��.�ص��黻���Ƿ�����(һ���Ǳ�����0A)\n ������ֽ���16���Ʊ༭ɾ��.\n \nʾ��");
		Color(0xB);
		printf("\n ����:		%s gui.txt chs-gui.cfg\n", argv[0]);
		Color(0xE);
		printf(" �����ļ�����:	\"SYSTEM\" \"ϵͳ\"	\n");

		Color(0x7);
		printf("\n [�ų�����] �ų��б��ļ���ճ��SE.log����ʾ��δ֪���� ������˺�ķ���,���˶���ĳ�汾���õķ���������Ӽ����ٶ�\n	ʹ��-A���ų���ͬʱ���з���\nʾ��");
		Color(0xB);
		printf("\n ����:		 %s gui.txt exc.txt gui2.txt\n ", argv[0]);
		Color(0x7);

		Color(0x7);
		printf("\n [��ȡ�ڴ�ģʽ] �����ļ���ƫ�ƶ�ȡ�ڴ沢������ļ� ��ʽ����Ҫ������ʽ������ %%X��%%d ��%%s ���printf���������ʽ,");
		Color(0xC);
		printf("\n ���Բ��˽���ʹ��ʾ����ʽ	0x00 %%X = %%s\n �����ļ��ڱ�����ƫ��ֵ�������ڴ��ַ �����ƫ��ֵ���ܻᵼ�³���ը ");
		Color(0x7);
		printf("\n ��CE�Ѹ���ɫ��ַȻ��㿪���������XXX.exe + ABCD... �� + XXX���־���ƫ����\n PID�ǽ���ID ������������� �˹������ں����޷�ͨ��gui.cfg�ı���ִ�\nʾ��");
		Color(0xB);
		printf("\n ����:		%s offset.txt out.txt 0x00%%X=%%s [PID] \n ", argv[0]);
		Color(0xE);
		printf("�����ļ�����:	0x0012345	\n");
		Color(0x7);
		printf("\n [CE XML��ַ����] ��CE�ڸ��Ƶĵ�ַ��XML��ʽ�� �޷�ֱ�ӽ��ж�ȡ,����Ӵ˹��� �������[��ȡ�ڴ�ģʽ]\n �����ʽͬ�� %%s��� ����+ƫ�� %%d��%%X ֻ���ƫ�� \nʾ��");
		Color(0xB);
		printf("\n ����:		%s ce.txt ceout.txt %%s\n 		%s ce.txt ceout.txt %%d\n 		%s ce.txt ceout.txt %%X\n ", argv[0], argv[0], argv[0]);
		Color(0x7);
		
	}
	setlocale(LC_CTYPE, ".936");

	std::vector<STA> A = WCharAdd.No;
	DWORD Err = 0;
	if (!A.empty()) {
		Color(0xE);
		printf("�����ַ�δ���� ");
		Color(0x7);
		printf("�����ʽ [�ַ�:Ƶ��]\n");
		for (unsigned int i = 0;i < A.size();i++) {
			printf("%s:%d ", A[i].str, WCharAdd.Wstr[A[i].ID[0]].Size);
		}
	}
	else if ((Err = GetLastError()) != 0) {
		char MsgBuf[256];
		FormatMessageA( FORMAT_MESSAGE_FROM_SYSTEM , NULL, Err, 0,MsgBuf,256, NULL);
		Color(0xC);
		printf("����:%d", Err);
		Color(0x7);
		printf(" ����:%s\n",  MsgBuf);
	
	}
	
	else { 
		Color(0xA);
		printf("\n���");
		Color(0x7);
	};

	printf("\n");
	while (!A.empty()) {
		printf("%s", A.back().str);
		delete[] A.back().str;
		A.pop_back();

	}

	Color(0x7);
	CloseHandle(hHandle);
    return 0;
}
std::vector<std::wstring> wstrv;
#include <deque>
void TEST(char* In, char*In2,char*Out,int mode) {
	FILE*fp=0, *fp2=0,*fp3=0;
	//bool mode = 0;
	fopen_s(&fp, In, "rb");
	if (!fp) { printf("�޷���%s\n",In);return;
	}

		//mode = 1;
	fopen_s(&fp2, In2, "rb");
	if (!fp2) { printf("�޷���%s\n", In2); return;
	}
	
	fopen_s(&fp3, Out, "wb+");
	if (!fp3) { printf("�޷���%s\n", Out); return;
	}
	std::vector<std::wstring> dew;
	fseek(fp2, 0, SEEK_END);
	size_t len = ftell(fp2) / 2;
	wchar_t *buf2 = new WCHAR[len];
	rewind(fp2);
	fread(buf2, sizeof(wchar_t), len, fp2);
	//std::wstring ws = buf2;
	size_t l = 0,st=0;
	WCHAR P = 0;
	std::wstring ws;
	printf("��ȡ�ų��б�\n");

	while (l < len) {
		P = buf2[l++];
		
		if (P == '"') { st++; 
		continue;
		}
		if (P == '\r'|| P == '\n')st = 0;
		else if (st == 1&&P!='"') {
			ws.push_back(P);

		}
		else if (st == 2) {
			if(ws.size()>0){
			wstrv.push_back(ws);
		//	printf("PUSH:%ws\n", ws.c_str());
			ws.clear();
			}
			//st = 0;
			//st = 0;
		}
		

	}
	if(buf2)delete[] buf2;
	fseek(fp, 0, SEEK_END);
	len = ftell(fp) / 2;
	rewind(fp);
	wchar_t *buf = new WCHAR[len];
	fread(buf, sizeof(wchar_t), len, fp);
	buf[0] = ' ', buf[len - 1] = 0;

	l = 0;
	st = 0;
	ws.clear();
	printf("��ʼ�ų�\n");
	int Y=0,Z=0,X=0;
	std::wstring TMP;
	while (l <len) {
		P= buf[l++];
		ws.push_back(P);
		if (P == '"')st++;
		if (st == 1 && P != '"')TMP.push_back(P);
		if (P == '\r' || P == '\n'){
			st = 0;
		
			if (ws.size()> 4) {


				Z++;
				for (std::vector<std::wstring>::iterator i = dew.begin();i != dew.end();i++) {
					if ((*i).compare(ws) == 0) {
						printf("�Ѽ�⵽�ظ�[%d]->%ws", Z, ws.c_str());
						printf("\n");
						goto NO;
					}

				}
				for (std::vector < std::wstring>::iterator it = wstrv.begin();it != wstrv.end();it++){
					

					
					if ((*it).compare(TMP) == 0) { 
						Y++;
						TMP.clear(), ws.clear(); 
						break;
					}
			}

				if(ws.size()>0){
					X++;

					dew.push_back(ws);
			if (ws.find('\n') == std::wstring::npos)ws.push_back('\n');
			if (mode)

			fwrite(ws.c_str(), sizeof(WCHAR), ws.size(), fp3);
			else {
				std::string str;
				WCharAdd.Start(ws, &str);
				if (!str.empty()) {
					fwrite(str.c_str(), sizeof(CHAR), str.size(), fp3);
				}
				else { printf("�����ڴ�ʧ��\n"); }
			}//dew.push_back(ws);
			
				}
			}
			NO:
			ws.clear();
			TMP.clear();
			//st = 0;
			//st = 0;
		}
		
	}
	dew.clear();
	printf("���ų� %d/%d/%d ��\n", X, Y,Z);
	if (X == Z)printf("=>>>>�ļ�������ܲ���Unicode\n");
	if(buf)delete[] buf;
	if(fp)fclose(fp);
	if (fp2)fclose(fp2);
	if (fp3)(fp3);
}

void TEST(char* In, char*Out) {
	FILE*fp, *fp2;
	fopen_s(&fp, In, "rb");
	fopen_s(&fp2, Out, "wb+");
	if (fp == 0 || fp2 == 0) {
		printf("���ļ�ʧ��");
		return;
	}
	fseek(fp, 0, SEEK_END);
	unsigned int len = ftell(fp) / 2;
	rewind(fp);
	wchar_t *buf = new WCHAR[len], TMP[1024];
	fread(buf, sizeof(wchar_t), len, fp);
	buf[0] = ' ',buf[len-1] = 0;
	
	unsigned int i = 0, j = 0;
	char *p = 0;
	while (i <len) {
		TMP[j] = buf[i];
		if (TMP[j] == '\r')buf[i] = ' ';
		if (TMP[j] == '\n'|| i == len - 1) {
			TMP[++j] = '\0';
			p=WCharAdd.Start(TMP,j);
			fwrite(p, sizeof(char), strlen(p), fp2);
			delete[] p;
			j = 0;
		}
		i++,j++;
	}
	delete[] buf;
	fclose(fp);
	fclose(fp2);
}
