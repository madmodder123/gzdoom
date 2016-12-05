
#include "templates.h"
#include "doomtype.h"
#include "doomdef.h"
#include "r_defs.h"
#include "r_draw.h"
#include "r_main.h"
#include "r_things.h"
#include "v_video.h"
#include "r_draw_pal.h"

namespace swrenderer
{
	PalWall1Command::PalWall1Command()
	{
		using namespace drawerargs;

		_iscale = dc_iscale;
		_texturefrac = dc_texturefrac;
		_colormap = dc_colormap;
		_count = dc_count;
		_source = dc_source;
		_dest = dc_dest;
		_vlinebits = vlinebits;
		_mvlinebits = mvlinebits;
		_tmvlinebits = tmvlinebits;
		_pitch = dc_pitch;
		_srcblend = dc_srcblend;
		_destblend = dc_destblend;
	}

	PalWall4Command::PalWall4Command()
	{
		using namespace drawerargs;

		_dest = dc_dest;
		_count = dc_count;
		_pitch = dc_pitch;
		_vlinebits = vlinebits;
		_mvlinebits = mvlinebits;
		_tmvlinebits = tmvlinebits;
		for (int col = 0; col < 4; col++)
		{
			_palookupoffse[col] = palookupoffse[col];
			_bufplce[col] = bufplce[col];
			_vince[col] = vince[col];
			_vplce[col] = vplce[col];
		}
		_srcblend = dc_srcblend;
		_destblend = dc_destblend;
	}

	void DrawWall1PalCommand::Execute(DrawerThread *thread)
	{
		uint32_t fracstep = _iscale;
		uint32_t frac = _texturefrac;
		uint8_t *colormap = _colormap;
		int count = _count;
		const uint8_t *source = _source;
		uint8_t *dest = _dest;
		int bits = _vlinebits;
		int pitch = _pitch;

		do
		{
			*dest = colormap[source[frac >> bits]];
			frac += fracstep;
			dest += pitch;
		} while (--count);
	}

	void DrawWall4PalCommand::Execute(DrawerThread *thread)
	{
		uint8_t *dest = _dest;
		int count = _count;
		int bits = _vlinebits;
		uint32_t place;
		auto pal0 = _palookupoffse[0];
		auto pal1 = _palookupoffse[1];
		auto pal2 = _palookupoffse[2];
		auto pal3 = _palookupoffse[3];
		auto buf0 = _bufplce[0];
		auto buf1 = _bufplce[1];
		auto buf2 = _bufplce[2];
		auto buf3 = _bufplce[3];
		const auto vince0 = _vince[0];
		const auto vince1 = _vince[1];
		const auto vince2 = _vince[2];
		const auto vince3 = _vince[3];
		auto vplce0 = _vplce[0];
		auto vplce1 = _vplce[1];
		auto vplce2 = _vplce[2];
		auto vplce3 = _vplce[3];
		auto pitch = _pitch;

		do
		{
			dest[0] = pal0[buf0[(place = vplce0) >> bits]]; vplce0 = place + vince0;
			dest[1] = pal1[buf1[(place = vplce1) >> bits]]; vplce1 = place + vince1;
			dest[2] = pal2[buf2[(place = vplce2) >> bits]]; vplce2 = place + vince2;
			dest[3] = pal3[buf3[(place = vplce3) >> bits]]; vplce3 = place + vince3;
			dest += pitch;
		} while (--count);
	}

	void DrawWallMasked1PalCommand::Execute(DrawerThread *thread)
	{
		uint32_t fracstep = _iscale;
		uint32_t frac = _texturefrac;
		uint8_t *colormap = _colormap;
		int count = _count;
		const uint8_t *source = _source;
		uint8_t *dest = _dest;
		int bits = _mvlinebits;
		int pitch = _pitch;

		do
		{
			uint8_t pix = source[frac >> bits];
			if (pix != 0)
			{
				*dest = colormap[pix];
			}
			frac += fracstep;
			dest += pitch;
		} while (--count);
	}

