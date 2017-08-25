#pragma once
#include "Windows.h"

#include<CommCtrl.h>
#include "resource.h"
#include<stdio.h>
#include<memory>
#include<vector>
#define IDM_FIND 20001
#define IDM_LOG 20002

class LogWin {

	 const wchar_t*const MsgTypeW[5]={ L"[Info]" ,L"[Debug]",L"[Warning]",L"[Error]",L"NULL" };
	 const char*const MsgType[5]={ "[Info]" ,"[Debug]","[Warning]","[Error]","NULL" };
	 HWND This;
	 HFONT Font;
public:
	LogWin(HWND parent,HMENU hMenu ,int x,int y,int w,int h,DWORD dwStyle,HINSTANCE hInstance=nullptr,LPVOID lParam=nullptr) {
		This = CreateWindow(WC_EDIT, L"", dwStyle | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_READONLY | WS_BORDER,
			x, y, w, h, parent, hMenu, hInstance, lParam);
		Font = CreateFont(16, 0, 0, 0, FW_NORMAL, false, false, false, GB2312_CHARSET, OUT_TT_PRECIS, CLIP_STROKE_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, L"微软雅黑");
		SendMessage(This, WM_SETFONT, (WPARAM)Font, TRUE);
		SendMessage(This, EM_LIMITTEXT, -1, -1);
	}
	~LogWin() {
		if(Font)DeleteObject(Font);
	}
	/*Edit消息处理
	info	0
	debug	1
	warning 2
	error	3*/
	void addMsg(UINT message, const char* lParam, ...) {
		char* buf = new char[4096];
		SYSTEMTIME sys_time;
		GetLocalTime(&sys_time);
		size_t len = snprintf(buf, 4096, "%02d:%02d:%02d.%03d %s ", sys_time.wHour, sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds, MsgType[message < 4 ? message : 4]);
		va_list vlArgs;
		va_start(vlArgs, lParam);
		vsnprintf(buf + len, 4096 - len, lParam, vlArgs);
		va_end(vlArgs);
		SendMessage(This, EM_SETSEL, -2, -1);
		if(SendMessageA(This, EM_REPLACESEL, TRUE, (LPARAM)buf) == FALSE)SendMessage(This, WM_SETTEXT, TRUE, (LPARAM)L"");
		else SendMessage(This, EM_REPLACESEL, TRUE, (LPARAM)_T("\r\n"));
		delete[] buf;
	}
	void addMsg(UINT message, const wchar_t* lParam, ...) {
		WCHAR* buf = new WCHAR[4096];
		SYSTEMTIME sys_time;
		GetLocalTime(&sys_time);
		size_t len = swprintf(buf, 4096, L"%02d:%02d:%02d.%03d %s ", sys_time.wHour, sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds, MsgTypeW[message < 4 ? message : 4]);
		va_list vlArgs;
		va_start(vlArgs, lParam);
		vswprintf(buf + len, 4096 - len, lParam, vlArgs);
		va_end(vlArgs);
		SendMessage(This, EM_SETSEL, -2, -1);
		if (SendMessageW(This, EM_REPLACESEL, TRUE, (LPARAM)buf)==FALSE)SendMessage(This, WM_SETTEXT, TRUE, (LPARAM)L"");
		else SendMessage(This, EM_REPLACESEL, TRUE, (LPARAM)_T("\r\n"));
		delete[] buf;
	}
};
extern std::unique_ptr<LogWin> logHw;
typedef void (CALLBACK*FindWinProc)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
class FindWin {
#define FindWinClass "FindWinClass"
	WNDPROC onFind, onAllMsg;
	HWND Parent, This,Last;
	int x, y, h, w;
	DWORD exStyle, dwStyle;
	HICON NomalImg, FindImg;
	HCURSOR NomalCur, FindCur;
	HPEN hPen;
	bool Select;
	//
	//  函数: SpyRegisterClass()
	//
	//  目的: 注册窗口类。
	//
	ATOM SpyRegisterClass(HINSTANCE hInstance)
	{
		WNDCLASSEXW wcex{ 0 };

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_DBLCLKS | CS_GLOBALCLASS|CS_PARENTDC;// CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = FindWin::WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		//wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SPY));
		//wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		//wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		//wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SPY);
		wcex.lpszClassName = _T(FindWinClass);
		//wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		return RegisterClassExW(&wcex);
	}

