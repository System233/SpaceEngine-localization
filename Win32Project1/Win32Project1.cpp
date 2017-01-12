// Win32Project1.cpp : 定义 DLL 应用程序的导出函数。
//
#include "stdafx.h"
#include <vector>
#include "gl/gl.h"
#pragma  comment(lib, "opengl32.lib")
CharAdd CharADD;
char *Pstr[8] = { "File","1","2","3","4","5","6","7" };
std::vector<BYTE> Charvec;
int strX = 0, strY = 0;
HANDLE mProc =0;
//偏移 写入代码 大小
BOOL WriteAdd(DWORD OffSet, BYTE *Code, size_t Size)
{
	
	LPVOID lpAddress = (void*)((DWORD)hModule2 + OffSet);
	DWORD dwTemp = 0, dwOldProtect = 0;
	if (Code == 0 || lpAddress == 0 || Size == 0)return FALSE;
	VirtualProtectEx(mProc, lpAddress, Size, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	if(!WriteProcessMemory(mProc, lpAddress, Code, Size, 0))return FALSE;
	VirtualProtectEx(mProc, lpAddress, Size, dwOldProtect, &dwTemp);
	return TRUE;
	
	
}
BOOL ReadAdd(DWORD OffSet, BYTE *Code, size_t Size) {
	LPVOID lpAddress = (void*)((DWORD)hModule2 + OffSet);
	DWORD dwTemp = 0, dwOldProtect=0;
	if (Code == 0 || lpAddress == 0 || Size == 0)return FALSE;
	VirtualProtectEx(mProc, lpAddress, Size, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	if (!ReadProcessMemory(mProc, lpAddress, Code, Size, 0))return FALSE;
	VirtualProtectEx(mProc, lpAddress, Size, dwOldProtect, &dwTemp);
	
	return TRUE;
	
}

SYSTEMTIME sys_time;
//bool RunOnce = true;
BYTE STR[8192];
//char tmp[3] = { 0 };
//int counter = 0;


/*void Save() {
	char Name[256];
	int width = 2048, height = 1024;
	PNGDATA IMAGE;
	IMAGE.B = 8;
	IMAGE.W = width;
	IMAGE.H = height;//1024 1536
	IMAGE.DATA = new BYTE[width* height * 4];
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, IMAGE.DATA);
	//	Dlog(3, "LastError:%d *p:0x%8p", GetLastError(), pixels);
	//IMAGE.DATA = FontTexture;
	GetLocalTime(&sys_time);
	snprintf(Name, 1000, "%02d-%02d-%02d-%02d-%02d-%02d-%02d.png", sys_time.wYear, sys_time.wMonth, sys_time.wDay, sys_time.wHour, sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds);
	write_png(Name, IMAGE);
	free(IMAGE.DATA);



}

*/
/*
BYTE* CharAnalysis(BYTE* str) {
	if (*start>300&& Lstr[0] != tmp[0]) {
		if (RunOnce|| tmp[1]!= Lstr[1]|| Lstr[2]!= tmp[2]) {

			if (counter>2000) {
			tmp[0] = Lstr[0];
			tmp[1] = Lstr[1];
			tmp[2] = Lstr[2];
			//snprintf(tmp, 128, "%s", Lstr);
			//tmp = Lstr;
			counter = 0;
			RunOnce = false;
			PNGDATA IMAGE;
			load_png_image(FontFile, &IMAGE);//CN-font
			glTexSubImage2D(GL_TEXTURE_2D, 0, 256, 512, IMAGE.W, IMAGE.H, GL_RGBA, GL_UNSIGNED_BYTE, IMAGE.DATA);
			free(IMAGE.DATA);
			}
			
		}
		counter++;
	}
	Charvec.clear();
	int i = 0, s = 0;
	while (str[i] != '\0') {
		if (str[i] == 0XB) {
			STR[s++] = str[i++];
			Charvec.push_back(str[i]);
			i++;
		}
		else { STR[s++] = str[i++]; }

	}
	STR[s] = *"\0";
	return STR;

}
*/

void DEFASM CharAna() {//字符串解析
	__asm {
		push ecx
		push[esp + 0xC]
		call CharAnalysis
		mov[esp + 0x10], eax
		add esp, 0x4
		pop ecx
		pop eax
		push ebp
		mov ebp, esp
		and esp, -0x10
		jmp eax
	}

}
/*老函数
void DEFASM GetCharXY() {
	__asm {
		push eax
		push ecx
		push edx
		push[esp + 0x3C]
		call GetChar
		add esp, 4
		pop edx
		pop ecx
		cmp eax, 0
		pop eax
		jz NoChar
		mov eax, strX
		movd xmm7, eax
		mov eax, strY
		//add esp, 4
		ret 0
		NoChar:

		movd xmm7, eax
			movzx eax, cl
			ret 0

	}

}*/
/*
void DEFASM CharXY() {
	__asm {
		push eax
		mov eax, [esp + 0x34]
		cmp eax, 0XB
		pop eax
		jz MIN
		movd xmm7, eax
		movzx eax, cl
		ret 0
		MIN:
		push[esp + 0x30]
			call GetChar
			mov eax, strX
			movd xmm7, eax
			mov eax, strY
			add esp, 4
			ret 0
	}
}
*//*
class Chararr {

public:
	Chararr()
	{
		offsetX = 0;
		offsetY = 0;
		Width = 12;
		Offset = 0;
		X = 0;
		Y = 0;
	}
	unsigned int   offsetX = 256;
	unsigned int   offsetY = 512;
	unsigned int Width = 12;
	unsigned int Offset = 0;
	unsigned int X;
	unsigned int Y;
};
*/
/*int write_png(char *file_name, PNGDATA DATA)
{
	FILE *fp;
	png_structp png_ptr;
	png_infop info_ptr;
	//	png_colorp palette;
	long width = DATA.W;
	long height = DATA.H;
	long bit_depth = DATA.B;
	fopen_s(&fp, file_name, "wb");
	if (fp == NULL)
		return (ERROR);
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (png_ptr == NULL)
	{
		fclose(fp);
		return (ERROR);
	}
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL)
	{
		fclose(fp);
		png_destroy_write_struct(&png_ptr, NULL);
		return (ERROR);
	}
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		fclose(fp);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		return (ERROR);
	}
	png_init_io(png_ptr, fp);
	png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, PNG_COLOR_TYPE_RGBA,
		PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	png_write_info(png_ptr, info_ptr);
	BYTE* image = DATA.DATA;//new BYTE[height*width*4];

	png_bytep* row_pointers = new png_bytep[height];

	if (height > PNG_UINT_32_MAX / (sizeof(png_bytep)))
		png_error(png_ptr, "Image is too tall to process in memory");
	for (long k = 0; k < height; k++)
		row_pointers[k] = image + k*width * 4;
	png_write_image(png_ptr, row_pointers);
	png_write_end(png_ptr, info_ptr);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);
	return 1;
}*/
int LoadPNG(const char *filepath, PNGDATA *IMAGE)
{
	FILE *fp;
	png_structp png_ptr;
	png_infop info_ptr;
	png_bytep* row_pointers;
	char buf[PNG_BYTES_TO_CHECK];
	int w, h, x, y, temp, color_type;

	fopen_s(&fp, filepath, "rb");
	if (fp == NULL) {
		return -1;
	}

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	info_ptr = png_create_info_struct(png_ptr);

	setjmp(png_jmpbuf(png_ptr));
	temp = fread(buf, 1, PNG_BYTES_TO_CHECK, fp);
	if (temp < PNG_BYTES_TO_CHECK) {
		fclose(fp);
		png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		return -2;
	}
	temp = png_sig_cmp((png_bytep)buf, (png_size_t)0, PNG_BYTES_TO_CHECK);
	if (temp != 0) {
		fclose(fp);
		png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		return -3;
	}
	rewind(fp);
	png_init_io(png_ptr, fp);
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);
	color_type = png_get_color_type(png_ptr, info_ptr);
	w = png_get_image_width(png_ptr, info_ptr);
	h = png_get_image_height(png_ptr, info_ptr);
	IMAGE->B = png_get_bit_depth(png_ptr, info_ptr);
	IMAGE->W = w;
	IMAGE->H = h;
	BYTE *IMG=IMAGE->DATA = new BYTE[w*h * 4];
	if (IMG == NULL)return -4;
	row_pointers = png_get_rows(png_ptr, info_ptr);
	int Xsize = 0;
	switch (color_type) {
	case PNG_COLOR_TYPE_RGB_ALPHA:
		for (y = 0; y<h; ++y) {
			for (x = 0; x<w * 4; ) {
				IMG[Xsize++] = row_pointers[y][x++]; // red  
				IMG[Xsize++] = row_pointers[y][x++]; // green  
				IMG[Xsize++] = row_pointers[y][x++]; // blue  
				IMG[Xsize++] = row_pointers[y][x++]; // alpha  
			}
		}
		break;

	case PNG_COLOR_TYPE_RGB:
		for (y = 0; y<h; ++y) {
			for (x = 0; x<w * 3; ) {
				IMG[Xsize++] = row_pointers[y][x++]; // red  
				IMG[Xsize++] = row_pointers[y][x++]; // green  
				IMG[Xsize++] = row_pointers[y][x++]; // blue  
				IMG[Xsize++] = 255;
			}
		}
		break;
	default:
		fclose(fp);
		png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		return 0;
	}
	fclose(fp);
	png_destroy_read_struct(&png_ptr, &info_ptr, 0);
	return 0;
}
//移除
/*
void GetChar(wchar_t ch) {
	if (ch == 0X0B) {
		int ID = Charvec.front();
		Charvec.erase(Charvec.begin());
		strX = 16 + (ID % 16);
		strY = ID / 16;
	}
}*/
/*
bool RunOnce = true;
BYTE STR[8192];int *start = (int*)((DWORD)hModule2 + 0X407E64);
char* Lstr = (char*)((DWORD)hModule2 + 0X4AD788), tmp[3] = { 0 };
int counter = 0;
*/
/*	if (*start > 100 && Lstr[0] != tmp[0]) {
if (RunOnce || tmp[1] != Lstr[1] || Lstr[2] != tmp[2]) {

//if (counter > 2000) {
tmp[0] = Lstr[0];
tmp[1] = Lstr[1];
tmp[2] = Lstr[2];
//snprintf(tmp, 128, "%s", Lstr);
//tmp = Lstr;
//counter = 0;
RunOnce = false;
if (!INITED) {
MainInit();
}
DrawTexture();
//}
//counter++;
}
}*/
int TIMES = 0;bool TMSO = true;
bool ReTex = false;
/*BYTE* CharAnalysis(BYTE* str) {

	if (ReTex) {
		if (TMSO) {
			TMSO = false;
			TIMES = *start;
		}
		if((*start-TIMES)>2){
		CharADD.MainInit();
		DrawTexture();
		WCharAdd.Start();
		ReTex = false;
		TMSO = true;
		}

	}

	Charvec.clear();
	int i = 0, s = 0;

	while (str[i] != '\0') {

		if (CharADD.Page[STR[s] = str[i]].use)Charvec.push_back(str[++i]);
		s++;i++;
	}
	STR[s] = 0;
	return STR;

}*//*
void SAVE(int width, int height) {
	char Name[256];
	PNGDATA IMAGE;
	IMAGE.B = 8;
	IMAGE.W = width;
	IMAGE.H = height;//1024 1536
	IMAGE.DATA = new BYTE[width* height * 4];
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, IMAGE.DATA);
	//	Dlog(3, "LastError:%d *p:0x%8p", GetLastError(), pixels);
	//IMAGE.DATA = FontTexture;
	GetLocalTime(&sys_time);
	snprintf(Name, 1000, "%02d-%02d-%02d-%02d-%02d-%02d-%02d.png", sys_time.wYear, sys_time.wMonth, sys_time.wDay, sys_time.wHour, sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds);
	write_png(Name, IMAGE);
	delete[] IMAGE.DATA;

}*/
BYTE* CharAnalysis(BYTE* str) {

	if (ReTex) {
		if (TMSO) {
			TMSO = false;
			TIMES = *start;
		}
		if ((*start - TIMES)>2) {
			CharADD.MainInit();
			DrawTexture();
			WCharAdd.Start();
			ReTex = false;
			TMSO = true;
			//SAVE(0x800, 0x400);
		}

	}
	
	Charvec.clear();
	int i = 0, s = 0;

	while (str[i] != '\0') {

		if (CharADD.Page[STR[s] = str[i]].use)Charvec.push_back(str[++i]);
		s++;i++;
	}
	STR[s] = 0;
	return STR;

}
/*老函数
int GetChar(wchar_t ch) {
	BYTE PID = 0;
	if (CharADD.Page[ch].use) {//ch==0X0B
		if (Charvec.empty())return 0;

		int ID = Charvec.front();
	//	Charvec.erase(Charvec.begin());//偏移支持后需要移除以在偏移处清理
		strX = CharADD.Page[ch].OffSetX + (ID % 16);//strX = 16 + (ID % 16);
		strY = CharADD.Page[ch].OffSetY + (ID / 16);//strY = ID / 16;
		return 1;
	}
	return 0;
}
*/
void DrawTexture() {
	for (int i = 0;i<7;i++) {
		BYTE PID = CharADD.PageId[i];
		int x = CharADD.Page[PID].PX;
		int y = CharADD.Page[PID].PY;
		PNGDATA IMAGE;
		
		const char *File1 = CharADD.Page[PID].File.c_str();
		const char *TMP=0;
		int j = 0;
		while (File1[j] != '\0') {
			if (File1[j] != ' ') {
				TMP= &File1[j];
				break;
			}
			j++;
		}
		char File[256];
		snprintf(File, 256, "%s/%s",localePath, TMP);
		int ERR = LoadPNG(File, &IMAGE);

		if (ERR != 0 || IMAGE.W != IMAGE.H || IMAGE.W != 256) {
			CharADD.Page[PID].use = false;	
			continue;
		}
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, IMAGE.W, IMAGE.H, GL_RGBA, GL_UNSIGNED_BYTE, IMAGE.DATA);
		delete[] IMAGE.DATA;
	}

}

