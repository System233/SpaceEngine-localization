// Test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<string>
#include <iostream>
/*
SEL WCharAdd;
std::string LOGPATH;
char *Msg[] = { "Info" ,"Error" ,"Warning" ,"Debug" ,"Null" };
BOOL isone = TRUE;
//0 Info 1 Error 2 Warning 3 Debug û���õĴ������.......
void msgmgr(int type, char* msg, ...) {

	char str[2048];
	va_list vlArgs;
	va_start(vlArgs, msg);
	vsnprintf_s(str, 2048, msg, vlArgs);
	va_end(vlArgs);
	GetLocalTime(&sys_time);
	printf("%02d:%02d:%02d.%03d [%s] %s\n", sys_time.wHour, sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds, Msg[type>3 ? 4 : type], str);
	

}
void GetError(int d) {
	DWORD Err = GetLastError();
	if (Err != 0) {
		char ErrInfo[256], ERR[512];
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, Err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), ErrInfo, 256, NULL);
		snprintf(ERR, 512, "λ��:%d ����(0x%X):%s", d, Err, ErrInfo);
	//	MessageBoxA(0, ERR, "Error", MB_OK);
		msgmgr(1, ERR);
		SetLastError(0);
	}


}
SYSTEMTIME sys_time;
DWORD Base = 0;
HMODULE hModule2=0, DLL=0;
WCHAR *Type[2] = { L"Config",L"PNG" };
BYTE WID[8] = { 0 };
char *Pstr[8] = { "File","1","2","3","4","5","6","7" };
int ResId[7] = { 0 };//IDR_CONFIG
char * SYSTEMPATH = "";
char * localePath = "";
char *ResPath[7] = { "chs-font1.png","chs-font2.png","chs-font3.png","chs-menu.png","CN-font.png","chs-gui.cfg","CN-font.cfg" };
char *ConfigFilePath = "Config2.ini";
BOOL GetFileVersion(Version *Ver, HMODULE *hModle) {
	Ver->HM = 0, Ver->LM = 9, Ver->HL = 8, Ver->LL = 0;
	return TRUE;
};
CharAdd CharADD;*/
//std::string str=0;
int main2()
{
	
/*	printf("START2\n");
	for(int i=0;i<100;i++){
	msgmgr(3, "\nSTART[%d]\n",i);
	CharADD.MainInit();
	}
	system("pause");
	for (int i = 0;i<100;i++) {
		msgmgr(3, "\nSTART[%d]\n", i);
		CharADD.MainInit();
	}*/
	//std::string str;
	//str.push_back('A');
	//str.resize(5);
	//snprintf((char*)str.data(),5,"%s","DWADAWDAWD");
	//printf("str:%s\n[%p][%p][%d]", str.data(), str.c_str(),str.data(), str[str.size()]);

	printf("%d%d%d", 1, 2, 3);
	/*std::stringstream ss;
	std::vector<BYTE> cmd;
	std::string tmp="0xA 0xb 0xf 0x10 0x30 0x50 0x70 0x79 0x80 0xaa 0xee 0xCC 0xAA 0xAF";
	printf("%s\n", tmp.c_str());
	ss.str(tmp);
	tmp.clear();
	while (ss >> tmp)cmd.push_back(BYTE(strtol(tmp.c_str(), 0, 16)));
	printf("\n");
	for (std::vector<BYTE>::iterator i = cmd.begin();i != cmd.end();i++)printf("0x%02X ", *i);
	printf("\n");
	for(size_t i=0;i<cmd.size();i++)printf("0x%02X ", cmd[i]);
	tmp.clear();
	tmp.push_back(0xFF);
	printf("\n0x%02X ", (BYTE)tmp[0]);*/
    return 0;
}/*
BOOL CALLBACK EnumDeskProc(HWND hWnd, LPARAM lParam) {
	char Name[256];
	GetClassNameA(hWnd, Name, 255);
	if(strcmp(Name, "WorkerW") == 0){
		HWND hw = FindWindowEx(hWnd, 0, L"SHELLDLL_DefView", 0);
			if (hw == NULL)return TRUE;
			HWND hw2 = FindWindowEx(hw, 0, L"SysListView32", 0);
			if(hw2==NULL)return TRUE;
		GetWindowTextA(hw2, Name, 255);
		printf("Name:%s\n",Name);
		if (strcmp(Name, "FolderView") == 0) {
			static long ww(GetSystemMetrics(SM_CXSCREEN)), wh(GetSystemMetrics(SM_CYSCREEN));
			RECT rt;
			GetWindowRect(hWnd, &rt);
			long ph = rt.top - rt.bottom, pw = rt.left - rt.right;
			if (ph < 0)ph = -ph;
			if (pw < 0)pw = -pw;
			printf("%d*%d\n", pw, ph);
			if (pw == ww&&ph == wh) {
				*(HWND*)lParam = hWnd;
				return FALSE;
			}
		}
	
	}
	return TRUE;
};
int main(int argc,char**argv) {
	HWND hwnd;
	if (argc == 2) {
	
		DWORD pid;
	EnumWindows(EnumDeskProc, (LPARAM)&hwnd);
	printf("DESK:%X\n", hwnd);
	GetWindowThreadProcessId(hwnd, &pid);
	Inject inject(pid, argv[1]);
	while (getchar() != EOF) {
		printf("����\n");
		inject.Start();
		if (getchar() == EOF)break;;
		inject.Free();
	}
	}
	else printf("ARGERR:%d", argc);

	
}
*/

