#pragma once
#include "stdafx.h"
#include <freetype/freetype.h>  
#include <freetype/ftglyph.h>  
#include "gl/gl.h"
class WChar {
public:
	bool use = false;
	BYTE str[2] = { 0 };
	BYTE ID = 0;
};

class WIDC {
public:
	BYTE ID[1];
	int Xstart = 0;
	int Ystart = 0;

};
class SEL {
public:
	void Init(int ID, wchar_t* str) {
		if (ID == 0) {
			SetPage(str);
			return;
		}
		int i = 0;
		int C = 0X10;
		while (str[i] != '\0'&&i<256) {
			if (str[i] == 0XD || str[i] == 0XA) {
				i++;
				continue;
			}
			if (str[i] == ' ') {
				i++;continue;
			}
			if (str[i] == '?') {
				//		alc = true;
				i++;C++;continue;
			};
			//	alc = false;
			WChar* WT = &Wstr[str[i]];
			if (WT->use&&str[i] != '?') {
				//printf(Pstr[WIDToID(WT->ID)]);
				printf("警告:%X->%X:%X str:%d 重复\n", C, WT->ID, WT->str[1], str[i]);

			}
			else {
				WT->use = true;
				WT->ID = WID[ID - 1].ID[0];
				WT->str[0] = ID == 8 ? 0 : WID[ID - 1].ID[0];
				WT->str[1] = C;
			}
			i++, C++;// C++;
		}
	}
	
	void SetPage(wchar_t*str) {
		int i = 0;
		wchar_t sum[256];
		int ID = 0, j = 0;
		while ((sum[j++] = str[i++]) != '\0') {
			if (str[i] == ',' || str[i + 1] == '\0') {
				WID[ID].ID[0] = wcstol(sum, 0, 16);
				ID++, i++, j = 0;
			}
		}


	};
	int WIDToID(int ID) {
		for (int a = 1;a < 8;a++) {
			if (WID[a].ID[0] == ID) {
				return a;
			}
		}
		return 0;
	}

	void TypeInit(const char* fontFile, int fontSize)
	{
		xStart = 256;
		yStart = 512;
		FT_Init_FreeType(&library);
		FT_New_Face(library, fontFile, 0, &face);
		FT_Set_Char_Size(face, fontSize << 6, fontSize << 6, 72, 72);
		FT_Set_Pixel_Sizes(face, fontSize, fontSize);

	}
	void DrawChar(wchar_t ch)
	{
		FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT);
		FT_Glyph glyph;
		FT_Get_Glyph(face->glyph, &glyph);
		FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
		FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
		FT_Bitmap& bitmap = bitmap_glyph->bitmap;

		//*   如果没有数据，则不写，直接过去

		if (bitmap.width != 0 || bitmap.rows != 0)
		{
			FT_Bitmap &     bitmap = bitmap_glyph->bitmap;
			//BYTE* 
			PNGDATA IMAGE;
			IMAGE.DATA = new BYTE[bitmap.rows* bitmap.width * 4];
			IMAGE.H = (long)bitmap.rows;
			IMAGE.W = (long)bitmap.width;
			IMAGE.B = 8;
			BYTE Alpha[1];
			BYTE RGB[1];
			int Xsize = 0;
			for (unsigned int i = 0; i <bitmap.rows; ++i)
			{
				for (unsigned int j = 0; j <bitmap.width; ++j)
				{
					Alpha[0] = bitmap.buffer[i * bitmap.width + j];
					//bool A = ;
					RGB[0] = (Alpha[0] != 0) ? 0XFF : 0;
					IMAGE.DATA[Xsize++] = RGB[0];
					IMAGE.DATA[Xsize++] = RGB[0];
					IMAGE.DATA[Xsize++] = RGB[0];
					IMAGE.DATA[Xsize++] = Alpha[0];//bitmap.buffer[i * bitmap.width + j];

				}
			}
			//			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexSubImage2D(GL_TEXTURE_2D, 0,
				X * 16,
				512 + Y * 16,
				bitmap.width,
				bitmap.rows,
				GL_ALPHA, GL_UNSIGNED_BYTE, bitmap.buffer);

			free(IMAGE.DATA);
			//			_xStart += FontSize + 1;
		}
	}
	int X = 0, Y = 0, xStart, yStart;
	FT_Library  library;
	FT_Face     face;
	WIDC WID[8];
	WChar Wstr[65535];

};