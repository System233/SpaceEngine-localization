
#include <ctime>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
struct RGBA{
uint8_t r,g,b,a;
void reset(){r=g=b=0;}
bool check(){return !a&&(r||g||b);}
};
    template<class _Ty,class _Alloc=std::allocator<_Ty>>
    struct msvc_string{
        typedef std::basic_string<_Ty,std::char_traits<_Ty>,_Alloc> GNUString;
        typedef std::basic_string<_Ty> EString;
        typedef _Ty value_type;
        typedef value_type * pointer;
        typedef value_type const* const_pointer;
        typedef value_type & reference;
        typedef value_type const& const_reference;
        typedef size_t size_type;
        union{
            value_type data_ca[0x10/sizeof(value_type)];
            pointer data_ptr;
        };
        static constexpr size_type npos=size_type(-1);
        size_type _size;
        size_type _reserve;
        msvc_string():_size(0),_reserve(0xF){memset(data_ca,0,sizeof(data_ca));}
        msvc_string(const_pointer ptr,size_type len=npos):_size(0),_reserve(0xF){assign(ptr,len);}
        msvc_string(EString const&rv):_size(0),_reserve(0xF){assign(rv);}
        ~msvc_string(){clear();}
        bool inStack()const{return _reserve<0x10;}
        void assign(EString&rv){
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
        GNUString toGNUString()const{return GNUString(data(),_size);}
        void resize(size_type sz){
            size_type newsz(1);
            while(sz>=newsz)
                newsz<<=1;
            _Alloc alloc;
            if(newsz>0x10&&_reserve!=newsz){
                auto tmp=alloc.allocate(newsz);//mscvrt
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
        msvc_string&operator=(EString const&rv){assign(rv);return *this;}
        msvc_string&operator=(const_pointer rv){assign(rv);return *this;}
        operator GNUString()const{return toGNUString();}
    };
#include <set>
#include <windows.h>
template<class _Ty>
class CAlloc:public  std::allocator<_Ty>{
    typedef std::allocator<_Ty> alloc;
    public:
     typedef _Ty value_type;
     typedef value_type* pointer;
     typedef value_type const* const_pointer;
     typedef value_type& reference;
     typedef value_type const& const_reference;
     typedef size_t size_type;
     static std::set<pointer>set;
     template<class Other>  
        struct rebind  
        {  
            typedef CAlloc<Other> other;  
        };  
        //CAlloc():alloc(){};;
    pointer allocate(size_type sz){
        pointer ptr=alloc::allocate(sz);
        std::cout<<"alloc:"<<(void*)ptr<<","<<sz<<std::endl;
        set.insert(ptr);
        return ptr;
    };
    void deallocate(pointer ptr,size_type n){
        std::cout<<"dealloc:"<<(void*)ptr<<","<<n<<";"<<std::endl;
        alloc::deallocate(ptr,n);
        set.erase(ptr);
    };
    static void check(){
        std::cout<<"MEM_LEAK:"<<std::endl;
        for(auto m:set)
            std::cout<<(void*)m<<std::endl;
    }
    
};
    template<class _Ty>
    class GlobalHeap{//¶Ñ¿ØÖÆ
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
        pointer allocate(size_type n){return reinterpret_cast<pointer>(HeapAlloc(GetProcessHeap(),0,n*sizeof(value_type)));};
        void deallocate(pointer ptr,size_type n){HeapFree(GetProcessHeap(),0,ptr);};
    };
template<class _Ty>
    std::set<_Ty*> CAlloc<_Ty>::set;
main(){
    
    {
    msvc_string<char,GlobalHeap<char>>mstr="123456";
    auto gnustr=mstr.toGNUString();
    std::cout<<"ESP:"<<(void*)&mstr<<std::endl;
    std::cout<<"GESP:"<<(void*)&gnustr<<std::endl;
    std::cout<<mstr.toGNUString()<<"->"<<(void*)mstr.data()<<",sz:"<<mstr.size()<<",cap:"<<mstr.capacity()<<std::endl;
    mstr="012345678901234567890123456789";
    std::cout<<mstr.toGNUString()<<"->"<<(void*)mstr.data()<<",sz:"<<mstr.size()<<",cap:"<<mstr.capacity()<<std::endl;
    mstr="123456";
    std::cout<<mstr.toGNUString()<<"->"<<(void*)mstr.data()<<",sz:"<<mstr.size()<<",cap:"<<mstr.capacity()<<std::endl;
   mstr="012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
    std::cout<<mstr.toGNUString()<<"->"<<(void*)mstr.data()<<",sz:"<<mstr.size()<<",cap:"<<mstr.capacity()<<std::endl;
    mstr="012345678901234567890123456789";
    std::cout<<mstr.toGNUString()<<"->"<<(void*)mstr.data()<<",sz:"<<mstr.size()<<",cap:"<<mstr.capacity()<<std::endl;
    mstr="012345678901200";
    std::cout<<mstr.toGNUString()<<"->"<<(void*)mstr.data()<<",sz:"<<mstr.size()<<",cap:"<<mstr.capacity()<<std::endl;
    asm volatile("int3");
   }
   CAlloc<char>::check();
   /* std::string file="chs-font-large.png";//"7f248701a18b87d6841d05ad0b0828381e30fdda.jpg";//
    //while(std::cout<<'>',std::getline(std::cin,file)){
        int tex_wid,tex_hig,n;
        uint8_t *data = stbi_load(file.c_str(), &tex_wid, &tex_hig, &n, 0);
        intptr_t const cw=16;
        intptr_t const ix=tex_wid/cw,iy=tex_hig/cw,tsize(tex_wid*tex_hig*n);
        if(data){
            std::ofstream out(file+".raw",std::ios::binary);
            out.write((char*)data,tsize);
            out.close();
            /*
            bool o=1;
            if(n!=4)
                std::cout<<'n',o=0;
            else for(size_t i=x*y;i;){
                RGBA &rgba=((RGBA*)data)[--i];
                if(rgba.check())
                    {o=0;
                    //break;std::cout<<'x';
                    }
                if(!rgba.a)
                    rgba.reset();
            }
            std::cout<<(o?'o':'x');
            stbi_write_png((file+".png").c_str(),x,y,n, data,x*n);
            intptr_t char_x(0),char_y(0),char_col(0);
            while(std::cout<<"x,y>",std::cin>>std::hex>>char_y>>char_x){
                //ÏñËØ×ø±ê
                auto checkPos=[data,n,tex_wid,tsize](auto x,auto y){
                                                intptr_t const pos((y*tex_wid+x)*n);
                                                if(pos>=0&&pos<tsize)
                                                    for(uint8_t t(n);t--;)
                                                        if(data[pos+t])
                                                            return true;
                                                return false;
                                            };
                                            //ÁÐ
                                            auto checkCol=[ix,iy,char_x,char_y,checkPos](char col){
                                                intptr_t const px=char_x*ix+col,py=char_y*iy;
                                                for(char i(0);i<iy;++i)
                                                    if(checkPos(px,py+i))
                                                        return true;;
                                                return false;
                                            };
                                            char char_wid(0),char_off(0);
                                            bool const dis=checkCol(0);
                                            for(char x=0;x<ix&&x>-char(ix);char_off=dis?x--:x++)
                                                if(dis?!checkCol(x):checkCol(x))break;
                                            bool fg=false;
                                            for(char x=std::max(char_off,char(0))+1;x<ix*2;char_wid=x++)
                                                if(checkCol(x))
                                                   fg=true;
                                                else if(fg)
                                                    break;
                                               
                                            char_wid-=char_off;     
                std::cout<<std::hex<<"char("<<char_x<<','<<char_y<<')'
                        <<std::dec
                        <<"char_wid:"<<+char_wid
                        <<",char_off:"//(void*)((char_wid<<24)|(char_off<<16)|(char_y<<8)|char_x)
                        <<+char_off<<" VAL="<<(void*)(uint8_t(char_wid)<<24|(uint8_t(char_off)<<16))<<std::endl;
            }
            std::cin.ignore();
            std::cin.clear();
            stbi_image_free(data);
        }
    //}*/
}