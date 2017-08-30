// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"
#include "Windows.h"
#include <vector>
#include <stdio.h>
#include <tchar.h>
#include <sstream> 
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <memory>
#include <json\json.h>
#include <png.h>
#include<mutex>
#include<iostream>
#include<stdlib.h>
//#include<errno.h>
#include<io.h>
//#include <algorithm>
#include "resource.h"
extern DWORD Base;
extern size_t maxLogSize,wngCnt, errCnt;
void openErr(const std::wstring&path);
enum class MsgType { Info, Error, Warning, Debug, Null };
void msgmgr(MsgType _Ty, const std::wstring msg, ...);
BOOL WriteAdd(LPVOID lpAddress, uint8_t *Code, size_t Size);
BOOL ReadAdd(LPVOID lpAddress, uint8_t *Code, size_t Size);
BOOL WriteAdd(DWORD Offset, const uint8_t *Code, size_t Size);
BOOL ReadAdd(DWORD Offset, uint8_t *Code, size_t Size);
#include<TlHelp32.h>  

#include <ft2build.h>
#include <assert.h>
#include FT_FREETYPE_H
#include FT_STROKER_H
class ReadProcAdd {
	DWORD Base=0;
	DWORD GetBase(DWORD Pid)
	{
		
		HANDLE phSnapshot;
		hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Pid);
		MODULEENTRY32 me32;
		phSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, Pid);
		if (phSnapshot == INVALID_HANDLE_VALUE)return false;
		me32.dwSize = sizeof(MODULEENTRY32);
		if (!Module32First(phSnapshot, &me32))return false;
		
		do
		{
			if (me32.th32ProcessID == Pid)
			{
				Base = (DWORD)me32.modBaseAddr;
				break;
			}
		} while (Module32Next(phSnapshot, &me32));

		CloseHandle(phSnapshot);
		if (Base != 0)return Base;
		return false;
	}
	size_t ReadMem(DWORD OF,char *p) {
		size_t l = 0;
		char *p2 = p;
		if(p!=0){
		DWORD LP = Base + OF;
		while(l<256&&ReadProcessMemory(hProc, (LPVOID)LP++, p2, 1, 0)&&*(p2++)!=0)l++;
		p[l] = 0;
		}
		return l;
	}
	HANDLE hProc = 0;
public:
	~ReadProcAdd() {
		CloseHandle(hProc);
	}
	ReadProcAdd(char *Path, char*Out, char *F,DWORD PID) {
		std::ifstream IF(Path);
		char str[256],str2[256],str3[512];
		GetBase(PID);
		if (hProc == NULL) return;
		std::ofstream OF(Out);
		while(IF.getline(str,256)){
			size_t L = 0;
			DWORD LP=strtol(str, 0, 16);
			if (L = ReadMem(LP, str2)) {
				snprintf(str3, 512, F, LP, str2);
				printf("%s\n", str3);
				OF << str3 << std::endl;

			}
			
		
		}
		IF.close();
		OF.close();
	}
};


class UTF {
	std::string utf8;
	std::wstring utf16;
public:
	UTF(std::string &str) {
		Codec(str);
	}
	UTF(std::wstring &str) {
		Codec(str);
	}
	size_t Codec(std::string &str) {
		utf8 = str;
		utf16 = Decode(str);
		return utf16.size();
	}
	size_t Codec(std::wstring &str) {
		utf8 = Encode(str);
		utf16 = str;
		return utf8.size();
	}
	const std::string& getUTF8()const { return utf8; }
	const std::wstring& getUTF16()const { return utf16; }
	static std::string Encode(const std::wstring &str) {
		std::string utf8;
		for (auto ch : str)Encode(ch, utf8);
		return utf8;
	}
	static std::string Encode(wchar_t ch) {
		std::string utf8;
		return Encode(ch, utf8);
	}
	static std::string& Encode(wchar_t ch, std::string &utf8) {
		//std::string utf8;

		if (ch < 0x80)
			utf8 += (char)ch;
		else if (ch < 0x800)
		{
			utf8 += (char)(0xc0 | ((ch & 0x7c0) >> 6));
			utf8 += (char)(0x80 | (ch & 0x3f));
		}
		else if (ch < 0x10000)
		{
			utf8 += (char)(0xe0 | ((ch & 0xf000) >> 12));
			utf8 += (char)(0x80 | ((ch & 0x0fc0) >> 6));
			utf8 += (char)(0x80 | ((ch & 0x003f)));
		}
		else if (ch < 0x200000)
		{
			utf8 += (char)(0xf0 | ((ch & 0x1c0000) >> 18));
			utf8 += (char)(0x80 | ((ch & 0x03f000) >> 12));
			utf8 += (char)(0x80 | ((ch & 0x000fc0) >> 6));
			utf8 += (char)(0x80 | ((ch & 0x00003f)));
		}
		else if (ch < 0x4000000)
		{
			utf8 += (char)(0xf8 | ((ch & 0x3000000) >> 24));
			utf8 += (char)(0x80 | ((ch & 0x0fc0000) >> 18));
			utf8 += (char)(0x80 | ((ch & 0x003f000) >> 12));
			utf8 += (char)(0x80 | ((ch & 0x0000fc0) >> 6));
			utf8 += (char)(0x80 | ((ch & 0x000003f)));
		}
		else
		{
			utf8 += (char)(0xfc | ((ch & 0x40000000) >> 30));
			utf8 += (char)(0x80 | ((ch & 0x3f000000) >> 24));
			utf8 += (char)(0x80 | ((ch & 0x00fc0000) >> 18));
			utf8 += (char)(0x80 | ((ch & 0x0003f000) >> 12));
			utf8 += (char)(0x80 | ((ch & 0x00000fc0) >> 6));
			utf8 += (char)(0x80 | ((ch & 0x0000003f)));
		}

		return utf8;
	}
	static std::wstring Decode(const std::string &str) {
		std::wstring utf16;
		for (size_t i(0), sz(str.size()); i<sz;) {
			wchar_t ch = str[i];
			if (ch < 0x80)
				ch = str[i], i++;
			else if ((ch & 0xe0) == 0xc0)
				ch = ((str[i] & 0x1f) << 6) |
				((unsigned int)str[i + 1] & 0x3f), i += 2;
			else if ((ch & 0xf0) == 0xe0)
				ch = ((str[i] & 0x0f) << 12) |
				(((unsigned int)str[i + 1] & 0x3f) << 6) |
				((unsigned int)str[i + 2] & 0x3f), i += 3;
			else if ((ch & 0xf8) == 0xf0)
				ch = ((str[i] & 0x07) << 18) |
				(((unsigned int)str[i + 1] & 0x3f) << 12) |
				(((unsigned int)str[i + 2] & 0x3f) << 6) |
				((unsigned int)str[i + 3] & 0x3f), i += 4;
			else if ((ch & 0xfc) == 0xf8)
				ch = ((str[i] & 0x03) << 24) |
				(((unsigned int)str[i + 1] & 0x3f) << 18) |
				(((unsigned int)str[i + 2] & 0x3f) << 12) |
				(((unsigned int)str[i + 3] & 0x3f) << 6) |
				((unsigned int)str[i + 4] & 0x3f), i += 5;
			else if ((ch & 0xfe) == 0xfc)
				ch = ((str[i] & 0x01) << 30) |
				(((unsigned int)str[i + 1] & 0x3f) << 24) |
				(((unsigned int)str[i + 2] & 0x3f) << 18) |
				(((unsigned int)str[i + 3] & 0x3f) << 12) |
				(((unsigned int)str[i + 4] & 0x3f) << 6) |
				((unsigned int)str[i + 5] & 0x3f), i += 6;
			utf16 += ch;
		}
		return utf16;
	}

};

