// ConsoleApplication3.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#pragma comment (lib, "Version.lib")   

BOOL GetFileVersion()
{
	
	DWORD dwVerSize;
	DWORD dwHandle;
	TCHAR szFullPath[MAX_PATH];
//	DWORD dwVerInfoSize = 0;
//	DWORD dwVerHnd;
//	VS_FIXEDFILEINFO * pFileInfo;

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

//CharAdd CharADD;
SEL WCharAdd;
//char Ver[] = "[SpaceEngine ���������� 1.0.0.4]";
int main(int argc, char *argv[])
{
	HANDLE hHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hHandle, 0xB);
	printf("\n [SpaceEngine ���������� 1.0.0.4]\n\n");
	SetConsoleTextAttribute(hHandle, 0x7);
	if (argc != 3) {
		SetConsoleTextAttribute(hHandle, 0xA);
		printf("\n�÷�: %s [�����ļ�] [����ļ�]\n", argv[0]);
		SetConsoleTextAttribute(hHandle, 0xC);
		printf("\n �����ļ�����ʹ��Unicode�ַ���,���ڴ���FontConfig\\FontTexture�ַ����лᱻ����.\n");
		SetConsoleTextAttribute(hHandle, 0x7);
		printf("\n ����Ŀ¼����ҪConfig.ini�ַ������ļ� �����������Զ�����\n ����һ��һ��\n Ҫ���ƵĻ������UE��[�û����а�(ctrl+����)]ȥ����,ϵͳ���а���ƻ�����\n ������ˣ���ʱһЩ������Ȼ�ᱻ�ƻ�,�����м��.�ص��黻���Ƿ�����(һ���Ǳ�����0A)\n ������ֽ���16���Ʊ༭ɾ��.\n \nʾ��");
		SetConsoleTextAttribute(hHandle, 0xB);
		printf("\n ����:		%s gui.txt chs-gui.cfg\n ", argv[0]);
		SetConsoleTextAttribute(hHandle, 0xE);
		printf("�ļ�����:	\"SYSTEM\" \"ϵͳ\"	\n");
		SetConsoleTextAttribute(hHandle, 0x7);
	}
	else {
		WCharAdd.WMainInit();
		TEST(argv[1], argv[2]);

	}
	setlocale(LC_CTYPE, ".936");

	std::vector<STA> A = WCharAdd.No;
	DWORD Err = 0;
	if (!A.empty()) {
		SetConsoleTextAttribute(hHandle, 0xE);
		printf("�����ַ�δ���� ");
		SetConsoleTextAttribute(hHandle, 0x7);
		printf("�����ʽ [�ַ�:Ƶ��]\n");
		for (unsigned int i = 0;i < A.size();i++) {
			printf("%s:%d ", A[i].str, WCharAdd.Wstr[A[i].ID[0]].Size);
		}
	}
	else if ((Err = GetLastError()) != 0) {
		char MsgBuf[256];
		FormatMessageA( FORMAT_MESSAGE_FROM_SYSTEM , NULL, Err, 0,MsgBuf,256, NULL);
		SetConsoleTextAttribute(hHandle, 0xC);
		printf("����:%d", Err);
		SetConsoleTextAttribute(hHandle, 0x7);
		printf(" ����:%s\n",  MsgBuf);
	
	}
	
	else { 
		SetConsoleTextAttribute(hHandle, 0xA);
		printf("\n���");
		SetConsoleTextAttribute(hHandle, 0x7);
	};

	printf("\n");
	while (!A.empty()) {
		printf("%s", A.back().str);
		delete[] A.back().str;
		A.pop_back();

	}

	SetConsoleTextAttribute(hHandle, 0x7);
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
