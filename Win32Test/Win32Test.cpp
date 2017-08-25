// Win32Test.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Win32Test.h"
#include<deque>
#include<thread>
std::unique_ptr<DesktopController>desk;
std::unique_ptr<FindWin>findWin;
//DesktopController *desk;
ULONGLONG LastTime;
class MsgStr{
	char*str;
	wchar_t *wstr;
	bool Type;
	size_t Size;
public		  :
	MsgStr(bool type, size_t size) :str(nullptr),wstr(nullptr),Size(size), Type(type) {
		if(Type)
		str = new char[size]; 
		else wstr = new wchar_t[size];
		
	}
	MsgStr(bool type, LPVOID data, size_t size) :str(nullptr), wstr(nullptr), Size(size), Type(type) {
		if (Type)
			str = new char[size];
		else wstr = new wchar_t[size];
		memcpy(type?(PVOID)str: (PVOID)wstr, data, size);
	}
	void setData(bool Type,LPVOID data) {
	}
	bool getType()const { return Type; }
	LPARAM get()const{
		if (Type)return (LPARAM)str;
		else return (LPARAM)wstr;
	}
	void reset(){
		if (str)delete[]str;
		str = nullptr;
		if (wstr)delete[]wstr;
		wstr = nullptr;
	}
	size_t getSize()const { return Size; }
	~MsgStr() {
		reset();
	}
};
DWORD CPid;
void tmpfun(){ desk.reset(new DesktopController()); }
#define MAX_LOADSTRING 100
std::deque<MsgStr*>MsgList;
bool flag = true,Exitflag =false;
LRESULT WndFindProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case FIND_DOWN:
		
		break;
		case FIND_UP:
		{
			DWORD Pid;
			GetWindowThreadProcessId(hWnd, &Pid);
			if (Pid != CPid)
				desk->setWindow(hWnd);
			else { addMsg(3, "����ѡ�����������,��ᵼ��ʧ��"); break; };
		}

			
			break;
		case FIND_CHANGE:
			if(hWnd){
			char Text[32], Class[32];// = new char[100];
			GetWindowTextA(hWnd, Text, 32);
			Text[31] = 0;
			//Text[30] = Text[29] = Text[28] = '.';
			GetClassNameA(hWnd, Class, 32);
			Class[31] = 0;
			//Class[30] = Class[29] = Class[28] = '.';
			DWORD Tid, Pid;
			Tid = GetWindowThreadProcessId(hWnd, &Pid);
			addMsg(0, "����:%p ����:%s\t��:%s\t����:%X->%X", hWnd, Text, Class, Pid, Tid);
			}//delete[]Text;
			break;
	default:
		break;
	}
	return TRUE;
};
// ȫ�ֱ���: 

