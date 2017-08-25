// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>

// C 运行时头文件
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <memory>
#include <sstream>
#include <tchar.h>
#include "TlHelp32.h"
#include "Psapi.h"  
#include<conio.h>  
#include<fstream>  
#include<CommCtrl.h>
#define IDC_STA 20000
#define SET_DESK 20001
#define SET_CON 20002
#define SET_RST 20003
#define GET_DESK 20004
#define GET_CON 20005
#define UN_DESK 20006
#define UN_CON 20007
#define IDM_FIND 20008
#define SET_WIN 20009
#define SET_CAP 20010
#define IDM_CON 20011
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
extern long ww,wh;
extern bool flag, Exitflag;
extern HWND hWnds;
typedef LRESULT(CALLBACK  *OWndProc)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void addMsg(UINT message,const char* lParam, ...);
void addMsg(UINT message, const wchar_t* lParam, ...);
BOOL CALLBACK EnumWorkerWProc(HWND hWnd, LPARAM lParam);
BOOL CALLBACK EnumDeskProc(HWND hWnd, LPARAM lParam);
BOOL CALLBACK EnumSpaceEngineProc(HWND hWnd, LPARAM lParam);
LRESULT CALLBACK MsgHookProc(int code, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK NewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow);
// TODO: 在此处引用程序需要的其他头文件

extern FILE *fp;
struct Work {
	HWND *WorkerView,*DefView, *FolderView;
};
class Desktop {
	static HWND Worker, Desk, SpaceEngine,FolderView;
	LONG_PTR style;
	bool set,con;
	RECT rt;
	static OWndProc OldWndProc,DeskProc;
	static LRESULT CALLBACK NewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	bool getDesk()const { return set; }
	bool getCon()const { return con; }
	Desktop():con(false), set(false){
		Reset();
		
	}
	void Reset() {
		unDesk();
		unControl();
		Work wk{ &Desk ,&FolderView };
		EnumWindows(EnumDeskProc, (LPARAM)&wk);
		EnumWindows(EnumSpaceEngineProc, (LPARAM)&SpaceEngine);
		EnumWindows(EnumWorkerWProc, (LPARAM)&Worker);
		style = GetWindowLongPtr(SpaceEngine, GWL_STYLE);
		//fprintf(fp, "Desk:%X SpaceEngine:%X Worker:%X\n", Desk, SpaceEngine, Worker);
		con = set = false;

	}
	void setDesk() {
		if (!set){
			GetWindowRect(SpaceEngine,&rt);
			set = true;
			SetWindowPos(SpaceEngine, 0, 0, 0, ww, wh, SWP_ASYNCWINDOWPOS| SWP_SHOWWINDOW| SWP_FRAMECHANGED);
			SetWindowLongPtr(SpaceEngine, GWL_STYLE, WS_VISIBLE | WS_CHILD);
			SetParent(SpaceEngine, Worker);
		}
	}
	void unDesk() {
		if (set) {
			SetParent(SpaceEngine, NULL);
			SetWindowLongPtr(SpaceEngine, GWL_STYLE, style);
			set = false;
			//SetWindowPos(SpaceEngine, 0, 0, 0, 1200, 600, SWP_ASYNCWINDOWPOS | SWP_SHOWWINDOW | SWP_FRAMECHANGED);
			SetWindowPos(SpaceEngine,0,rt.left,rt.top, abs(rt.left-rt.right), abs(rt.top - rt.bottom), SWP_ASYNCWINDOWPOS | SWP_SHOWWINDOW | SWP_FRAMECHANGED);
		}
		
	}
	void setControl() {
		if (!con) {
			
			DWORD id = GetCurrentProcessId(),pid=0;
			GetWindowThreadProcessId(FolderView, &pid);
			std::ofstream of("F:\\Documents\\Visual Studio 2015\\Projects\\Win32Project1\\x64\\Debug\\dll.log");
			if (of) {

				of <<"DESK:"<< FolderView << " CID:" << id << " PID:" << pid;
				of.close();
			}
			//fprintf(fp, "CID:%X PID:%X\n",id,pid);
			//if(pid==id){
				
			//	MessageBoxA(Desk, "开始控制", "控制", MB_OK);
			OldWndProc = (OWndProc)GetWindowLongPtr(FolderView, GWLP_WNDPROC);
			DeskProc = (OWndProc)GetWindowLongPtr(Desk, GWLP_WNDPROC);
			SetWindowLongPtr(FolderView, GWLP_WNDPROC, (LONG_PTR)NewWndProc);
			SetWindowLongPtr(Desk, GWLP_WNDPROC, (LONG_PTR)NewWndProc);
			con = true;
			//}
		}
		
	}
	static void InvalidateWin(HWND hWnd) {
		RECT rt;
		GetWindowRect(hWnd, &rt);
		InvalidateRect(hWnd, &rt, TRUE);
		UpdateWindow(hWnd);
	}
	void unControl() {
		if (con) {
			//MessageBoxA(Desk, "结束控制", "控制", MB_OK);
			con = false;
			SetWindowLongPtr(FolderView, GWLP_WNDPROC, (LONG_PTR)OldWndProc);
			SetWindowLongPtr(Desk, GWLP_WNDPROC, (LONG_PTR)DeskProc);
			InvalidateWin(FolderView);
			InvalidateWin(Desk);
		};
	}
	~Desktop() {
		unControl();
		unDesk();
	}
};
class Inject {
	DWORD dwProcessID, Pid;
	std::wstring Path, DllName;
	