class PNG {
#define PNG_BYTES_TO_CHECK 8
	//#define PNG_HEADER "\x89\x50\x4E\x47\x0D\x0A\x1A\x0A"
public:
	uint8_t *data;
	size_t fmt = 0, w = 0, h = 0, b = 0, Err = 0;
	void resize(size_t w, size_t h, size_t b) {
		clear();
		data = new uint8_t[w*h*b];
		this->w = w, this->h=h, this->b=b;
	}
	long getFormat()const { return fmt; }
	long getWidth()const { return w; }
	long getHeight()const { return h; }
	long getBit()const { return b; }
	long getError()const { return Err; }
	uint8_t*getData()const { return data; }
	PNG(std::string &path) :data(nullptr), w(0), h(0), b(0), Err(0)
	{
		Err = open(path);
	}
	PNG(std::wstring &path) :data(nullptr), w(0), h(0), b(0), Err(0)
	{
		Err = LoadPNG(path);
	}
	PNG(const char*path) :data(nullptr), w(0), h(0), b(0), Err(0)
	{
		Err = LoadPNG(path);
	}
	PNG(const wchar_t*path) :data(nullptr), w(0), h(0), b(0), Err(0)
	{
		Err = LoadPNG(path);
	}
	operator bool()const { return(data != nullptr); }
	~PNG() {
		clear();
	}
	void clear() {
		w = h = b = Err = 0;
		if (*this)delete[]data;
		data = nullptr;
	}
	bool open(const std::string&path) {
		clear();
		Err = LoadPNG(path);
		return *this;
	}
	int LoadPNG(const std::string &path) {
		return LoadPNG(path.c_str());
	}
	int LoadPNG(const char*path) {
		FILE *fp;
		fopen_s(&fp, path, "rb");
		return LoadPNG(fp);
	}
	int LoadPNG(const std::wstring path) {
		return LoadPNG(path.c_str());
	}
	int LoadPNG(const wchar_t*path) {
		FILE *fp;
		_wfopen_s(&fp, path, L"rb");
		return LoadPNG(fp);
	}
	int LoadPNG(FILE *fp)
	{
		int status(0);
		png_structp png_ptr;
		png_infop info_ptr;
		png_bytepp row_pointers;
		png_byte buf[PNG_BYTES_TO_CHECK];
		if (fp != NULL) {
			rewind(fp);
			png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
			if (png_ptr != NULL)
			{
				info_ptr = png_create_info_struct(png_ptr);
				if (info_ptr != NULL)
				{
					if (!setjmp(png_jmpbuf(png_ptr)))
					{
						if (fread(buf, sizeof(png_byte), PNG_BYTES_TO_CHECK, fp) == PNG_BYTES_TO_CHECK&&png_sig_cmp(buf, 0, PNG_BYTES_TO_CHECK) == 0) {
							rewind(fp);
							png_init_io(png_ptr, fp);
							png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);
							png_byte color_type = png_get_color_type(png_ptr, info_ptr);
							if (data)clear();
							w = png_get_image_width(png_ptr, info_ptr);
							h = png_get_image_height(png_ptr, info_ptr);
							b = png_get_channels(png_ptr, info_ptr);

							data = new png_byte[w*h *b];
							if (data != NULL) {
								row_pointers = png_get_rows(png_ptr, info_ptr);
								for (size_t y(0), cw = png_get_rowbytes(png_ptr, info_ptr); y < h; y++)
									memcpy(data + cw*y, row_pointers[y], cw);
								/*switch (color_type) {
								case PNG_COLOR_TYPE_RGB_ALPHA:fmt = GL_RGBA; break;
								case PNG_COLOR_TYPE_RGB:fmt = GL_RGB; break;
								case PNG_COLOR_TYPE_GRAY_ALPHA:fmt = GL_ALPHA; break;
								default:fmt = NULL;
								}*/
							}
							else status = -6;
						}
						else status = -1;
					}
					else status = -2;
					//png_read_end(png_ptr, info_ptr);
				}
				else status = -3;
				png_destroy_read_struct(&png_ptr, &info_ptr, 0);
			}
			else status = -4;
			fclose(fp);
		}
		else status = -5;
		return status;
	}
	template<class _Ty>
	int write(_Ty file) {
		return write_png(file, data, w, h,b);
	}
	static int write_png(const std::string &file_name,  uint8_t* data, size_t Width, size_t Height, size_t bit = 4) {
		return write_png(file_name.c_str(), data, Width, Height, bit);
	}	
	static int write_png(const std::wstring &file_name,  uint8_t* data, size_t Width, size_t Height, size_t bit = 4) {
		return write_png(file_name.c_str(), data, Width, Height, bit);
	}
	static int write_png(const char *file_name,  uint8_t* data, size_t Width, size_t Height, size_t bit = 4) {
		FILE *fp;
		fopen_s(&fp, file_name, "wb");
		return write_png(fp, data, Width, Height, bit);
	}
	static int write_png(const wchar_t *file_name,  uint8_t* data, size_t Width, size_t Height, size_t bit = 4) {
		FILE *fp;
		_wfopen_s(&fp, file_name, L"wb");
		return write_png(fp, data, Width, Height,bit);
	}
	static int write_png(FILE *fp,  uint8_t* data, size_t Width, size_t Height,size_t bit=4)
	{
		int status(0);
		png_structp png_ptr;
		png_infop info_ptr;

		if (fp != NULL) {
			png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
			if (png_ptr != NULL)
			{
				info_ptr = png_create_info_struct(png_ptr);
				if (info_ptr != NULL)
				{
					if (!setjmp(png_jmpbuf(png_ptr)))
					{
						int color(0);
						switch (bit) {
						case 1:color = PNG_COLOR_TYPE_GRAY; break;
						case 2:color = PNG_COLOR_TYPE_GA; break;
						case 3:color = PNG_COLOR_TYPE_RGB; break;
						case 4:color = PNG_COLOR_TYPE_RGBA; break;
						}
						png_init_io(png_ptr, fp);
						png_set_IHDR(png_ptr, info_ptr, Width, Height, 8, color,
							PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
						png_write_info(png_ptr, info_ptr);
						png_bytep* row_pointers = new png_bytep[Height];
						if (Height > PNG_UINT_32_MAX / (sizeof(png_bytep)))
							png_error(png_ptr, "Image is too tall to process in memory");
						for (size_t k = 0; k < Height; k++)
							row_pointers[k] = data + k*Width * bit;
						png_write_image(png_ptr, row_pointers);
						delete[]row_pointers;
					}
					else status = -2;
					png_write_end(png_ptr, info_ptr);
				}
				else status = -3;
				png_destroy_write_struct(&png_ptr, &info_ptr);
			}
			else status = -4;
			fclose(fp);
		}
		else status = -5;
		return status;
	}
};


