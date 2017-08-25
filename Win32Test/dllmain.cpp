#include"stdafx.h"
//Desktop desk;
FILE*fp;
#include<Thread>
std::thread ui;
/*int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
_In_opt_ HINSTANCE hPrevInstance,
_In_ LPWSTR    lpCmdLine,
_In_ int       nCmdShow)*/
struct Arg {
	HINSTANCE hInstance;
	HINSTANCE hPrevInstance;
	LPWSTR    lpCmdLine;
	int       nCmdShow;
};
HMODULE Dll;
DWORD WINAPI UI_Thread(
	LPVOID lpThreadParameter
) {
	return wWinMain(Dll, NULL, L"", SW_SHOW);

};
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: {
		Dll = hModule;
		//Arg arg = { hModule, NULL, L"",SW_SHOW};
		HANDLE handle=CreateThread(0, 0, UI_Thread, 0, 0, 0);
		CloseHandle(handle);
		//ui = std::thread(wWinMain, (HINSTANCE)hModule, (HINSTANCE)NULL, (LPWSTR)L"", (int)SW_SHOW);
		//ui = std::thread(UI_Thread, nullptr);
		//ui.detach();
		
		//AllocConsole();
		//fopen_s(&fp,"F:/stdout.log", "wb");
		//if(fp==NULL)MessageBoxA(0, "aaaa", "DAWD", MB_OK);
		//freopen("stdout.log", "w", stderr);
	//	freopen("stdout.log", "r", stdin);
		//fprintf(fp,"Test\n");
		//desk.setDesk();
		//desk.setControl();
	}break;
	case DLL_THREAD_ATTACH:break;
	case DLL_THREAD_DETACH:break;
	case DLL_PROCESS_DETACH:
		flag = false;
		while (!Exitflag)Sleep(100);
	//	FreeConsole();
		//desk.unDesk();
		//desk.unControl();
		break;

	}
	return TRUE;
}