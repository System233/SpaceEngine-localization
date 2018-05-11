
#include "Hook.h"
#include <windows.h>
#include <fstream>
std::string getCWD(HMODULE hModule){
    std::string cwd(MAX_PATH,0);
    GetModuleFileName(hModule,(char*)cwd.data(),MAX_PATH);
    bool fg=false;
    for(auto it=cwd.rbegin(),end=cwd.rend();it!=end;++it)
        if(*it=='/'||*it=='\\'){
            if(fg)
                return std::string(end.base(),it.base());
            else 
                fg=true;
        }
        
    return "../";
}
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
	{
        case DLL_PROCESS_ATTACH:Hook::initialize(getCWD(hModule),size_t(GetModuleHandle(nullptr)));break;
        case DLL_THREAD_ATTACH :break;
        case DLL_THREAD_DETACH :break;
        case DLL_PROCESS_DETACH:Hook::uninitialize();break;
	}
	return TRUE;
}