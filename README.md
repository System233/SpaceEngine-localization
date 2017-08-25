# SpaceEngine-localization
使SpaceEngine支持更多字符以方便本地化

ConsoleApplication:本地化文件生成器项目

Win32Project1:本地化补丁项目

~~eng-menu.psd:主菜单纹理~~

~~win1252-font.psd:字体纹理~~

**纹理请使用Release-\*\*.zip内的**

其他:依赖库

![效果](http://imgsrc.baidu.com/forum/pic/item/b78638f082025aaff24aa914f3edab64024f1a0e.jpg)

![生成器](http://imgsrc.baidu.com/forum/pic/item/1565c9025aafa40f1cbe1902a364034f79f0190e.jpg)

将Win32Project1项目生成的文件替换SpaceEngine 的vorbis.dll文件

生成器输入格式详见gui.txt

<br>添加新版本支持只需在dllmain.cpp内的start函数按照格式添加偏移值,必要时需自行编写钩子函数

<br>1.0.1.0 支持980 974RC1 974RC2 974RC3 973 972 971 970

<br>980跟974\*,973以下分别共用字体纹理

```
if (Ver.HM == 0 && Ver.LM == 9 && Ver.HL == 8 && Ver.LL == 0) {//版本			
CanRun = true;//可以运行标志
ReAdd = ReAdd980;//ASM内所需地址偏移			
sTexAdd = TexInitAdd[0];//可以是一个值，切换语言时钩子判定之后继续调用的偏移地址
sStartAdd = StartAdd[0];//SE内置计时器的偏移值			
localePath = "data/locale";//locale目录相对路径
//需要写入的资源 (类型PNG:CONFIG,文件名,释放路径,资源ID)	
res.push_back(new RES(Type[1], ResName[0],localePath, ResId[0]));		
res.push_back(new RES(Type[1], ResName[1], localePath, ResId[1]));
res.push_back(new RES(Type[1], ResName[2], localePath, ResId[2]));
res.push_back(new RES(Type[1], ResName[4], localePath, ResId[4]));
res.push_back(new RES(Type[0], ResName[5], localePath, IDR_GUI980));
//修改内存所需的参数，(钩子函数,目标地址偏移，调用方式0xE8=CALL:0xE9=JMP,钩子大小)，
RwMem.Add(CharAna, FunAdd980[0], 0xE8, 6);CharAna是字串处理钩子		
RwMem.Add(GetWidth980, FunAdd980[3], 0xE8, 6);//设置宽度
RwMem.Add(GetCharXYOffAndWid, FunAdd980[4], 0xE9, 6);//设定坐标、偏移和宽度			
RwMem.Add(TexInit, FunAdd980[5], 0xE8,5);//判定是否需要初始化的钩子
RwMem.Add(SetBackWid980, FunAdd980[6], 0xE8, 6);//设置背景黄条宽度		
}
```