class Hook {
	class Address {
		void GetCode() {
			DWORD CODE = (DWORD)Fun - (Base + Offset) - 5;
			BYTE* P = (BYTE*)&CODE;
			for (int i = 0; i < 4; i++) {
				Code[i + 1] = P[i];
			}
		}
	public:
		DWORD Offset = 0;
		LPVOID Fun = 0;
		BYTE *Code = 0, *CodeOld = 0;
		size_t Size = 0;
		BYTE Method = 0xE8;
		bool sted = false;
		Address(LPVOID F, DWORD Of, BYTE Met, size_t s) {
			Offset = Of, Fun = F, Method = Met, Size = s;
			Code = new BYTE[s], CodeOld = new BYTE[s];
			ReadAdd(Offset, CodeOld, Size);
			GetCode();
			for (size_t i = 5; i < Size; i++)Code[i] = 0x90;
			Code[0] = Method;
		}
		~Address() {
			//	End();
			if (Code)delete[] Code;
			if (CodeOld)delete[] CodeOld;
			Code = CodeOld = nullptr;
		}
		void Hook() {
			if (!sted) {
				WriteAdd(Offset, Code, Size);
				sted = true;
			}
		}
		void unHook() {
			if (sted) {
				WriteAdd(Offset, CodeOld, Size);
				sted = false;
			}
		}
	};
	std::vector<std::unique_ptr<Address>> list;
public:
	void Add(LPVOID Fun, DWORD Offset, BYTE Met, size_t s) { list.push_back(std::unique_ptr<Address>(new Address(Fun, Offset, Met, s))); };
	~Hook() { for (auto &p : list)p.reset(nullptr); list.clear(); }
	void HookAll() { for (auto &p : list)p->Hook(); }
	void unHookAll() { for (auto &p : list)p->unHook(); }
};
struct Offset { float Off = 0.0, Width = 12.0f; };
class Localization {
private:
	struct WChar {
		bool use;
		uint8_t str[2]//页ID XY
			, PID;//页ID
		wchar_t ch;
		size_t refCnt;
		WChar() :use(false), str{ 0 }, PID(0), ch(0), refCnt(0){
		}
		WChar(uint8_t pid, uint8_t fid, wchar_t ch) :use(true), PID(pid), ch(ch), refCnt(0) {
			str[0] = pid, str[1] = fid;
		}
	};
	