HGDIOBJ rush;
HINSTANCE hInst;// ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������
HWND setDesk, setCon,setRst, setStc,hWnds,setCap ;
char Mode(2);
// �˴���ģ���а����ĺ�����ǰ������: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: �ڴ˷��ô��롣
	hInst = hInstance;
	CPid = GetCurrentProcessId();
    // ��ʼ��ȫ���ַ���
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32TEST, szWindowClass, MAX_LOADSTRING);
	SetLastError(0);
	HANDLE mex = CreateMutex(NULL, TRUE, szWindowClass);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		HWND hw = FindWindow(szWindowClass, szTitle);
		if (hw != NULL) {
			ShowWindow(hw, SW_SHOW);
			SetForegroundWindow(hw);
		}
		return ERROR_ALREADY_EXISTS;
	}
	//if (mex)ReleaseMutex(mex);
		//CloseHandle(mex);
	
	

    MyRegisterClass(hInstance);
	;
	addMsg(0, "��ʼ��:%p:%p", GetShellWindow(), GetDesktopWindow());
    // ִ��Ӧ�ó����ʼ��: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32TEST));
	HFONT FN = CreateFont(18, 0, 0, 0, FW_NORMAL, false, false, false, GB2312_CHARSET, OUT_TT_PRECIS, CLIP_STROKE_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, L"΢���ź�");

    MSG msg;
	//desk.reset(new DesktopController());
	std::thread th(&tmpfun);
	th.detach();
	rush= GetStockObject(WHITE_BRUSH);
	RegisterHotKey(hWnds, 1212, MOD_NOREPEAT |MOD_SHIFT| MOD_ALT | MOD_CONTROL, 0);
	//  MessageBoxA(0, "dwadaw", "dwadaw", MB_OK);
	setDesk = CreateWindow(WC_BUTTON, L"����", WS_CHILD | WS_VISIBLE,
		440, 10, 35, 20, hWnds, (HMENU)SET_DESK, hInstance, NULL);
	setCon = CreateWindow(WC_BUTTON, L"����", WS_CHILD | WS_VISIBLE,
		440, 40, 35, 20, hWnds, (HMENU)SET_CON, hInstance, NULL);
	EnableWindow(setCon, FALSE);
	setCap = CreateWindow(WC_BUTTON, L"ʼ��", WS_CHILD | WS_VISIBLE,
		440, 70, 35, 20, hWnds, (HMENU)SET_CAP, hInstance, NULL);
	setRst = CreateWindow(WC_BUTTON, L"����", WS_CHILD | WS_VISIBLE,
		440, 100, 35, 20, hWnds, (HMENU)SET_RST, hInstance, NULL);

	setStc = CreateWindow(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_READONLY | WS_BORDER,
		5, 5, 430, 210, hWnds, (HMENU)IDC_STA, hInstance, NULL);
	SendMessage(setStc, EM_LIMITTEXT, -1, -1);
	findWin.reset(new FindWin(hWnds, WS_CHILD | WS_VISIBLE, HMENU(IDM_FIND), hInstance, 442, 130, 32, 32));
	HCURSOR findcur = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_FINDCUR)),
		nomalcur = LoadCursor(nullptr, IDC_ARROW);
	HICON findimg = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FIND)),
		nomalimg = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NORMAL));
	findWin->setImage(findimg, nomalimg, findcur, nomalcur);
	findWin->setOnFindLintener(WndFindProc);
	
	SendMessage(setCap, WM_SETFONT, (WPARAM)FN, TRUE);
	SendMessage(setDesk, WM_SETFONT, (WPARAM)FN, TRUE);
	SendMessage(setCon, WM_SETFONT, (WPARAM)FN, TRUE);
	SendMessage(setRst, WM_SETFONT, (WPARAM)FN, TRUE);
	// HFONT FN2 = CreateFont(16, 0, 0, 0, FW_NORMAL, false, false, false, GB2312_CHARSET, OUT_TT_PRECIS, CLIP_STROKE_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, L"΢���ź�");

	SendMessage(setStc, WM_SETFONT, (WPARAM)FN, TRUE);

    // ����Ϣѭ��: 
    while (GetMessage(&msg, nullptr, 0, 0)&& flag)
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		//if (::GetAsyncKeyState(VK_CONTROL) < 0 && ::GetAsyncKeyState(VK_MENU) < 0 && ::GetAsyncKeyState(VK_SHIFT) < 0) {
		//	ShowWindow(hWnds, (IsWindowVisible(hWnds) ? SW_HIDE : SW_SHOW));; Sleep(200); }
		while (!MsgList.empty()) {
			auto &var = MsgList.front();
			SendMessage(setStc, EM_SETSEL, -2, -1);
			
			if(var->getType())
			SendMessageA(setStc, EM_REPLACESEL, TRUE, var->get());
			else SendMessageW(setStc, EM_REPLACESEL, TRUE, var->get());
			SendMessage(setStc, EM_REPLACESEL, TRUE, (LPARAM)_T("\r\n"));
			//SendMessageA(setStc, WM_SETTEXT, TRUE, (LPARAM)MsgList.front().get());
			var->reset();
			delete var;
			MsgList.pop_front();
		}
    }

	UnregisterHotKey(hWnds, 1212);
	desk->unDesk();
	desk->unControl();
	//MessageBoxA(0, "DAWD", "DAW",MB_OK);
	desk.reset(nullptr);
	while (!MsgList.empty()) {
		delete MsgList.front();
		MsgList.pop_front();
	}
	DeleteObject(findcur);
	DeleteObject(nomalcur);
	DeleteObject(findimg);
	DeleteObject(nomalimg);
	DeleteObject(FN);
	Exitflag = true;
	if (mex) {
		ReleaseMutex(mex);
		CloseHandle(mex);
	}
    return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32TEST));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32TEST);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