	void DrawWallMasked4PalCommand::Execute(DrawerThread *thread)
	{
		uint8_t *dest = _dest;
		int count = _count;
		int bits = _mvlinebits;
		uint32_t place;
		auto pal0 = _palookupoffse[0];
		auto pal1 = _palookupoffse[1];
		auto pal2 = _palookupoffse[2];
		auto pal3 = _palookupoffse[3];
		auto buf0 = _bufplce[0];
		auto buf1 = _bufplce[1];
		auto buf2 = _bufplce[2];
		auto buf3 = _bufplce[3];
		const auto vince0 = _vince[0];
		const auto vince1 = _vince[1];
		const auto vince2 = _vince[2];
		const auto vince3 = _vince[3];
		auto vplce0 = _vplce[0];
		auto vplce1 = _vplce[1];
		auto vplce2 = _vplce[2];
		auto vplce3 = _vplce[3];
		auto pitch = _pitch;

		do
		{
			uint8_t pix;

			pix = buf0[(place = vplce0) >> bits]; if (pix) dest[0] = pal0[pix]; vplce0 = place + vince0;
			pix = buf1[(place = vplce1) >> bits]; if (pix) dest[1] = pal1[pix]; vplce1 = place + vince1;
			pix = buf2[(place = vplce2) >> bits]; if (pix) dest[2] = pal2[pix]; vplce2 = place + vince2;
			pix = buf3[(place = vplce3) >> bits]; if (pix) dest[3] = pal3[pix]; vplce3 = place + vince3;
			dest += pitch;
		} while (--count);
	}

	void DrawWallAdd1PalCommand::Execute(DrawerThread *thread)
	{
		uint32_t fracstep = _iscale;
		uint32_t frac = _texturefrac;
		uint8_t *colormap = _colormap;
		int count = _count;
		const uint8_t *source = _source;
		uint8_t *dest = _dest;
		int bits = _tmvlinebits;
		int pitch = _pitch;

		uint32_t *fg2rgb = _srcblend;
		uint32_t *bg2rgb = _destblend;

		do
		{
			uint8_t pix = source[frac >> bits];
			if (pix != 0)
			{
				uint32_t fg = fg2rgb[colormap[pix]];
				uint32_t bg = bg2rgb[*dest];
				fg = (fg + bg) | 0x1f07c1f;
				*dest = RGB32k.All[fg & (fg >> 15)];
			}
			frac += fracstep;
			dest += pitch;
		} while (--count);
	}

	void DrawWallAdd4PalCommand::Execute(DrawerThread *thread)
	{
		uint8_t *dest = _dest;
		int count = _count;
		int bits = _tmvlinebits;

		uint32_t *fg2rgb = _srcblend;
		uint32_t *bg2rgb = _destblend;

		uint32_t vplce[4] = { _vplce[0], _vplce[1], _vplce[2], _vplce[3] };

		do
		{
			for (int i = 0; i < 4; ++i)
			{
				uint8_t pix = _bufplce[i][vplce[i] >> bits];
				if (pix != 0)
				{
					uint32_t fg = fg2rgb[_palookupoffse[i][pix]];
					uint32_t bg = bg2rgb[dest[i]];
					fg = (fg + bg) | 0x1f07c1f;
					dest[i] = RGB32k.All[fg & (fg >> 15)];
				}
				vplce[i] += _vince[i];
			}
			dest += _pitch;
		} while (--count);
	}

	void DrawWallAddClamp1PalCommand::Execute(DrawerThread *thread)
	{
		uint32_t fracstep = _iscale;
		uint32_t frac = _texturefrac;
		uint8_t *colormap = _colormap;
		int count = _count;
		const uint8_t *source = _source;
		uint8_t *dest = _dest;
		int bits = _tmvlinebits;
		int pitch = _pitch;

		uint32_t *fg2rgb = _srcblend;
		uint32_t *bg2rgb = _destblend;

		do
		{
			uint8_t pix = source[frac >> bits];
			if (pix != 0)
			{
				uint32_t a = fg2rgb[colormap[pix]] + bg2rgb[*dest];
				uint32_t b = a;

				a |= 0x01f07c1f;
				b &= 0x40100400;
				a &= 0x3fffffff;
				b = b - (b >> 5);
				a |= b;
				*dest = RGB32k.All[a & (a >> 15)];
			}
			frac += fracstep;
			dest += pitch;
		} while (--count);
	}

