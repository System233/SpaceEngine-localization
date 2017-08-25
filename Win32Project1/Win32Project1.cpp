// Win32Project1.cpp : 定义 DLL 应用程序的导出函数。
//
#include "stdafx.h"
#include <vector>
#include <stack>
#include "Define.h"
#pragma  comment(lib, "opengl32.lib")
Localization StrMap;
std::vector<BYTE> StrTemp;
//std::deque<BYTE> Bque;
std::deque<BYTE> StrVec;
float *WidAdd = NULL,*TABWid=NULL,*UWid=NULL;//输入部分:不需要
int strX = 0, strY = 0;
HANDLE mProc =0;

//偏移 写入代码 大小
BOOL WriteAdd(LPVOID lpAddress, const uint8_t *Code, size_t Size)
{
	DWORD dwTemp = 0, dwOldProtect = 0;
	if (Code == 0 || lpAddress == 0 || Size == 0|| IsBadReadPtr(lpAddress,Size))return FALSE;
	VirtualProtectEx(mProc, lpAddress, Size, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	if (!WriteProcessMemory(mProc, lpAddress, Code, Size, 0))return FALSE;
	VirtualProtectEx(mProc, lpAddress, Size, dwOldProtect, &dwTemp);
	return TRUE;
}
BOOL WriteAdd(DWORD Offset, const uint8_t *Code, size_t Size)
{
	return WriteAdd((LPVOID)(Base + Offset), Code, Size);
}
BOOL ReadAdd(DWORD Offset, uint8_t *Code, size_t Size) {
	return ReadAdd((LPVOID)(Base + Offset), Code, Size);
}
BOOL ReadAdd(LPVOID lpAddress, uint8_t *Code, size_t Size) {
	DWORD dwTemp = 0, dwOldProtect = 0;
	if (Code == 0 || lpAddress == 0 || Size == 0||IsBadReadPtr(lpAddress, Size))return FALSE;
	VirtualProtectEx(mProc, lpAddress, Size, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	if (!ReadProcessMemory(mProc, lpAddress, Code, Size, 0))return FALSE;
	VirtualProtectEx(mProc, lpAddress, Size, dwOldProtect, &dwTemp);
	return TRUE;
}
#define GL_TEXTURE_BASE_LEVEL 0x813C  
SYSTEMTIME sys_time;
void save_texture() {
	GLint Width, Height, Level;
	
	glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, &Level);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, Level, GL_TEXTURE_WIDTH, &Width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, Level, GL_TEXTURE_HEIGHT, &Height);
	uint8_t *data = new uint8_t[Height*Width * 4];
	glGetTexImage(GL_TEXTURE_2D, Level, GL_RGBA, GL_UNSIGNED_BYTE, data);
	GetLocalTime(&sys_time);
	WCHAR path[MAX_PATH];
	swprintf(path, MAX_PATH, L"%04d-%02d-%02d %02d-%02d-%02d-%03d.png", sys_time.wYear, sys_time.wMonth, sys_time.wDay, sys_time.wHour, sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds);
	PNG::write_png(path,data,Width,Height);
	delete[]data;
	msgmgr(MsgType::Debug, L"writing %s", path);
}
void DEFASM CharAna() {//字符串解析
	__asm {
		push ecx
		push[esp + 0xC+4*0]
		call StringHook
		mov[esp + 0x10+4*0], eax
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
		call StringHook972
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
		call StringHook971
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
		call StringHook971
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
void DrawTexture() {
	for (int i = 1; i < 256; i++) {
		if (StrMap.Page[i].use) {
			BYTE PID = StrMap.Page[i].PID;
			std::wstring Path = SYSTEMROOT + localePath + L'/' + StrMap.Page[PID].File;
			PNG img(Path);
			long x = StrMap.Page[PID].OffsetX * 16, y = StrMap.Page[PID].OffsetY * 16 + 512, w = img.getWidth(), h = img.getHeight(), b = img.getBit();
			if (!img || h != w || w != 256)
				StrMap.Page[PID].use = false, msgmgr(MsgType::Error, Localization::sTexErr, (img ? Localization::sFmtErr : Localization::sLoadErr).c_str(), img.getError(), PID, w, h, b, x, y, Path.c_str());
			else
				glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, img.getFormat(), GL_UNSIGNED_BYTE, img.getData());
			//	for (GLenum err;(err = glGetError()) != GL_NO_ERROR;)msgmgr(1,"GLERR ",gluErrorString(err));
			// msgmgr(3, "加载[%d]:%d*%d*%d X:%d Y:%d Path:%s", img.getError(), w, h, b, x, y, Path.c_str());
		}
	}
}
size_t last(0);
bool ReTex(false),Init(true), isOk(false);;
BYTE* StringHook(BYTE* str) {

	if(str){
	if (ReTex) {
		if (Init){
			if (!StrMap.MainInit())ReTex = false;
			else last = *start, Init = false;
		}
		else if ((*start - last)>1) {
			DrawTexture();
			//save_texture();
			Init = true;
			ReTex = false;
		}
	}
	StrVec.clear();
	StrTemp.clear();
	size_t i = 0;
	for (; str[i] != 0; i++) {
		StrTemp.push_back(str[i]);
		if (StrMap.Page[str[i]].use) { 
			const BYTE T = str[++i];
			StrVec.push_back(T); 
			if (T==0) break;
		}
		
	}
	StrTemp.push_back(0);
	return StrTemp.data();
	}
	return str;
}

float Old1 = 0.0f,Old2=0.0f;
BYTE* StringHook972(BYTE* str) {
	if(str){
	if (ReTex) {
		if (Init) {
			isOk = StrMap.MainInit();
			last = *start;
			Init = false;
		}
		else if ((*start - last) > 1) {
			GLint Level = 0, Height = 0, Width = 0;
			glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, &Level);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, Level, GL_TEXTURE_WIDTH, &Width);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, Level, GL_TEXTURE_HEIGHT, &Height);
			if (isOk&&Height == Width&&Height % 256 == 0&& Width>256) {
				int F= Width / 256;
				auto it = StrMap.PageList.begin(), end = StrMap.PageList.end();
				for (int Y = 0;Y < F;Y++)
				for (int X = 0;X < F&&it!=end;X++, it++)
				 {
						StrMap.Page[*it].OffsetX = X * 16;
						StrMap.Page[*it].OffsetY = Y * 16;
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
			}

			Init = true;
			ReTex = false;
		}
	}



	StrVec.clear();
	StrTemp.clear();
	for (int i = 0; str[i] != 0; i++) {
		BYTE T = str[i];
		StrTemp.push_back(T);
		if (StrMap.Page[T].use) {
			StrVec.push_back(T = str[++i]);
			if (T == 0) break;
		};
		
	}
	StrTemp.push_back(0);
	return StrTemp.data();
	}
	return str;
}

