// stdafx.cpp : 只包括标准包含文件的源文件
// Win32Test.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中引用任何所需的附加头文件，
//而不是在此文件中引用
BOOL CALLBACK EnumWorkerWProc(HWND hWnd, LPARAM lParam)
{
	char Name[256]; 
	GetClassNameA(hWnd, Name, 255);
	if (strcmp(Name, "WorkerW") == 0)
	{
		GetWindowTextA(hWnd, Name, 255);
		if (Name[0] == 0) {
			if (GetParent(hWnd) != 0) {
				if (GetWindowLongPtr(hWnd, GWL_STYLE)&WS_DISABLED) {
					*(HWND*)lParam = hWnd;
					return FALSE;
				};
			}
		}
	}
	return TRUE;
}
long ww(GetSystemMetrics(SM_CXSCREEN)), wh(GetSystemMetrics(SM_CYSCREEN));
BOOL CALLBACK EnumDeskProc(HWND hWnd, LPARAM lParam) {
	char Name[256];
	GetClassNameA(hWnd, Name, 255);
	if (strcmp(Name, "WorkerW") == 0) {
		HWND hw = FindWindowEx(hWnd, 0, _T("SHELLDLL_DefView"), 0);
		if (hw != NULL) {
			HWND hw2 = FindWindowEx(hw, 0, _T("SysListView32"), _T("FolderView"));
			if (hw2 != NULL) {
				//*(HWND*)lParam = hw2;
				Work *wk = (Work*)lParam;
				*wk->FolderView = hw2;
				*wk->DefView = hw;
				*wk->WorkerView = hWnd;
				return FALSE;

			}
		}

	}
	return TRUE;
};
BOOL CALLBACK EnumSpaceEngineProc(HWND hWnd, LPARAM lParam) {
	char Name[256];
	GetClassNameA(hWnd, Name, 256);
	if (strcmp(Name, "SpaceEngine Window") == 0) {
		*(HWND*)lParam = hWnd;
		return FALSE;
	}
	return TRUE;
};
#include<Commctrl.h>

HWND Desktop::Worker, Desktop::Desk, Desktop::SpaceEngine, Desktop::FolderView,Focus;
OWndProc Desktop::OldWndProc, Desktop::DeskProc;
LRESULT CALLBACK Desktop::NewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	//fprintf(fp, "hWnd:%X msg:%X wp:%p lp:%p\n", hWnd, message, wParam, lParam);
	switch (message) {
	case WM_PAINT: {
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;
	}
	//case WM_NOTIFY:
	//case WM_WINDOWPOSCHANGING:return OldWndProc(hWnd, message, wParam, lParam);
	case WM_SETCURSOR :
	case WM_CONTEXTMENU:return TRUE;
	case LVM_GETHEADER:return OldWndProc(hWnd, message, wParam, lParam); //return DefWindowProc(hWnd, message, wParam, lParam);
	//case WM_MOUSEMOVE: {POINT p{ LOWORD(lParam),HIWORD(lParam) };
	//				   if (Background != WindowFromPoint(p))return SendMessage(SpaceEngine, WM_MOUSELEAVE, wParam, lParam); }
	//case WM_MOUSELEAVE:Focus = NULL;
	case WM_NCHITTEST:	return DefWindowProc(hWnd, message, wParam, lParam);
	default:
		
		return SendMessage(SpaceEngine, message, wParam, lParam);
		break;
	}
	
	
	return DefWindowProc(hWnd, message, wParam, lParam);
}
HHOOK DesktopController::hKeyboardHook, DesktopController::hMouseHook, DesktopController::hBlockHook;
HWND DesktopController::Controller,DesktopController::WindowPtr, DesktopController::Worker, DesktopController::WorkerView, DesktopController::DefView, DesktopController::FolderView, DesktopController::Parent;