	void DrawWallAddClamp4PalCommand::Execute(DrawerThread *thread)
	{
		uint8_t *dest = _dest;
		int count = _count;
		int bits = _tmvlinebits;

		uint32_t *fg2rgb = _srcblend;
		uint32_t *bg2rgb = _destblend;

		uint32_t vplce[4] = { _vplce[0], _vplce[1], _vplce[2], _vplce[3] };

		do
		{
			for (int i = 0; i < 4; ++i)
			{
				uint8_t pix = _bufplce[i][vplce[i] >> bits];
				if (pix != 0)
				{
					uint32_t a = fg2rgb[_palookupoffse[i][pix]] + bg2rgb[dest[i]];
					uint32_t b = a;

					a |= 0x01f07c1f;
					b &= 0x40100400;
					a &= 0x3fffffff;
					b = b - (b >> 5);
					a |= b;
					dest[i] = RGB32k.All[a & (a >> 15)];
				}
				vplce[i] += _vince[i];
			}
			dest += _pitch;
		} while (--count);
	}

	void DrawWallSubClamp1PalCommand::Execute(DrawerThread *thread)
	{
		uint32_t fracstep = _iscale;
		uint32_t frac = _texturefrac;
		uint8_t *colormap = _colormap;
		int count = _count;
		const uint8_t *source = _source;
		uint8_t *dest = _dest;
		int bits = _tmvlinebits;
		int pitch = _pitch;

		uint32_t *fg2rgb = _srcblend;
		uint32_t *bg2rgb = _destblend;

		do
		{
			uint8_t pix = source[frac >> bits];
			if (pix != 0)
			{
				uint32_t a = (fg2rgb[colormap[pix]] | 0x40100400) - bg2rgb[*dest];
				uint32_t b = a;

				b &= 0x40100400;
				b = b - (b >> 5);
				a &= b;
				a |= 0x01f07c1f;
				*dest = RGB32k.All[a & (a >> 15)];
			}
			frac += fracstep;
			dest += pitch;
		} while (--count);
	}

	void DrawWallSubClamp4PalCommand::Execute(DrawerThread *thread)
	{
		uint8_t *dest = _dest;
		int count = _count;
		int bits = _tmvlinebits;

		uint32_t *fg2rgb = _srcblend;
		uint32_t *bg2rgb = _destblend;

		uint32_t vplce[4] = { _vplce[0], _vplce[1], _vplce[2], _vplce[3] };

		do
		{
			for (int i = 0; i < 4; ++i)
			{
				uint8_t pix = _bufplce[i][vplce[i] >> bits];
				if (pix != 0)
				{
					uint32_t a = (fg2rgb[_palookupoffse[i][pix]] | 0x40100400) - bg2rgb[dest[i]];
					uint32_t b = a;

					b &= 0x40100400;
					b = b - (b >> 5);
					a &= b;
					a |= 0x01f07c1f;
					dest[i] = RGB32k.All[a & (a >> 15)];
				}
				vplce[i] += _vince[i];
			}
			dest += _pitch;
		} while (--count);
	}

	void DrawWallRevSubClamp1PalCommand::Execute(DrawerThread *thread)
	{
		uint32_t fracstep = _iscale;
		uint32_t frac = _texturefrac;
		uint8_t *colormap = _colormap;
		int count = _count;
		const uint8_t *source = _source;
		uint8_t *dest = _dest;
		int bits = _tmvlinebits;
		int pitch = _pitch;

		uint32_t *fg2rgb = _srcblend;
		uint32_t *bg2rgb = _destblend;

		do
		{
			uint8_t pix = source[frac >> bits];
			if (pix != 0)
			{
				uint32_t a = (bg2rgb[*dest] | 0x40100400) - fg2rgb[colormap[pix]];
				uint32_t b = a;

				b &= 0x40100400;
				b = b - (b >> 5);
				a &= b;
				a |= 0x01f07c1f;
				*dest = RGB32k.All[a & (a >> 15)];
			}
			frac += fracstep;
			dest += pitch;
		} while (--count);
	}