float OneByte = 0.004f;
float OFFSetA=0.0f,Width=0.0f;
/*老函数float XMM0TMP = 0.0f;

int GetCharOffSet(int ch) {
	if (CharADD.Page[ch].use) {
		if (Charvec.empty())return 0;
		int ID = Charvec.front();
		Charvec.erase(Charvec.begin());
		OffSet*PAGE = CharADD.Page[ch].Page;
		if(PAGE!=0){
		//double OFF = PAGE[ch].Off;
			OFFSetA = PAGE[ID].Off / 256.0f;
		//COffSet = OFF*OneByte;
		return 1;
		}
		
		return 0;
	}
	return 0;
}
void DEFASM GetCharOff() {
	__asm {
		
		push eax
		MOVSS [XMM0TMP],XMM0
		push ecx
		push edx
		call GetCharOffSet
		cmp eax,0
		movSS  xmm0, [XMM0TMP]
		pop edx
		pop ecx
		pop eax
		jz NO
		addss xmm7, OFFSetA
		ret 0
		NO:
		addss xmm7, [esi + edx * 0X4 + 0X0000045C]
		ret 0
	}

}*/
bool HasConfig =0;
void GetWidth(int ch) {//宽1处设置所有值
	if (CharADD.Page[ch].use) {
		if (Charvec.empty()) { 
			HasConfig = 0;
			return; }
		int ID = Charvec.front();
		Charvec.erase(Charvec.begin());
		OffSet*PAGE = CharADD.Page[ch].Page;
		if (PAGE != 0) {
			//double OFF = PAGE[ch].Off;
			
			strX = CharADD.Page[ch].OffSetX + (ID % 16);//strX = 16 + (ID % 16);
			strY = CharADD.Page[ch].OffSetY + (ID / 16);//strY = ID / 16;
			Width = PAGE[ID].Width;
			OFFSetA = PAGE[ID].Off / 256.0f;
			HasConfig = 1;
			return;
		}
	}
	HasConfig = 0;
	return;

}
void DEFASM GetWidth980() {
	__asm{
	//	push ebx
		push ecx
		push eax
		call GetWidth
		pop eax
		pop ecx
	//	pop ebx
		cmp HasConfig,0
		jz NOCONFIG
		mulss xmm4, Width
		ret 0
		NOCONFIG:
	mulss xmm4, [esi + eax * 0X4 + 0X5C]
		ret 0
	}

}
void DEFASM GetWidth974() {
	__asm {
	//	push ebx
		push ecx
		push eax
		push edx
		call GetWidth
		pop edx
		pop eax
		pop ecx
	//	pop ebx
		cmp HasConfig, 0
		jz NOCONFIG
		mulss xmm4, Width
		ret 0
		NOCONFIG:
		mulss xmm4, [esi + edx * 0x4 + 0x5C]
			ret 0
	}

}
/*老函数
int GetCharXYAW(int ch) {
	if (CharADD.Page[ch].use) {
		if (Charvec.empty())return 0;
		int ID = Charvec.front();
		Charvec.erase(Charvec.begin());
		OffSet*PAGE = CharADD.Page[ch].Page;
		if (PAGE != 0) {
			//double OFF = PAGE[ch].Off;
			
			Width = PAGE[ID].Width;
			OFFSetA = PAGE[ID].Off / 256.0f;
			return 1;
		}
	}
	return 0;
}

*/
void* RE0, *RE1, *RE2;
void DEFASM GetCharXYOffAndWid() {//宽度 偏移 坐标 三合一

	__asm {
			cmp HasConfig, 0
			push edi
			jz NOCONFIG
			movss xmm5, Width
			mov edi,[RE1]
			mulss xmm5, [edi]//[SpaceEngine.exe + 0x3B48F4]{ [0.00] }
			pop edi
			push ecx
			movd xmm7,strX// eax//纵坐标
			movzx eax,strY// cl//横坐标

			
			mov ecx, RE2// SpaceEngine.exe + 0x472F90{ [000003E8] }
			
			cvtdq2ps xmm7, xmm7
			movd xmm6, eax
			cvtdq2ps xmm6, xmm6
			mulss xmm7, xmm0
			mulss xmm6, xmm0
			addss xmm7, OFFSetA
			
			jmp RE0
			NOCONFIG:
			movss xmm5, [esi + edx * 0x4 + 0x5C]
				mov edi, [RE1]
			mulss xmm5, [edi]//[SpaceEngine.exe + 0x3B48F4]{ [0.00] }
				pop edi
			push ecx
			movd xmm7, eax
			movzx eax, cl
			mov ecx, [RE2]// SpaceEngine.exe + 0x472F90{ [000003E8] }
			cvtdq2ps xmm7, xmm7
			movd xmm6, eax
			cvtdq2ps xmm6, xmm6
			mulss xmm7, xmm0
			mulss xmm6, xmm0
			addss xmm7, [esi + edx * 4 + 0x0000045C]
			jmp RE0////////////////

	}


}
void DEFASM GetCharXYOW974() {

	__asm{
		cmp HasConfig, 0
		push edi
		jz NOCONFIG
		movss xmm5, Width
		and al, 0x0F//{ 15 }
		mov edi, [RE1]
		mulss xmm5,[edi] //SpaceEngine.exe + 0x390DD4]//{ [0.00] }
			pop edi
		movzx eax, al
		movss xmm3, [esp + 0x14]
		shr cl, 0x04 //{ 4 }
		push ecx
		movd xmm7, strX
		movzx eax, strY

		mov ecx, RE2//SpaceEngine.exe + 0x44D350//{ [000003E8] }
		cvtdq2ps xmm7, xmm7
		movd xmm6, eax
		cvtdq2ps xmm6, xmm6
		mulss xmm7, xmm0
		mulss xmm6, xmm0
		addss xmm7, OFFSetA
		jmp RE0
		NOCONFIG:
		movss xmm5, [esi + edx * 0x4 + 0x5C]
		and al, 0x0F//{ 15 }
		mov edi,[RE1]
		mulss xmm5, [edi]//SpaceEngine.exe + 0x390DD4]//{ [0.00] }
			pop edi
		movzx eax, al
		movss xmm3, [esp + 0x14]
		shr cl, 0x04 //{ 4 }
		push ecx
		movd xmm7, eax
		movzx eax, cl
		mov ecx, RE2//SpaceEngine.exe + 0x44D350//{ [000003E8] }
		cvtdq2ps xmm7, xmm7
		movd xmm6, eax
		cvtdq2ps xmm6, xmm6
		mulss xmm7, xmm0
		mulss xmm6, xmm0
		addss xmm7, [esi + edx * 0x4 + 0x0000045C]
		jmp RE0
	}
}
/*
void DEFASM glTex2D() {
	__asm{
		cmp dword ptr [esp+0x10], 0x800
		jz HASONE
	CONE :
			jmp glTexAdd//glTexAdd
	HASONE:
		cmp  dword ptr [esp+0x14],0x400
			jz HASTOW
			jmp CONE
	HASTOW:
		mov ReTex,1
			jmp CONE
		//call dword ptr[SpaceEngine.exe + 36A2BC]{ ->OPENGL32.glTexImage2D }

	}

}*/
/*
void TInit() {
	CharADD.MainInit();
	DrawTexture();
	WCharAdd.Start();
	SAVE(0x800, 0x400);
}*/
void DEFASM TexInit() {
			
	__asm {
		mov ReTex, 1
		jmp TexEnd
	
	}
}
float Offset2 = 0;
int ostr = 0, swi = 0;//lpage = 0;
OffSet* LPage;
bool ohas = 0;//seted = 1;
void GetOffset() {

	/*if (CharADD.Page[ostr].use) {
		if (!BackWidth.empty()) {
		Offset2 = BackWidth.front();
		BackWidth.erase(BackWidth.begin());
		ohas = 1;
		//seted = 0;
		return;
		}
	}
	ohas = 0;
	return;*/
	switch (swi) {
	case 0:{
		if (CharADD.Page[ostr].use) {
			swi++;
			LPage = CharADD.Page[ostr].Page;
			ohas = 1;Offset2 = 0;
			return; 
		}
		ohas = 0;
		return;
		//CharADD.Page[1].Page[1].Off;
	}break;
	case 1:{
		swi--;
		Offset2 = LPage[ostr].Width;
		ohas = 1;
		return;
	}break;

	}
	/*if (CharADD.Page[ostr].use) { ohas = 1;return; }*/
	ohas = 0;
	return;

}
void DEFASM SetBackWid980() {//黄色背景宽度 位置SpaceEngine.exe+20705C  方式:call

	__asm {
		push eax
		push ecx
		mov ostr, edx
		call GetOffset
		cmp ohas,1
		pop ecx
		pop eax
		jz OHASC
		movss xmm0, [esi + edx * 0x4 + 0x5C]
		ret 0
		OHASC:
		movss xmm0, Offset2
			ret 0
	}

}

