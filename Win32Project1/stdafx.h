// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#define DEFASM __declspec(naked) 
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>
#include <png.h>
#include "resource.h"
#include <map>
#include<memory>
#include "gl/gl.h"
//#include "gl/glu.h"
//#include <iostream>
#include <vector>
#include <sstream> 
#include <fstream>
#include <algorithm>
#include "targetver.h"
#include "json\json.h"
#include<mutex>
extern DWORD Base;
extern HANDLE mProc;
extern bool ReTex;
extern std::wstring SYSTEMROOT;
extern LPCSTR Lang;
extern LPCWSTR localePath;
extern float Old1, Old2;
extern size_t maxLogSize, errCnt, wngCnt;;
extern SYSTEMTIME sys_time;
extern MD5 md5;
enum class MsgType {Info,Error,Warning,Debug,Null};
//0 Info 1 Error 2 Warning 3 Debug
//void msgmgr(MsgType _Ty, const char* msg, ...);
void msgmgr(MsgType _Ty, const std::wstring msg, ...);
void openErr(const std::wstring&path);
//void msgmgr(int _Ty, const std::wstring &msg, ...);
BOOL WriteAdd(LPVOID lpAddress, uint8_t *Code, size_t Size);
BOOL ReadAdd(LPVOID lpAddress, uint8_t *Code, size_t Size);
BOOL WriteAdd(DWORD Offset, const uint8_t *Code, size_t Size);
BOOL ReadAdd(DWORD Offset, uint8_t *Code, size_t Size);
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
	static std::string& Encode(wchar_t ch,std::string &utf8) {
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

class PNG{
#define PNG_BYTES_TO_CHECK 8
//#define PNG_HEADER "\x89\x50\x4E\x47\x0D\x0A\x1A\x0A"
	BYTE *data;
	size_t fmt = 0,w=0,h=0,b=0,Err=0;
	
public:
	long getFormat()const { return fmt; }
	long getWidth()const { return w; }
	long getHeight()const { return h; }
	long getBit()const { return b; }
	long getError()const { return Err; }
	BYTE*getData()const { return data; }
	PNG(std::string &path):data(nullptr),w(0),h(0),b(0),Err(0)
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
	bool open(const std::string&path){
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
							
							png_byte channels = png_get_channels(png_ptr, info_ptr);
							b = png_get_bit_depth(png_ptr, info_ptr)/8;
							data = new png_byte[w*h *channels];
							if (data != NULL) {
							row_pointers = png_get_rows(png_ptr, info_ptr);
							for (size_t y(0),cw = png_get_rowbytes(png_ptr, info_ptr); y < h; y++)
								memcpy(data+cw*y, row_pointers[y], cw);
							switch (color_type) {
							case PNG_COLOR_TYPE_RGB_ALPHA:fmt = GL_RGBA; break;
							case PNG_COLOR_TYPE_RGB:fmt = GL_RGB; break;
							case PNG_COLOR_TYPE_GRAY_ALPHA:fmt = GL_LUMINANCE_ALPHA; break;
							case PNG_COLOR_TYPE_GRAY:fmt =GL_LUMINANCE; break;
							default:fmt = NULL;
							}
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
		return write_png(file, data, w, h, b);
	}
	static int write_png(const std::string &file_name, uint8_t* data, size_t Width, size_t Height, size_t bit = 4) {
		return write_png(file_name.c_str(), data, Width, Height, bit);
	}
	static int write_png(const std::wstring &file_name, uint8_t* data, size_t Width, size_t Height, size_t bit = 4) {
		return write_png(file_name.c_str(), data, Width, Height, bit);
	}
	static int write_png(const char *file_name, uint8_t* data, size_t Width, size_t Height, size_t bit = 4) {
		FILE *fp;
		fopen_s(&fp, file_name, "wb");
		return write_png(fp, data, Width, Height, bit);
	}
	static int write_png(const wchar_t *file_name, uint8_t* data, size_t Width, size_t Height, size_t bit = 4) {
		FILE *fp;
		_wfopen_s(&fp, file_name, L"wb");
		return write_png(fp, data, Width, Height, bit);
	}
	static int write_png(FILE *fp, uint8_t* data, size_t Width, size_t Height, size_t bit = 4)
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
			DWORD CODE = (DWORD)Fun - (Base+ Offset) - 5;
			BYTE* P = (BYTE*)&CODE;
			for (int i = 0;i < 4;i++) {
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
			for (size_t i = 5;i < Size;i++)Code[i] = 0x90;
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
	void Add(LPVOID Fun, DWORD Offset, BYTE Met, size_t s) {list.push_back(std::unique_ptr<Address>(new Address(Fun, Offset, Met, s)));};
	~Hook() {for(auto &p: list)p.reset(nullptr);list.clear();}
	void HookAll() {for (auto &p : list)p->Hook();}
	void unHookAll() {for (auto &p : list)p->unHook();}
};
struct Offset { float Off = 0.0, Width = 12.0f; };
class Localization{
private:
	struct WChar {
		bool use;
		uint8_t str[2]//页ID XY
		,PID;//页ID
		wchar_t ch;
		WChar() :use(false), str{0},PID(0),ch(0) {
		}
		WChar(uint8_t pid, uint8_t fid, wchar_t ch):use(true),PID(pid),ch(ch) {
			str[0] = pid, str[1] = fid;
		}
	};
	WChar *Wstr;
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
		Offset*getInfo(){return Info == nullptr? newPage():Info; };
		Offset*newPage(size_t size=256){ 
			if (Info != nullptr)delete[] Info, Info =nullptr;
			return Info =new Offset[size];
		};
		size_t Init(size_t id, uint8_t pid,const std::wstring&font, const std::string&params) {
			OffsetX = (id%4) * 16, OffsetY = (id/4) * 16;
			ID = id,PID=pid;
			File = font;
			std::stringstream ss(params);
			newPage();
			size_t i = 0;
			while (i<256&&ss >> Info[i].Off >> Info[i].Width)i++;
			use = true;
			return i;
		}
		PageInfo():Info(nullptr) {
			Clear();
		};
		~PageInfo() {
			Clear();
		}
		std::wstring File;
		size_t OffsetX = 0, OffsetY = 0,ID=0; //坐标起始位置 序号
		BYTE PID = 0;// 页ID
		bool use = false;
	};
	std::map<wchar_t, size_t>err;
	std::map<std::string, std::string>Map;
public:
	BYTE *GetCharCode(size_t UTF16) {
		if (UTF16>0 && UTF16<0XFFFF && Wstr[UTF16].use)return Wstr[UTF16].str;
		return 0;
	}
	static std::wstring sCfgErr, sFontMsg, sIdMsg, sParamsMsg, sMapMsg, sMapErr, sUnCfgErr, sWDefErr, sReDefErr, sTexErr, sFmtErr, sLoadErr, sPageMsg, sMapSzErr;
	void Clear() {
		Map.clear();
		err.clear();
		PageList.clear();
		for (auto &p:Page)p.Clear();}
	std::string Config;
	void InitMsg(const Json::Value&val) {
		sCfgErr = val["sCfgErr"].isString()? UTF::Decode(val["sCfgErr"].asString()):L"%s.Pages[%d] %s 配置错误,目标类型为 %s,%s",
			sFontMsg = val["sFontMsg"].isString() ? UTF::Decode(val["sFontMsg"].asString()) : L"指定一个字体纹理文件名",
			sIdMsg = val["sIdMsg"].isString() ? UTF::Decode(val["sIdMsg"].asString()) : L"指定一个页映射Id",
			sParamsMsg = val["sParamsMsg"].isString() ? UTF::Decode(val["sParamsMsg"].asString()) : L"指定字体偏移与宽度,不配置则使用默认值",
			sMapMsg = val["sMapMsg"].isString() ? UTF::Decode(val["sMapMsg"].asString()) : L"指定字体在纹理上的位置,不配置则无法使用字符映射表";
			sMapErr = val["sMapErr"].isString() ? UTF::Decode(val["sMapErr"].asString()) : L"%s.Pages[%d](%d,%d)->%c已存在于Pages[%d](%d,%d)->%c",
			sUnCfgErr= val["sUnCfgErr"].isString() ? UTF::Decode(val["sUnCfgErr"].asString()) : L"未配置字符(按出现频率排序) %s";
			sWDefErr= val["sWDefErr"].isString() ? UTF::Decode(val["sWDefErr"].asString()) : L"无法访问 %08X->%s";
			sReDefErr = val["sReDefErr"].isString() ? UTF::Decode(val["sReDefErr"].asString()) : L"%s 重定义";
			sTexErr = val["sTexErr"].isString() ? UTF::Decode(val["sTexErr"].asString()) : L"纹理%s[%d]:PID:%d %d*%d*%d X:%d Y:%d Path:%s";
			sFmtErr = val["sFmtErr"].isString() ? UTF::Decode(val["sFmtErr"].asString()) : L"格式不规范";
			sLoadErr = val["sLoadErr"].isString() ? UTF::Decode(val["sLoadErr"].asString()) : L"加载失败";
			sPageMsg = val["sPageMsg"].isString() ? UTF::Decode(val["sPageMsg"].asString()) : L"指定字体纹理的显示参数,若不配置则不显示相关字符";
			sMapSzErr= val["sMapSzErr"].isString() ? UTF::Decode(val["sMapSzErr"].asString()) : L"%s.Pages[%d].Maps 的字符数量(%d)超出了最大值256,超出部分将截断:%s";
			//sStr2lErr = val["sStr2lErr"].isString() ? UTF::Decode(val["sStr2lErr"].asString()) : L"字符串产生的结果超过了允许的最大长度15 %s->(len=%d)";
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
			else for (uint8_t c : Wstr[v].str)if (c)str += c;
		}
		//if (!err.empty())msgmgr(MsgType::Error, sUnCfgErr, wval.c_str(), err.c_str());
		if (!str.empty())Map[key] = str;
		return str;
	}
	std::map<DWORD, std::string>written;
	void WriteDefine(const std::string&key, const Json::Value& sub) {
		if (sub.isString())WriteDefine(key, std::strtol(sub.asString().c_str(), 0, 1 << 4));
		else if (sub.isInt64())WriteDefine(key, sub.asInt64());
	}
	void WriteDefine(const std::string&key, DWORD off) {
		std::string &ptr = *(std::string*)(Base + off);
		if (!IsBadWritePtr((LPVOID)(Base + off), 20)) {
			written.insert(std::pair<DWORD, std::string>(off, ptr));
			auto it = Map.find(key);
			ptr = it != Map.end() ? it->second : InitDefine(key, key);
		}
		else msgmgr(MsgType::Error, sWDefErr, off, UTF::Decode(key).c_str());
	}
	void ApplyDefine(const Json::Value&val) {
		const auto &def = val.getMemberNames();
		for (auto &key : def) {
			auto &sub = val[key];
			if (sub.isArray())for (auto arr : sub)WriteDefine(key, arr);
			else WriteDefine(key, sub);
		}
	}
	void UndoDefine() {
		for (auto&val : written) {
			if (!IsBadWritePtr((LPVOID)(Base + val.first), 20)){
			*(std::string*)(Base + val.first) = val.second;
			//if (!WriteAdd(val.first, (uint8_t*)val.second.c_str(), val.second.size()+1))
			}else msgmgr(MsgType::Error, sWDefErr, val.first, UTF::Decode(val.second).c_str());
		}
		written.clear();
	}
	BOOL MainInit() {
		Clear();
		UndoDefine();
		std::wstring cfgPath = SYSTEMROOT + L"System/localization.json";
		std::ifstream Input(cfgPath, std::ios::binary);
		if (Input) {
			memset(Wstr, 0, sizeof(WChar) * 1 << 16);
			size_t curPID = 1;
			Json::Value val;
			Json::Reader reader;
			reader.parse(Input, val);
			Input.close();
			const Json::Value &lang = val["Language"][Lang],&logSz = val["maxLogSize"];
			if (logSz.isInt())maxLogSize = logSz.asInt();
			if (!lang.isNull()){
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
					const std::string &M = md5.GetCapMd5();
					if (val["Address"][M].isObject())ApplyDefine(val["Address"][M]);
					if (!err.empty()) {
						std::wstring ws;
						auto &refmap = err;
						for (auto &ch : err)ws += ch.first;
						auto sortA = [&refmap](wchar_t l, wchar_t r)->bool {
							return refmap[l] > refmap[r];
						};
						std::sort(ws.begin(), ws.end(), sortA);
						msgmgr(MsgType::Error, sUnCfgErr, ws.c_str());
					}
					return TRUE;
				}
				else  msgmgr(MsgType::Error, sCfgErr, wLang.c_str(), curPID, L"Pages", L"{Id,Font,Maps,Params}", sPageMsg.c_str());
			}
		}
		else openErr(cfgPath);
		return FALSE;
	}

	Offset* GetPage(uint8_t ID) {
		for(auto &p:Page)if (p.PID == ID&&p.use)return p.getInfo();
		return nullptr;
	}
	Localization():Wstr(new WChar[1 << 16]){
	}
	~Localization() {
		if (Wstr)delete[] Wstr;
		Wstr = nullptr;
	}
	std::basic_string<uint8_t> PageList;
	PageInfo Page[256];

};
extern Localization StrMap;

