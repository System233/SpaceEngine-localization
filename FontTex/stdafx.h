// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include<ft2build.h>
#include<assert.h>
#include<Windows.h>
#include <vector>
#include FT_FREETYPE_H
#include FT_STROKER_H

#include<png.h>

// TODO: 在此处引用程序需要的其他头文件
class PNG {
public:
	size_t Width, Height;
	BYTE *data = NULL;
	PNG(size_t w, size_t h) {
		Width = w, Height = h;
		data = new BYTE[w*h * 4];
		//struct px = { 0,0,0,0 };
		/*for(size_t y=0,x=0;y<h*4,y++)
			for(x=0;x<w;x++)data[]*/
		memset(data, 0, w*h * 4);
	}
	~PNG() {
		if (data)delete[] data;
	}
	int write_png(const char *file_name)

	{
		int a = 1;
		FILE *fp;
		png_structp png_ptr;
		png_infop info_ptr;
		fopen_s(&fp, file_name, "wb");
		if (fp == NULL)
			return -1;
		png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

		if (png_ptr == NULL)
		{
			fclose(fp);
			return -2;
		}
		info_ptr = png_create_info_struct(png_ptr);
		if (info_ptr == NULL)
		{
			fclose(fp);
			png_destroy_write_struct(&png_ptr, NULL);
			return -3;
		}
		if (setjmp(png_jmpbuf(png_ptr)))
		{
			fclose(fp);
			png_destroy_write_struct(&png_ptr, &info_ptr);
			return -4;
		}
		png_init_io(png_ptr, fp);
		png_set_IHDR(png_ptr, info_ptr, Width, Height, 8, PNG_COLOR_TYPE_RGBA,
			PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
		png_write_info(png_ptr, info_ptr);
		png_bytep* row_pointers = new png_bytep[Height];

		if (Height > PNG_UINT_32_MAX / (sizeof(png_bytep)))
			png_error(png_ptr, "Image is too tall to process in memory");
		long X = 0;
		for (size_t k = 0; k < Height; k++)
			row_pointers[k] = data + k*Width * 4;
		png_write_image(png_ptr, row_pointers);
		png_write_end(png_ptr, info_ptr);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		return 1;
	}

	static int write_png(const char *file_name,BYTE* data,long Width,long Height)

	{
		int a = 1;
		FILE *fp;
		png_structp png_ptr;
		png_infop info_ptr;
		fopen_s(&fp, file_name, "wb");
		if (fp == NULL)
			return -1;
		png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

		if (png_ptr == NULL)
		{
			fclose(fp);
			return -2;
		}
		info_ptr = png_create_info_struct(png_ptr);
		if (info_ptr == NULL)
		{
			fclose(fp);
			png_destroy_write_struct(&png_ptr, NULL);
			return -3;
		}
		if (setjmp(png_jmpbuf(png_ptr)))
		{
			fclose(fp);
			png_destroy_write_struct(&png_ptr, &info_ptr);
			return -4;
		}
		png_init_io(png_ptr, fp);
		png_set_IHDR(png_ptr, info_ptr, Width, Height, 8, PNG_COLOR_TYPE_GA,
			PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
		png_write_info(png_ptr, info_ptr);
		png_bytep* row_pointers = new png_bytep[Height];

		if (Height > PNG_UINT_32_MAX / (sizeof(png_bytep)))
			png_error(png_ptr, "Image is too tall to process in memory");
		long X = 0;
		for (size_t k = 0; k < Height; k++)
			row_pointers[k] = data + k*Width*4;
		png_write_image(png_ptr, row_pointers);
		png_write_end(png_ptr, info_ptr);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		return 1;
	}
};
class wcscstr {
private:
	CHAR *str = 0;
	WCHAR *wstr = 0;
	void Release() {

		if (str) { delete[] str; str = NULL; }
		if (wstr) { delete[] wstr; wstr = NULL; }
	}
public:
	~wcscstr() {
		Release();
	}

	char* WcharToChar(const wchar_t *wc, size_t l)
	{
		Release();
		if (l == NULL)l = wcslen(wc);
		int len = WideCharToMultiByte(CP_ACP, 0, wc, l, NULL, 0, NULL, NULL);
		str = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, wc, l, str, len, NULL, NULL);
		str[len] = '\0';
		return str;
	}

	wchar_t* CharToWchar(const char* c, size_t L)
	{
		Release();
		if (L == NULL)L = strlen(c);
		int len = MultiByteToWideChar(CP_ACP, 0, c, L, NULL, 0);
		wstr = new wchar_t[len + 1];
		MultiByteToWideChar(CP_ACP, 0, c, L, wstr, len);
		wstr[len] = '\0';
		return wstr;
	}
	wchar_t* AutoCharToWchar(const char* c)
	{
		Release();
		size_t L = strlen(c);
		int len = MultiByteToWideChar(CP_ACP, 0, c, L, NULL, 0);
		wstr = new wchar_t[len + 1];
		MultiByteToWideChar(CP_ACP, 0, c, L, wstr, len);
		wstr[len] = '\0';
		return wstr;
	}
};
struct Span
{
	Span() { }
	Span(int _x, int _y, int _width, int _coverage)
		: x(_x), y(_y), width(_width), coverage(_coverage) { }

