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
HANDLE Thread;
DWORD WINAPI UI_Thread(
	LPVOID lpThreadParameter
) {
	return wWinMain(Dll, NULL, L"", SW_HIDE);//SW_HIDE SW_SHOW

};
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Dll = hModule;
		//ChangeWindowMessageFilterEx
		Thread=CreateThread(0, 0, UI_Thread, 0, 0, 0);
		break;
	case DLL_THREAD_ATTACH:break;
	case DLL_THREAD_DETACH:break;
	case DLL_PROCESS_DETACH:{
		if(hWnds)DestroyWindow(hWnds);
		if (WaitForSingleObject(Thread, 3000) == WAIT_TIMEOUT)TerminateThread(Thread, -1);
		CloseHandle(Thread);
	}break;

	}
	return TRUE;
}