	LPVOID pAddrStart;
	BOOL jed = false;
	void ResetPath() {
		size_t i = Path.rfind('\\');
		if (i != std::wstring::npos || (i = Path.rfind('/')) != std::wstring::npos) {
			DllName = Path.substr(i + 1);
		}
		else DllName = Path;

	}
public:
	DWORD getPID()const { return Pid; }
	Inject(DWORD pid, LPCSTR path) :Pid(pid), jed(false) {setPath(path);}
	Inject() :Pid(0), jed(false) {}
	void setCWPathName(LPCWCHAR name) {

		Path.clear();
		WCHAR path[MAX_PATH];
		GetModuleFileName(NULL, path, MAX_PATH);
		Path = path;
		DllName = name;
		size_t i = Path.rfind('\\');
		if (i != std::wstring::npos || (i = Path.rfind('/')) != std::wstring::npos)
			Path = Path.substr(0, i+1) + DllName;
		addMsg(1, L"TESTPATH:%s", Path.c_str());
		std::wifstream IF(Path);
		if (!IF)addMsg(3,L"bad Path:%s", Path.c_str());
		else IF.close();
	}

	void setPid(DWORD pid) { Pid = pid; }
	void setPath(std::wstring &path) {
		Path = path;
		ResetPath();
	}
	void setPath(LPCWSTR path) {
		Path = path;
		ResetPath();
	}
	void setPath(LPCSTR path) {
		std::wstringstream wss;
		wss << path;
		setPath(wss.str());
	}
	bool Start() {
		Free();
		return jed = dll_inject(Pid, Path);

	}
	bool Free() {
		if (jed) {
			jed = false;
			return dll_free(Pid, DllName);
		}
		return false;
	}
	DWORD GetProcessIdByName(LPCWSTR ProcessName)
	{
		PROCESSENTRY32 stProcess;
		HANDLE hProcessShot;
		stProcess.dwSize = sizeof(PROCESSENTRY32);
		hProcessShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		Process32First(hProcessShot, &stProcess);
		do if (!wcscmp(ProcessName, stProcess.szExeFile))return stProcess.th32ProcessID;
		while (Process32Next(hProcessShot, &stProcess));
		CloseHandle(hProcessShot);
		return -1;
	}