	int x, y, width, coverage;
};
union Pixel32;
typedef std::vector<Span> Spans;
extern bool Xstr[1 << 16];

// Define some fixed size types.

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
// Render the specified character as a colored glyph with a colored outline
// and dump it to a TGA.

// A simple 32-bit pixel.
union Pixel32
{
	Pixel32()
		: integer(0) { }
	Pixel32(uint8 bi, uint8 gi, uint8 ri, uint8 ai = 255)
	{
		b = bi;
		g = gi;
		r = ri;
		a = ai;
	}

	uint32 integer;

	struct
	{
#ifdef BIG_ENDIAN
		uint8 a, r, g, b;
#else // BIG_ENDIAN
		uint8 b, g, r, a;
#endif // BIG_ENDIAN
	};
};
class FreeType {
	struct IMG{
		Pixel32*data;
		long w, h;
		IMG(long w, long h):w(w),h(h)
		{
			data = new Pixel32[w*h];
			memset(data, 0, sizeof(Pixel32) * w*h);
			//data = new BYTE[w*h];
		}
		~IMG() {
			if (data)delete[] data;
			data = nullptr;
		}

	};
	class Face {
		friend void
			RasterCallback(int y0,
				int count,
				const FT_Span * spans,
				void *  user);
	public:
		FT_Face face = NULL;
		FT_Library library = NULL;
		Face(std::string file) {
			FT_Init_FreeType(&library);
			assert(library != 0);
			FT_New_Face(library, file.c_str(), 0, &face);
			assert(face != 0);

		}
		~Face() {
			if (library != 0)FT_Done_FreeType(library);
		}
		FT_Error Set_Pixel_Sizes(size_t w, size_t h) {
			return FT_Set_Pixel_Sizes(face, w, h);
		}
		FT_Error Set_Char_Size(size_t fw, size_t fh, size_t w, size_t h) {
			return FT_Set_Char_Size(face, fw << 6, fh << 6, h, w);
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
		void Render_Outline(long w,long h,long x,long y,BYTE*byte, FT_Glyph *glyph);
		IMG*
			Render_Outline(
				FT_UInt index,
				const Pixel32 &fontCol,
				const Pixel32 outlineCol,
				float outlineWidth);
		void Render_Outline() {

			FT_Stroker stroker;
			FT_Stroker_New(library, &stroker);
			FT_Stroker_Set(stroker,
				(int)(1 * 64),
				FT_STROKER_LINECAP_ROUND,
				FT_STROKER_LINEJOIN_ROUND,
				0);	FT_Glyph glyph;
			if (FT_Get_Glyph(face->glyph, &glyph) == 0)
			{
				FT_Glyph_StrokeBorder(&glyph, stroker, 0, 1);
				// Again, this needs to be an outline to work.
				if (glyph->format == FT_GLYPH_FORMAT_OUTLINE)
				{
					// Render the outline spans to the span list
					FT_Outline *o =
						&reinterpret_cast<FT_OutlineGlyph>(glyph)->outline;
				}

				// Clean up afterwards.
				FT_Stroker_Done(stroker);
				FT_Done_Glyph(glyph);
			}
		
		}
	};