double DOld1 = 0, DOld2 = 0;float DOld3 = 0;
BYTE* StringHook971(BYTE* str) {
	if (str) {
	if (ReTex) {
		
		if (Init) {
			isOk = StrMap.MainInit();
			last = *start;
			Init = false;
		}
		else if (*start - last > 1) {
			GLint Level = 0, Height = 0, Width = 0;
			glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, &Level);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, Level, GL_TEXTURE_WIDTH, &Width);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, Level, GL_TEXTURE_HEIGHT, &Height);
			if (isOk&&Height == Width&&Height % 256 == 0 && Width>256) {
				int F = Width / 256;
				auto it = StrMap.PageList.begin(), end = StrMap.PageList.end();
				for (int Y = 0;Y < F;Y++)
					for (int X = 0;X < F&&it != end; X++, it++)
					{
						StrMap.Page[*it].OffsetX = X * 16;
						StrMap.Page[*it].OffsetY = Y * 16;
						/*if (Y == 0&&X == 0) continue;
								(*it)->OffsetX = X * 16, (*it)->OffsetY = Y * 16;
								it++;*/
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
			}

			Init = true;
			ReTex = false;
		}
	}


	StrVec.clear();
	StrTemp.clear();
	
	for (int i = 0; str[i] != 0;i++) {
		BYTE T = str[i];
		StrTemp.push_back(T);
		if (StrMap.Page[T].use) {
			T = str[++i];
			StrVec.push_back(T);
			if (T == 0) break;
		}
	}
	StrTemp.push_back(0);
	return StrTemp.data();
	}else return str;
}