	void DrawWallRevSubClamp4PalCommand::Execute(DrawerThread *thread)
	{
		uint8_t *dest = _dest;
		int count = _count;
		int bits = _tmvlinebits;

		uint32_t *fg2rgb = _srcblend;
		uint32_t *bg2rgb = _destblend;

		uint32_t vplce[4] = { _vplce[0], _vplce[1], _vplce[2], _vplce[3] };

		do
		{
			for (int i = 0; i < 4; ++i)
			{
				uint8_t pix = _bufplce[i][vplce[i] >> bits];
				if (pix != 0)
				{
					uint32_t a = (bg2rgb[dest[i]] | 0x40100400) - fg2rgb[_palookupoffse[i][pix]];
					uint32_t b = a;

					b &= 0x40100400;
					b = b - (b >> 5);
					a &= b;
					a |= 0x01f07c1f;
					dest[i] = RGB32k.All[a & (a >> 15)];
				}
				vplce[i] += _vince[i];
			}
			dest += _pitch;
		} while (--count);
	}

	/////////////////////////////////////////////////////////////////////////

	PalSkyCommand::PalSkyCommand(uint32_t solid_top, uint32_t solid_bottom)
	{
	}

	void DrawSingleSky1PalCommand::Execute(DrawerThread *thread)
	{
	}

	void DrawSingleSky4PalCommand::Execute(DrawerThread *thread)
	{
	}

	void DrawDoubleSky1PalCommand::Execute(DrawerThread *thread)
	{
	}

	void DrawDoubleSky4PalCommand::Execute(DrawerThread *thread)
	{
	}

	/////////////////////////////////////////////////////////////////////////

	PalColumnCommand::PalColumnCommand()
	{
	}

	void DrawColumnPalCommand::Execute(DrawerThread *thread)
	{
	}

	void FillColumnPalCommand::Execute(DrawerThread *thread)
	{
	}

	void FillColumnAddPalCommand::Execute(DrawerThread *thread)
	{
	}

	void FillColumnAddClampPalCommand::Execute(DrawerThread *thread)
	{
	}

	void FillColumnSubClampPalCommand::Execute(DrawerThread *thread)
	{
	}

	void FillColumnRevSubClampPalCommand::Execute(DrawerThread *thread)
	{
	}

	void DrawColumnAddPalCommand::Execute(DrawerThread *thread)
	{
	}

	void DrawColumnTranslatedPalCommand::Execute(DrawerThread *thread)
	{
	}

	void DrawColumnTlatedAddPalCommand::Execute(DrawerThread *thread)
	{
	}

	void DrawColumnShadedPalCommand::Execute(DrawerThread *thread)
	{
	}

	void DrawColumnAddClampPalCommand::Execute(DrawerThread *thread)
	{
	}

	void DrawColumnAddClampTranslatedPalCommand::Execute(DrawerThread *thread)
	{
	}

	void DrawColumnSubClampPalCommand::Execute(DrawerThread *thread)
	{
	}

	void DrawColumnSubClampTranslatedPalCommand::Execute(DrawerThread *thread)
	{
	}

	void DrawColumnRevSubClampPalCommand::Execute(DrawerThread *thread)
	{
	}

	void DrawColumnRevSubClampTranslatedPalCommand::Execute(DrawerThread *thread)
	{
	}

	void DrawFuzzColumnPalCommand::Execute(DrawerThread *thread)
	{
	}

	/////////////////////////////////////////////////////////////////////////

	PalSpanCommand::PalSpanCommand()
	{
		using namespace drawerargs;

		_source = ds_source;
		_colormap = ds_colormap;
		_xfrac = ds_xfrac;
		_yfrac = ds_yfrac;
		_y = ds_y;
		_x1 = ds_x1;
		_x2 = ds_x2;
		_destorg = dc_destorg;
		_xstep = ds_xstep;
		_ystep = ds_ystep;
		_xbits = ds_xbits;
		_ybits = ds_ybits;
		_srcblend = dc_srcblend;
		_destblend = dc_destblend;
		_color = ds_color;
	}

