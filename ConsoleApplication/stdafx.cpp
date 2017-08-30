// stdafx.cpp : 只包括标准包含文件的源文件
// ConsoleApplication3.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中引用任何所需的附加头文件，
//而不是在此文件中引用
HANDLE mProc = 0;
DWORD Base;
std::wstring Localization::sCfgErr,
Localization::sFontMsg,
Localization::sIdMsg,
Localization::sParamsMsg,
Localization::sMapMsg,
Localization::sMapErr,
Localization::sUnCfgErr,
Localization::sWDefErr,
Localization::sReDefErr,
Localization::sTexErr,
Localization::sFmtErr,
Localization::sLoadErr,
Localization::sPageMsg,
Localization::sMapSzErr,
Localization::sStr2lErr;
//偏移 写入代码 大小
BOOL WriteAdd(LPVOID lpAddress, const uint8_t *Code, size_t Size)
{
	DWORD dwTemp = 0, dwOldProtect = 0;
	if (Code == 0 || lpAddress == 0 || Size == 0 || IsBadReadPtr(lpAddress, Size))return FALSE;
	VirtualProtectEx(mProc, lpAddress, Size, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	if (!WriteProcessMemory(mProc, lpAddress, Code, Size, 0))return FALSE;
	VirtualProtectEx(mProc, lpAddress, Size, dwOldProtect, &dwTemp);
	return TRUE;
}
BOOL WriteAdd(DWORD Offset, const uint8_t *Code, size_t Size)
{
	return WriteAdd((LPVOID)(Base + Offset), Code, Size);
}
BOOL ReadAdd(DWORD Offset, uint8_t *Code, size_t Size) {
	return ReadAdd((LPVOID)(Base + Offset), Code, Size);
}
BOOL ReadAdd(LPVOID lpAddress, uint8_t *Code, size_t Size) {
	DWORD dwTemp = 0, dwOldProtect = 0;
	if (Code == 0 || lpAddress == 0 || Size == 0 || IsBadReadPtr(lpAddress, Size))return FALSE;
	VirtualProtectEx(mProc, lpAddress, Size, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	if (!ReadProcessMemory(mProc, lpAddress, Code, Size, 0))return FALSE;
	VirtualProtectEx(mProc, lpAddress, Size, dwOldProtect, &dwTemp);
	return TRUE;
}
size_t maxLogSize = 131072;
SYSTEMTIME sys_time;

const char *const Msg[] = { "Info" ,"Error" ,"Warning" ,"Debug" ,"Null" };
std::mutex mtx;
union MsgData {
	wchar_t wstr[2048];
	char str[sizeof(wchar_t) * 2048];
};
static MsgData mData;
std::ofstream& openLog(MsgType _Ty) {
	static std::ofstream log;

	if (!log.is_open()) {
		std::wstring Path(L"localization.log");
		size_t size(0);
		HANDLE handle = CreateFileW(Path.c_str(), FILE_READ_EA, FILE_SHARE_READ, 0, OPEN_ALWAYS, 0, 0);
		if (handle != INVALID_HANDLE_VALUE)
		{
			size = GetFileSize(handle, NULL);
			CloseHandle(handle);
		}
		log.open(Path, (size > maxLogSize) ? std::ios::trunc : std::ios::app);//128k
		if (size>maxLogSize || !size)log.write("\xEF\xBB\xBF", 3);
		GetLocalTime(&sys_time);
		snprintf(mData.str, sizeof(MsgData::wstr), "\n %04d-%02d-%02d %02d:%02d:%02d\n--------------------------\n", sys_time.wYear, sys_time.wMonth, sys_time.wDay, sys_time.wHour, sys_time.wMinute, sys_time.wSecond);
		log << mData.str;
	}

	return log;
}
void Exception(DWORD code, LPCWSTR Info, LPCWSTR fotmat) {
	mtx.unlock();
	msgmgr(MsgType::Error, L"Exception(0x%X) %s FormatError:%s", code, Info, fotmat);
	mtx.lock();
}
int mwsprintf(wchar_t* const _Buffer, size_t  const _BufferCount, wchar_t const* const _Format, va_list   _ArgList) {
	__try {

		return vswprintf(_Buffer, _BufferCount, _Format, _ArgList);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		//	mtx_locker.~lock_guard();

		LPWSTR Info(nullptr);
		DWORD code(GetExceptionCode());
		FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_MAX_WIDTH_MASK, NULL, code & 0x3FFFFFFF, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&Info, NULL, NULL);

		Exception(code, Info ? Info : L"Null", _Format);

		if (Info)LocalFree(Info);
	}
	return -1;
}
size_t wngCnt, errCnt;
void msgmgr(MsgType _Ty, const std::wstring msg, ...) {
	if (_Ty == MsgType::Warning)wngCnt++;
	else if (_Ty == MsgType::Error)errCnt++;
	if (maxLogSize) {
		mtx.lock();
		std::ofstream &log = openLog(_Ty);
		va_list vlArgs;
		va_start(vlArgs, msg);
		//vswprintf(mData.wstr, 2048, msg.c_str(), vlArgs);
		GetLocalTime(&sys_time);
		char MsgId[32];
		snprintf(MsgId, 32, "%02d:%02d:%02d.%03d [%s] ", sys_time.wHour, sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds, Msg[int(_Ty)>3 ? 4 : int(_Ty)]);
		if (mwsprintf(mData.wstr, 2048, msg.c_str(), vlArgs) != -1)
			log << MsgId << UTF::Encode(mData.wstr) << std::endl;
		va_end(vlArgs);
		mtx.unlock();
	}
	//	log.close();

};

void openErr(const std::wstring&path) {
	LPWSTR Info;
	if (FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_MAX_WIDTH_MASK, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&Info, NULL, NULL)) {
		msgmgr(MsgType::Error, L"%s %s", Info, path.c_str());
		LocalFree(Info);
	}
}