#include <cstdint>
#include <string>
#define API extern "C" 
#define STDCALL __stdcall
#define CDECL __cdecl
#define TEST_API(x) API x CDECL //__declspec(dllexport) void __cdecl
#define STD_API(x) API x STDCALL 

namespace Hook{
    TEST_API(void) Hack();
    struct Draw{
        int32_t int_00;     //+0
        int32_t int_01;     //+4
        int32_t int_02;     //+8
        int32_t int_03;     //+C
        float float_04;     //+10
        float float_05;     //+14
        int32_t int_06;     //+18
        int32_t int_07=-1;  //+1C
        int32_t int_08=-1;  //+20
        int32_t int_09;     //+24
        int32_t int_10;     //+28
        int32_t int_11;     //+2C
        int32_t int_12;     //+30
        int32_t int_13_42[42-13];     //+30
        int32_t int_43;     //+172
        void draw(uint8_t const*str,bool b);
    };
    struct Thunk;
    struct DecodePack{
        uint8_t const*utf8;//@eax
        uint16_t u16;//@edx
    };
    STD_API(uint32_t) GetCode(uint16_t ch,uint16_t sz);
    STD_API(bool) external_cmp(uint16_t);
    STD_API(void) GenTex();
    STD_API(void) TestAPI();
    STD_API(void) HookMain();
    STD_API(DecodePack) Decode(uint8_t const*utf8);//@stack
    STD_API(uint32_t) GetUWidth(uint16_t ch);
    STD_API(uint32_t) GetWidth(uint32_t);//@stack
    STD_API(uint32_t) GetOffset(uint32_t);//@stack
    STD_API(uint8_t) GetPosX(uint32_t ch);
    STD_API(uint8_t) GetPosY(uint32_t ch);
    STD_API(void) initialize(std::string const&,size_t);
    STD_API(void) uninitialize();
};