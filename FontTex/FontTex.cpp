// FontTex.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Windows.h"
#include <fstream>
int main(int argc,char**argv) {
	if (argc == 6){
		long w = atoi(argv[2]),h=w,tw= atoi(argv[3]),th=tw;
		char*p = strstr(argv[2], "*");
		if (p)h = atoi(p + 1);
		p=strstr(argv[3], "*");
		if (p)th = atoi(p + 1);
		printf("FontFile:\t%s\nFontSize(w*h):\t%d*%d\nTexSize(w*h):\t%d*%d\nStrMap:\t%s\nImgOut:\t%s\n", argv[1], w,h, tw, th, argv[4], argv[5]);
	FreeType ft(argv[1],w,h, tw,th);
	ft.Start(argv[4]);
	ft.write(argv[5]);
	}
	else printf("ARGERR\n\t%s [字体文件] [字体大小] [纹理尺寸] [字符表(UNICODE编码)] [纹理输出]\n示例:\t%s msyh.ttc;msjh.ttc 12*12 256*256 map.txt font.png", argv[0], argv[0]);
	return 0;
}
HWND hWnds = NULL;
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	char Name[256];
	GetClassNameA(hWnd, Name, 255);
	if (stricmp(Name, "WorkerW") == 0)
	{
		GetWindowTextA(hWnd, Name, 255);
		if (Name[0] == 0) {
			if (GetParent(hWnd) != 0) {
				if (GetWindowLongPtr(hWnd, GWL_STYLE)&WS_DISABLED) {
					hWnds = hWnd;
					return FALSE;
				};
			}
		}
	}
	return TRUE;
}

int main2()
{

	/*HDESK hDesk = CreateDesktop(_T("MyDesk1"), NULL, NULL, 0, GENERIC_ALL| DESKTOP_CREATEWINDOW, NULL);
	if (hDesk == NULL)printf("ERR");
	STARTUPINFO si = { 0 };
	si.lpDesktop = _T("MyDesk1");
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;
	PROCESS_INFORMATION pi = { 0 };
	
	TCHAR szApp[MAX_PATH] = { _T("cmd.exe") };
	if (CreateProcess(NULL, szApp, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		getchar();
		CloseHandle(pi.hThread);
		SetThreadDesktop(hDesk);
		CloseHandle(pi.hProcess);
	}
	getchar();
	CloseDesktop(hDesk);
	​*/

	/*EnumWindows(EnumWindowsProc, 0);
	HWND a, b;
	printf("Hwnds:%X\n", hWnds);
	while (1) {
		scanf_s("%X %X", &a, &b);
		long style = GetWindowLong(a, GWL_STYLE),cx= GetSystemMetrics(SM_CXSCREEN),cy= GetSystemMetrics(SM_CYSCREEN);
		SetWindowLong(a, GWL_STYLE, WS_VISIBLE | WS_CHILD);
		printf("%X->%X:%d %d\n", a, b,cx,cy);
		RECT rt;
		GetWindowRect(b, &rt);
		//MoveWindow(b, 0, 0, cx, cy, 0);
		//MoveWindow(a, 0, 0,cx, cy, 0);
		SetWindowPos(a, HWND_TOPMOST, 0, 0, 1200, 600, SWP_NOZORDER);
		SetWindowPos(a, HWND_TOPMOST, 0, 0,cx,cy, SWP_NOZORDER);
		SetParent(a, b);
		system("pause");
		SetWindowLong(a, GWL_STYLE, style);
		SetParent(a, NULL);
		printf("%X->NULL\n", a);
	}*/
    return 0;
}
HDC hdc;
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: {
		EnumWindows(EnumWindowsProc, 0);
		hdc = GetDC(hWnds);
		char A[512];
		snprintf(A, 512, "%p %p", &hdc, &hWnds);
		std::ofstream OF("111.log");
		OF << &hdc << ":" << hdc<<"\n"<< &hWnds<<":"<< hWnds;
		OF.close();
		//MessageBoxA(NULL, A, "I", MB_OK);
		//wglMakeCurrent;

	}break;
	case DLL_THREAD_ATTACH:break;
	case DLL_THREAD_DETACH:break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}