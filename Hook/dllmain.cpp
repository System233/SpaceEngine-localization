
#include "Hook.h"
#include <windows.h>
#include <fstream>

namespace Hook{
    
    std::string write_memory(intptr_t add,std::string const&data){
        std::string raw;
        if(!IsBadReadPtr(LPVOID(add), data.size())){
            DWORD oldProtect(0);
            VirtualProtect(LPVOID(add),data.size(),PAGE_EXECUTE_READWRITE, &oldProtect);
            int8_t *mem=(int8_t*)add;
            for(auto&c:data)
                raw+=*mem,*mem++=c;
            VirtualProtect(LPVOID(add),data.size(),oldProtect, nullptr);
        }
        return raw;
    }
    int getLastErr(){return GetLastError();}
    void* HeapAlloc(size_t n){return ::HeapAlloc(GetProcessHeap(),0,n);};
    bool HeapFree(void*ptr){return ::HeapFree(GetProcessHeap(),0,ptr);}
}
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