float OneByte = 0.004f;
float OffsetA=0.0f,Width=0.0f;

bool HasConfig =0;
void GetWidth(BYTE ch) {//宽1处设置所有值
	if (!StrVec.empty()&&StrMap.Page[ch].use) {
			BYTE ID = StrVec.front();
			StrVec.pop_front();
			//	StrVec.erase(StrVec.begin());
			Offset*PAGE = StrMap.Page[ch].getInfo();

			if (PAGE != nullptr) {
				//double OFF = PAGE[ch].Off;
				strX = StrMap.Page[ch].OffsetX + (ID % 16);//strX = 16 + (ID % 16);
				strY = StrMap.Page[ch].OffsetY + (ID / 16);//strY = ID / 16;
				Width = PAGE[ID].Width;
				OffsetA = PAGE[ID].Off;
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
		push ecx
		push eax
		push edx
		call GetWidth
		pop edx
		pop eax
		pop ecx
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
		addss xmm0, OffsetA//[esi + edx * 0x4 + 0x000004CC]
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
		push eax
		push edx
		push ecx
		call GetWidth
		cmp HasConfig, 0
		pop ecx
		pop edx
		pop eax
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
		fadd dword ptr [OffsetA]//[eax + edx * 0x4 + 0x00000468]
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
		push eax
		push edx
		push ecx
		call GetWidth
		pop ecx
		pop edx
		pop eax
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
		push edx
		push ecx
		push eax
		call GetWidth
		cmp HasConfig, 0
		pop eax
		pop ecx
		pop edx
		
		jz NOCONFIG
		mulss xmm4, Width
		ret 0
		NOCONFIG:
	mulss xmm4, [esi + eax * 0x4 + 0x5C]
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
		addss xmm0, OffsetA
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
			addss xmm7, OffsetA
			
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
void DEFASM GetXYOW974RC3() {
	/*movss xmm5,[esi+edx*4+5C]
mulss xmm5,[SpaceEngine.exe+3B2B34] { [0.00] }
push ecx
movd xmm7,eax
movzx eax,cl
mov ecx,SpaceEngine.exe+471300 { [000004B0] }
cvtdq2ps xmm7,xmm7
movd xmm6,eax
cvtdq2ps xmm6,xmm6
mulss xmm7,xmm0
mulss xmm6,xmm0
addss xmm7,[esi+edx*4+0000045C]
*/
	__asm {
		cmp HasConfig, 0
		push edi
		jz NOCONFIG
		movss xmm5, Width//[esi + edx * 0x4 + 0x5C]
		mov edi, [RE1]
		mulss xmm5, [edi]// [SpaceEngine.exe + 0x3B2B34]{ [0.00] }
		pop edi

		push ecx
		mov eax, strX
		movd xmm7, eax
		movzx eax, strY
		mov ecx, [RE2]//SpaceEngine.exe + 0x471300 { [000004B0] }
		cvtdq2ps xmm7, xmm7
		movd xmm6, eax
		cvtdq2ps xmm6, xmm6
		mulss xmm7, xmm0
		mulss xmm6, xmm0
		addss xmm7, OffsetA//[esi + edx * 0x4 + 0x0000045C]
		jmp[RE0]
		NOCONFIG:
		movss xmm5, [esi + edx * 0x4 + 0x5C]
		mov edi,[RE1]
		mulss xmm5,[edi]// [SpaceEngine.exe + 0x3B2B34]{ [0.00] }
		pop edi

		push ecx
		movd xmm7, eax
		movzx eax, cl
		mov ecx, [RE2]//SpaceEngine.exe + 0x471300 { [000004B0] }
		cvtdq2ps xmm7, xmm7
		movd xmm6, eax
		cvtdq2ps xmm6, xmm6
		mulss xmm7, xmm0
		mulss xmm6, xmm0
		addss xmm7, [esi + edx * 0x4 + 0x0000045C]
		jmp [RE0]
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
		addss xmm7, OffsetA
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
//int ostr = 0, swi = 0;//lpage = 0;

Offset* LPage;
bool ohas = 0, OH2 = false;;//seted = 1;
void GetOffset(BYTE ostr) {
	if(!OH2){
		if (StrMap.Page[ostr].use) {
			LPage = StrMap.Page[ostr].getInfo();
			ohas = 1;Offset2 = 0;
			OH2 = true;
			return;
		}
	}else {
	//	if(LPage)
	//	msgmgr(1, "LPage:%p", LPage);
		Offset2 = LPage?LPage[ostr].Width:10.0f;
		
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
//		mov ostr, edx
		push edx
		call GetOffset
		pop edx
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
		push edx
		push eax
		push ecx
		//mov ostr, ecx

		call GetOffset
		cmp ohas, 1
		pop ecx
		pop eax
		pop edx
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
		//mov ostr, ecx
		push ecx
		call GetOffset
		pop ecx
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
		//mov ostr, edx
		push edx
		call GetOffset
		pop edx
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




size_t Input(size_t UTF16,BYTE *str,size_t sp) {
	BYTE*P=StrMap.GetCharCode(UTF16);
	if (P!=0) {
		if (P[0] != 0) { 
			str[sp] = P[0];
			size_t size = 0;
			while (str[sp + size] != 0)size++;
			while (size)str[sp + size + 1] = str[sp + size], size--;
			str[sp + 1] = P[1];
			return 2; }
		else { str[sp] = P[1]; 
			return 1;
			}
		
	}
	return 0;
}
void DEFASM Input980() {
	__asm {
		
		mov ecx, [ebp + 0x10]
		push eax
		push edx
		push ecx
		call Input
		cmp eax, 1
		pop ecx
		pop edx
		
		jz RET0
		jg cpyw
		pop eax
		mov[eax + edx], cl
		ret 0
		cpyw:
		mov eax, [esp+0x40]
		inc dword ptr[eax+0X134]
		inc dword ptr[ebp+0X28]
		RET0:
		pop eax
		ret 0
	}
}
VOID DEFASM InputFlag980() {
	__asm {

	}
}
DWORD MOVDP = 0;
float PtrWidth = 0.0f;
/*
void DEFASM PtrRM() {//call SpaceEngine.exe+15B0CA - 89 81 34010000        - mov [ecx+00000134],eax { 指针右移}

	__asm {
		push eax
		push ecx
		push 0
		push ecx
		add dword ptr [esp], 0xFC
		push edx
		call PtrMove
		cmp eax, 0
		pop ecx
		pop eax
		jz NMV
		inc eax
		movss xmm1, PtrWidth//{ [1.00] }

		NMV :
		mov[ecx + 0x134], eax//{ 指针右移}
		ret 0
	}
}

void DEFASM PtrLM() {//call SpaceEngine.exe+15B12C - F3 0F10 0C 85 6C2E7900  - movss xmm1,[eax*4+SpaceEngine.exe+532E6C]

	__asm {
		push eax
		push ecx
		push 1
		push ecx
		add dword ptr [esp],0xFC
		push edx
		call PtrMove
		cmp eax,1
		pop ecx
		pop eax
		jz HMV
		push ebx
		mov ebx,[MOVDP]
		movss xmm1, [eax * 4 + ebx]
		pop ebx
		ret 0
		HMV:
		movss xmm1, PtrWidth
		cmp [ecx + 0X134], 0
		jz RET0
		dec[ecx + 0X134]
		RET0:
		ret 0
	}
}*/
float TW = 0;
float* WINAPI PtrMove(size_t p, BYTE*str,size_t *ptr, bool m) {
	if(str[p])
	if (StrMap.Page[str[p - m]].use) {
		//PtrWidth = StrMap.Page[str[p - m]].Page[str[p + !m]].Width;
		m ? (*ptr)-=2: (*ptr)+=2;
		return &StrMap.Page[str[p - m]].getInfo()[str[p + !m]].Width;
	}
	else {
		//PtrWidth = WidAdd[str[p]];
		m ? (*ptr)-- : (*ptr)++;
		return &WidAdd[str[p]];
	}
	return &TW;
}
void DEFASM PtrLMove() {//jmp SpaceEngine.exe+15B0F0 - 80 A1 54010000 FE     - and byte ptr [ecx+00000154],-02 { 254 } 7

	__asm {
		and byte ptr[ecx + 0x154], -0x02 //{ 254 }
		mov eax, [ecx + 0x134]
			test eax, eax
		je RET0//je SpaceEngine.exe + 15B151
			lea edx, [eax - 0x01]
			lea eax, [ecx + 0xFC]
			//mov[ecx + 0x134], edx//{ 指针左移}
			cmp dword ptr[eax + 0x14], 0x10// { 16 }
		jb J15B118 //jb SpaceEngine.exe + 15B118
			mov eax, [eax]
		J15B118:
			push ebx
			mov bl, [edx + eax]
			cmp bl, 0x09 //{ 9 }
		jne J15B129//SpaceEngine.exe + 15B129
			mov ebx,[TABWid]
			movss xmm1, [ebx]//[SpaceEngine.exe + 0x532E14]{ [150.00] }
		jmp J15B135//SpaceEngine.exe + 15B135
		J15B129:
			push ecx
			push 1
			push ecx
			add dword ptr[esp],0x134
			push eax
			push edx
			call PtrMove
			pop ecx
		//	movzx eax, al
		//	mov ebx,[WidAdd]
			movss xmm1,[eax] //[eax * 4 + ebx]//[eax * 4 + SpaceEngine.exe + 532E6C]
		J15B135:
			mov ebx, [UWid]
			mulss xmm1,[ebx]// [SpaceEngine.exe + 0x532E1C]{ [1.00] }
			pop ebx
			movss xmm0, [ecx + 0x138]
			subss xmm0, xmm1
			movss[ecx + 0x138], xmm0
			RET0:
			ret 0

	}

}
void DEFASM PtrRMove() {//jmp SpaceEngine.exe+15B070 - 8B 91 34010000        - mov edx,[ecx+00000134] 6

	__asm {
		mov edx, [ecx + 0x134]
		and byte ptr[ecx + 0x154], -0x02// { 254 }
		movd xmm0, edx
			cvtdq2ps xmm0, xmm0
			ucomiss xmm0, [ecx + 0x13C]
			lahf
			test ah, 0x44// { 68 }
		jnp RET0//SpaceEngine.exe + 0x15B0E4
			cmp dword ptr[ecx + 0x110], 0x10// { 16 }
		lea eax, [ecx + 0xFC]
			jb J15B0A2//SpaceEngine.exe + 0x15B0A2
			mov eax, [eax]
		J15B0A2:
			push ebx
			
			mov bl, [edx + eax]
			cmp bl, 0x09// { 9 }
		jne J15B0B3//SpaceEngine.exe + 0x15B0B3
			mov ebx, [TABWid]
			movss xmm1,[ebx]// [SpaceEngine.exe + 0x532E14]//{ [150.00] }
			jmp J15B0BF//SpaceEngine.exe + 0x15B0BF
		J15B0B3:
			push ecx
			push 0
			push ecx
			add  dword ptr[esp], 0x134
			push eax
			push edx
			call PtrMove
			//movzx eax, al
			movss xmm1, [eax]//[eax * 0x4 + SpaceEngine.exe + 0x532E6C]
			pop ecx
		J15B0BF:
			mov ebx, [UWid]
			mulss xmm1, [ebx]//[SpaceEngine.exe + 0x532E1C]//{ [1.00] }
			pop ebx
			//lea eax, [edx + 0x01]
		//	mov[ecx + 0x134], eax//{ 指针右移}
			movss xmm0, [ecx + 0x138]
			addss xmm0, xmm1
			movss[ecx + 0x138], xmm0
		RET0:
			ret


	}

}
void WINAPI NInput980(BYTE *pstr,size_t UTF16,size_t p,size_t *m,size_t *ptr) {
	BYTE*P = StrMap.GetCharCode(UTF16);
	if(P){
		size_t size = 0;
		while (pstr[p + (size++)]);
		if(*m>p)while (size--)  pstr[p + size + (P[0] ? 1 : 0)] = pstr[p + size-1]; 
		if (P[0]) {
		pstr[p] = P[0],pstr[p+1] = P[1];
		(*ptr)++,(*m)++;
		}else 
			pstr[p] = P[1];
	}else {
		pstr[p] = BYTE(UTF16);
	}
}
void *IRETADD=0;
void DEFASM InputASM980() {
	__asm {
		push ebp
		mov ebp, esp
		mov eax, [ebp + 0x0C]
		mov edx, ecx
		cmp eax, 0x01// { 1 }
		jne J3F3B2//SpaceEngine.exe + 0x3F3B2
			cmp dword ptr[edx + 0x14], 0x10 //{ 16 }
		jb J3F3A5//SpaceEngine.exe + 0x3F3A5
			mov edx, [edx]
		J3F3A5:
			//mov eax, [ebp + 0x08]
			//mov cl, [ebp + 0x10]//<<<<<<<
			//mov[eax + edx], cl
			/*mov eax, [esp+0x18]
			add eax,0x134//0x28
			inc dword ptr [eax]
			lea eax,[esp+0x28]
			inc dword ptr [eax]*/
			push [esp+0x18]
			add  dword ptr[esp], 0x134
			push esp
			add [esp],0x28+4
			push [ebp + 0x08]
			push [ebp + 0x10]
			push edx
			call NInput980

			
			pop ebp
			ret 0xC//{ 12 }
		J3F3B2:
			cmp dword ptr[edx + 0x14], 10 //{ 16 }
		jb J3F3BA//SpaceEngine.exe + 0x3F3BA
			mov edx, [edx]
		J3F3BA:
			JMP IRETADD
			/*push eax
			mov eax, [ebp + 0x10]
			movsx eax, al
			push eax
			mov eax, [ebp + 0x08]
			add eax, edx
			push eax
			call //SpaceEngine.exe + 7F010
			add esp, 0x0C//{ 12 }
			pop ebp
			ret 0xC//{ 12 }*/

	}
}

/*void DelStr(BYTE*wstr,BYTE*mstr,size_t s){//SpaceEngine.exe+3E091 - call SpaceEngine.exe+789F0 { 删除}

	if (StrMap.Page[*(wstr - 1)].use)wstr--;
	while (s--)*(wstr++) = *(mstr++);
}*/
void WINAPI DelStr2(float *F1,float *F2,BYTE *str,size_t m,size_t *p) {
	float A = 0;
	if (StrMap.Page[str[m - 1]].use) {
		m--,(*p)--,A = StrMap.Page[str[m]].getInfo()[m+1].Width;
		while (str[m+2] != 0) { str[m] = str[m + 2]; m++; }
		
	}else {
		if (!StrMap.Page[str[m]].use)A = WidAdd[str[m]];
		else if (str[m] == 0x9)A = *TABWid;
		while (str[m + 1] != 0) { str[m] = str[m + 1]; m++; }
	}
	str[m] = 0;
	*F1 -= A,*F2 -= A;

}
void DEFASM DelStr980() {//SpaceEngine.exe+15B29B - 72 04                 - jb SpaceEngine.exe+15B2A1 6
	__asm {
		jb J15B2A1//SpaceEngine.exe + 15B2A1
			mov eax, [ecx]
		jmp J15B2A3//SpaceEngine.exe + 15B2A3
		J15B2A1:
			mov eax, ecx
		J15B2A3:
			push esi//[esi + 00000134]
			add [esp],0x134
			push edx
			push eax
			lea eax,[esi + 0x00000138]
			push eax
			lea eax, [esi + 0x00000140]
			push eax
			call DelStr2
			pop esi
			ret 
		/*	mov al, [edx + eax]
			cmp al, 0x09 //{ 9 }
		jne J15B2B4//SpaceEngine.exe + 15B2B4
			mov ebx, [TABWid]
			movss xmm1, [ebx]//[SpaceEngine.exe + 0x532E14]//{ [150.00] }
		jmp J15B2C0//SpaceEngine.exe + 15B2C0
		J15B2B4:
			movzx eax, al
			movss xmm1, [eax * 0x4 + SpaceEngine.exe + 0x532E6C]
		J15B2C0:
			mulss xmm1, [SpaceEngine.exe + 0x532E1C]//{ [1.00] }
			push 0x01 //{ 1 }
		movss xmm0, [esi + 0x00000138]
			push edx
			subss xmm0, xmm1
			movss[esi + 0x00000138], xmm0
			movss xmm0, [esi + 0x00000140]
			subss xmm0, xmm1
			movss[esi + 0x00000140], xmm0
			call SpaceEngine.exe + 0x3E030
			mov eax, [esi + 0x000000E0]
			test eax, eax
		je J15B305//SpaceEngine.exe + 15B305
			pop esi
			jmp eax
		J15B305:
			pop esi
			ret*/

	}
}
