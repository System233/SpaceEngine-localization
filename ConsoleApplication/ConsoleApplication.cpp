// ConsoleApplication3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#pragma comment (lib, "Version.lib")   

BOOL GetFileVersion()
{
	
	DWORD dwVerSize;
	DWORD dwHandle;
	TCHAR szFullPath[MAX_PATH];

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
	printf("\n [SpaceEngine 汉化生成器 1.0.0.7]\n\n");
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
		printf("\n用法: %s [输入文件] [输出文件]\n	读取SE内存: %s [偏移列表文件] [输出文件] [输出格式] [PID] \n CE XML格式地址析出 %s [输入文件] [输出文件] [输出格式]", argv[0], argv[0], argv[0]);
		Color(0xC);
		printf("\n [翻译模式] 输入文件必须使用Unicode编码,现在存在FontConfig\\FontTexture字符的行会被忽略.\n");
		Color(0x7);
		printf("\n 程序目录下需要Config.ini字符配置文件 若不存在则自动创建\n 翻译一行一个\n 要复制的话最好用UE的[用户剪切板(ctrl+数字)]去复制,系统剪切板会破坏内容\n 即便如此，有时一些内容仍然会被破坏,请自行检查.重点检查换行是否正常(一般是被插入0A)\n 错误的字节用16进制编辑删除.\n \n示例");
		Color(0xB);
		printf("\n 命令:		%s gui.txt chs-gui.cfg\n ", argv[0]);
		Color(0xE);
		printf("输入文件内容:	\"SYSTEM\" \"系统\"	\n");
		Color(0x7);
		printf("\n [读取内存模式] 根据文件内偏移读取内存并输出到文件 格式化需要两个格式化参数 %%X或%%d 和%%s 详参printf函数输出格式");
		Color(0xC);
		printf("\n 若仍不了解请使用示例格式	0x00 %%X = %%s\n 输入文件内必须是偏移值而不是内存地址 错误的偏移值可能会导致程序爆炸 ");
		Color(0x7);
		printf("\n 用CE搜个绿色基址然后点开看到后面的XXX.exe + ABCD... 的 + XXX部分就是偏移了\n PID是进程ID 打开任务管理器看");
		Color(0xB);
		printf("\n 命令:		%s offset.txt out.txt 0x00%%X=%%s \n ", argv[0]);
		Color(0xE);
		printf("输入文件内容:	0x0012345	\n");
		Color(0x7);
		printf("\n [CE XML地址析出] 从CE内复制的地址是XML格式的 无法直接进行读取,故添加此功能 用于配合[读取内存模式]\n 输出格式同上 %%s输出 程序+偏移 %%d或%%X 只输出偏移");
		Color(0xB);
		printf("\n 命令:		%s ce.txt ceout.txt %%s\n 		%s ce.txt ceout.txt %%d\n 		%s ce.txt ceout.txt %%X\n ", argv[0], argv[0], argv[0]);
		Color(0x7);
		
	}
	setlocale(LC_CTYPE, ".936");

	std::vector<STA> A = WCharAdd.No;
	DWORD Err = 0;
	if (!A.empty()) {
		Color(0xE);
		printf("以下字符未配置 ");
		Color(0x7);
		printf("输出格式 [字符:频度]\n");
		for (unsigned int i = 0;i < A.size();i++) {
			printf("%s:%d ", A[i].str, WCharAdd.Wstr[A[i].ID[0]].Size);
		}
	}
	else if ((Err = GetLastError()) != 0) {
		char MsgBuf[256];
		FormatMessageA( FORMAT_MESSAGE_FROM_SYSTEM , NULL, Err, 0,MsgBuf,256, NULL);
		Color(0xC);
		printf("错误:%d", Err);
		Color(0x7);
		printf(" 描述:%s\n",  MsgBuf);
	
	}
	
	else { 
		Color(0xA);
		printf("\n完成");
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
