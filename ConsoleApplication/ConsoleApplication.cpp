// ConsoleApplication3.cpp : 定义控制台应用程序的入口点。
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
	//printf("信息:");
	dwVerSize = GetFileVersionInfoSize(szFullPath, &dwHandle);
	if (dwVerSize == 0)
		return FALSE;
	TCHAR *szVersionBuffer=new TCHAR[dwVerSize];
	if (GetFileVersionInfo(szFullPath, 0, dwVerSize, szVersionBuffer))
	{
		//printf("信息2");
		VS_FIXEDFILEINFO * pInfo;
		unsigned int nInfoLen;

		if (VerQueryValue(szVersionBuffer, _T("\\"), (void**)&pInfo, &nInfoLen))
		{

			printf(("版本: %d.%d.%d.%d"),
				HIWORD(pInfo->dwFileVersionMS), LOWORD(pInfo->dwFileVersionMS),
				HIWORD(pInfo->dwFileVersionLS), LOWORD(pInfo->dwFileVersionLS));
			return TRUE;
		}
	}

	return FALSE;
}

//CharAdd CharADD;
SEL WCharAdd;
//char Ver[] = "[SpaceEngine 汉化生成器 1.0.0.4]";
int main(int argc, char *argv[])
{
	HANDLE hHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hHandle, 0xB);
	printf("\n [SpaceEngine 汉化生成器 1.0.0.4]\n\n");
	SetConsoleTextAttribute(hHandle, 0x7);
	if (argc != 3) {
		SetConsoleTextAttribute(hHandle, 0xA);
		printf("\n用法: %s [输入文件] [输出文件]\n", argv[0]);
		SetConsoleTextAttribute(hHandle, 0xC);
		printf("\n 输入文件必须使用Unicode字符集,现在存在FontConfig\\FontTexture字符的行会被忽略.\n");
		SetConsoleTextAttribute(hHandle, 0x7);
		printf("\n 程序目录下需要Config.ini字符配置文件 若不存在则自动创建\n 翻译一行一个\n 要复制的话最好用UE的[用户剪切板(ctrl+数字)]去复制,系统剪切板会破坏内容\n 即便如此，有时一些内容仍然会被破坏,请自行检查.重点检查换行是否正常(一般是被插入0A)\n 错误的字节用16进制编辑删除.\n \n示例");
		SetConsoleTextAttribute(hHandle, 0xB);
		printf("\n 命令:		%s gui.txt chs-gui.cfg\n ", argv[0]);
		SetConsoleTextAttribute(hHandle, 0xE);
		printf("文件内容:	\"SYSTEM\" \"系统\"	\n");
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
		printf("以下字符未配置 ");
		SetConsoleTextAttribute(hHandle, 0x7);
		printf("输出格式 [字符:频度]\n");
		for (unsigned int i = 0;i < A.size();i++) {
			printf("%s:%d ", A[i].str, WCharAdd.Wstr[A[i].ID[0]].Size);
		}
	}
	else if ((Err = GetLastError()) != 0) {
		char MsgBuf[256];
		FormatMessageA( FORMAT_MESSAGE_FROM_SYSTEM , NULL, Err, 0,MsgBuf,256, NULL);
		SetConsoleTextAttribute(hHandle, 0xC);
		printf("错误:%d", Err);
		SetConsoleTextAttribute(hHandle, 0x7);
		printf(" 描述:%s\n",  MsgBuf);
	
	}
	
	else { 
		SetConsoleTextAttribute(hHandle, 0xA);
		printf("\n完成");
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
		printf("打开文件失败");
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