	long px = 0, py = 0, w = 0, h = 0, maxh = 0;;
	PNG *png = NULL;
	size_t Fsize = 0, Csize = 0;
	FT_Library alibrary = NULL, blibrary = NULL, clibrary;
	//	FT_Face face = NULL, face2 = NULL, face3 = NULL;
	FT_Glyph glyph;
	FT_BitmapGlyph bitmap_glyph;
	//std::ofstream of;
	//FILE *op = NULL;
	long fe = 64;// 26.6f * 2;


	std::vector<Face*> faces;
public:
	FreeType(std::string f,  long ww,long wh, long tw,long th) {
		std::string tmp;
		std::string::iterator end = f.end();
		for (std::string::iterator i = f.begin(); i != end; i++)
			if ((*i) == ';' || i + 1 == end) {
				if (i + 1 == end)tmp.push_back(*i);
				printf("\t\t%s\n", tmp.c_str());
				Face*fc = new Face(tmp);
				fc->Set_Char_Size(ww, wh, 72, 72);
				//fc->Set_Pixel_Sizes(fontSize, fontSize);
				faces.push_back(fc);
				tmp.clear();
			}
			else tmp.push_back(*i);
			png = new PNG(tw, th);
			w =tw, h = th;
			px = 0;// 16 * 0xA + 16;
			Fsize = wh;
			printf("Init done\n");

	}
	void Start(const char*map) {

		FILE *fp = NULL;
		fopen_s(&fp, map, "rb");
		assert(fp != NULL);
		fseek(fp, 0, SEEK_END);
		size_t size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		WCHAR *ws = (WCHAR*)new BYTE[size];
		//std::wstringstream ss;
		fread(ws, sizeof(BYTE), size, fp);
		fclose(fp);

		//fopen_s(&op, XMLFile, "wb");
		//assert(op != NULL);
		//fwprintf(op, L"<?xml version=\"1.0\" encoding=\"utf - 8\"?>\n<Font size = \"9\" family = \"Noto Sans\" height = \"16\" style = \"Regular\">\n");
		size_t unc = 0;
		FT_UInt index = 0;

		printf("MAP:%s\n", map);
		std::vector<Face*>::iterator it = faces.begin(), itend = faces.end();
		for (size_t i = 0, wsize = size / 2 ; i<size / 2; i++) {
			index = 0;
			WCHAR str = ws[i];
			{
				if(i==0&&str==0xFFFE)continue;
				if (str == L' ') {
					if (px == w)px = 0, py += 16;
					px += 16;
					//if (px == w)px = 0,py+=16;
					continue;
				}
				for (it = faces.begin(); it != itend; it++) {
					index = (*it)->Get_Char_Index(str);
				
					if (index != 0) {
						(*it)->Load_Glyph(index, FT_LOAD_DEFAULT);
						(*it)->Render_Glyph(FT_RENDER_MODE_NORMAL);
						(*it)->Get_Glyph(&glyph);
						FT_Glyph cp_glyph;
						//FT_Glyph_Copy(glyph, &cp_glyph);
						FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, 0, 1);
						bitmap_glyph = (FT_BitmapGlyph)glyph;
						FT_Bitmap &bitmap = bitmap_glyph->bitmap;
						FT_Glyph_Metrics &met = (*it)->face->glyph->metrics;
						
						if (w - px < long(bitmap.width)) {
							py += 16;
							px = 0;
						}
						
						//of = of > 0 ? of : 0;
						if (h - py <bitmap.rows + (*it)->face->size->metrics.ascender* float(1.0 / 64.0) - (*it)->face->glyph->bitmap_top) {
							printf("空间不足[%d:%d:%d:%d:%d:%d]",w,h,px,py, (*it)->face->glyph->bitmap.rows , (*it)->face->glyph->bitmap_top);
							return;
						}
					/*	switch (str)
						{

						case ' ':fwprintf(op, L"<Char width=\"4\" offset=\"%ld %ld\" rect=\"%ld %ld %ld 4\" code=\" \"/>\n", 0, of, px, py + of, bitmap.rows);
							break;
						case '"':fwprintf(op, L"<Char width=\"%ld\" offset=\"%ld %ld\" rect=\"%ld %ld %ld %ld\" code=\"&quot;\"/>\n", bitmap.width + 1, 0, of, px, py + of, bitmap.width + 1, bitmap.rows);
							break;
						case '&':fwprintf(op, L"<Char width=\"%ld\" offset=\"%ld %ld\" rect=\"%ld %ld %ld %ld\" code=\"&amp;\"/>\n", bitmap.width + 1, 0, of, px, py + of, bitmap.width + 1, bitmap.rows);
							break;
						case '<':fwprintf(op, L"<Char width=\"%ld\" offset=\"%ld %ld\" rect=\"%ld %ld %ld %ld\" code=\"&lt;\"/>\n", bitmap.width + 1, 0, of, px, py + of, bitmap.width + 1, bitmap.rows);
							break;
						default:
							size_t S = swprintf(P, 512, L"<Char width=\"%ld\" offset=\"%ld %ld\" rect=\"%ld %ld %ld %ld\" code=\"A\"/>\n", bitmap.width + 1, 0, of, px, py + of, bitmap.width + 1, bitmap.rows);
							wcsrchr(P, '=')[2] = str;
							fwrite(P, sizeof(WCHAR), S, op);
							break;
						}*/
						
						;
						BYTE *bit = new BYTE[bitmap.width*bitmap.rows * 4];
						memset(bit, 0, bitmap.width*bitmap.rows * 4);
						for (size_t x = 0, size = 0; x <bitmap.rows; x++)
							for (size_t y = 0; y < bitmap.width; y++) {
								BYTE T = bitmap.buffer[x*bitmap.width + y];
								
								/*if (T) {
									bit[size] = T;
									bit[size + 1] = T;
									bit[size + 2] = T;
								}
								bit[size+3] = T;
								size += 4;*/
								bit[size++] = T;
								bit[size++] = T;
								bit[size++] = T;
								bit[size++] = T;
							};
						long base = long((*it)->face->size->metrics.ascender* float(1.0 / 64.0)) - (*it)->face->glyph->bitmap_top-1;
						if (base < 0)base = 0;
						//long base = 16-long((*it)->face->size->metrics.ascender* float(1.0 / 64.0));
						for (size_t i = 0; i < bitmap.rows; i++) memcpy(png->data + png->Width*(py + i + base)*4 + (px + (*it)->face->glyph->bitmap_left) * 4, bit + i*bitmap.width * 4, bitmap.width * 4);
					//	(*it)->Render_Outline(bitmap.width, long((*it)->face->size->metrics.ascender* float(1.0 / 64.0)) - 1, px, py, png->data, 0);
						/*FT_Stroker stroker;
						FT_Stroker_New(library, &stroker);
						FT_Stroker_Set(stroker,
							(int)(1 * 64),
							FT_STROKER_LINECAP_ROUND,
							FT_STROKER_LINEJOIN_ROUND,
							0);

						FT_Glyph_StrokeBorder(&cp_glyph, stroker, 1, 0);
						FT_Outline *o =
							&reinterpret_cast<FT_OutlineGlyph>(cp_glyph)->outline;*/
						
						/*FT_Stroker_Done(stroker);*/
					//	FT_Done_Glyph(cp_glyph);
						delete[] bit;
						px += 16;
						break;
						/*		px += 16;
						long offset = long((*it)->face->size->metrics.ascender* float(1.0 / 64.0)) - (*it)->face->glyph->bitmap_top,lf= (*it)->face->glyph->bitmap_left;
						IMG *img=(*it)->Render_Outline(index, fc, ol, 2);
						if (img==nullptr)continue;
						BYTE *bit = new BYTE[img->w*img->h * 4];
						for (size_t x = 0, size = 0; x <img->h; x++)
							for (size_t y = 0; y <img->w; y++) {
								Pixel32 &T = img->data[x*img->w + y];
								
								bit[size++] =T.r;
								bit[size++] = T.g;
								bit[size++] = T.b;
								bit[size++] = T.a;
							}
						for (size_t i = 0; i < img->h; i++) memcpy(png->data + png->Width*(py + i + offset * 4) + (px+ lf) * 4, bit + i*img->w * 4, img->w * 4);
						delete img;*/
						
						
					}
				}
				if (index == 0)unc++;
				printf("\rProcess:\t%.2f%% [%d/%d/%d]", i*100.0f / wsize, unc, i, wsize);
			}
		}
	//	fwprintf(op, L"</Font>");
	//	fclose(op);
		delete[] ws;
	}
	int write(const char *f) {
		return png->write_png(f);
	}

	~FreeType() {
		for (std::vector<Face*>::iterator i = faces.begin(); i != faces.end(); i++)if ((*i) != NULL)delete (*i);
	}

};