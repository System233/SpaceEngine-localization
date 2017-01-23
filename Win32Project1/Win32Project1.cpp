// Win32Project1.cpp : 定义 DLL 应用程序的导出函数。
//
#include "stdafx.h"
#include <vector>
#include <stack>
#include "gl/gl.h"
#include "标头.h"
#pragma  comment(lib, "opengl32.lib")
CharAdd CharADD;
char *Pstr[8] = { "File","1","2","3","4","5","6","7" };
//std::vector<BYTE> Charvec;
//std::deque<BYTE> Bque;
std::deque<BYTE> Charvec;
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
#define GL_TEXTURE_BASE_LEVEL 0x813C  
SYSTEMTIME sys_time;
BYTE STR[8192];

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
//CALL==972
void DEFASM CharAna973() {
	__asm {
		push ebp
		mov ebp, esp
		and esp, -0x40// { 192 }

	}
}
void DEFASM CharAna972() {
	__asm {
		push ecx
		push[esp + 0xC]
		call CharAnalysis972
		mov[esp + 0x10], eax
		add esp, 0x4
		pop ecx
		pop eax
		push ebp
		mov ebp, esp
		and esp, -0x40// { 192 }
		jmp eax
	}

}

//CALL SpaceEngine.exe + 163180 9
void DEFASM CharAna971() {
	__asm {
		push ecx
		push [esp+0x18]
		call CharAnalysis971
		mov [esp + 0x1C],eax
		add esp,4
		pop ecx
		pop eax
		push ebp
		mov ebp, esp
		sub esp, 0x00000160 //{ 352 }
		jmp eax

	}
}
//CALL SpaceEngine.exe + 149E50 9
void DEFASM CharAna970() {
	__asm {
		push ecx
		push[esp + 0x18]
		call CharAnalysis971
		mov[esp + 0x1C], eax
		add esp, 4
		pop ecx
		pop eax
		push ebp
		mov ebp, esp
		sub esp, 0x00000184 //{ 352 }
		jmp eax

	}
}
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
	//IMAGE->fmt = color_type;
	w = png_get_image_width(png_ptr, info_ptr);
	h = png_get_image_height(png_ptr, info_ptr);
	IMAGE->B = png_get_bit_depth(png_ptr, info_ptr);
	int channels = png_get_channels(png_ptr, info_ptr);
	IMAGE->W = w;
	IMAGE->H = h;
	BYTE *IMG=IMAGE->DATA = new BYTE[w*h *channels];
	if (IMG == NULL)return -4;
	row_pointers = png_get_rows(png_ptr, info_ptr);

	int Xsize = 0;
	switch (color_type) {
	case PNG_COLOR_TYPE_RGB_ALPHA:
		IMAGE->fmt = GL_RGBA;
		for (y = 0; y<h; ++y) {
			for (x = 0; x<w * channels; ) {
				IMG[Xsize++] = row_pointers[y][x++]; // red  
				IMG[Xsize++] = row_pointers[y][x++]; // green  
				IMG[Xsize++] = row_pointers[y][x++]; // blue  
				IMG[Xsize++] = row_pointers[y][x++]; // alpha  
			}
		}
		break;

	case PNG_COLOR_TYPE_RGB:
		IMAGE->fmt = GL_RGB;
		for (y = 0; y<h; ++y) {
			for (x = 0; x<w * channels; ) {
				IMG[Xsize++] = row_pointers[y][x++]; // red  
				IMG[Xsize++] = row_pointers[y][x++]; // green  
				IMG[Xsize++] = row_pointers[y][x++]; // blue  
			//	IMG[Xsize++] = 255;
			}
		}
	
		break;
	case 0:
		IMAGE->fmt = GL_ALPHA;
		for (y = 0; y<h; ++y) {
			for (x = 0; x<w * channels; ) {
				IMG[Xsize++] = row_pointers[y][x++]; // red  
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
int TIMES = 0;bool TMSO = true;
bool ReTex = false;

BYTE* CharAnalysis(BYTE* str) {

	if (ReTex) {
		if (TMSO) {
			TMSO = false;
			TIMES = *start;
		}
		if ((*start - TIMES) > 1) {
			CharADD.MainInit();
			DrawTexture();
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

}

float Old1 = 0.0f,Old2=0.0f;
BYTE* CharAnalysis972(BYTE* str) {

	if (ReTex) {
		if (TMSO) {
			TMSO = false;
			TIMES = *start;
		}
		if ((*start - TIMES) > 1) {
			CharADD.MainInit();
			GLint Level = 0, Hight = 0, Width = 0;
 
			glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, &Level);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, Level, GL_TEXTURE_WIDTH, &Width);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, Level, GL_TEXTURE_HEIGHT, &Hight);
			if (Hight == Width&&Hight % 256 == 0&& Width>256) {
				int Z = 0,F= Width / 256;
				for (int Y = 0;Y < F;Y++)
				for (int X = 0;X < F;X++)
				 {
						if (X == 0 && Y == 0) {
							continue;
						}
						else if(Z<8){
							while ((WID[Z]) == 0)Z++;

						//	msgmgr(3, "ID:%X X:%d Y:%d F:%d W:%d", WID[Z], X, Y, F, Width);
							CharADD.Page[WID[Z]].OffSetX = X * 16, CharADD.Page[WID[Z++]].OffSetY = Y * 16;
							
						}
					}
				//0.03125f 0.0020f
				float A = Old1/ F, A2 = Old2/ F;
				
				WriteAdd(FloatAdd[0], (BYTE*)&A, sizeof(A));
				WriteAdd(FloatAdd[1], (BYTE*)&A2, sizeof(A2));
			//	WriteAdd(0x39B180, (BYTE*)&A, sizeof(A));
			//	WriteAdd(0x39B098, (BYTE*)&A2, sizeof(A2));
			}
			else {
			//	float A = 0.03125f, A2 = 0.0020f;
			//	WriteAdd(0x39B180, (BYTE*)&Old1, sizeof(Old1));
			//	WriteAdd(0x39B098, (BYTE*)&Old2, sizeof(Old2));
				WriteAdd(FloatAdd[0], (BYTE*)&Old1, sizeof(Old1));
				WriteAdd(FloatAdd[1], (BYTE*)&Old2, sizeof(Old2));
			//	msgmgr(3, "IO1:%f o2:%f", Old1,Old2);
			}

			
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

}

double DOld1 = 0, DOld2 = 0;float DOld3 = 0;
BYTE* CharAnalysis971(BYTE* str) {
	if (str) {
	if (ReTex) {
		if (TMSO) {
			TMSO = false;
			TIMES = *start;
		}
		if ((*start - TIMES) > 1) {
			CharADD.MainInit();
			GLint Level = 0, Hight = 0, Width = 0;

			glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, &Level);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, Level, GL_TEXTURE_WIDTH, &Width);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, Level, GL_TEXTURE_HEIGHT, &Hight);
			if (Hight == Width&&Hight % 256 == 0 && Width>256) {
				int Z = 0, F = Width / 256;
				for (int Y = 0;Y < F;Y++)
					for (int X = 0;X < F;X++)
					{
						if (X == 0 && Y == 0) {
							continue;
						}
						else if (Z<8) {
							while ((WID[Z]) == 0)Z++;

							//	msgmgr(3, "ID:%X X:%d Y:%d F:%d W:%d", WID[Z], X, Y, F, Width);
							CharADD.Page[WID[Z]].OffSetX = X * 16, CharADD.Page[WID[Z++]].OffSetY = Y * 16;

						}
					}
				//0.03125f 0.0020fSpaceEngine.exe+2B80B0
				double A = DOld1 * F, A2 = double(Width);
				float A3 = DOld3 / F;
				/*WriteAdd(0x2B80B0, (BYTE*)&A, sizeof(A));
				WriteAdd(0x2B82E0, (BYTE*)&A2, sizeof(A2));
				WriteAdd(0x2B82F0,(BYTE*)&A3, sizeof(A3));*/
				WriteAdd(DoubleAdd[0], (BYTE*)&A, sizeof(A));
				WriteAdd(DoubleAdd[1], (BYTE*)&A2, sizeof(A2));
				WriteAdd(DoubleAdd[2], (BYTE*)&A3, sizeof(A3));
			}
			else {
				//	float A = 0.03125f, A2 = 0.0020f;
			/*	WriteAdd(0x2B80B0, (BYTE*)&DOld1, sizeof(DOld1));
				WriteAdd(0x2B82E0, (BYTE*)&DOld2, sizeof(DOld2));
				WriteAdd(0x2B82F0, (BYTE*)&DOld3, sizeof(DOld3))*/
				WriteAdd(DoubleAdd[0], (BYTE*)&DOld1, sizeof(DOld1));
				WriteAdd(DoubleAdd[1], (BYTE*)&DOld2, sizeof(DOld2));
				WriteAdd(DoubleAdd[2], (BYTE*)&DOld3, sizeof(DOld3));
				//	msgmgr(3, "IO1:%f o2:%f", Old1,Old2);
			}


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
	}else return str;
}
void DrawTexture() {
	for (int i = 0;i < 256;i++) {
		if (CharADD.Page[i].use) {
			BYTE PID = CharADD.Page[i].PID;
			int x = CharADD.Page[PID].PX;
			int y = CharADD.Page[PID].PY;
			PNGDATA IMAGE;
			std::string Path = SYSTEMPATH + "/" + localePath + "/" + CharADD.Page[PID].File;
			int ERR = LoadPNG(Path.c_str(), &IMAGE);
			msgmgr(2, "加载纹理[%d]:%d*%d*%d X:%d Y:%d FMT:%d Path:%s", ERR, IMAGE.W, IMAGE.H, IMAGE.B, x, y, IMAGE.fmt,Path.c_str());
			if (ERR != 0 || IMAGE.W != IMAGE.H || IMAGE.W != 256) {
				CharADD.Page[PID].use = false;
				msgmgr(2, "纹理加载失败[%d]:%d*%d*%d X:%d Y:%d Path:%s", ERR, IMAGE.W, IMAGE.H, IMAGE.B, x, y, Path.c_str());
				//continue;
			}else{
			glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, IMAGE.W, IMAGE.H, IMAGE.fmt, GL_UNSIGNED_BYTE, IMAGE.DATA);
			}
			if (IMAGE.DATA) delete[] IMAGE.DATA; 
		}

	}
	/*for (int i = 0;i<7;i++) {
		
		BYTE PID = CharADD.PageId[i];
		if (!CharADD.Page[PID].use)continue;
		int x = CharADD.Page[PID].PX;
		int y = CharADD.Page[PID].PY;
		PNGDATA IMAGE;
		
		const char *File = CharADD.Page[PID].File.c_str();
		
	
		std::string Path = SYSTEMPATH + "/" + localePath + "/"+File;
		int ERR = LoadPNG(Path.c_str(), &IMAGE);

		if (ERR != 0 || IMAGE.W != IMAGE.H || IMAGE.W != 256) {
			CharADD.Page[PID].use = false;	
			msgmgr(2, "纹理加载失败[%d]:%d*%d*%d X:%d Y:%d Path:%s", ERR, IMAGE.W, IMAGE.H, IMAGE.B, x,y, Path.c_str());
			//continue;
		}
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, IMAGE.W, IMAGE.H, GL_RGBA, GL_UNSIGNED_BYTE, IMAGE.DATA);
		delete[] IMAGE.DATA;
	}
	*/
}

float OneByte = 0.004f;
float OFFSetA=0.0f,Width=0.0f;

bool HasConfig =0;
void GetWidth(int ch) {//宽1处设置所有值
	if (CharADD.Page[ch].use&& !Charvec.empty()) {
			BYTE ID = Charvec.front();
			Charvec.pop_front();
			//	Charvec.erase(Charvec.begin());
			OffSet*PAGE = CharADD.Page[ch].Page;

			if (PAGE != 0) {
				//double OFF = PAGE[ch].Off;
				strX = CharADD.Page[ch].OffSetX + (ID % 16);//strX = 16 + (ID % 16);
				strY = CharADD.Page[ch].OffSetY + (ID / 16);//strY = ID / 16;
				Width = PAGE[ID].Width;
				OFFSetA = PAGE[ID].Off;
				HasConfig = 1;
				return;
			}
		
	}
	HasConfig = 0;
	return;

}
//JMP SpaceEngine.exe+201B6B RE SpaceEngine.exe+201BC9 9B
void DEFASM SetAll973() {
	__asm {
		push edx
		call GetWidth
		pop edx
		cmp HasConfig, 0
		jz NOCONFIG
		movss xmm1, Width//[esi + edx * 0x4 + 0x000000CC]
		//mov al, cl
		movss xmm0, [esi + 0x0C]
		//and al, 0x0F//{ 15 }
		mulss xmm0, xmm1
		movzx eax, strX//al
		push edx
		mov edx, [RE0]
		mulss xmm1, [edx]// [SpaceEngine.exe + 0x3B6CB0]//{ [0.00] }
		//shr cl, 0x04// { 4 }
		//mov ecx,strY
		cmp byte ptr[esi + 0x14], 00 //{ 0 }
		movss[esp + 0x40+4], xmm0
		movss xmm0, [esi + 0x10]
		mov edx, [RE1]
		mulss xmm0, [edx]//[SpaceEngine.exe + 0x3B7C68]//{ [16.00] }
		pop edx
		movss[esp + 0x3C], xmm1
		movss[esp + 0x38], xmm0
		movd xmm0, eax
		cvtdq2ps xmm0, xmm0
		//movzx eax, cl
		mov eax, strY
		mulss xmm0, xmm2
		addss xmm0, OFFSetA//[esi + edx * 0x4 + 0x000004CC]
		jmp RE2
		NOCONFIG:
		movss xmm1, [esi + edx * 0x4 + 0x000000CC]
		mov al, cl
		movss xmm0, [esi + 0x0C]
		and al, 0x0F//{ 15 }
		mulss xmm0, xmm1
		movzx eax, al
		push edx
		mov edx,[RE0]
		mulss xmm1,[edx]// [SpaceEngine.exe + 0x3B6CB0]//{ [0.00] }
		shr cl, 0x04// { 4 }
		cmp byte ptr[esi + 0x14], 00 //{ 0 }
		movss[esp + 0x40+4], xmm0
		movss xmm0, [esi + 0x10]
		mov edx,[RE1]
		mulss xmm0, [edx]//[SpaceEngine.exe + 0x3B7C68]//{ [16.00] }
		pop edx
		movss[esp + 0x3C], xmm1
		movss[esp + 0x38], xmm0
		movd xmm0, eax
		cvtdq2ps xmm0, xmm0
		movzx eax, cl
		mulss xmm0, xmm2
		addss xmm0, [esi + edx * 0x4 + 0x000004CC]
		jmp RE2
	}

}
//SpaceEngine.exe+1633BD call 7
void DEFASM SetAll971() {
	__asm {
		push ecx
		call GetWidth
		cmp HasConfig, 0
		pop ecx
		jz NOCONFIG
		fmul dword ptr [Width]//[eax + ecx * 4 + 0x68]
		fstp dword ptr[ebp - 0x2C]
		mov ecx, [ebp - 0x64]
		fld dword ptr[ecx + 0x4C]
		fmul qword ptr [sewid971]//[SpaceEngine.exe + 0x2B80B0]//{ [32.00] }//要求16
		fstp dword ptr[ebp - 0x30]
		movzx edx, byte ptr[ebp - 0x35]
		//mov eax, [ebp - 0x64]
		fld dword ptr [Width]//[eax + edx * 0x4 + 0x68]
		mov ecx,[RE1]
		fdiv qword ptr [ecx]//[SpaceEngine.exe + 0x2B82E0]//{ [512.00] }
		fstp dword ptr[ebp - 0x34]
		movzx ecx, byte ptr[ebp - 0x35]
		mov ecx, strX//and ecx, 0x0F//{ 15 }
		mov[ebp - 0x00000084], ecx
		fild dword ptr[ebp - 0x00000084]
		mov edx,[RE0]
		fdiv qword ptr [edx]//[SpaceEngine.exe + 0x2B80B0]//{ [32.00] }
		movzx edx, byte ptr[ebp - 0x35]
		//mov eax, [ebp - 0x64]
		fadd dword ptr [OFFSetA]//[eax + edx * 0x4 + 0x00000468]
		fstp dword ptr[ebp - 0x3C]
		movzx ecx, byte ptr[ebp - 0x35]
		mov ecx,strY//sar ecx, 0x04// { 4 }
		jmp RE2
		NOCONFIG:
		fmul dword ptr[eax + ecx * 4 + 0x68]
		fstp dword ptr[ebp - 0x2C]
		mov ecx, [ebp - 0x64]
		fld dword ptr[ecx + 0x4C]
		fmul qword ptr [sewid971]//[SpaceEngine.exe + 0x2B80B0]//{ [32.00] }
		fstp dword ptr[ebp - 0x30]
		movzx edx, byte ptr[ebp - 0x35]
		mov eax, [ebp - 0x64]
		fld dword ptr[eax + edx * 0x4 + 0x68]
		mov ecx,[RE1]
		fdiv qword ptr [ecx]//[SpaceEngine.exe + 0x2B82E0]//{ [512.00] }
		fstp dword ptr[ebp - 0x34 ]
		movzx ecx, byte ptr[ebp - 0x35 ]
		and ecx, 0x0F//{ 15 }
		mov[ebp - 0x00000084 ], ecx
		fild dword ptr[ebp - 0x00000084 ]
		mov eax,[RE0]
		fdiv qword ptr [eax]//[SpaceEngine.exe + 0x2B80B0]//{ [32.00] }
		movzx edx, byte ptr[ebp - 0x35 ]
		mov eax, [ebp - 0x64 ]
		fadd dword ptr[eax + edx * 0x4 + 0x00000468]
		fstp dword ptr[ebp - 0x3C ]
		movzx ecx, byte ptr[ebp - 0x35 ]
		sar ecx, 0x04// { 4 }
		//pop eax
		jmp RE2
		
	}

}
//JMP SpaceEngine.exe+14A144   RE SpaceEngine.exe+14A195 7
void DEFASM SetAll970() {
	__asm {
		push ecx
		call GetWidth
		pop ecx
		
		cmp HasConfig, 0
		jz NOCONFIG
		

		fmul dword ptr[Width]//[eax + ecx * 4 + 0x68]
		fstp dword ptr[ebp - 0x2C]
		mov ecx, [ebp - 0x68]
		fld dword ptr[ecx + 0x4C]
		fmul qword ptr[sewid971]//[SpaceEngine.exe + 0x272518]//{ [15.00] }
		fstp dword ptr[ebp - 0x34]
		movzx edx, byte ptr[ebp - 0x39]


		mov eax, [ebp - 0x68]
		fld dword ptr[Width]
		mov eax, [RE0]
		fdiv qword ptr[eax]//[SpaceEngine.exe + 0x272660]//{ [512.00] }
		fstp dword ptr[ebp - 0x38]
		movzx ecx, byte ptr[ebp - 0x39]
	//	and ecx, 0x0F//{ 15 }
		mov ecx,strX 
		mov[ebp - 0x000000A8], ecx
		fild dword ptr[ebp - 0x000000A8]
		mov eax, [RE1]
		fdiv qword ptr[eax]//[SpaceEngine.exe + 0x272440]//{ [32.00] }
		movzx edx, byte ptr[ebp - 0x39]
		mov eax, [ebp - 0x68]
		fadd dword ptr[eax + edx * 0x4 + 0x00000468]
		fstp dword ptr[ebp - 0x40]
		movzx ecx, byte ptr[ebp - 0x39]
		//sar ecx, 0x04 //{ 4 }
		mov ecx,strY
		jmp RE2

		NOCONFIG:

		fmul dword ptr[eax + ecx * 4 + 0x68]
		fstp dword ptr[ebp - 0x2C]
		mov ecx, [ebp - 0x68]
		fld dword ptr[ecx + 0x4C]
		fmul qword ptr[sewid971]//[SpaceEngine.exe + 0x272518]//{ [15.00] }
		fstp dword ptr[ebp - 0x34]
		movzx edx, byte ptr[ebp - 0x39]

		mov eax, [ebp - 0x68]
		fld dword ptr[eax + edx * 0x4 + 0x68]
		mov eax,[RE0]
		fdiv qword ptr [eax]//[SpaceEngine.exe + 0x272660]//{ [512.00] }
		fstp dword ptr[ebp - 0x38]
		movzx ecx, byte ptr[ebp - 0x39]
		and ecx, 0x0F//{ 15 }
		mov[ebp - 0x000000A8], ecx
		fild dword ptr[ebp - 0x000000A8]
		mov eax,[RE1]
		fdiv qword ptr [eax]//[SpaceEngine.exe + 0x272440]//{ [32.00] }
		movzx edx, byte ptr[ebp - 0x39]
		mov eax, [ebp - 0x68]
		fadd dword ptr[eax + edx * 0x4 + 0x00000468]
		fstp dword ptr[ebp - 0x40]
		movzx ecx, byte ptr[ebp - 0x39]
		sar ecx, 0x04 //{ 4 }
		jmp RE2

	}

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
void DEFASM GetWidthXYOFF972() {
	__asm {
		push ecx
		push eax
		push edx
		call GetWidth
		pop edx
		pop eax
		pop ecx
		cmp HasConfig, 0
		jz NOCONFIG
		movss xmm1, Width
		movss xmm0, [esi + 0x0C]
		mulss xmm0, xmm1
		mov eax, strX
		push edx
		mov edx, [RE0]
		mulss xmm1, [edx]//[SpaceEngine.exe + 39B098]{ [0.00] }

		shr cl, 0x04// { 4 }
		cmp byte ptr[esi + 0x14], 00// { 0 }
		movss[esp + 0x44], xmm0//<<<
		movss xmm0, [esi + 0x10]

		mov edx, [RE1]
		mulss xmm0, [edx]//[SpaceEngine.exe + 39BF40]{ [16.00] }
		pop edx
		movss[esp + 0x3C], xmm1
		movss[esp + 0x38], xmm0
		movd xmm0, eax
		cvtdq2ps xmm0, xmm0

		movzx eax, strY
		mulss xmm0, xmm2
		addss xmm0, OFFSetA
		jmp RE2//SpaceEngine.exe+1F0CB9 - F3 0F11 44 24 2C      - movss [esp+2C],xmm0



		NOCONFIG :
		movss xmm1, [esi + edx * 0x4 + 0x000000CC]
			mov al, cl
			movss xmm0, [esi + 0x0C]
			and al, 0x0F//{ 15 }
			mulss xmm0, xmm1
			movzx eax, al
			push edx
			mov  edx, [RE0]
			mulss xmm1, [edx]//[SpaceEngine.exe + 39B098]{ [0.00] }

			shr cl, 0x04// { 4 }
			cmp byte ptr[esi + 0x14], 00// { 0 }
			movss[esp + 0x44], xmm0//<<<<<
			movss xmm0, [esi + 0x10]
			mov  edx, [RE1]
			//mov esp, [esp]
			mulss xmm0, [edx]//[SpaceEngine.exe + 39BF40]{ [16.00] }
			pop  edx
			movss[esp + 0x3C], xmm1
			movss[esp + 0x38], xmm0
			movd xmm0, eax
			cvtdq2ps xmm0, xmm0
			movzx eax, cl
			mulss xmm0, xmm2
			addss xmm0, [esi + edx * 4 + 0x000004CC]
			jmp RE2//SpaceEngine.exe+1F0CB9 - F3 0F11 44 24 2C      - movss [esp+2C],xmm0


	}

}

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
void DEFASM TexInit() {
			
	__asm {
		mov ReTex, 1
		jmp TexEnd
	
	}
}
float Offset2 = 0;
int ostr = 0, swi = 0;//lpage = 0;
OffSet* LPage;
bool ohas = 0, OH2 = false;;//seted = 1;
void GetOffset() {
	if(!OH2){
		if (CharADD.Page[ostr].use) {
			LPage = CharADD.Page[ostr].Page;
			ohas = 1;Offset2 = 0;
			OH2 = true;
			return;
		}
	}else {
		Offset2 = LPage[ostr].Width;
		ohas = 1;
		OH2 = false;
		return;
	}
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



void DEFASM SetBack972() {
	__asm {
		push eax
		push ecx
		mov ostr, ecx
		call GetOffset
		cmp ohas, 1
		pop ecx
		pop eax
		jz OHASC
		movss xmm0, [esi + ecx * 0x4 + 0x000000CC]
		ret 0
		OHASC:
		movss xmm0, Offset2
			ret 0

	}

}
//CALL SpaceEngine.exe + 164BCB 7
void DEFASM SetBack971() {
	__asm {
		push eax
		//psuh ecx
		mov ostr, ecx
		call GetOffset
		//pop ecx
		pop eax
		cmp ohas, 1
		jz OHASC
		fmul dword ptr[eax + ecx * 4 + 0x68]
		fstp dword ptr[ebp - 0x14]
		pop ecx
		jmp ecx
		OHASC:
		fmul dword ptr[Offset2]
		fstp dword ptr[ebp - 0x14]
		pop ecx
		jmp ecx
	}
}
//CALL SpaceEngine.exe+14AB8E 7b
void DEFASM SetBack970() {
	__asm {
		push ecx
		mov ostr, edx
		call GetOffset
		pop ecx
		pop eax
		cmp ohas, 1
		jz OHASC
		fmul dword ptr[ecx + edx * 0x4 + 0x68]
		fstp dword ptr[ebp - 0x14]
		jmp eax
		OHASC:
		fmul dword ptr[Offset2]
		fstp dword ptr[ebp - 0x14]
		jmp eax
	}

}