	class PageInfo {
		Offset* Info;
	public:
		void Clear() {
			if (Info != nullptr)delete[] Info;
			Info = nullptr;
			OffsetX = OffsetY = ID = PID = 0;
			File.clear();
			use = false;
		}
		Offset*getInfo() { return Info == nullptr ? newPage() : Info; };
		Offset*newPage(size_t size = 256) {
			if (Info != nullptr)delete[] Info, Info = nullptr;
			return Info = new Offset[size];
		};
		size_t Init(size_t id, uint8_t pid, const std::wstring&font, const std::string&params) {
			OffsetX = (id % 4) * 16, OffsetY = (id / 4) * 16;
			ID = id, PID = pid;
			File = font;
			std::stringstream ss(params);
			newPage();
			size_t i = 0;
			while (i<256 && ss >> Info[i].Off >> Info[i].Width)i++;
			use = true;
			return i;
		}
		PageInfo() :Info(nullptr) {
			Clear();
		};
		~PageInfo() {
			Clear();
		}
		std::wstring File;
		size_t OffsetX = 0, OffsetY = 0, ID = 0; //坐标起始位置 序号
		BYTE PID = 0;// 页ID
		bool use = false;
	};
	std::map<std::string, std::string>Map;
	std::map<wchar_t, size_t>err;
	WChar *Wstr;
public:
	WChar& GetCharCfg(size_t UTF16) {
		return Wstr[UTF16];
	}
	uint8_t *GetCharCode(size_t UTF16) {
		if (UTF16>0 && UTF16<1<<16 && Wstr[UTF16].use)return Wstr[UTF16].str;
		return 0;
	}
	static std::wstring sCfgErr, sFontMsg, sIdMsg, sParamsMsg, sMapMsg, sMapErr, sUnCfgErr, sWDefErr, sReDefErr, sTexErr, sFmtErr, sLoadErr, sPageMsg, sMapSzErr, sStr2lErr;
	void Clear() {
		Map.clear();
		PageList.clear();
		for (auto &p : Page)p.Clear();
	}
	void InitMsg(const Json::Value&val) {
		sCfgErr = val["sCfgErr"].isString() ? UTF::Decode(val["sCfgErr"].asString()) : L"%s.Pages[%d] %s 配置错误,目标类型为 %s,%s",
			sFontMsg = val["sFontMsg"].isString() ? UTF::Decode(val["sFontMsg"].asString()) : L"指定一个字体纹理文件名",
			sIdMsg = val["sIdMsg"].isString() ? UTF::Decode(val["sIdMsg"].asString()) : L"指定一个页映射Id",
			sParamsMsg = val["sParamsMsg"].isString() ? UTF::Decode(val["sParamsMsg"].asString()) : L"指定字体偏移与宽度,不配置则使用默认值",
			sMapMsg = val["sMapMsg"].isString() ? UTF::Decode(val["sMapMsg"].asString()) : L"指定字体在纹理上的位置,不配置则无法使用字符映射表";
		sMapErr = val["sMapErr"].isString() ? UTF::Decode(val["sMapErr"].asString()) : L"%s.Pages[%d](%d,%d)->%c已存在于Pages[%d](%d,%d)->%c",
			sUnCfgErr = val["sUnCfgErr"].isString() ? UTF::Decode(val["sUnCfgErr"].asString()) : L"未配置字符 %s";
		sWDefErr = val["sWDefErr"].isString() ? UTF::Decode(val["sWDefErr"].asString()) : L"写入失败 %s->%s";
		sReDefErr = val["sReDefErr"].isString() ? UTF::Decode(val["sReDefErr"].asString()) : L"%s 重定义";
		sTexErr = val["sTexErr"].isString() ? UTF::Decode(val["sTexErr"].asString()) : L"纹理%s[%d]:PID:%d %d*%d*%d X:%d Y:%d Path:%s";
		sFmtErr = val["sFmtErr"].isString() ? UTF::Decode(val["sFmtErr"].asString()) : L"格式不规范";
		sLoadErr = val["sLoadErr"].isString() ? UTF::Decode(val["sLoadErr"].asString()) : L"加载失败";
		sPageMsg = val["sPageMsg"].isString() ? UTF::Decode(val["sPageMsg"].asString()) : L"指定字体纹理的显示参数,若不配置则不显示相关字符";
		sMapSzErr = val["sMapSzErr"].isString() ? UTF::Decode(val["sMapSzErr"].asString()) : L"%s.Pages[%d].Maps 的字符数量(%d)超出了最大值256,超出部分将截断:%s";
		sStr2lErr = val["sStr2lErr"].isString() ? UTF::Decode(val["sStr2lErr"].asString()) : L"字符串产生的结果超过了允许的最大长度15 %s->(len=%d)";
	}
	void InitDefine(const Json::Value&val) {

		const auto &def = val.getMemberNames();
		for (auto &key : def) {
			std::string str;
			if (Map.find(key) != Map.end())msgmgr(MsgType::Error, sReDefErr, UTF::Decode(key).c_str());
			else InitDefine(key, val[key].asString());
		}
	}


	
	std::string InitDefine(const std::string&key, const std::string&val) {

		
		
		const std::wstring &wval = UTF::Decode(val);
		std::string str;
		for (auto v : wval) {
			if (!Wstr[v].use) err[v]++;
			else {
				for (uint8_t c : Wstr[v].str)if (c)str += c;
				Wstr[v].refCnt++;
			}
		}
	
		if (!str.empty())Map[key] = str;
		return str;
	}
	void ApplyDefine(const Json::Value&val) {
		const auto &def = val.getMemberNames();
		for (auto &key : def) {
			auto it = Map.find(key);
			std::string code;
			if (it != Map.end())code = it->second;
			else code = InitDefine(key, key);
			const auto &str = UTF::Decode(val[key].asString());
			DWORD off = std::wcstol(str.c_str(), 0, 1 << 4);
			code += '\0';
			if (code.size() > 15)msgmgr(MsgType::Error, sStr2lErr, UTF::Decode(key).c_str(), code.size());
			else if (!WriteAdd(off, (uint8_t*)code.c_str(), code.size()))msgmgr(MsgType::Error, sWDefErr, str.c_str(), UTF::Decode(key).c_str());
		}
	}

	BOOL MainInit(const std::string &Lang,const Json::Value val) {
		Clear();
		err.clear();
			memset(Wstr, 0, sizeof(WChar) * 1 << 16);
			size_t curPID = 1;
			const Json::Value &lang = val["Language"][Lang], &logSz = val["maxLogSize"];
			if (logSz.isInt())maxLogSize = logSz.asInt();
			if (!lang.isNull()) {
				std::wstring wLang(UTF::Decode(Lang));
				if (lang["String"].isObject())InitMsg(lang["String"]);
				if (lang["Pages"].isArray()) {
					for (auto page : lang["Pages"]) {
						if (page["Id"].isInt()) {
							uint8_t pid = uint8_t(page["Id"].asInt());
							if (pid == 0 || page["Font"].isString()) {
								std::string args;
								const Json::Value &Params = page["Params"], &Maps = page["Maps"];;
								if (Params.isString())args = Params.asString();
								else if (Params.isArray())for (auto&arg : Params)args.append(arg.asString()) += ' ';
								else  msgmgr(MsgType::Warning, sCfgErr, wLang.c_str(), curPID, L"Params", L"String or String[]", sParamsMsg.c_str());
								Page[pid].Init(curPID, pid, UTF::Decode(page["Font"].asString()), args);
								if (pid)curPID++;
								PageList += pid;
								args.clear();
								if (Maps.isString())args = Maps.asString();
								else if (Maps.isArray())for (auto&arg : Maps)args.append(arg.asString());
								else msgmgr(MsgType::Warning, sCfgErr, wLang.c_str(), curPID, L"Maps", L"String or String[]", sMapMsg.c_str());
								const std::wstring&wstr = UTF::Decode(args);
								size_t fid(0), sz(wstr.size());
								if (sz > 0x100)msgmgr(MsgType::Warning, sMapSzErr, wLang.c_str(), pid, wstr.size(), wstr.substr(0x100).c_str());
								for (wchar_t ch; fid < 0x100 && fid < sz; fid++) {
									ch = wstr[fid];
									auto &WT = Wstr[ch];
									if (!WT.use)WT = WChar(pid, uint8_t(fid), ch);
									else if (ch != '?')msgmgr(MsgType::Warning, sMapErr, wLang.c_str(), pid, fid >> 4, fid & 0xF, ch, WT.PID, WT.str[1] >> 4, WT.str[1] & 0xF, WT.ch);
								}
							}
							else msgmgr(MsgType::Error, sCfgErr, wLang.c_str(), curPID, L"Font", L"String", sFontMsg.c_str());
						}
						else msgmgr(MsgType::Error, sCfgErr, wLang.c_str(), curPID, L"Id", L"Int", sIdMsg.c_str());
					}
					if (lang["Define"].isObject())InitDefine(lang["Define"]);
					//const std::string &M = md5.GetCapMd5();
					//if (val["Address"][M].isObject())ApplyDefine(val["Address"][M]);

					if (!err.empty()) {
						std::wstring ws;
						auto &refmap = err;
						for (auto &ch : err)ws += ch.first;
						auto sortA=[&refmap](wchar_t l, wchar_t r)->bool{
							return refmap[l] > refmap[r];
						};
						
						std::sort(ws.begin(), ws.end(), sortA);
						msgmgr(MsgType::Error, sUnCfgErr, ws.c_str());
					}
					return TRUE;
				}
				else  msgmgr(MsgType::Error, sCfgErr, wLang.c_str(), curPID, L"Pages", L"{Id,Font,Maps,Params}", sPageMsg.c_str());

				
			}
		return FALSE;
	}