	/*static void GetError(HWND hwnd) {
		DWORD Err = GetLastError();
		WCHAR ErrInfo[100];
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, Err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), ErrInfo, 100, NULL);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)ErrInfo);
	}*/
	static void getLastError(const CHAR* ftm) {
		DWORD Err = GetLastError();
		CHAR ErrInfo[100];
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM| FORMAT_MESSAGE_MAX_WIDTH_MASK, NULL, Err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), ErrInfo, 100, NULL);
		//SendMessage(setStc, WM_SETTEXT, 0, (LPARAM)ErrInfo);
		addMsg((UINT)Err ? 3 : 1,"%s %s", (ftm? ftm:""),ErrInfo);
	}

	bool dll_inject(std::wstring &pProcessName, std::wstring &Path)
	{
		dwProcessID = GetProcessIdByName(pProcessName.c_str());
		if (dwProcessID != -1)return dll_inject(dwProcessID, Path);
		return false;
	}
	bool dll_inject(DWORD dwProcessID, std::wstring &Path)
	{
		HANDLE hProcessHandle, hThreadHandle;
		bool ret = false;
		hProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessID);
		
		if (hProcessHandle != NULL) {
			pAddrStart = VirtualAllocEx(hProcessHandle, 0, Path.size() * 2, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			if (pAddrStart != NULL)
			{
				if (WriteProcessMemory(hProcessHandle, pAddrStart, Path.c_str(), Path.size() * 2, 0))
				{
					hThreadHandle = CreateRemoteThread(hProcessHandle, 0, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryW"), pAddrStart, 0, 0);
					if (hThreadHandle != NULL)
					{
						WaitForSingleObject(hThreadHandle, INFINITE);
						CloseHandle(hThreadHandle);
						ret = true;
					}
					else getLastError("远程线程失败 加载失败");
				}
				else getLastError("写内存失败");
				VirtualFreeEx(hProcessHandle, pAddrStart, Path.size() * 2, MEM_RELEASE);
			}
			else getLastError("分配内存失败");
			CloseHandle(hProcessHandle);
		}
		else getLastError("打开进程失败");
		return ret;
	}
	bool dll_free(std::wstring &pProcessName, std::wstring &pDllName)
	{
		dwProcessID = GetProcessIdByName(pProcessName.c_str());
		if (dwProcessID != -1)
			return dll_free(dwProcessID, pDllName);
		return false;

	}
	bool dll_free(DWORD dwProcessID, std::wstring &pDllName)
	{
		HANDLE hProcessHandle, hThreadHandle;
		bool ret = false;
		HANDLE hModuleSnap = INVALID_HANDLE_VALUE, hProcess = NULL, hThread = NULL;
		hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessID);
		if (INVALID_HANDLE_VALUE != hModuleSnap) {
			MODULEENTRY32 me32{ 0 };
			me32.dwSize = sizeof(MODULEENTRY32);
			if (FALSE != Module32First(hModuleSnap, &me32))
				do
				{
					if (0 == pDllName.compare(me32.szModule) && me32.th32ProcessID == dwProcessID)
					{
						hProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessID);
						if (hProcessHandle != NULL) {

							hThreadHandle = CreateRemoteThread(hProcessHandle, NULL, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "FreeLibrary"), me32.modBaseAddr, 0, NULL);
							
							if (hThreadHandle != NULL) {
								WaitForSingleObject(hThreadHandle, INFINITE);
								CloseHandle(hThreadHandle);
								ret = true;
							}
							else getLastError("远程线程失败 卸载失败");
							CloseHandle(hProcessHandle);
						}
						else getLastError("打开进程失败");
					}
				} while (TRUE == ::Module32Next(hModuleSnap, &me32));
				CloseHandle(hModuleSnap);
		}
		else getLastError("创建快照失败");
		return ret;
	}

};
#define CTRszTitle L"Dynamic_Desktop_Controller"                  // 标题栏文本
#define  CTRszWindowClass   L"Dynamic_Desktop_Controller_Class"          // 主窗口类名
/*class DesktopController:public Inject {
	HWND Controller, SpaceEngine,Worker,Desk,FolderView;
	bool SendMsg(UINT msg) {

	}
public:
	bool isBad()const { return Controller==NULL; };
	LRESULT getDesk()const {
		LRESULT rst = FALSE;
		if (!isBad()) {
			rst= SendMessage(Controller, WM_COMMAND, LOWORD(GET_DESK), 0);
			//getLastError("getDesk");
		}
		else addMsg(3, "getDesk isBad");
		return rst;
	}
	LRESULT getCon()const {
		LRESULT rst = FALSE;
		if (!isBad()) {
			rst = SendMessage(Controller, WM_COMMAND, LOWORD(GET_CON), 0);
			getLastError("getCon");
		}
		else addMsg(3, "getCon isBad");
		return rst;
	}
	DesktopController() :Controller(NULL){
		Reset();
		
	}
	LRESULT Reset() {
		setCWPathName(L"Test.dll");
		if (!isBad()) {
			unControl();
			unDesk();
		}
		HWND hw= FindWindow(CTRszWindowClass, CTRszTitle);
		getLastError("Reset FindWin");
		if (hw != NULL) {
				SendMessage(hw, WM_COMMAND, LOWORD(SET_RST), 0);
				getLastError("Send RST");
				Controller = hw;
		}
		else {
			HWND Desk;
			Work wk{ &Desk ,NULL };
			EnumWindows(EnumDeskProc, (LPARAM)&wk); 
			getLastError("Reset EnumWin");
			DWORD pid = 0;
			GetWindowThreadProcessId(Desk, &pid);
			getLastError("Reset GetPID");
			setPid(pid);
			addMsg(0, "PID:%X", pid);
			Start();
			Controller = NULL;
			size_t sep = 20;
			while (Controller == NULL&&sep--) { Controller = FindWindow(CTRszWindowClass, CTRszTitle); Sleep(200); }
			if(sep==0)getLastError("Reset FindWin TIMEOUT");
			if(Controller == NULL)getLastError("初始化失败");
			else addMsg(0, "就绪");
		}
		return TRUE;
	}
	LRESULT setDesk() {
		
		LRESULT rst = FALSE;
		if (!isBad()) {
			rst = SendMessage(Controller, WM_COMMAND, LOWORD(SET_DESK), 0);
			getLastError("setDesk");
		}
		else addMsg(3, "setDesk isBad");
		return rst;
	}
	LRESULT unDesk() {
		LRESULT rst = FALSE;
		if (!isBad()) {
			rst = SendMessage(Controller, WM_COMMAND, LOWORD(UN_DESK), 0);
			getLastError("unDesk");
		}
		else addMsg(3, "unDesk isBad");
		return rst;
	}
	LRESULT setControl() {
		
		LRESULT rst = FALSE;
		if (!isBad()) {
			rst = SendMessage(Controller, WM_COMMAND, LOWORD(SET_CON), 0);
			getLastError("setControl");
		}
		else addMsg(3, "setControl isBad");
		return rst;
	}
	LRESULT unControl() {
		
		LRESULT rst = FALSE;
		if (!isBad()) {
			rst = SendMessage(Controller, WM_COMMAND, LOWORD(UN_CON), 0);
			getLastError("unControl");
		}
		else addMsg(3, "unControl isBad");
		return rst;
	}
	void End() {
		addMsg(3, "正在停止...");
		if (!isBad()) {
			unDesk();
			unControl();
			SendMessage(Controller, WM_COMMAND, LOWORD(SET_RST), 0);
			SendMessage(Controller, WM_DESTROY, 0, 0);
		}
		Free();
		Controller = NULL;
	}
	LRESULT setWindow(HWND hWnd) {
		LRESULT rst = FALSE;
		if (!isBad()) {
			rst = SendMessage(Controller, WM_COMMAND, LOWORD(SET_WIN), LPARAM(hWnd));
			getLastError("setWindow");
		}
		else addMsg(3, "setWindow isBad");
		return rst;
	}
	~DesktopController() {
		End();
	}

};*/
#include<thread>