	//LoadCursor(nullptr, IDC_ARROW);
	static void DrawRect(HWND hWnd,HPEN hPen) {
		RECT rt;
		GetClientRect(hWnd, &rt);
		HDC hdc = GetDC(hWnd);
		HGDIOBJ LastPen = SelectObject(hdc, hPen),
			LastBrush=SelectObject(hdc, GetStockObject(NULL_BRUSH));
		int lt = SetROP2(hdc, R2_NOTXORPEN);
		Rectangle(hdc, rt.left,  rt.top, rt.right, rt.bottom);
		SetROP2(hdc, lt);
		SelectObject(hdc, LastPen);
		SelectObject(hdc, LastBrush);
		ReleaseDC(hWnd, hdc);
	}
public:
	FindWin(HWND parent, DWORD style, HMENU hMenu = nullptr, HINSTANCE hInstance = GetModuleHandle(NULL), int x = CW_USEDEFAULT, int y = 0, int h = CW_USEDEFAULT, int w = 0, DWORD _exStyle = 0L) :
		Parent(parent), x(x), y(y), h(h), w(w), dwStyle(style),
		onFind(nullptr), onAllMsg(nullptr),
		NomalImg(nullptr), FindImg(nullptr),
		NomalCur(nullptr), FindCur(nullptr), Last(nullptr),
		Select(false), exStyle(_exStyle){
		SpyRegisterClass(hInstance);
		This = CreateWindowEx(exStyle, _T(FindWinClass), L"", dwStyle, x, y, w, h, Parent, hMenu, hInstance, this);
		SetWindowLongPtr(This, GWLP_USERDATA, LONG_PTR(this));
		hPen=CreatePen(PS_SOLID,5, 0xFFCC66);
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
	/*void setImage(LPCWSTR FindImg, LPCWSTR NomalImg, LPCWSTR FindCur = IDC_ARROW, LPCWSTR NomalCur =IDC_ARROW) {
		this->FindCur = FindCur,
			this->NomalCur = NomalCur,
			this->FindImg = FindImg,
			this->NomalImg = NomalImg;

		if (NomalImg != nullptr)//SendMessage(This, STM_SETIMAGE, IMAGE_ICON, (LPARAM)NomalImg);
			DrawIcon(GetDC(This), 0, 0, NomalImg);
	};*/
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
					if(st->Last)DrawRect(st->Last, st->hPen);
					st->Last = NULL;
					ReleaseCapture();
					st->Select = false;
					if (st->NomalCur)SetCursor(st->NomalCur);
					if (st->NomalImg)DrawIcon(GetDC(hWnd), 0, 0, st->NomalImg);// SendMessage(hWnd, STM_SETIMAGE, IMAGE_ICON, (LPARAM)st->NomalImg);;
					logHw->addMsg( 0, "左键释放: msg:%X wp:%p lp:%p", message, wParam, lParam);
					//MessageBoxA(hWnd, "UP", "UP", MB_OK);
				}break;
			case WM_MOUSEMOVE: {
				if (st->Select) {
					
					POINT pt;
					GetCursorPos(&pt);
					HWND hw = WindowFromPoint(pt);
					if (hw&&st->Last!=hw) {
						logHw->addMsg(0, "move:[%X:%X] msg:%X wp:%p lp:%p", hw, st->Last, message, wParam, lParam);
						if(st->Last)
							DrawRect(st->Last, st->hPen);
						st->Last = hw;
						DrawRect(hw, st->hPen);
					}
				}
			}break;
			case WM_LBUTTONDOWN:
				SetCapture(hWnd);
				//TrackMouseEvent
				st->Select = true;
				if (st->FindCur)SetCursor(st->FindCur);
				if (st->FindImg)DrawIcon(GetDC(hWnd), 0, 0, st->FindImg); //SendMessage(hWnd, STM_SETIMAGE, IMAGE_ICON, (LPARAM)st->FindImg);
				logHw->addMsg( 0, "左键按下: msg:%X wp:%p lp:%p", message, wParam, lParam);												  //MessageBoxA(hWnd, "DOWN", "DOWN", MB_OK);
				break;
			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				// TODO: 在此处添加使用 hdc 的任何绘图代码...
				DrawIcon(hdc, 0, 0, st->Select? st->FindImg:st->NomalImg);
				EndPaint(hWnd, &ps);
			}
			break;
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			default:
			//	LogWin::addMsg(logHw,0,"msg:%d wp:%p lp:%p",message,wParam,lParam);
				
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