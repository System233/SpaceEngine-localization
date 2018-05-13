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
    void* HeapAlloc(size_t n);
    bool HeapFree(void* p);
    template<class _Ty>
    class GlobalHeap{//全局堆分配器,避免修改参数后主程序无法释放DLL内存
        public:
         typedef _Ty value_type;
         typedef value_type* pointer;
         typedef value_type const* const_pointer;
         typedef value_type& reference;
         typedef value_type const& const_reference;
         typedef size_t size_type;
         template<class Other>  
            struct rebind  
            {  
                typedef GlobalHeap<Other> other;  
            };  
        pointer allocate(size_type n){return reinterpret_cast<pointer>(HeapAlloc(n*sizeof(value_type)));};
        void deallocate(pointer p,size_type n){HeapFree(p);};
        
    };
    template<class _Ty,class _Alloc=std::allocator<_Ty>>
    struct msvc_basic_string{//MSVC的string实现与GNU不同,使用自定义string与内存交互以保证兼容性
        typedef _Ty value_type;
        typedef value_type * pointer;
        typedef value_type const* const_pointer;
        typedef value_type & reference;
        typedef value_type const& const_reference;
        typedef size_t size_type;
        typedef std::basic_string<value_type> String;
        union{
            value_type data_ca[0x10/sizeof(value_type)];
            pointer data_ptr;
        };
        static constexpr size_type npos=size_type(-1);
        size_type _size;
        size_type _reserve;
        msvc_basic_string():_size(0),_reserve(0xF){memset(data_ca,0,sizeof(data_ca));}
        msvc_basic_string(const_pointer ptr,size_type len=npos):_size(0),_reserve(0xF){assign(ptr,len);}
        msvc_basic_string(String const&rv):_size(0),_reserve(0xF){assign(rv);}
        ~msvc_basic_string(){clear();}
        bool inStack()const{return _reserve<0x10;}
        void assign(String const&rv){
            resize(rv.size());
            memcpy(data(),rv.data(),rv.size()*sizeof(value_type));
        }
        void clear(){resize(0);}
        void assign(const_pointer rv,size_type len=npos){
            if(len==npos)
                 for(len=0;rv[len];)
                    ++len;
            resize(len);
            memcpy(data(),rv,len*sizeof(value_type));
        }
        pointer data(){return inStack()?data_ca:data_ptr;}
        const_pointer data()const{return inStack()?data_ca:data_ptr;}
        const_pointer c_str()const{return data();}
        String toGNUString()const{return String(data(),_size);}
        void resize(size_type sz){
            size_type newsz(1);
            while(sz>=newsz)
                newsz<<=1;
            _Alloc alloc;
            if(newsz>0x10&&_reserve!=newsz){
                auto tmp=alloc.allocate(newsz);//mscvrt x
                memcpy(tmp,data(),std::min(sz,_size)*sizeof(value_type));
                if(!inStack())
                    alloc.deallocate(data_ptr,_reserve+1);
                _reserve=newsz-1;
                data_ptr=tmp;
            }else if(!inStack()){
                auto tmp=data();
                memcpy(data_ca,tmp,std::min(sz,_size)*sizeof(value_type));
                alloc.deallocate(tmp,_reserve+1);
                _reserve=sizeof(data_ca)-1;
            }
            data()[sz]=0;
            _size=sz;
        }
        size_type size()const{return _size;}
        size_type capacity()const{return _reserve;}
        msvc_basic_string&operator=(String const&rv){assign(rv);return *this;}
        msvc_basic_string&operator=(const_pointer rv){assign(rv);return *this;}
        operator String()const{return toGNUString();}
    };
    typedef msvc_basic_string<char,GlobalHeap<char>> msvc_string;
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
    std::string write_memory(intptr_t add,std::string const&data);
    int getLastErr();
};