class DesktopController {

#define ControllerTitle _T("WindowController") 
#define ControllerClass _T("WindowControllerClass") 
	static HWND  Controller,WindowPtr, Worker, WorkerView, DefView, FolderView, Parent;
	WINDOWPLACEMENT wndpl;
	BOOL set, con,cap;
	static HHOOK hKeyboardHook, hMouseHook,hBlockHook;
	ULONG_PTR dwStyle, cnStyle;
	static DWORD getLastError(const CHAR* ftm) {
		DWORD Err = GetLastError();
		if (Err) {
			char* str(new char[4096]);
			FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_MAX_WIDTH_MASK, NULL, Err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), str, 4096, NULL);
			addMsg(3, "%s\t[%Xh:%dd]%s %s", (ftm ? ftm : ""), Err, Err, str, (Err == 5 ? "可尝试以管理员权限启动" : ""));
			delete[]str;
			SetLastError(0);
		}
		return Err;

	}
	int ControllerWindow(HWND hWndParent) {
		WNDCLASSEX wcex;
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_DBLCLKS | CS_NOCLOSE| CS_PARENTDC;
		wcex.lpfnWndProc = ControllerWndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = GetModuleHandle(0);
		wcex.hIcon = NULL;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);;
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = ControllerClass;
		wcex.hIconSm = NULL;
		RegisterClassEx(&wcex);Controller = CreateWindow(ControllerClass, ControllerTitle , WS_DISABLED | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_CHILD| WS_MAXIMIZE, 0, 0, ww, wh, hWndParent, nullptr, nullptr, nullptr);
			if (!getLastError("ControllerWindow-CWEX")) {
					SetWindowLongPtr(Controller, GWLP_USERDATA, (LPARAM)this);
					if (!getLastError("ControllerWindow-SWLP")) {
						MSG msg;
						while (GetMessage(&msg, nullptr, 0, 0))
						{
							TranslateMessage(&msg);
							DispatchMessage(&msg);
						}
						return (int)msg.wParam;
					}
			}

		return -1;
	}

