# SpaceEngine 字符扩展

------

由于Space Engine自身特性，可用字符总数被限制为255个，这极大的阻碍了其他非拉丁字母语言的本土化。

本补丁程序通过**DLL劫持(替换)** 实现自动加载，并在**运行时修改**主程序在内存中的代码，从而使得游戏能够**显示超过255种字符** 。

[前往下载页面](https://github.com/System233/SpaceEngine-localization/releases)

### 特性
支持版本: **0.970~0.980e、0.981b9(仅源码可用)**

附带语言：**简体中文，繁体中文(简转繁)**

支持扩展其他因字符数量超过255个而受限的语言。

#### **扩展后的字符数限制**
|主程序版本|最大尺寸|字数限制|
|-|-|:-:|
|0.974\~0.980|64×32|约1813字|
|0.970\~0.973|32×32|约 813字|
|0.981b9 (UTF-8)|32×32|约 831字|

### 缺陷
|描述|版本|
|-|:-:|
|不支持游戏内复制与编辑|所有版本|
|不支持大小写映射|所有版本|
|单行过长自动换行截断(SE功能)导致显示不正常|所有版本|
|线程不安全:疑似引起文字随机闪烁|0.970~0.980e|
|语言切换延时:切换语言时闪烁|0.970~0.980e|
|仅支持PNG字体纹理|0.970~0.980e|
|自定义编码:不便编辑-gui.cfg翻译文件|0.970~0.980e|
|未附带语言文件|Github版补丁R1.0.1.0及以下|
|不成熟的自定义配置文件|补丁版本R1.0.1.0及以下|
|内存泄漏|补丁版本R1.0.0.4及以下|
|代码太丑|0.970~0.980e|





------

## 原理
### 分析问题
SE内部将纹理划分为一个16×16的网格，并通过字符的ASCII码值确定其坐标，这便是255字符限制的主要原因。
```C++
//游戏内部默认坐标计算函数
char ch;        //='A',ASCII=0x41
char x=ch&0xF;  //0x41&0xF  =0x01
char y=ch>>4;   //0x41>>4   =0x04
/*最终x=1,y=4，字符'A'的坐标便是(1,4)
 *可以数数字体纹理上的字符A在第几行第几列
 *坐标值从0开始,第一行被控制符占用所以没有字符，但不要漏算
 *此步之后，XY坐标会被转换为浮点类型纹理坐标。
 */
```

ASNI编码的中文是双字节字符，一个char是存不下的，而且中文编码也没有这种规律，所以默认SE内的gui.cfg文件不能输入中文。

SE默认的16×16字符也是不够用的，根据字体纹理在显存中的使用方式(调用`glGetTexImage`)，在0.970\~0.973、0.981B9中经过修改可以划分成32×32，每个网格像素为16×16的网格，在0.974~0.980e中更可以划分为64×32，对中文来讲勉强够用。

但是在981B9中有三个不同的字体纹理

|字体|编号|网格|像素|用途|
|-|-|-|-|-|
|小字体|0|16×16|256×256|大部分菜单上显示|
|小字体(带阴影)|1|16×16|256×256|仅用于显示左上角的天体信息|
|大字体|2|16×16|512×512|主菜单显示|

其中带阴影小字体在显存中紧贴小字体的右侧，当网格扩展为32×32(512×512像素)时，右侧的带阴影字体将不复存在。

### 解决问题
目前针对0.970~0.980e的补丁使用自定义编码来解决坐标问题，其原理还是通过编码值来确定坐标，但需要在(0,0xFF)区间内选出几个值来标记需要处理的字符，被标记的字符会在计算完坐标后再给XY分别加上一个偏移值。
```C++
/*例如'我'字被编码为0B,64,其中0B是标记,64是被标记的坐标
 *设0B值被用来专门标记该点集{(X,Y)|X∈[16,32),Y∈[0,16)}内的坐标,
 *也就是在原16×16网格右侧的另一个16×16网格。
 */
std::vector<char>mak,data;  //全局变量，分别存储被标记字符和其他剩余字符
char X,Y;                   //全局变量,方便坐标传递
char const*TEST="\x0B\x64";
char*Hook(char*p){  //函数修改了全局变量，因此线程不安全
    mak.clear();data.clear();   //清空之前数据
    while(*p){                  //如果字符不为NULL终止符
        data.push_back(*p);     //存入容器data
        if(*p++==0xB)           //如果是标记
            mak.push_back(*p++);//把标记后被标记的值存入容器mak
    }
    data.push_back(0);  //0值结尾
    return data.data(); //返回容器data内部数据的指针
}
void SetPos(char ch){//根据ch的值与容器mak内的数据设置全局变量X,Y，同样线程不安全
    if(ch==0xB&&!mak.empty()){
        auto it=mak.begin();
        X=*it&0xF   +16,//给坐标X值加16
        Y=*it>>4    + 0;//给坐标Y值加0,如果0XB代表的是32×32网格中右下16×16部分则也需要加16
                        //坐标偏移由补丁自动处理，不需要手动设置
        mak.erase(it);  //读取之后删除该元素，这里会导致容器中所有数据向前移动，
                        //因此它是整个钩子中开销最大的部分
        return;
    }
    X=ch&0xF;
    Y=ch>>4;
}
游戏内部字符处理函数(char*str){     //str:要显示的字符串
    str=Hook(str);              //在函数头部下钩子，跳转到Hook函数，并修改参数str的值
    while(*str){
        char ch=*str++;
        SetPos(ch);
        /*控制符处理*/
        char x=X;//char x=ch&0xF;  修改这部分代码
        char y=Y;//char y=ch>>4;
        /*...坐标转换部分...*/
    }
}
//当字符串TEST被传入内部处理函数，'我'字的坐标值会从(6,4)变成(6+16,4+0)
```
流程图

![旧流程](https://github.com/System233/SpaceEngine-localization/blob/mingw/Hook/flow-old.svg)
由于修改了全局变量，函数变成了线程不安全，多个线程在此类函数内运行时将出现问题，但因为"显示字符"是UI相关操作，而UI最忌讳的就是多线程，所以我不大觉得这个函数会有多个线程同时在里面运行，也没有做过针对测试。

**为避免上述隐患**，重写后的981B9补丁不再使用全局变量来传递数据，同时改自定义编码为UTF-8编码。

UTF-8编码跟ANSI编码都是多字节字符集，所以它也可以被SE读取，但仍需修改主程序才能支持新编码。

目前981b9补丁的大致原理如下
```C++
/*字符:'我',UTF-8编码：E6,88,91，UTF16编码:0x6211。
 *uint16占用2字节，char占用1字节。
*/
char const *TEST="\xE6\x88\x91";//相当于"我"
uint16_t Decode(char*&p)//UTF-8解码函数，返回解码后的UTF16值，同时指针p增加相应字节数,'我'字为3字节，解码之后指针p+3以指向下一个字符
std::unordered_map<uint32_t,uint32_t>map;//用于建立字符值到字符参数的映射:坐标yyxx、宽度ww、偏移oo
                                         //数据排列为wwooyyxx
                                         //键值排列为XXXXYYYY，其中XXXX为字号,YYYY为UTF16编码
                                         //该字段在dll被加载时从json配置文件读取
uint32_t Get(uint16_t ch){  //获取字符参数
    auto it=map.find(ch);   //这个查找过程是整个钩子中开销最大的部分。
    if(it!=map.end())       //如果找到了
        return it->second;  //直接返回数据
    return wwoo|ch&0xF0<<4|ch&0xF;//否则就地构造一个数据，wwoo为SE内部的字体宽度和偏移参数
}
游戏内部字符处理函数(char*str){
    while(*str){
        char m=1;//981中还有字号要处理，这里假设字号一直是1，也就是无阴影小字体
        uint16_t ch=Decode(str) //char ch=*str;把全部1字节的char改为2字节的uint16_t，
                                //在汇编中就是把低8位寄存器都改为更大的寄存器
        /*控制符处理*/
        uint32_t data=Get(m<<16|ch);//混合字号信息后再传入
        char x=data&0xFF;   //char x=ch&0xF; 取wwooyyxx中的xx部分
        char y=data>>8&0xFF;//char y=ch>>4;  取wwooyyxx中的yy部分
        /*...坐标转换和宽偏处理部分...*/
    }
}
//当字符串TEST被传入内部处理函数，'我'字的坐标会变成map中设置的值。
```
流程图

![新流程](https://github.com/System233/SpaceEngine-localization/blob/mingw/Hook/flow-utf8.svg)

这种方式解决了因全局变量引起的线程不安全问题，但对原程序中的汇编代码改动较大，所以尚未在0.980e及以下版本的补丁中应用。

添加UTF-8支持后，人们可以直接拿起记事本用中文修改-gui.cfg。

由于每个字的UTF-8编码是固定的，所以不会再出现自定义编码中因文字编码更新，但SE保存了旧编码而导致的乱码（例如保存的天体坐标）。

## 开发
### 编译环境
本补丁当前已改用 [CMake](https://github.com/Kitware/CMake)+[MSYS2](https://github.com/msys2/msys2) 构建。
CMake 是一个跨平台编译工具，它可以根据 [CMakeLists.txt](https://github.com/System233/SpaceEngine-localization/blob/mingw/Hook/SpaceEngine.CT) 内的描述生成用户想要的工程文件。
MSYS2 是一套仿Unix平台工具，它可以很方便地在Windows上编译在Linux上开发的软件，用这类软件的人估计都遇过在 [Visual Studio](https://www.visualstudio.com/) 中根本没法编译的项目。
### 代码
当前补丁代码主要位于[Hook.cpp](https://github.com/System233/SpaceEngine-localization/blob/mingw/Hook/Hook.cpp)，修改内存进行Hook的过程位于Hook::initialize函数中。

在以下示例Mod中,0x217641为偏移值，第二个字符串类型的参数为要写入的汇编码，之后的链式调用为代码重定位。
```C++
Mod::make_mod(0x217641,//相对基址偏移
            "\x56\xE8\x00\x00\x00\x00\x66\x85\xD2\x0F\x84\xF8\x08\x00\x00\xF3"//已编译的汇编码
            "\x0F\x10\x0D\x00\x00\x00\x00\xF3\x0F\x10\x1D\x00\x00\x00\x00\xF3"//或称字节码、机器码
            "\x0F\x10\x25\x00\x00\x00\x00\x66\x0F\x1F\x84\x00\x00\x00\x00\x00"
            "\x8B\xF0\x8B\xCE\x89\x74\x24\x24\x2B\x4D\x08")
            .fix(0x2,Decode)//修复汇编码中偏移0x2位置的数据为Decode函数的调用地址
            .fix<intptr_t>(0x13,0x3A7E44)//修复0x13位置的数据为基址偏移0x3A7E44后的地址
            .fix<intptr_t>(0x1B,0x3A7E08)//模板参数'intptr_t'用于限定数据类型
            .fix<intptr_t>(0x23,0x3A8E34));
```
### 为什么要重定位？
大部分程序的加载地址(基址)都是没有设定的，而反汇编中夹杂了大量与地址相关的代码，只要程序基址改变，原汇编码便会出错，所以在写入之前，需要对汇编码中与地址相关的指令进行重定位(修复)。另外，[PE文件](https://zh.wikipedia.org/wiki/%E5%8F%AF%E7%A7%BB%E6%A4%8D%E5%8F%AF%E6%89%A7%E8%A1%8C) 编译出来的时候本身也会有一个重定位表。
### 通过CE获取偏移值和汇编码
[Cheat Engine](https://github.com/cheat-engine/cheat-engine) 是个非常牛叉的内存修改器，数值搜索、游戏变速、调试器、代码注入等等功能一应俱全，名字中的"引擎"二字当之无愧！
其中的内存定位功能(找出写入/访问该内存的代码)可用来定位游戏中的字符串处理函数，自动汇编功能可用来测试自己的汇编码是否可行。
当然，这个从无到有的测试过程会很漫长。文件 [SpaceEngine.CT](https://github.com/System233/SpaceEngine-localization/blob/mingw/Hook/SpaceEngine.CT) 是981B9补丁制作过程中使用的CT作弊表，可供各位参考。
### 补丁配置文件
当前981B9版补丁的配置文件为 [system/language.json](https://github.com/System233/SpaceEngine-localization/blob/mingw/Hook/language.json)，文件编码为UTF-8，其"\_comment"注释字段已经描述了各参数的作用以及配置规则，某些参数可能需要配合代码才能理解。

欲知JSON内的参数如何影响游戏内的显示，建议使用上述CT作弊表。

修改配置文件后请务必确保语法格式无误，否则补丁不会运行。
### 字体纹理
在SE中，不单单是编码阻碍了其翻译到其他的语言，就连P个能用的字体纹理也是个大麻烦！
经过在Photoshop中多次测试，总算调出了自己比较满意的效果，以下文件可供参考

|文件|描述|
|-|-|
|[win1252-font-big.psd](https://github.com/System233/SpaceEngine-localization/blob/mingw/Hook/win1252-font-big.psd)|16×16，512×512像素，中文大字体|
|[win1252-font-981b9.psd](https://github.com/System233/SpaceEngine-localization/blob/mingw/Hook/win1252-font-981b9.psd)|32×32，512×512像素，小字以及带阴影小字|


## 使用方法
由于历史遗留问题，各版本补丁的使用方法比较混乱，建议查看压缩包内的说明。

[前往下载页面](https://github.com/System233/SpaceEngine-localization/releases)

为防止连带问题，不贴上度盘链接。

![效果(0.980)](http://imgsrc.baidu.com/forum/pic/item/b78638f082025aaff24aa914f3edab64024f1a0e.jpg)

------
  >* 2018-05-29   写了些说明，虽然不够详细，但总比没有好。