	Offset* GetPage(uint8_t ID) {
		for (auto &p : Page)if (p.PID == ID&&p.use)return p.getInfo();
		return nullptr;
	}
	Localization() :Wstr(new WChar[1 << 16]) {
	}
	~Localization() {
		if (Wstr)delete[] Wstr;
		Wstr = nullptr;
	}
	std::basic_string<uint8_t> PageList;
	PageInfo Page[256];

};



class FreeType {

	class Face {
		void open(std::string &file) {
			FT_Init_FreeType(&library);
			assert(library != 0);
			FT_New_Face(library, file.c_str(), 0, &face);
			assert(face != 0);
		}
	public:
		FT_Face face;
		FT_Library library;
		Face(std::string &file) :face(0), library(0) {
			open(file);
		}
		Face(std::string &file, size_t w, size_t h, size_t pw = 100, size_t ph = 100):face(0), library(0){
			open(file);
			Set_Char_Size(w, h, pw, ph);
		}
		Face(Face&&right):face(right.face), library(right.library){
			right.face = 0,
				right.library = 0;
		}
		~Face() {
			if (face)FT_Done_Face(face);
			if (library)FT_Done_FreeType(library);
		}
		FT_Error Set_Pixel_Sizes(size_t w, size_t h) {
			return FT_Set_Pixel_Sizes(face, w, h);
		}
		FT_Error Set_Char_Size(size_t fw, size_t fh, size_t w, size_t h) {
			return FT_Set_Char_Size(face, fw<<6 ,fh<<6, h, w);
		}
		FT_UInt Get_Char_Index(WCHAR str) {
			return FT_Get_Char_Index(face, str);
		}
		FT_Error Render_Glyph(FT_Render_Mode mode) {


			return FT_Render_Glyph(face->glyph, mode);
		}
		FT_Error Get_Glyph(FT_Glyph *glyph) {



			return FT_Get_Glyph(face->glyph, glyph);
		}
		FT_Error Load_Glyph(FT_UInt index, FT_Int32 load_flags) {
			return FT_Load_Glyph(face, index, load_flags);
		}
		
	};

	long px = 0, py = 0, w = 0, h = 0, maxh = 0, base;
	size_t Fsize = 0, Csize = 0;
	FT_Library alibrary = NULL, blibrary = NULL, clibrary;
	//	FT_Face face = NULL, face2 = NULL, face3 = NULL;
	FT_Glyph glyph;
	FT_BitmapGlyph bitmap_glyph;
	//std::ofstream of;
	//FILE *op = NULL;
	long fe = 64;// 26.6f * 2;

	std::vector<Face> faces;
public:
	FreeType(std::string fonts, size_t fw, size_t fh, size_t tw, size_t th,long b) {
		size_t sp(0), lp(0);
		do{
			sp = fonts.find(';', lp);
			std::string font = fonts.substr(lp, (sp==std::string::npos?fonts.size():sp)-lp);
			if (!font.empty()) {
			if (_access(font.c_str(), 4)) {
				std::string root;
				size_t rs;
				root.resize(MAX_PATH);
				getenv_s(&rs, (char*)root.data(), MAX_PATH, "SYSTEMROOT");
				root.erase(rs-1);
				font = root + "\\Fonts\\" + font;
			}
			
			if (!_access(font.c_str(), 4)) {
				std::cout << font << std::endl;
				faces.push_back(std::move(Face(font, fw, fh, 72, 72)));
			}
			}
			lp = sp + 1;
			
		}while(sp != std::string::npos);
		
		base = b;
			w = tw, h = th;
			px =py= 0;// 16 * 0xA + 16;
			Fsize = fh;
			std::cout << "texSize:\t" << w << '*' << h << "\nfontSize:\t" << fw << '*' << fh << "\nbaseLine:\t" << b << std::endl;
	}
	void Render(std::wstring &map, const char*out) {
		px = py = 0;
		size_t sfw = w / 16, sfh = h / 16, index;
		uint8_t *data = new uint8_t[w*h*2];
		memset(data, 0, sizeof(uint8_t)*w*h*2);
		for (WCHAR ch : map) {
				if (ch != ' '&&ch!='?')
					for (Face &face:faces) {
					index = face.Get_Char_Index(ch);
					
					if (!face.Load_Glyph(index, FT_LOAD_DEFAULT)) {
						face.Render_Glyph(FT_RENDER_MODE_NORMAL);
						face.Get_Glyph(&glyph);
						FT_Glyph cp_glyph;
						FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, 0, 1);
						bitmap_glyph = (FT_BitmapGlyph)glyph;
						FT_Bitmap &bitmap = bitmap_glyph->bitmap;
						FT_Glyph_Metrics &met = face.face->glyph->metrics;
						long bearingY = met.horiBearingY / 64,bearingX = met.horiBearingX / 64;
						/*for (long i(0),x; i < bitmap.rows; i++) {
							long ptr = py + base - bearingY + i;
							if (ptr >= 0 && ptr<h)
								for (x = 0; x < bitmap.width; x++) {
								uint8_t T = bitmap.buffer[i*bitmap.width+x];
								data[ptr*w+ px+x+bearingX] = Pixel32(T,T,T,T);
							}
						}*/
						for (long i(0),x; i < bitmap.rows; i++) {
							long ptr = py + base - bearingY + i;
							if (ptr >= 0 && ptr < h)//memcpy(&data[ptr*w + px  + bearingX], &bitmap.buffer[i*bitmap.width], bitmap.pitch);
								for (x = 0; x < bitmap.width; x++) {
									data[(ptr*w + px + x + bearingX)*2] = data[(ptr*w + px + x + bearingX) * 2+1] = bitmap.buffer[i*bitmap.width + x];
								}
						}
						//std::cout << px << ':' << py << std::endl;
						break;
					}
				}
				px += sfw;
				if (px >= w)px = 0, py += sfh;
		}
		/*uint8_t*alpha = new uint8_t[w*h * 2];
		memset(alpha, 0, w*h);
		for (size_t i(0), sz(w*h); i < sz; i++)alpha[i * 2] = ((Pixel32*)data)[i].getGray(),
			alpha[i * 2 + 1] = min(((Pixel32*)data)[i].a+ alpha[i * 2],255);
		PNG::write_png(out, alpha, w, h, 2);
		delete[] alpha;*/
		PNG::write_png(out, data, w, h, 2);
		delete[] data;
		
	}

	~FreeType() {
		
	}