const wchar_t*MsgTypeW[]{ L"[Info]" ,L"[Debug]",L"[Warning]",L"[Error]",L"NULL" };
const char*MsgType[]{ "[Info]" ,"[Debug]","[Warning]","[Error]","NULL"};
/*Edit��Ϣ����
info	0
debug	1
warning 2
error	3*/
void addMsg(UINT message,const char* lParam, ...) {
	MsgStr* buf=new MsgStr(1, 4096);
	SYSTEMTIME sys_time;
	GetLocalTime(&sys_time);
	size_t len=snprintf((char*)buf->get(), 4096, "%02d:%02d:%02d.%03d %s ", sys_time.wHour, sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds, MsgType[message < 4 ? message : 4]);
	va_list vlArgs;
	va_start(vlArgs, lParam);
	vsnprintf((char*)buf->get()+len, 4096-len, lParam, vlArgs);
	va_end(vlArgs);
	char*p(nullptr),*lp((char*)buf->get());
	while ((p = strstr(lp, "\n")) != nullptr)lp = p, *p = ' ';
	MsgList.push_back(buf);
}
void addMsg(UINT message, const wchar_t* lParam, ...) {
	//std::unique_ptr<wchar_t[]>buf(new wchar_t[4096]);
	MsgStr* buf = new MsgStr(0, 4096);
	SYSTEMTIME sys_time;
	GetLocalTime(&sys_time);
	size_t len = swprintf((wchar_t*)buf->get(), 4096, L"%02d:%02d:%02d.%03d %s ", sys_time.wHour, sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds, MsgTypeW[message < 4 ? message : 4]);
	va_list vlArgs;
	va_start(vlArgs, lParam);
	vswprintf(((wchar_t*)buf->get()) + len, 4096 - len, lParam, vlArgs);
	va_end(vlArgs);
	wchar_t*p(nullptr), *lp((wchar_t*)buf->get());
	while ((p = wcsstr(lp, L"\n")) != nullptr)lp = p, *p = L' ';
	MsgList.push_back(buf);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_CAPTION|WS_SYSMENU | WS_OVERLAPPED,
      CW_USEDEFAULT, 0, 500,285,/*300, 160,*/ nullptr, nullptr, hInstance, nullptr);
 
   if (!hWnd)
   {
      return FALSE;
   }
  
   hWnds = hWnd;
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case ID_HIDE:
			ShowWindow(hWnds, (IsWindowVisible(hWnds) ? SW_HIDE : SW_SHOW));
			break;
		case IDM_EXIT:
			//	desk->End();
			DestroyWindow(hWnd);
			break;
		case SET_DESK: {
			//Inject::getLastError("����11");
			if (!desk->getDesk()) {

				if (desk->setDesk()) {
					EnableWindow(setCon, TRUE);
					SetWindowText(setDesk, L"ȡ��");

				}

				else addMsg(3, "����ʧ��");

			}
			else {

				if (desk->unDesk()) {
					EnableWindow(setCon, FALSE);
					SetWindowText(setDesk, L"����");
					if (desk->getCon()) {
						if (desk->unControl())
							SetWindowText(setCon, L"����");
					}
				}
				else addMsg(3, "����ʧ��");
			};
		}break;
		case SET_CON:
			if (desk->getCon()) {
				if (desk->unControl())
					SetWindowText(setCon, L"����");
				else addMsg(3, "����ʧ��");
				;
				//Inject::GetError(setStc);
			}
			else {
				if (desk->setControl())
					SetWindowText(setCon, L"�ͷ�");
				else addMsg(3, "����ʧ��");
				;
				//Inject::GetError(setStc);
			};
			break;
		case SET_CAP:{
			switch (desk->setCapture(++Mode %= 3))
			{
			case 0:	SetWindowText(setCap, _T("����")); break;
			case 1:	SetWindowText(setCap, _T("����")); break;
			case 2:	SetWindowText(setCap, _T("ʼ��")); break;
			default:
				addMsg(3, "����ʧ��:%d", Mode);
				break;
			}
		
			
		}break;
		case SET_RST: {
			desk->Reset();

			EnableWindow(setCon, FALSE);
			SetWindowText(setDesk, L"����");
			SetWindowText(setCon, L"����");
		}break;
		case IDM_FIND:
			FindWin::WndProc(hWnd, message, wParam, lParam);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
		EndPaint(hWnd, &ps);
	}
	break;



	case WM_HOTKEY:
		//MOD_NOREPEAT | MOD_SHIFT | MOD_ALT | MOD_CONTROL
		
		if (lParam&(MOD_SHIFT | MOD_ALT | MOD_CONTROL)) {
			ULONGLONG now=GetTickCount64();
			if (now - LastTime >= 200) {
				ShowWindow(hWnds, (IsWindowVisible(hWnds) ? SW_HIDE : SW_SHOW));
				LastTime = now;
				return TRUE;
			}
		}
		
		break;
	case WM_COPYDATA: {
		COPYDATASTRUCT *cp = (COPYDATASTRUCT*)lParam;
		switch (LOWORD(cp->dwData)) {
		case 0:addMsg(HIWORD(cp->dwData), L"Զ��:%s", cp->lpData); return TRUE;
		case 1:addMsg(HIWORD(cp->dwData), "Զ��:%s", cp->lpData); return TRUE;
		default:
			addMsg(HIWORD(cp->dwData), "nullԶ��:%s", cp->lpData); return TRUE;
		};
	}break;
	case WM_CTLCOLORSTATIC:
		return (LRESULT)rush; break;
	case WM_DESTROY:
		//desk.End();
		//ShowWindow(hWnds, IsWindowVisible(hWnds) ? SW_HIDE : SW_SHOW);
		PostQuitMessage(0);
		break;
	default:

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
    return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
