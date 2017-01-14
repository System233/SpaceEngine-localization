// ConsoleApplication3.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#pragma comment (lib, "Version.lib")   

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
		WCharAdd.WMainInit();
		TEST(argv[1], argv[2]);
	}
	else if (argc==5) {
		ReadAdd RA(argv[1], argv[2], argv[3],atoi(argv[4]));
	
	
	}
	else if (argc==4) {
		GetOff GF(argv[1], argv[2], argv[3]);

	}
	else {
		
		Color(0XA);
		printf("\n�÷�: %s [�����ļ�] [����ļ�]\n	��ȡSE�ڴ�: %s [ƫ���б��ļ�] [����ļ�] [�����ʽ] [PID] \n CE XML��ʽ��ַ���� %s [�����ļ�] [����ļ�] [�����ʽ]", argv[0], argv[0], argv[0]);
		Color(0xC);
		printf("\n [����ģʽ] �����ļ�����ʹ��Unicode����,���ڴ���FontConfig\\FontTexture�ַ����лᱻ����.\n");
		Color(0x7);
		printf("\n ����Ŀ¼����ҪConfig.ini�ַ������ļ� �����������Զ�����\n ����һ��һ��\n Ҫ���ƵĻ������UE��[�û����а�(ctrl+����)]ȥ����,ϵͳ���а���ƻ�����\n ������ˣ���ʱһЩ������Ȼ�ᱻ�ƻ�,�����м��.�ص��黻���Ƿ�����(һ���Ǳ�����0A)\n ������ֽ���16���Ʊ༭ɾ��.\n \nʾ��");
		Color(0xB);
		printf("\n ����:		%s gui.txt chs-gui.cfg\n ", argv[0]);
		Color(0xE);
		printf("�����ļ�����:	\"SYSTEM\" \"ϵͳ\"	\n");
		Color(0x7);
		printf("\n [��ȡ�ڴ�ģʽ] �����ļ���ƫ�ƶ�ȡ�ڴ沢������ļ� ��ʽ����Ҫ������ʽ������ %%X��%%d ��%%s ���printf���������ʽ");
		Color(0xC);
		printf("\n ���Բ��˽���ʹ��ʾ����ʽ	0x00 %%X = %%s\n �����ļ��ڱ�����ƫ��ֵ�������ڴ��ַ �����ƫ��ֵ���ܻᵼ�³���ը ");
		Color(0x7);
		printf("\n ��CE�Ѹ���ɫ��ַȻ��㿪���������XXX.exe + ABCD... �� + XXX���־���ƫ����\n PID�ǽ���ID �������������");
		Color(0xB);
		printf("\n ����:		%s offset.txt out.txt 0x00%%X=%%s \n ", argv[0]);
		Color(0xE);
		printf("�����ļ�����:	0x0012345	\n");
		Color(0x7);
		printf("\n [CE XML��ַ����] ��CE�ڸ��Ƶĵ�ַ��XML��ʽ�� �޷�ֱ�ӽ��ж�ȡ,����Ӵ˹��� �������[��ȡ�ڴ�ģʽ]\n �����ʽͬ�� %%s��� ����+ƫ�� %%d��%%X ֻ���ƫ��");
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
	fclose(fp);
	fclose(fp2);
}