	void DrawSpanPalCommand::Execute(DrawerThread *thread)
	{
		dsfixed_t xfrac;
		dsfixed_t yfrac;
		dsfixed_t xstep;
		dsfixed_t ystep;
		uint8_t *dest;
		const uint8_t *source = _source;
		const uint8_t *colormap = _colormap;
		int count;
		int spot;

		xfrac = _xfrac;
		yfrac = _yfrac;

		dest = ylookup[_y] + _x1 + _destorg;

		count = _x2 - _x1 + 1;

		xstep = _xstep;
		ystep = _ystep;

		if (_xbits == 6 && _ybits == 6)
		{
			// 64x64 is the most common case by far, so special case it.
			do
			{
				// Current texture index in u,v.
				spot = ((xfrac >> (32 - 6 - 6))&(63 * 64)) + (yfrac >> (32 - 6));

				// Lookup pixel from flat texture tile,
				//  re-index using light/colormap.
				*dest++ = colormap[source[spot]];

				// Next step in u,v.
				xfrac += xstep;
				yfrac += ystep;
			} while (--count);
		}
		else
		{
			uint8_t yshift = 32 - _ybits;
			uint8_t xshift = yshift - _xbits;
			int xmask = ((1 << _xbits) - 1) << _ybits;

			do
			{
				// Current texture index in u,v.
				spot = ((xfrac >> xshift) & xmask) + (yfrac >> yshift);

				// Lookup pixel from flat texture tile,
				//  re-index using light/colormap.
				*dest++ = colormap[source[spot]];

				// Next step in u,v.
				xfrac += xstep;
				yfrac += ystep;
			} while (--count);
		}
	}

	void DrawSpanMaskedPalCommand::Execute(DrawerThread *thread)
	{
		dsfixed_t xfrac;
		dsfixed_t yfrac;
		dsfixed_t xstep;
		dsfixed_t ystep;
		BYTE *dest;
		const BYTE *source = _source;
		const BYTE *colormap = _colormap;
		int count;
		int spot;

		xfrac = _xfrac;
		yfrac = _yfrac;

		dest = ylookup[_y] + _x1 + _destorg;

		count = _x2 - _x1 + 1;

		xstep = _xstep;
		ystep = _ystep;

		if (_xbits == 6 && _ybits == 6)
		{
			// 64x64 is the most common case by far, so special case it.
			do
			{
				int texdata;

				spot = ((xfrac >> (32 - 6 - 6))&(63 * 64)) + (yfrac >> (32 - 6));
				texdata = source[spot];
				if (texdata != 0)
				{
					*dest = colormap[texdata];
				}
				dest++;
				xfrac += xstep;
				yfrac += ystep;
			} while (--count);
		}
		else
		{
			BYTE yshift = 32 - _ybits;
			BYTE xshift = yshift - _xbits;
			int xmask = ((1 << _xbits) - 1) << _ybits;
			do
			{
				int texdata;

				spot = ((xfrac >> xshift) & xmask) + (yfrac >> yshift);
				texdata = source[spot];
				if (texdata != 0)
				{
					*dest = colormap[texdata];
				}
				dest++;
				xfrac += xstep;
				yfrac += ystep;
			} while (--count);
		}
	}

	void DrawSpanTranslucentPalCommand::Execute(DrawerThread *thread)
	{
		dsfixed_t xfrac;
		dsfixed_t yfrac;
		dsfixed_t xstep;
		dsfixed_t ystep;
		BYTE *dest;
		const BYTE *source = _source;
		const BYTE *colormap = _colormap;
		int count;
		int spot;
		DWORD *fg2rgb = _srcblend;
		DWORD *bg2rgb = _destblend;

		xfrac = _xfrac;
		yfrac = _yfrac;

		dest = ylookup[_y] + _x1 + _destorg;

		count = _x2 - _x1 + 1;

		xstep = _xstep;
		ystep = _ystep;

		if (_xbits == 6 && _ybits == 6)
		{
			// 64x64 is the most common case by far, so special case it.
			do
			{
				spot = ((xfrac >> (32 - 6 - 6))&(63 * 64)) + (yfrac >> (32 - 6));
				DWORD fg = colormap[source[spot]];
				DWORD bg = *dest;
				fg = fg2rgb[fg];
				bg = bg2rgb[bg];
				fg = (fg + bg) | 0x1f07c1f;
				*dest++ = RGB32k.All[fg & (fg >> 15)];
				xfrac += xstep;
				yfrac += ystep;
			} while (--count);
		}
		else
		{
			BYTE yshift = 32 - _ybits;
			BYTE xshift = yshift - _xbits;
			int xmask = ((1 << _xbits) - 1) << _ybits;
			do
			{
				spot = ((xfrac >> xshift) & xmask) + (yfrac >> yshift);
				DWORD fg = colormap[source[spot]];
				DWORD bg = *dest;
				fg = fg2rgb[fg];
				bg = bg2rgb[bg];
				fg = (fg + bg) | 0x1f07c1f;
				*dest++ = RGB32k.All[fg & (fg >> 15)];
				xfrac += xstep;
				yfrac += ystep;
			} while (--count);
		}
	}

