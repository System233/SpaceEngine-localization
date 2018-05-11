#include "Hook.h"
#include <ctime>
#include <memory>
#include <fstream>
#include <unordered_map>
#include <cstdint>
#include <gl/gl.h>
//#define STBI_SUPPORT_ZLIB
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define GL_TEXTURE_BASE_LEVEL 0x813C  

#include <json/json.h>
namespace Hook{
    TEST_API(void) Hack(){
        GLint w, h, lv;
        glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, &lv);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, lv, GL_TEXTURE_WIDTH, &w);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, lv, GL_TEXTURE_HEIGHT, &h);
        int constexpr px=4;
        auto data = std::make_unique<uint8_t[]>(h*w*px);
        glGetTexImage(GL_TEXTURE_2D, lv, GL_RGBA, GL_UNSIGNED_BYTE, data.get());
        timeb tb;
        ftime(&tb);
        auto tm=std::localtime(&tb.time);
        char filename[0x100];
        snprintf(filename,sizeof(filename),"%04d-%02d-%02d %02d-%02d-%02d.%03d.png",tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday,tm->tm_hour,tm->tm_min,tm->tm_sec,tb.millitm);
        stbi_write_png(filename,w,h,px, data.get(),w*px);
    }
    
    void Draw::draw(uint8_t const*str,bool b){
        
      /*  for(uint8_t p=str,ch=*str;ch;ch=*++p){
            switch(ch){
                case 0x1u:
                    if(int_09<2)
                        int_09+=1;
                    if(b){
                    
                    }else{
                        float_47+=0.5;
                        sub_434E20(p-str);
                    }
                case 0x2u:
                case 0x3u:
                case 0x4u:
                case 0x5u:
                case 0x6u:
                case 0x7u:
                case 0x8u:
                case 0x9u:
                case 0xAu:
                case 0xBu:
                case 0xCu:
                case 0xFu:
            
            }
        }*/
    };
    STD_API(DecodePack) Decode(uint8_t const*utf8){
        uint32_t code(*utf8++);
        if(code>=0x80)
            for(char bit(0xE0),sz(1);sz<6;bit>>=1,++sz)
                if(char(code&bit)==char(bit<<1)){
                    DecodePack dp{utf8,uint16_t(code&(~bit))};
                    for(;sz&&char(*dp.utf8&0xC0)==char(0x80);--sz)
                            dp.u16=(dp.u16<<6)|(*dp.utf8++&0x3F);
                    if(!sz)
                        return dp;
            }
        return DecodePack{utf8,uint16_t(code)};
    };
    STD_API(void) GenTex(){
        GLint w, h, lv;
        glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, &lv);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, lv, GL_TEXTURE_WIDTH, &w);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, lv, GL_TEXTURE_HEIGHT, &h);
        int constexpr px=4;
        auto data = std::make_unique<uint32_t[]>(h*w*2);
        memset(data.get()+h*w,0,h*w*px);
        glGetTexImage(GL_TEXTURE_2D, lv, GL_RGBA, GL_UNSIGNED_BYTE, data.get());
        glTexImage2D(GL_TEXTURE_2D,lv,GL_RGBA,w,h*2,0,GL_RGBA,GL_UNSIGNED_BYTE,data.get());
    };
    struct DrawCfg{
        float w;//18.0 32
        int32_t diph;//0x96
        int32_t dipw;//0x96?
        int32_t int_3;//0
        float dw,dh;//显示比例
        int32_t int_6;
        int32_t int_7;
        int32_t int_8;
        int32_t int_9;
        char font[4*4];
        int32_t int_14;//0e
        int32_t int_15;//F
        
        
        
    };
    struct Thunk{
        std::array<std::pair<size_t,size_t>,1>rebased={{{0x10C+3,0}}};
        Thunk(size_t base);
    };
    std::unordered_map<uint32_t,uint32_t> map;
    static size_t base;
    static std::string cwd;
    static char const*lang_ptr;
    static Json::Value root; 
    static float *defmap_ptr;//0X36W:0X336O:0x636:1/w
    //float UnitWidth[3];//大中小 1/纹理宽度
    //uint32_t (*map)[0xFFFF];//w|o|y|x
    bool mapped=false;
    struct DisCfg{float x,y,dw,dh;} *disCfg_ptr;
    STD_API(void) Decode_ASM(){//arg:esi,ret:@eax=utf8,@ebx=code
        __asm __volatile__("push edx;push ecx;push esi;call _Decode;pop ecx;mov ebx,edx;pop edx;test bx,bx;");
    }
    STD_API(void) Decode_ASM_AC(){//@eax=utf8,@ecx=code
        __asm __volatile__("push edx;push ebx;push esi;call _Decode;pop ebx;mov ecx,edx;pop edx;test cx,cx;");
    }
    STD_API(uint32_t) GetCode(uint16_t ch,uint16_t sz){
        if(!mapped)
            HookMain();
        uint16_t const code=(ch&0xFF)|(sz<<8);
        std::unordered_map<uint32_t,uint32_t>::const_iterator cit;
        return ch>=0xC0&&(cit=map.find(ch|(sz<<16)))!=map.end()?cit->second:(uint8_t(defmap_ptr[code+0x36])<<24|uint8_t(defmap_ptr[code+0x336])<<16|(ch&0xF0)<<4|ch&0xF);
    };
    STD_API(void) ASMTEST(){
        //__asm __volatile__("mov %eax,%ebx;push %ebx;pop %ebx;");
    }
    /*STD_API(uint32_t) GetCode(uint16_t ch,uint16_t sz){
        uint8_t const code=(ch&0xFF)|sz<<16;
        std::unordered_map<uint32_t,uint32_t>::const_iterator cit;
        return ch>=0xC0&&(cit=map.find(ch|(sz<<16)))!=map.end()?cit->second:uint8_t(defmap_ptr[code+0x36])<<24|uint8_t(defmap_ptr[code+0x336])<<16|(ch&0xF0)<<4|ch&0xF;
    };*/
    STD_API(bool) external_cmp(uint16_t ch){return ch<48||(ch>=58&&ch<=63)||(ch>=91&&ch<=95)||(ch>=123&&ch<=126);};
    STD_API(void) chcmp_asm(uint16_t ch){
        __asm __volatile__("push edx;push eax;push ecx;\
                            mov edx,[esp+0x0C];\
                            lea eax,[edx-0x3A];\
                            cmp ax,0x05;\
                            setbe al;\
                            cmp dx,0x2F;\
                            setbe cl;\
                            or al,cl;\
                            jne end;\
                            lea ecx,[edx-0x5B];\
                            mov eax,00000001;\
                            cmp cx,0x04;\
                            jna end;\
                            sub edx,0x7B;\
                            cmp dx,0x03;\
                            setbe al;\
                            end:test al,al;pop ecx;pop eax;pop edx;ret 0x04;");};
    STD_API(uint32_t) GetUWidth(uint16_t ch){
        if(!mapped)
            HookMain();
    return *(uint32_t*)(&defmap_ptr[ch+0x636]);};
    STD_API(uint32_t) GetWidth(uint32_t ch){
        uint16_t const code=ch&0xFFFF;
        std::unordered_map<uint32_t,uint32_t>::const_iterator cit;
        float tmp=ch>=0xC0&&(cit=map.find(ch))!=map.end()?char(cit->second>>24):defmap_ptr[0x36+(code&0xFF)|((ch>>8)&0xFF00)];
        return *(uint32_t*)(&tmp);
    };
    STD_API(uint32_t) GetWidth2(uint16_t ch,uint16_t sz){
        //__asm 
        uint16_t const code=(ch&0xFF)|(sz<<8);
        std::unordered_map<uint32_t,uint32_t>::const_iterator cit;
        float tmp=ch>=0xC0&&(cit=map.find(ch))!=map.end()?char(cit->second>>24):defmap_ptr[code+0x36];
        return *(uint32_t*)(&tmp);
    };
     STD_API(void) GetWidth_ASM(){//@ebx=code,@eax=Tex
        __asm __volatile__("push ecx;push edx;push eax;push ebx;call _GetWidth2;pop edx;pop ecx;movd xmm0,eax;");
    }
    STD_API(void) GetWidth_ASM_CA(){//@ecx=code,@eax=Tex
        __asm __volatile__("push ebx;push edx;push eax;push ecx;call _GetWidth2;pop edx;pop ebx;movd xmm0,eax;");
    }
    STD_API(uint32_t) GetOffset(uint32_t ch){
        uint16_t const code=ch&0xFFFF;
        std::unordered_map<uint32_t,uint32_t>::const_iterator cit;
        float tmp=ch>=0xC0&&(cit=map.find(ch))!=map.end()?char((cit->second>>16)&0xFF):defmap_ptr[0x336+(code&0xFF)|(ch>>8&0xFF00)];
        return *(uint32_t*)(&tmp);
    };
    STD_API(uint8_t) GetPosX(uint32_t ch){
        uint16_t const code=ch&0xFFFF;
        std::unordered_map<uint32_t,uint32_t>::const_iterator cit;
        return ch>=0xC0&&(cit=map.find(ch))!=map.end()?(cit->second&0xFF):ch&0xF;
    };
    STD_API(uint8_t) GetPosY(uint32_t ch){
        uint16_t const code=ch&0xFFFF;
        std::unordered_map<uint32_t,uint32_t>::const_iterator cit;
        return ch>=0xC0&&(cit=map.find(ch))!=map.end()?(cit->second>>8)&0xFF:(ch>>4)&0xF;
    };
    STD_API(void) TestAPI(){
        uint8_t const*utf8=(uint8_t const*)"测试";
        auto x=Decode(utf8);
        auto co=GetCode(x.u16,0xFFEE);
        auto w=GetWidth(x.u16);
        auto o=GetOffset(x.u16);
        x.utf8+=x.u16;
        x.u16+=w*o;
    };
    std::array<uint32_t,4>constexpr glformat={GL_LUMINANCE,GL_LUMINANCE_ALPHA,GL_RGB,GL_RGBA};
    void MappingTexture(std::string const&path,size_t x,size_t y){
        GLint w, h, lv,iw,ih,n(0);
        uint8_t *data = stbi_load(path.c_str(), &iw, &ih, &n, 0);
        if(data){
            glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, &lv);
            glGetTexLevelParameteriv(GL_TEXTURE_2D, lv, GL_TEXTURE_WIDTH, &w);
            glGetTexLevelParameteriv(GL_TEXTURE_2D, lv, GL_TEXTURE_HEIGHT, &h);
            if(n&&n<=4&&x+iw<w&&y+ih<y)
                glTexSubImage2D(GL_TEXTURE_2D, lv, x, y, iw, ih, glformat[n-1], GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
    }
    bool initialized=false;
    STD_API(void) HookMain(){
        //std::ofstream out("zlib1.log");
        //out<<"initialized:"<<initialized<<std::endl;
        if(initialized){
            GLint w(0), h(0), lv;
            glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, &lv);
            glGetTexLevelParameteriv(GL_TEXTURE_2D, lv, GL_TEXTURE_WIDTH, &w);
            glGetTexLevelParameteriv(GL_TEXTURE_2D, lv, GL_TEXTURE_HEIGHT, &h);
            if(w<256||h<256)
                return;
            Json::Value const&lang = root["language"][lang_ptr];
            map.clear();
            mapped=true;
            //out<<"lang.isNull():"<<lang.isNull()<<std::endl;
            if(!lang.isNull()){
                std::array<char const*,3>constexpr type={"normal","shadow","large"};
                for(size_t ty(0);ty<type.size();++ty){
                    auto&curcfg=lang["texture"][type[ty]],&link=curcfg["link"];
                    auto&cfg=lang["texture"][link.isString()?link.asString():type[ty]];
                    auto getCfg=[&curcfg,&cfg](std::string const&val)->auto const&{return (curcfg[val].isNull()?cfg:curcfg)[val];};
                    auto&file=getCfg("file"),&mmap=getCfg("map"),
                        &jx=getCfg("x"),&jy=getCfg("y"),
                        &jcw=getCfg("w"),&jp=getCfg("p"),
                        &jdw=getCfg("dw"),&jdh=getCfg("dh"),
                        &jfix=getCfg("fix"),&jcover=getCfg("cover");
                    /*out<<"file.isString()="<<file.isString()<<std::endl
                        <<"mmap.isArray()="<<mmap.isArray()<<std::endl
                        <<"jx.isInt()="<<jx.isInt()<<std::endl
                        <<"jy.isInt()="<<jcw.isInt()<<std::endl
                        <<"jp.isDouble()="<<jp.isDouble()<<std::endl;*/
                    if(file.isString()&&mmap.isArray()&&jx.isInt()&&jy.isInt()&&jcw.isInt()&&jp.isDouble()){
                        int tex_wid,tex_hig,n(0);
                        uint8_t *data = stbi_load((cwd+'/'+file.asString()).c_str(), &tex_wid, &tex_hig, &n, 0);
                        intptr_t const tsize(tex_wid*tex_hig*n), x=jx.asInt(), y=jy.asInt(), cw=jcw.asInt();
                        //out<<"data:"<<(void*)data<<std::endl;
                        if(data){
                            if(jfix.isBool()&&jfix.asBool()&&(n==2||n==4))//MDZZ Fix LA/RGBA
                                for(size_t p(tex_wid*tex_hig*n),c(n-1);p;)
                                    if(!data[--p])
                                        for(size_t x(c);x;--x)
                                            data[--p]=0;
                                    else p-=c;
                            /*out<<"w="<<w
                                <<",h="<<h
                                <<",lv="<<lv
                                <<",tex_wid="<<tex_wid
                                <<",tex_hig="<<tex_hig
                                <<",n="<<n
                                <<",x="<<x
                                <<",y="<<y
                                <<",cw="<<cw
                                <<std::endl;*/
                            if(n&&n<=4&&x+tex_wid<=w&&y+tex_hig<=h){
                                intptr_t char_x(0),char_y(0), ix=tex_wid/cw, iy=tex_hig/cw;
                                for(auto&m:mmap){
                                    auto line=m.asString();
                                    auto checkPos=[data,n,tex_wid,tsize](auto x,auto y){
                                        intptr_t const pos((y*tex_wid+x)*n);
                                        if(pos>=0&&pos<tsize)
                                            for(uint8_t t(n);t--;)
                                                if(data[pos+t])
                                                    return true;
                                        return false;
                                    };
                                    auto checkCol=[ix,iy,&char_x,&char_y,&checkPos](char col){
                                        intptr_t const px=char_x*ix+col,py=char_y*iy;
                                        for(char i(0);i<iy;++i)
                                            if(checkPos(px,py+i))
                                                return true;;
                                        return false;
                                    };
                                    auto checkBox=[ix,iy,&checkCol](){
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
                                            return std::make_pair(char_wid,char_off);
                                    };
                                    //out<<"line:"<<line<<std::endl;
                                    for(auto dp=Decode((uint8_t const*)line.data());dp.u16;dp=Decode(dp.utf8),++char_x)
                                        if(dp.u16!='?'&&!(char_y<0xC&&char_x<16)){
                                            auto box=checkBox();
                                            map[ty<<16|dp.u16]=(uint8_t(box.first)<<24)|(uint8_t(box.second)<<16)|(char_y<<8)|char_x;
                                            //out<<(void*)(ty<<16|dp.u16)<<"->"<<(void*)((uint8_t(char_wid)<<24)|(uint8_t(char_off)<<16)|(char_y<<8)|char_x)<<",VAL="<<(void*)(map[ty<<16|dp.u16])<<std::endl;
                                        }else if(dp.u16!='?'&&jcover.isBool()&&jcover.asBool()){
                                            auto box=checkBox();
                                            uint16_t const code=(ty<<8)|((char_y&0xF)<<4)|(char_x&0XF);
                                            defmap_ptr[code+0x36]=box.first;
                                            defmap_ptr[code+0x336]=box.second;
                                        }   
                                    char_x=0;
                                    ++char_y;
                                }
                                
                                defmap_ptr[ty+0x636]=jp.asFloat();
                                auto&discfg=disCfg_ptr[ty];
                                discfg.x=x/float(w),discfg.y=y/float(h);
                                if(jdw.isDouble())
                                    discfg.dw=jdw.asFloat();
                                if(jdh.isDouble())
                                    discfg.dh=jdh.asFloat();
                                glTexSubImage2D(GL_TEXTURE_2D, lv, x, y, tex_wid, tex_hig, glformat[n-1], GL_UNSIGNED_BYTE, data);
                            }
                            stbi_image_free(data);
                        }
                    }
                }
            }
        }
    }
    STD_API(void) initialize(std::string const&lcwd,size_t lbase){
        base=lbase,cwd=lcwd;
        lang_ptr=reinterpret_cast<char const*>(base+0x500054);
        defmap_ptr=reinterpret_cast<float*>(base+0x5D4CE0);
        disCfg_ptr=reinterpret_cast<DisCfg*>(base+0x5D4CE0+0x18E4);
        std::ofstream out("zlib1.log");
        out<<"lcwd:"<<lcwd<<std::endl;
        out<<"lbase:"<<(void*)lbase<<std::endl;
        out<<"lang_ptr:"<<(void*)lang_ptr<<std::endl;
        out<<"defmap_ptr:"<<(void*)defmap_ptr<<std::endl;
        std::ifstream in(cwd+"/system/language.json",std::ios::binary);
        Json::Reader reader;
        if(in&&reader.parse(in,root)){
            initialized=true;
            //map.reset(new uint32_t[0x10000]);
        }
        out<<"initialized:"<<initialized<<std::endl;
    }
    STD_API(void) uninitialize(){
        initialized=false;
        map.clear();
        //map.reset(nullptr);
    }
}