public:
	DesktopController() : set(false), con(false) , cap(true){
		Reset();
	}
	static LRESULT CALLBACK BlockProc(
		_In_ int    nCode,
		_In_ WPARAM wParam,
		_In_ LPARAM lParam
	) {
		if (nCode >= 0&&wParam) {

			CWPSTRUCT *msg((CWPSTRUCT*)lParam);
			if (msg->message==WM_SETCURSOR) {
				return FALSE;
				}
		}
		return CallNextHookEx(hMouseHook, nCode, wParam, lParam);

	}
	static LRESULT CALLBACK LowLevelKeyboardProc(
		_In_ int    nCode,
		_In_ WPARAM wParam,
		_In_ LPARAM lParam
	) {
		if (nCode >= 0) {
			if(GetForegroundWindow()== WorkerView){
				SendMessage(WindowPtr, wParam, ((KBDLLHOOKSTRUCT*)lParam)->vkCode, ((KBDLLHOOKSTRUCT*)lParam)->scanCode);
			}
		}
		return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
	};

	static LRESULT CALLBACK LowLevelMouseProc(
		_In_ int    nCode,
		_In_ WPARAM wParam,
		_In_ LPARAM lParam
	) {
		if (nCode >= 0) {
			MSLLHOOKSTRUCT *ms((MSLLHOOKSTRUCT*)lParam);
			if(WindowFromPoint(ms->pt)==WorkerView){
				SetCapture(WindowPtr);
				return SendMessage(WindowPtr, wParam, ms->mouseData, ms->pt.x | ms->pt.y << 16);
			}
			ReleaseCapture();
		}
		return CallNextHookEx(hMouseHook, nCode, wParam, lParam);
	};
	static LRESULT CALLBACK ControllerWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		DesktopController *This = (DesktopController*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		switch (message)
		{
		case  WM_PAINT:{
			PAINTSTRUCT ps;
			BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			return TRUE;
		}
					   
		case WM_SETCURSOR: {
			HWND WinPtr(This->WindowPtr);
			while (SendMessage(WinPtr, message, wParam, lParam) == FALSE) {
				WinPtr = GetParent(WinPtr);
				if(WinPtr==NULL)return DefWindowProc(hWnd, message, wParam, lParam);
			}
			return TRUE;
			//return SendMessage(This->WindowPtr, message, wParam, lParam); 
		}
		default:
			if(This&&This->cap){
				if (message == WM_LBUTTONDOWN) {
					SetCapture(This->WindowPtr);
					//int a = 1;
					//a <<= 1;
				/*	TRACKMOUSEEVENT tme;
					tme.cbSize = sizeof(tme);
					tme.hwndTrack = hWnd;
					tme.dwFlags = TME_LEAVE | TME_HOVER;
					tme.dwHoverTime = 1;
					TrackMouseEvent(&tme);*/
				}
			else if (message == WM_LBUTTONUP&&This->cap == 2)ReleaseCapture();
			}
			return (This != nullptr ? SendMessage(This->WindowPtr, message, wParam, lParam) : DefWindowProc(hWnd, message, wParam, lParam));

			break;
		};
		;
		
	};
	bool isBad()const { 
		
		//if (IsWindow(Controller)) {
			if (IsWindow(WindowPtr)) {
				if (IsWindow(Worker)) {
					if (IsWindow(WorkerView)) {
						if (IsWindow(FolderView))return false;
						else addMsg(3, "FolderView 未找到");
					}
					else addMsg(3, "Desk 未找到");
				}
				else addMsg(3, "Worker 未找到");
			}
			else addMsg(3, "目标Window 未找到");
		//}
		//else addMsg(3, "Controller 未找到");
		return true; };
	/*bool isBadCtr()const {
		if (IsWindow(Controller)) return false;
		else addMsg(3, "Controller:%p 未找到", Controller);
		return true;
	}*/
	LRESULT getCon()const {
		//if (!isBadCtr())return SendMessage(Controller, WM_COMMAND, LOWORD(GET_CON), NULL);
		return con;
	}
	LRESULT getDesk()const {return set;}
	LRESULT Reset() {
		//setCWPathName(L"Test.dll");
		if (con)unControl();
		if (set)unDesk();
		set = con= FALSE;
		Work wk{ &WorkerView ,&DefView,&FolderView };
		EnumWindows(EnumDeskProc, (LPARAM)&wk);
		if (!getLastError("Reset-EW-EDP")) {
			EnumWindows(EnumWorkerWProc, (LPARAM)&Worker);
			if (!getLastError("Reset-EW-EWP")) {
					if (Controller)DestroyWindow(Controller);
					std::thread th(&DesktopController::ControllerWindow, this, WorkerView);
					th.detach();
						addMsg(0, "初始化完成");
						return TRUE;
				}else getLastError("初始化失败");
			
		}
		return FALSE;
	}

	LRESULT setDesk() {
		if (!set && !isBad()) {
			GetWindowPlacement(WindowPtr, &wndpl);
			if (!getLastError("setDesk-GWPM")) {
				if (wndpl.showCmd == SW_SHOWMINIMIZED) {
					WINDOWPLACEMENT wp(wndpl);
					wp.showCmd = SW_NORMAL;
					SetWindowPlacement(WindowPtr, &wp);
					getLastError("setDesk-SWPM");
				}
			
				SetWindowPos(WindowPtr, 0, 0, 0, ww, wh, SWP_ASYNCWINDOWPOS | SWP_SHOWWINDOW | SWP_FRAMECHANGED);
				if (!getLastError("setDesk-SWP")) {
					dwStyle = GetWindowLongPtr(WindowPtr, GWL_STYLE);
					if (!getLastError("setDesk-GWLP")) {
						SetWindowLongPtr(WindowPtr, GWL_STYLE, WS_VISIBLE | WS_CHILD| WS_CLIPCHILDREN| WS_CLIPSIBLINGS);
						if (!getLastError("setDesk-GWLP")) {
							Parent = SetParent(WindowPtr, Worker);
							if (!getLastError("setDesk-SP")) {
								UpdateWindow(WindowPtr);
								if (!getLastError("setDesk-UW")) {
									set = true;
									return TRUE;
								}
							}
						}
					}
				}
			}

		}
		return FALSE;
	}
	LRESULT unDesk() {
		if (set && !isBad()) {
			SetParent(WindowPtr, Parent);
			if (!getLastError("unDesk-SP")) {
				SetWindowLongPtr(WindowPtr, GWL_STYLE, dwStyle);
				if (!getLastError("unDesk-SWLP")) {
					
					SetWindowPlacement(WindowPtr, &wndpl);
					if (!getLastError("unDesk-SWP")) {
						UpdateWindow(WindowPtr);
						if (!getLastError("unDesk-UW")) {
							char Path[MAX_PATH];
							SystemParametersInfoA(SPI_GETDESKWALLPAPER, MAX_PATH, Path, 0);
							if(*Path)SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, Path, SPIF_SENDWININICHANGE);
							set = false; return TRUE;
						}
					}
				}
			}
		}
		return FALSE;

	}
	LRESULT setCapture(char Mode) {
		
			return cap = Mode%3;
	}
	LRESULT setControl() {

		if (!con && !isBad()) {

			
			con = TRUE;
			EnableWindow(Controller, TRUE);
			hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, nullptr, 0);
			if (!getLastError("setControl-SWHE-WKB")) {
				//hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, nullptr, 0);
				//if (!getLastError("setControl-SWHE-WMS")) {
					ShowWindow(Controller, SW_SHOW);
					if (!getLastError("setControl-SW-CON")) {
						SetParent(DefView, Controller);
						EnableWindow(DefView, FALSE);
						if (!getLastError("setControl-SP-DV"))return TRUE;
					}
				//}
			}
		}
		return FALSE;
	}
	LRESULT unControl() {

		if (con&&!isBad()) {

			
			EnableWindow(DefView, TRUE);
			con = FALSE;;
			UnhookWindowsHookEx(hKeyboardHook);
			getLastError("setControl-UWHE-WKB");
			//UnhookWindowsHookEx(hMouseHook);
		//	getLastError("setControl-UWHE-WMS");
			SetParent(DefView, WorkerView);
			if (!getLastError("unControl-SP-CW")) {
				ShowWindow(Controller, SW_HIDE);
				EnableWindow(Controller, FALSE);
				if (!getLastError("unControl-SW-CON"))
					return UpdateWindow(WorkerView);
			}
		}
		return FALSE;
	}
	void End() {
		addMsg(3, "正在停止...");
		
			unControl();
			unDesk();
	}
	LRESULT setWindow(HWND hWnd) {
		BOOL Set = set;
		if (Set && !unDesk())return FALSE;
		else WindowPtr = hWnd;
		if (Set)setDesk();
		return TRUE;

	}
	~DesktopController() {
		End();
		set = 0;
	}
	
};