#ifdef _MSC_VER
#define MIN __min
#define MAX __max
#else
#define MIN std::min
#define MAX std::max
#endif


	// A horizontal pixel span generated by the FreeType renderer.

	struct Span
	{
		Span() { }
		Span(int _x, int _y, int _width, int _coverage)
			: x(_x), y(_y), width(_width), coverage(_coverage) { }

		int x, y, width, coverage;
	};

	typedef std::vector<Span> Spans;

	// A simple 32-bit pixel.

	union Pixel32
	{
		Pixel32() { }
		Pixel32(uint32_t hex):integer(hex){ }
		Pixel32(uint8_t bi, uint8_t gi, uint8_t ri, uint8_t ai = 255)
		{
			b = bi;
			g = gi;
			r = ri;
			a = ai;
		}
		Pixel32&operator+=(Pixel32&pxl) {
			b += pxl.b,a += pxl.a,g += pxl.g,r += pxl.r;
			return *this;
		}
		Pixel32&operator*=(Pixel32&pxl) {
			b *= pxl.b, a *= pxl.a, g *= pxl.g, r *= pxl.r;
			return *this;
		}
		Pixel32&operator-=(Pixel32&pxl) {
			b -= pxl.b, a -= pxl.a, g -= pxl.g, r -= pxl.r;
			return *this;
		}
		Pixel32&operator/=(Pixel32&pxl) {
			b /= pxl.b, a /= pxl.a, g /= pxl.g, r /= pxl.r;
			return *this;
		}
		Pixel32&operator%=(Pixel32&pxl) {
			b %= pxl.b, a%= pxl.a, g%= pxl.g, r %= pxl.r;
			return *this;
		}
		Pixel32&operator*(Pixel32&pxl) {
			Pixel32 tmp = *this;
			tmp *= pxl;
			return *this;
		}
		Pixel32 operator+(Pixel32&pxl) {
			Pixel32 tmp = *this;
			tmp += pxl;
			return tmp;
		}
		Pixel32 operator-(Pixel32&pxl) {
			Pixel32 tmp = *this;
			tmp -= pxl;
			return tmp;
		}Pixel32 operator/(Pixel32&pxl) {
			Pixel32 tmp = *this;
			tmp /= pxl;
			return tmp;
		}
		Pixel32 operator%(Pixel32&pxl) {
			Pixel32 tmp = *this;
			tmp %= pxl;
			return tmp;
		}
		uint8_t getGray()const {
			return (r * 30 + g * 59 + b * 11) / 100;
		}
		uint32_t integer;
		uint8_t data[4];
		//struct{uint8_t r, g, b, a;};
		struct { uint8_t b, g, r,a; };
	};

	struct Vec2
	{
		Vec2() { }
		Vec2(float a, float b)
			: x(a), y(b) { }

		float x, y;
	};


	struct Rect
	{
		Rect() { }
		Rect(float left, float top, float right, float bottom)
			: xmin(left), xmax(right), ymin(top), ymax(bottom) { }

		void Include(const Vec2 &r)
		{
			xmin = MIN(xmin, r.x);
			ymin = MIN(ymin, r.y);
			xmax = MAX(xmax, r.x);
			ymax = MAX(ymax, r.y);
		}

		float Width() const { return xmax - xmin + 1; }
		float Height() const { return ymax - ymin + 1; }

		float xmin, xmax, ymin, ymax;
	};


	// Each time the renderer calls us back we just push another span entry on
	// our list.

	static void
		RasterCallback(const int y,
			const int count,
			const FT_Span * const spans,
			void * const user)
	{
		Spans *sptr = (Spans *)user;
		for (int i = 0; i < count; ++i)
			sptr->push_back(Span(spans[i].x, y, spans[i].len, spans[i].coverage));
	}


	// Set up the raster parameters and render the outline.

	void
		RenderSpans(FT_Library &library,
			FT_Outline * const outline,
			Spans *spans)
	{
		FT_Raster_Params params;
		memset(&params, 0, sizeof(params));
		params.flags = FT_RASTER_FLAG_AA | FT_RASTER_FLAG_DIRECT;
		params.gray_spans = RasterCallback;
		params.user = spans;

		FT_Outline_Render(library, outline, &params);
	}


	// Render the specified character as a colored glyph with a colored outline
	// and dump it to a TGA.
	void RenderOutline(std::wstring &map, const char*out, 
		const Pixel32 &fontCol,
		const Pixel32 outlineCol,
		float outlineWidth) {
		px = py = 0;
		
		FT_UInt index(0);
		size_t sfw = w / 16,sfh=h/16;
		std::wstring err;
			uint8_t *data = new uint8_t[w*h * 4];
			memset(data, 0, sizeof(uint8_t)*w*h * 4);
			for (WCHAR ch : map) {
				if (py >= h)break;
				else
					if (ch != L' '&&ch!='?')
						for (Face &ft : faces)
							if (index = ft.Get_Char_Index(ch)) {
								if (!ft.Load_Glyph(index, FT_LOAD_NO_BITMAP)) {
								
									// Need an outline for this to work.
									if (ft.face->glyph->format == FT_GLYPH_FORMAT_OUTLINE)
									{
										// Render the basic glyph to a span list.
										Spans spans;
										RenderSpans(ft.library, &ft.face->glyph->outline, &spans);

										// Next we need the spans for the outline.
										Spans outlineSpans;

										// Set up a stroker.
										FT_Stroker stroker;
										FT_Stroker_New(ft.library, &stroker);
										FT_Stroker_Set(stroker,
											(int)(outlineWidth * 64),
											FT_STROKER_LINECAP_ROUND,
											FT_STROKER_LINEJOIN_ROUND,
											0);

										FT_Glyph glyph;
										if (FT_Get_Glyph(ft.face->glyph, &glyph) == 0)
										{
											FT_Glyph_StrokeBorder(&glyph, stroker, 0, 1);
											// Again, this needs to be an outline to work.
											if (glyph->format == FT_GLYPH_FORMAT_OUTLINE)
											{
												// Render the outline spans to the span list
												FT_Outline *o =
													&reinterpret_cast<FT_OutlineGlyph>(glyph)->outline;
												RenderSpans(ft.library, o, &outlineSpans);
											}
											// Clean up afterwards.
											FT_Stroker_Done(stroker);
											FT_Done_Glyph(glyph);
											
											// Now we need to put it all together.
											if (!spans.empty())
											{
												// Figure out what the bounding rect is for both the span lists.
												Rect rect(spans.front().x,
													spans.front().y,
													spans.front().x,
													spans.front().y);
												for (Span &s : spans)
												{
													rect.Include(Vec2(s.x, s.y));
													rect.Include(Vec2(s.x + s.width - 1, s.y));
												}
												for (Span s : outlineSpans)
												{
													rect.Include(Vec2(s.x, s.y));
													rect.Include(Vec2(s.x + s.width - 1, s.y));
												}

#if 1
												// This is unused in this test but you would need this to draw
												// more than one glyph.
												long bearingX = ft.face->glyph->metrics.horiBearingX / 64;
												long bearingY = ft.face->glyph->metrics.horiBearingY / 64;
												long advance = ft.face->glyph->advance.x / 64;
												
#endif

												// Get some metrics of our image.
												int imgWidth = rect.Width(),
													imgHeight = rect.Height(),
													imgSize = imgWidth * imgHeight;

												// Allocate data for our image and clear it out to transparent.
												Pixel32 *pxl = new Pixel32[imgSize];
												memset(pxl, 0, sizeof(Pixel32) * imgSize);

												// Loop over the outline spans and just draw them into the
												// image.
												/*for (Span &s : outlineSpans)
													for (int w = 0; w < s.width; ++w)
														pxl[((imgHeight - 1 - (s.y - (int)rect.ymin)) * imgWidth
															+ s.x - (int)rect.xmin + w)] =
														Pixel32(outlineCol.r, outlineCol.g, outlineCol.b,
															s.coverage / 256.0f*outlineCol.a);*/
												for (Span &s : outlineSpans)
													for (int w = 0; w < s.width; ++w)
														if(s.coverage)pxl[((imgHeight - 1 - (s.y - (int)rect.ymin)) * imgWidth
															+ s.x - (int)rect.xmin + w)] =
														Pixel32(outlineCol.r, outlineCol.g, outlineCol.b,
															s.coverage / 255.0f*outlineCol.a);
												/*for (Span &s : outlineSpans)
													for (int w = 0; w < s.width; ++w)
														if (s.coverage)pxl[((imgHeight - 1 - (s.y - (int)rect.ymin)) * imgWidth
															+ s.x - (int)rect.xmin + w)] =
															Pixel32(s.coverage, s.coverage, s.coverage,
																s.coverage);*/

												// Then loop over the regular glyph spans and blend them into
												// the image.
												for (Span &s : spans)
													for (int w = 0; w < s.width; ++w)
													{
														if(s.coverage){
														Pixel32 &dst =
															pxl[((imgHeight - 1 - (s.y - (int)rect.ymin)) * imgWidth
																+ s.x - (int)rect.xmin + w)];
														dst.r = (dst.r + ((fontCol.r - dst.r) * s.coverage) / 255.0f);
														dst.g = (dst.g + ((fontCol.g - dst.g) * s.coverage) / 255.0f);
														dst.b = (dst.b + ((fontCol.b - dst.b) * s.coverage) / 255.0f);
														dst.a =  min(255, dst.a+ fontCol.a);
														}
														
													}
												/*for (Span &s : spans)
													for (int w = 0; w < s.width; ++w)
													{
														Pixel32 &dst =
															pxl[(int)((imgHeight - 1 - (s.y - rect.ymin)) * imgWidth
																+ s.x - rect.xmin + w)];
														Pixel32 src = Pixel32(fontCol.r, fontCol.g, fontCol.b,
															s.coverage);
														src.r = (int)(dst.r + ((src.r - dst.r) * src.a) / 255.0f);
														src.g = (int)(dst.g + ((src.g - dst.g) * src.a) / 255.0f);
														src.b = (int)(dst.b + ((src.b - dst.b) * src.a) / 255.0f);
														dst.r = dst.g = dst.b = dst.a = MIN(255, 0.299 * src.r + 0.587 * src.g + 0.114 * src.b + s.coverage);
													}*/
												

												// Dump the image to disk.
												for (long i(0), rows(imgWidth * 4), pws(w * 4); i < imgHeight; i++) {
													long ptr = py + base - bearingY + i;
													if(ptr >=0&& ptr<h)memcpy(data + ptr*pws + (px + bearingX) * 4, ((uint8_t*)pxl)+rows*i, rows);
												}
												delete[] pxl;
												break;
											}
										}

									}

								}
								else err += ch;
							
							}
							px += sfw;
							if (px >= w)px = 0, py += sfh;
						
		}
		/*	struct data {
				size_t x, y;
				Pixel32 pxl;
			};
		std::vector<struct data>vec;
	for(size_t y=0,x;y<h;y++)
		for (x = 0; x < h; x++) {
			

		}*/
		/*uint8_t*alpha = new uint8_t[w*h*2];
		memset(alpha, 0, w*h);
		for (size_t i(0), sz(w*h); i < sz; i++)alpha[i * 2] = ((Pixel32*)data)[i].a / 255.0f*((Pixel32*)data)[i].getGray(),
			alpha[i * 2 + 1] = alpha[i * 2];// ((Pixel32*)data)[i].a;
		PNG::write_png(out, alpha, w, h,2);
		delete[] alpha;*/
		PNG::write_png(out, data, w, h, 4);
		delete[] data;
	}
	void
		WriteGlyphAsTGA(FT_Library &library,
			const std::string &fileName,
			wchar_t ch,
			FT_Face &face,
			int size,
			const Pixel32 &fontCol,
			const Pixel32 outlineCol,
			float outlineWidth)
	{
		// Set the size to use.
		if (FT_Set_Char_Size(face, size << 6, size << 6, 90, 90) == 0)
		{
			// Load the glyph we are looking for.
			FT_UInt gindex = FT_Get_Char_Index(face, ch);
			if (FT_Load_Glyph(face, gindex, FT_LOAD_NO_BITMAP) == 0)
			{
				// Need an outline for this to work.
				if (face->glyph->format == FT_GLYPH_FORMAT_OUTLINE)
				{
					// Render the basic glyph to a span list.
					Spans spans;
					RenderSpans(library, &face->glyph->outline, &spans);

					// Next we need the spans for the outline.
					Spans outlineSpans;

					// Set up a stroker.
					FT_Stroker stroker;
					FT_Stroker_New(library, &stroker);
					FT_Stroker_Set(stroker,
						(int)(outlineWidth * 64),
						FT_STROKER_LINECAP_ROUND,
						FT_STROKER_LINEJOIN_ROUND,
						0);

					FT_Glyph glyph;
					if (FT_Get_Glyph(face->glyph, &glyph) == 0)
					{
						FT_Glyph_StrokeBorder(&glyph, stroker, 0, 1);
						// Again, this needs to be an outline to work.
						if (glyph->format == FT_GLYPH_FORMAT_OUTLINE)
						{
							// Render the outline spans to the span list
							FT_Outline *o =
								&reinterpret_cast<FT_OutlineGlyph>(glyph)->outline;
							RenderSpans(library, o, &outlineSpans);
						}

						// Clean up afterwards.
						FT_Stroker_Done(stroker);
						FT_Done_Glyph(glyph);

						// Now we need to put it all together.
						if (!spans.empty())
						{
							// Figure out what the bounding rect is for both the span lists.
							Rect rect(spans.front().x,
								spans.front().y,
								spans.front().x,
								spans.front().y);
							for (Spans::iterator s = spans.begin();
								s != spans.end(); ++s)
							{
								rect.Include(Vec2(s->x, s->y));
								rect.Include(Vec2(s->x + s->width - 1, s->y));
							}
							for (Spans::iterator s = outlineSpans.begin();
								s != outlineSpans.end(); ++s)
							{
								rect.Include(Vec2(s->x, s->y));
								rect.Include(Vec2(s->x + s->width - 1, s->y));
							}

#if 0
							// This is unused in this test but you would need this to draw
							// more than one glyph.
							float bearingX = face->glyph->metrics.horiBearingX >> 6;
							float bearingY = face->glyph->metrics.horiBearingY >> 6;
							float advance = face->glyph->advance.x >> 6;
#endif

							// Get some metrics of our image.
							int imgWidth = rect.Width(),
								imgHeight = rect.Height(),
								imgSize = imgWidth * imgHeight;

							// Allocate data for our image and clear it out to transparent.
							Pixel32 *pxl = new Pixel32[imgSize];
							memset(pxl, 0, sizeof(Pixel32) * imgSize);

							// Loop over the outline spans and just draw them into the
							// image.
							for (Span &s : outlineSpans)
								for (int w = 0; w < s.width; ++w)
									pxl[(int)((imgHeight - 1 - (s.y - rect.ymin)) * imgWidth
										+ s.x - rect.xmin + w)] =
									Pixel32(outlineCol.r, outlineCol.g, outlineCol.b,
										s.coverage);

							// Then loop over the regular glyph spans and blend them into
							// the image.
							for (Span &s: spans)
								for (int w = 0; w < s.width; ++w)
								{
									Pixel32 &dst =
										pxl[(int)((imgHeight - 1 - (s.y - rect.ymin)) * imgWidth
											+ s.x - rect.xmin + w)];
									Pixel32 src = Pixel32(fontCol.r, fontCol.g, fontCol.b,
										s.coverage);
									dst.r = (int)(dst.r + ((src.r - dst.r) * src.a) / 255.0f);
									dst.g = (int)(dst.g + ((src.g - dst.g) * src.a) / 255.0f);
									dst.b = (int)(dst.b + ((src.b - dst.b) * src.a) / 255.0f);
									dst.a = MIN(255, dst.a + src.a);
								}
								

							// Dump the image to disk.
							
							PNG::write_png(fileName, ( uint8_t*)pxl, imgWidth, imgHeight);

							delete[] pxl;
						}
					}
				}
			}
		}
	}




};
/*
#include<gl/gl.h>
#include<gl/glu.h>
#include<gl/glut.h>
#include<gl/glew.h>
class openGL {
public:
	void InitGLUT(int argc, char** argv)
	{
		glutInit(&argc, argv);
		glutWindow = glutCreateWindow("GPGPU");
	}
	void InitFBO(int nWidth, int nHeight, GLuint*pFb)
	{
		//创建FBO并绑定
		glewInit();
		GLuint fb;
		glGenFramebuffersEXT(1, &fb);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
		*pFb = fb;

		//用绘制来调用
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, nWidth, 0, nHeight);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glViewport(0, 0, nWidth, nHeight);
	}
	GLuint vertShader,fragShader;
	void InitGLSL()
	{
		//创建顶点shader
		vertShader = glCreateShader(GL_VERTEX_SHADER);
		if (0 == vertShader)
		{
			fprintf(stderr, "Error creating vertex shader.\n");
			exit(1);
		}

		GLint result;

		//加载片元着色器
		fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		if (0 == fragShader)
		{
			fprintf(stderr, "片元着色器创建失败.\n");
			exit(1);
		}
		
		//c拷贝shader源码
		const char *shaderCode2 = loadShaderAsString("BrightNess.glsl");
		glShaderSource(fragShader, 1, &shaderCode2, NULL);

		delete[]shaderCode2;

		//编译shader
		glCompileShader(fragShader);

		//检查编译状态
		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
		if (GL_FALSE == result)
		{
			fprintf(stderr, "片元着色器编译失败!\n");
			GLint logLen;
			glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLen);
			if (logLen > 0)
			{
				char * log = (char *)malloc(logLen);
				GLsizei written;
				glGetShaderInfoLog(fragShader, logLen, &written, log);
				fprintf(stderr, "Shaderlog:\n%s", log);
				free(log);
			}
		}

		//创建程序对象
		programHandle = glCreateProgram();
		if (0 == programHandle)
		{
			fprintf(stderr, "Error creating program object.\n");
			exit(1);
		}

		//将着色器链接到程序对象
		glAttachShader(programHandle, fragShader);

		//链接程序
		glLinkProgram(programHandle);

		//检查链接状态
		GLint status;
		glGetProgramiv(programHandle, GL_LINK_STATUS, &status);
		if (GL_FALSE == status)
		{
			fprintf(stderr, "链接失败!\n");
			GLint logLen;
			glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH,
				&logLen);
			if (logLen > 0)
			{
				char * log = (char *)malloc(logLen);
				GLsizei written;
				glGetProgramInfoLog(programHandle, logLen,
					&written, log);
				fprintf(stderr, "Program log: \n%s", log);
				free(log);
			}

			glDeleteProgram(programHandle);
		}

		else
		{
			glUseProgram(programHandle);
		}
	}

};*/