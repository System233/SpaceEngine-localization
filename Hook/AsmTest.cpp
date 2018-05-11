#include <cstdint>
#include <iostream>
extern "C" intptr_t BASE;
intptr_t BASE;
auto x ="ABCDEF";
main(){
    BASE=((intptr_t)&printf);
    
    std::cout<<std::hex<<BASE<<std::endl;
    //std::cin.get();
    __asm __volatile__ ("loc_6175C9:push _x;int3;call [_BASE+0xF];jz      short loc_6175C9;");
   
}