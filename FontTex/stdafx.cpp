// stdafx.cpp : 只包括标准包含文件的源文件
// FontTex.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

#ifdef _MSC_VER
#define MIN __min
#define MAX __max
#else
#define MIN std::min
#define MAX std::max
#endif
struct Arg {
	long w,h,x,y;
	BYTE* data;
};
// TODO: 在 STDAFX.H 中引用任何所需的附加头文件，
//而不是在此文件中引用
void
RasterCallback(const int y,
	const int count,
	const FT_Span * const spans,
	void * const user)
{
	Arg*arg = (Arg*)user;

	for (int i = 0; i < count; ++i){
		//printf("%d:%d:%d->%d:%d\n", spans[i].x, y, arg->h, arg->h-y, arg->w);
		/*if(y>=0){
		size_t p = spans[i].x * 4 +y*arg->w * 4;
	
		arg->data[p] = spans[i].coverage;
		arg->data[p+1] = spans[i].coverage;
		arg->data[p+2] = spans[i].coverage;
		arg->data[p+3] = spans[i].coverage;
		}*/
		size_t p = (arg->x+spans[i].x) * 4 + 256*(arg->y+ arg->h-y)* 4;
		arg->data[p] = 
		arg->data[p + 1] = 
		arg->data[p + 2] =
		arg->data[p + 3] = spans[i].coverage;
	}
}
void FreeType::Face::Render_Outline(long w,long h, long x, long y, BYTE*byte, FT_Glyph *glyph) {
	FT_Raster_Params params{ 0 };
	params.flags = FT_RASTER_FLAG_AA | FT_RASTER_FLAG_DIRECT;
	struct Arg a = { w,h,x,y, byte };
	params.user = &a;
	params.gray_spans = RasterCallback;
	
	//FT_Glyph glyph;
	//Get_Glyph(&glyph);
/*	FT_Stroker stroker;
	FT_Stroker_New(library, &stroker);
	FT_Stroker_Set(stroker,
		(int)(2 * 64),
		FT_STROKER_LINECAP_ROUND,
		FT_STROKER_LINEJOIN_ROUND,
		0);

	FT_Glyph_StrokeBorder(&glyph, stroker, 0, 1);
	FT_Outline *o =
		&reinterpret_cast<FT_OutlineGlyph>(glyph)->outline;*/
	FT_Outline_Render(library, &face->glyph->outline, &params);
	/*FT_Stroker_Done(stroker);
	FT_Done_Glyph(glyph);*/

	
}
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

FreeType::IMG*
FreeType::Face::Render_Outline(
	FT_UInt index,
	const Pixel32 &fontCol,
	const Pixel32 outlineCol,
	float outlineWidth)
{
	// Set the size to use.
	//FT_LOAD_NO_BITMAP
	if (FT_Load_Glyph(face, index, FT_LOAD_NO_BITMAP) == 0)
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
					IMG *img = new IMG(imgWidth, imgHeight);
					Pixel32 *pxl = img->data;// new Pixel32[imgSize];


					// Loop over the outline spans and just draw them into the
					// image.
					for (Spans::iterator s = outlineSpans.begin();
						s != outlineSpans.end(); ++s)
						for (int w = 0; w < s->width; ++w)
							pxl[(int)((imgHeight - 1 - (s->y - rect.ymin)) * imgWidth
								+ s->x - rect.xmin + w)] =
							Pixel32(outlineCol.r, outlineCol.g, outlineCol.b,
								s->coverage);

					// Then loop over the regular glyph spans and blend them into
					// the image.
					for (Spans::iterator s = spans.begin();
						s != spans.end(); ++s)
						for (int w = 0; w < s->width; ++w)
						{
							Pixel32 &dst =
								pxl[(int)((imgHeight - 1 - (s->y - rect.ymin)) * imgWidth
									+ s->x - rect.xmin + w)];
							Pixel32 src = Pixel32(fontCol.r, fontCol.g, fontCol.b,
								s->coverage);
							dst.r = (int)(dst.r + ((src.r - dst.r) * src.a) / 255.0f);
							dst.g = (int)(dst.g + ((src.g - dst.g) * src.a) / 255.0f);
							dst.b = (int)(dst.b + ((src.b - dst.b) * src.a) / 255.0f);
							dst.a = MIN(255, dst.a + src.a);
						}

					// Dump the image to disk.
					//WriteTGA(fileName, pxl, imgWidth, imgHeight);

					return img;
				}
			}
		}
	}
			return nullptr;
}