// Win32Test.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#define MAX_LOADSTRING 100
// ȫ�ֱ���: 
WNDPROC OldWndProc, OldDeskProc;
bool cap=true,lcap;
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[]={ L"Dynamic_Desktop_Controller" };                  // �������ı�
WCHAR szWindowClass[]={L"Dynamic_Desktop_Controller_Class"};            // ����������
HWND hWnds,WindowPtr;
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
	// ��ʼ��ȫ���ַ���
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}


	MSG msg;

	// ����Ϣѭ��: 
	while (GetMessage(&msg, nullptr, 0, 0))
	{

	}
	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;// LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32TEST));
	wcex.hCursor = NULL;//LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_WIN32TEST);
	wcex.lpszClassName = szWindowClass; 
	wcex.hIconSm = NULL;// LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

LRESULT CALLBACK NewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_PAINT:{
			PAINTSTRUCT ps;
			BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
		}
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_CHAR:
	case WM_SYSKEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSCHAR:
	case WM_SETCURSOR:
	case WM_CONTEXTMENU:return TRUE;
	case LVM_GETHEADER:return DefWindowProc(hWnd, message, wParam, lParam);
	case WM_LBUTTONDOWN:if (cap) { SetCapture(WindowPtr); lcap = true; } break;
	case WM_LBUTTONUP:if (lcap) { ReleaseCapture(); lcap=false;} break;
	}
	
	return SendMessage(WindowPtr, message, wParam, lParam);


}
LRESULT CALLBACK DeskWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_CHAR:
	case WM_SYSKEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSCHAR:
		return SendMessage(WindowPtr, message, wParam, lParam);
	default:
		return OldDeskProc(hWnd, message, wParam, lParam);
		
	}

	


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
	HFONT FN = CreateFont(20, 0, 0, 0, FW_NORMAL, false, false, false, GB2312_CHARSET, OUT_TT_PRECIS, CLIP_STROKE_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, L"΢���ź�");

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_SYSMENU,
		CW_USEDEFAULT, 0, 300, 100, nullptr, nullptr, hInstance, nullptr);
	//SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)&NewWndProc);
	if (!hWnd)
	{
		return FALSE;
	}
	hWnds = hWnd;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

class Controller {
	HWND FolderView,WorkerView;

	bool con;
	BOOL isBad() {
		if (IsWindow(WorkerView)&&IsWindow(FolderView)&&OldDeskProc!=nullptr&& OldWndProc != nullptr)return FALSE;
		return TRUE;
	}
public:
	Controller():FolderView(nullptr), con(false){
		Work wk{ &WorkerView,&FolderView };
		EnumWindows(EnumDeskProc, (LPARAM)&wk);
		if(IsWindow(FolderView)&& IsWindow(WorkerView)){
		OldWndProc = (WNDPROC)GetWindowLongPtr(FolderView, GWLP_WNDPROC);
		OldDeskProc = (WNDPROC)GetWindowLongPtr(WorkerView, GWLP_WNDPROC);
		}
};
	LRESULT setCon() {
		if (!con&&!isBad()) {
			con = true;
			if(SetWindowLongPtr(FolderView, GWLP_WNDPROC, (LONG_PTR)NewWndProc))
				if (SetWindowLongPtr(WorkerView, GWLP_WNDPROC, (LONG_PTR)DeskWndProc))  return TRUE;
			unCon();
		}
		return FALSE;
	}
	LRESULT getCon()const {
		return con;
	}
	LRESULT unCon() {
		if (con && !isBad()) {
			con = false;
			if (SetWindowLongPtr(FolderView, GWLP_WNDPROC, (LONG_PTR)OldWndProc)) 
				if (SetWindowLongPtr(WorkerView, GWLP_WNDPROC, (LONG_PTR)OldDeskProc)) return TRUE;
		}
		return FALSE;
	}
	~Controller() {
		unCon();
	}
};
Controller desk;
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
	
		case SET_WIN:WindowPtr = HWND(lParam); break;
		case GET_CON:return desk.getCon(); break;
		case SET_CON:return desk.setCon(); break;
		case SET_CAP:return cap=!cap; break;
		case UN_CON:return desk.unCon(); break;
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
	case WM_DESTROY:
		  PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
