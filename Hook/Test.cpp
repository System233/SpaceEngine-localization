
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
main(){
    std::string file="chs-font-large.png";//"7f248701a18b87d6841d05ad0b0828381e30fdda.jpg";//
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
            stbi_write_png((file+".png").c_str(),x,y,n, data,x*n);*/
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
    //}
}