	void DrawSpanMaskedTranslucentPalCommand::Execute(DrawerThread *thread)
	{
		dsfixed_t xfrac;
		dsfixed_t yfrac;
		dsfixed_t xstep;
		dsfixed_t ystep;
		BYTE *dest;
		const BYTE *source = _source;
		const BYTE *colormap = _colormap;
		int count;
		int spot;
		DWORD *fg2rgb = _srcblend;
		DWORD *bg2rgb = _destblend;

		xfrac = _xfrac;
		yfrac = _yfrac;

		dest = ylookup[_y] + _x1 + _destorg;

		count = _x2 - _x1 + 1;

		xstep = _xstep;
		ystep = _ystep;

		if (_xbits == 6 && _ybits == 6)
		{
			// 64x64 is the most common case by far, so special case it.
			do
			{
				BYTE texdata;

				spot = ((xfrac >> (32 - 6 - 6))&(63 * 64)) + (yfrac >> (32 - 6));
				texdata = source[spot];
				if (texdata != 0)
				{
					DWORD fg = colormap[texdata];
					DWORD bg = *dest;
					fg = fg2rgb[fg];
					bg = bg2rgb[bg];
					fg = (fg + bg) | 0x1f07c1f;
					*dest = RGB32k.All[fg & (fg >> 15)];
				}
				dest++;
				xfrac += xstep;
				yfrac += ystep;
			} while (--count);
		}
		else
		{
			BYTE yshift = 32 - _ybits;
			BYTE xshift = yshift - _xbits;
			int xmask = ((1 << _xbits) - 1) << _ybits;
			do
			{
				BYTE texdata;

				spot = ((xfrac >> xshift) & xmask) + (yfrac >> yshift);
				texdata = source[spot];
				if (texdata != 0)
				{
					DWORD fg = colormap[texdata];
					DWORD bg = *dest;
					fg = fg2rgb[fg];
					bg = bg2rgb[bg];
					fg = (fg + bg) | 0x1f07c1f;
					*dest = RGB32k.All[fg & (fg >> 15)];
				}
				dest++;
				xfrac += xstep;
				yfrac += ystep;
			} while (--count);
		}
	}

	void DrawSpanAddClampPalCommand::Execute(DrawerThread *thread)
	{
		dsfixed_t xfrac;
		dsfixed_t yfrac;
		dsfixed_t xstep;
		dsfixed_t ystep;
		BYTE *dest;
		const BYTE *source = _source;
		const BYTE *colormap = _colormap;
		int count;
		int spot;
		DWORD *fg2rgb = _srcblend;
		DWORD *bg2rgb = _destblend;

		xfrac = _xfrac;
		yfrac = _yfrac;

		dest = ylookup[_y] + _x1 + _destorg;

		count = _x2 - _x1 + 1;

		xstep = _xstep;
		ystep = _ystep;

		if (_xbits == 6 && _ybits == 6)
		{
			// 64x64 is the most common case by far, so special case it.
			do
			{
				spot = ((xfrac >> (32 - 6 - 6))&(63 * 64)) + (yfrac >> (32 - 6));
				DWORD a = fg2rgb[colormap[source[spot]]] + bg2rgb[*dest];
				DWORD b = a;

				a |= 0x01f07c1f;
				b &= 0x40100400;
				a &= 0x3fffffff;
				b = b - (b >> 5);
				a |= b;
				*dest++ = RGB32k.All[a & (a >> 15)];
				xfrac += xstep;
				yfrac += ystep;
			} while (--count);
		}
		else
		{
			BYTE yshift = 32 - _ybits;
			BYTE xshift = yshift - _xbits;
			int xmask = ((1 << _xbits) - 1) << _ybits;
			do
			{
				spot = ((xfrac >> xshift) & xmask) + (yfrac >> yshift);
				DWORD a = fg2rgb[colormap[source[spot]]] + bg2rgb[*dest];
				DWORD b = a;

				a |= 0x01f07c1f;
				b &= 0x40100400;
				a &= 0x3fffffff;
				b = b - (b >> 5);
				a |= b;
				*dest++ = RGB32k.All[a & (a >> 15)];
				xfrac += xstep;
				yfrac += ystep;
			} while (--count);
		}
	}