//extern Desktop desk;

typedef void (CALLBACK*FindWinProc)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

class FindWin {
#define FindWinClass "FindWinClass"
#define FIND_DOWN 1
#define FIND_UP 2
#define FIND_CHANGE 3
	WNDPROC onFind, onAllMsg;
	HWND Parent, This, Last;
	int x, y, h, w;
	DWORD exStyle, dwStyle;
	HICON NomalImg, FindImg;
	HCURSOR NomalCur, FindCur;
	HPEN hPen;
	bool Select;
	ATOM SpyRegisterClass(HINSTANCE hInstance)
	{
		WNDCLASSEXW wcex{ 0 };

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_DBLCLKS | CS_GLOBALCLASS | CS_PARENTDC;// CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = FindWin::WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		//wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SPY));
		//wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		//wcex.hbrFolderView = (HBRUSH)(COLOR_WINDOW + 1);
		//wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SPY);
		wcex.lpszClassName = _T(FindWinClass);
		//wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		return RegisterClassExW(&wcex);
	}

	//LoadCursor(nullptr, IDC_ARROW);
	static void DrawRect(HWND hWnd, HPEN hPen) {
		RECT rt;
		GetClientRect(hWnd, &rt);
		HDC hdc = GetDC(hWnd);
		HGDIOBJ LastPen = SelectObject(hdc, hPen),
			LastBrush = SelectObject(hdc, GetStockObject(NULL_BRUSH));
		int lt = SetROP2(hdc, R2_NOTXORPEN);
		Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
		SetROP2(hdc, lt);
		SelectObject(hdc, LastPen);
		SelectObject(hdc, LastBrush);
		ReleaseDC(hWnd, hdc);
	}
public:
	FindWin(HWND parent, DWORD style, HMENU hMenu = nullptr, HINSTANCE hInstance = nullptr, int x = CW_USEDEFAULT, int y = 0, int h = CW_USEDEFAULT, int w = 0, DWORD _exStyle = 0L) :
		Parent(parent), x(x), y(y), h(h), w(w), dwStyle(style),
		onFind(nullptr), onAllMsg(nullptr),
		NomalImg(nullptr), FindImg(nullptr),
		NomalCur(nullptr), FindCur(nullptr), Last(nullptr),
		Select(false), exStyle(_exStyle) {
		SpyRegisterClass(hInstance);
		This = CreateWindowEx(exStyle, _T(FindWinClass), L"", dwStyle, x, y, w, h, Parent, hMenu, hInstance, nullptr);
		SetWindowLongPtr(This, GWLP_USERDATA, LONG_PTR(this));
		hPen = CreatePen(PS_SOLID, 5, 0xFFCC66);
		UpdateWindow(This);
	}
	void setImage(HICON FindImg, HICON NomalImg, HCURSOR FindCur = LoadCursor(nullptr, IDC_ARROW), HCURSOR NomalCur = LoadCursor(nullptr, IDC_ARROW)) {
		this->FindCur = FindCur,
			this->NomalCur = NomalCur,
			this->FindImg = FindImg,
			this->NomalImg = NomalImg;

		if (NomalImg != nullptr)//SendMessage(This, STM_SETIMAGE, IMAGE_ICON, (LPARAM)NomalImg);
			DrawIcon(GetDC(This), 0, 0, NomalImg);
	};
	void setOnFindLintener(WNDPROC proc) {
		onFind = proc;
	}
	HWND getWindow()const { return This; }
	HWND getParent()const { return Parent; }
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		FindWin *st = (FindWin*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		if (st != 0) {

			if (st->onAllMsg != nullptr)st->onAllMsg(hWnd, message, wParam, lParam);
			switch (message)
			{

			case WM_LBUTTONUP:
				if (st->Select) {
					if(st->onFind)st->onFind(st->Last, FIND_UP, wParam, lParam);
					if (st->Last)DrawRect(st->Last, st->hPen);
					st->Last = NULL;
					ReleaseCapture();
					st->Select = false;
//					desk->setWindow(st->Last);
					if (st->NomalCur)SetCursor(st->NomalCur);
					if (st->NomalImg)DrawIcon(GetDC(hWnd), 0, 0, st->NomalImg);// SendMessage(hWnd, STM_SETIMAGE, IMAGE_ICON, (LPARAM)st->NomalImg);;
					//addMsg(0, "左键释放: msg:%X wp:%p lp:%p", message, wParam, lParam);
					//MessageBoxA(hWnd, "UP", "UP", MB_OK);
				}break;
			case WM_MOUSEMOVE: {
				if (st->Select) {

					POINT pt;
					GetCursorPos(&pt);
					HWND hw = WindowFromPoint(pt);
					if (hw&&st->Last != hw) {
						if (st->onFind)st->onFind(hw, FIND_CHANGE, wParam, lParam);
						
						if (st->Last)
							DrawRect(st->Last, st->hPen);
						st->Last = hw;
						DrawRect(hw, st->hPen);
					}
				}
			}break;
			case WM_LBUTTONDOWN:
				if (st->onFind)st->onFind(hWnd, FIND_DOWN, wParam, lParam);
				SetCapture(hWnd);
				st->Select = true;
				if (st->FindCur)SetCursor(st->FindCur);
				if (st->FindImg)DrawIcon(GetDC(hWnd), 0, 0, st->FindImg);	
				break;
			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				// TODO: 在此处添加使用 hdc 的任何绘图代码...
				DrawIcon(hdc, 0, 0, st->Select ? st->FindImg : st->NomalImg);
				EndPaint(hWnd, &ps);
			}
			break;
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			default:
				break;
			}


		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	~FindWin() {
		//Handle
		if (NomalImg)DeleteObject(NomalImg);
		if (FindImg)DeleteObject(FindImg);
		if (NomalCur)DeleteObject(NomalCur);
		if (FindCur)DeleteObject(FindCur);
		DeleteObject(hPen);
	}
};