	void DrawSpanMaskedAddClampPalCommand::Execute(DrawerThread *thread)
	{
		dsfixed_t xfrac;
		dsfixed_t yfrac;
		dsfixed_t xstep;
		dsfixed_t ystep;
		BYTE *dest;
		const BYTE *source = _source;
		const BYTE *colormap = _colormap;
		int count;
		int spot;
		DWORD *fg2rgb = _srcblend;
		DWORD *bg2rgb = _destblend;

		xfrac = _xfrac;
		yfrac = _yfrac;

		dest = ylookup[_y] + _x1 + _destorg;

		count = _x2 - _x1 + 1;

		xstep = _xstep;
		ystep = _ystep;

		if (_xbits == 6 && _ybits == 6)
		{
			// 64x64 is the most common case by far, so special case it.
			do
			{
				BYTE texdata;

				spot = ((xfrac >> (32 - 6 - 6))&(63 * 64)) + (yfrac >> (32 - 6));
				texdata = source[spot];
				if (texdata != 0)
				{
					DWORD a = fg2rgb[colormap[texdata]] + bg2rgb[*dest];
					DWORD b = a;

					a |= 0x01f07c1f;
					b &= 0x40100400;
					a &= 0x3fffffff;
					b = b - (b >> 5);
					a |= b;
					*dest = RGB32k.All[a & (a >> 15)];
				}
				dest++;
				xfrac += xstep;
				yfrac += ystep;
			} while (--count);
		}
		else
		{
			BYTE yshift = 32 - _ybits;
			BYTE xshift = yshift - _xbits;
			int xmask = ((1 << _xbits) - 1) << _ybits;
			do
			{
				BYTE texdata;

				spot = ((xfrac >> xshift) & xmask) + (yfrac >> yshift);
				texdata = source[spot];
				if (texdata != 0)
				{
					DWORD a = fg2rgb[colormap[texdata]] + bg2rgb[*dest];
					DWORD b = a;

					a |= 0x01f07c1f;
					b &= 0x40100400;
					a &= 0x3fffffff;
					b = b - (b >> 5);
					a |= b;
					*dest = RGB32k.All[a & (a >> 15)];
				}
				dest++;
				xfrac += xstep;
				yfrac += ystep;
			} while (--count);
		}
	}

	void FillSpanPalCommand::Execute(DrawerThread *thread)
	{
		memset(ylookup[_y] + _x1 + _destorg, _color, _x2 - _x1 + 1);
	}

	/////////////////////////////////////////////////////////////////////////

	DrawTiltedSpanPalCommand::DrawTiltedSpanPalCommand(int y, int x1, int x2, const FVector3 &plane_sz, const FVector3 &plane_su, const FVector3 &plane_sv, bool plane_shade, int planeshade, float planelightfloat, fixed_t pviewx, fixed_t pviewy)
	{
	}

	void DrawTiltedSpanPalCommand::Execute(DrawerThread *thread)
	{
	}

	/////////////////////////////////////////////////////////////////////////

	DrawColoredSpanPalCommand::DrawColoredSpanPalCommand(int y, int x1, int x2)
	{
	}

	void DrawColoredSpanPalCommand::Execute(DrawerThread *thread)
	{
	}

	/////////////////////////////////////////////////////////////////////////

	DrawSlabPalCommand::DrawSlabPalCommand(int dx, fixed_t v, int dy, fixed_t vi, const uint8_t *vptr, uint8_t *p, const uint8_t *colormap)
	{
	}

	void DrawSlabPalCommand::Execute(DrawerThread *thread)
	{
	}

	/////////////////////////////////////////////////////////////////////////

	DrawFogBoundaryLinePalCommand::DrawFogBoundaryLinePalCommand(int y, int y2, int x1)
	{
	}

	void DrawFogBoundaryLinePalCommand::Execute(DrawerThread *thread)
	{
	}
}
