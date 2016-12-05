
#pragma once

#include "r_draw.h"
#include "v_palette.h"
#include "r_thread.h"

namespace swrenderer
{
	class PalWall1Command : public DrawerCommand
	{
	public:
		PalWall1Command();
		FString DebugInfo() override { return "PalWallCommand"; }

	protected:
		uint32_t _iscale;
		uint32_t _texturefrac;
		uint8_t *_colormap;
		int _count;
		const uint8_t *_source;
		uint8_t *_dest;
		int _vlinebits;
		int _mvlinebits;
		int _tmvlinebits;
		int _pitch;
		uint32_t *_srcblend;
		uint32_t *_destblend;
	};

	class PalWall4Command : public DrawerCommand
	{
	public:
		PalWall4Command();
		FString DebugInfo() override { return "PalWallCommand"; }

	protected:
		uint8_t *_dest;
		int _count;
		int _pitch;
		int _vlinebits;
		int _mvlinebits;
		int _tmvlinebits;
		uint8_t *_palookupoffse[4];
		const uint8_t *_bufplce[4];
		uint32_t _vince[4];
		uint32_t _vplce[4];
		uint32_t *_srcblend;
		uint32_t *_destblend;
	};

	class DrawWall1PalCommand : public PalWall1Command { public: void Execute(DrawerThread *thread) override; };
	class DrawWall4PalCommand : public PalWall4Command { public: void Execute(DrawerThread *thread) override; };
	class DrawWallMasked1PalCommand : public PalWall1Command { public: void Execute(DrawerThread *thread) override; };
	class DrawWallMasked4PalCommand : public PalWall4Command { public: void Execute(DrawerThread *thread) override; };
	class DrawWallAdd1PalCommand : public PalWall1Command { public: void Execute(DrawerThread *thread) override; };
	class DrawWallAdd4PalCommand : public PalWall4Command { public: void Execute(DrawerThread *thread) override; };
	class DrawWallAddClamp1PalCommand : public PalWall1Command { public: void Execute(DrawerThread *thread) override; };
	class DrawWallAddClamp4PalCommand : public PalWall4Command { public: void Execute(DrawerThread *thread) override; };
	class DrawWallSubClamp1PalCommand : public PalWall1Command { public: void Execute(DrawerThread *thread) override; };
	class DrawWallSubClamp4PalCommand : public PalWall4Command { public: void Execute(DrawerThread *thread) override; };
	class DrawWallRevSubClamp1PalCommand : public PalWall1Command { public: void Execute(DrawerThread *thread) override; };
	class DrawWallRevSubClamp4PalCommand : public PalWall4Command { public: void Execute(DrawerThread *thread) override; };

	class PalSkyCommand : public DrawerCommand
	{
	public:
		PalSkyCommand(uint32_t solid_top, uint32_t solid_bottom);
		FString DebugInfo() override { return "PalSkyCommand"; }
	};

	class DrawSingleSky1PalCommand : public PalSkyCommand { public: using PalSkyCommand::PalSkyCommand; void Execute(DrawerThread *thread) override; };
	class DrawSingleSky4PalCommand : public PalSkyCommand { public: using PalSkyCommand::PalSkyCommand; void Execute(DrawerThread *thread) override; };
	class DrawDoubleSky1PalCommand : public PalSkyCommand { public: using PalSkyCommand::PalSkyCommand; void Execute(DrawerThread *thread) override; };
	class DrawDoubleSky4PalCommand : public PalSkyCommand { public: using PalSkyCommand::PalSkyCommand; void Execute(DrawerThread *thread) override; };

	class PalColumnCommand : public DrawerCommand
	{
	public:
		PalColumnCommand();
		FString DebugInfo() override { return "PalColumnCommand"; }
	};

	class DrawColumnPalCommand : public PalColumnCommand { public: void Execute(DrawerThread *thread) override; };
	class FillColumnPalCommand : public PalColumnCommand { public: void Execute(DrawerThread *thread) override; };
	class FillColumnAddPalCommand : public PalColumnCommand { public: void Execute(DrawerThread *thread) override; };
	class FillColumnAddClampPalCommand : public PalColumnCommand { public: void Execute(DrawerThread *thread) override; };
	class FillColumnSubClampPalCommand : public PalColumnCommand { public: void Execute(DrawerThread *thread) override; };
	class FillColumnRevSubClampPalCommand : public PalColumnCommand { public: void Execute(DrawerThread *thread) override; };
	class DrawColumnAddPalCommand : public PalColumnCommand { public: void Execute(DrawerThread *thread) override; };
	class DrawColumnTranslatedPalCommand : public PalColumnCommand { public: void Execute(DrawerThread *thread) override; };
	class DrawColumnTlatedAddPalCommand : public PalColumnCommand { public: void Execute(DrawerThread *thread) override; };
	class DrawColumnShadedPalCommand : public PalColumnCommand { public: void Execute(DrawerThread *thread) override; };
	class DrawColumnAddClampPalCommand : public PalColumnCommand { public: void Execute(DrawerThread *thread) override; };
	class DrawColumnAddClampTranslatedPalCommand : public PalColumnCommand { public: void Execute(DrawerThread *thread) override; };
	class DrawColumnSubClampPalCommand : public PalColumnCommand { public: void Execute(DrawerThread *thread) override; };
	class DrawColumnSubClampTranslatedPalCommand : public PalColumnCommand { public: void Execute(DrawerThread *thread) override; };
	class DrawColumnRevSubClampPalCommand : public PalColumnCommand { public: void Execute(DrawerThread *thread) override; };
	class DrawColumnRevSubClampTranslatedPalCommand : public PalColumnCommand { public: void Execute(DrawerThread *thread) override; };

	class DrawFuzzColumnPalCommand : public DrawerCommand
	{
	public:
		void Execute(DrawerThread *thread) override;
		FString DebugInfo() override { return "DrawFuzzColumnPalCommand"; }
	};

	class PalSpanCommand : public DrawerCommand
	{
	public:
		PalSpanCommand();
		FString DebugInfo() override { return "PalSpanCommand"; }

	protected:
		const uint8_t *_source;
		const uint8_t *_colormap;
		dsfixed_t _xfrac;
		dsfixed_t _yfrac;
		int _y;
		int _x1;
		int _x2;
		uint8_t *_destorg;
		dsfixed_t _xstep;
		dsfixed_t _ystep;
		int _xbits;
		int _ybits;
		uint32_t *_srcblend;
		uint32_t *_destblend;
		int _color;
	};

	class DrawSpanPalCommand : public PalSpanCommand { public: void Execute(DrawerThread *thread) override; };
	class DrawSpanMaskedPalCommand : public PalSpanCommand { public: void Execute(DrawerThread *thread) override; };
	class DrawSpanTranslucentPalCommand : public PalSpanCommand { public: void Execute(DrawerThread *thread) override; };
	class DrawSpanMaskedTranslucentPalCommand : public PalSpanCommand { public: void Execute(DrawerThread *thread) override; };
	class DrawSpanAddClampPalCommand : public PalSpanCommand { public: void Execute(DrawerThread *thread) override; };
	class DrawSpanMaskedAddClampPalCommand : public PalSpanCommand { public: void Execute(DrawerThread *thread) override; };
	class FillSpanPalCommand : public PalSpanCommand { public: void Execute(DrawerThread *thread) override; };

	class DrawTiltedSpanPalCommand : public DrawerCommand
	{
	public:
		DrawTiltedSpanPalCommand(int y, int x1, int x2, const FVector3 &plane_sz, const FVector3 &plane_su, const FVector3 &plane_sv, bool plane_shade, int planeshade, float planelightfloat, fixed_t pviewx, fixed_t pviewy);
		void Execute(DrawerThread *thread) override;
		FString DebugInfo() override { return "DrawTiltedSpanPalCommand"; }
	};

	class DrawColoredSpanPalCommand : public PalSpanCommand
	{
	public:
		DrawColoredSpanPalCommand(int y, int x1, int x2);
		void Execute(DrawerThread *thread) override;
		FString DebugInfo() override { return "DrawColoredSpanPalCommand"; }
	};

	class DrawSlabPalCommand : public PalSpanCommand
	{
	public:
		DrawSlabPalCommand(int dx, fixed_t v, int dy, fixed_t vi, const uint8_t *vptr, uint8_t *p, const uint8_t *colormap);
		void Execute(DrawerThread *thread) override;
	};

	class DrawFogBoundaryLinePalCommand : public PalSpanCommand
	{
	public:
		DrawFogBoundaryLinePalCommand(int y, int y2, int x1);
		void Execute(DrawerThread *thread) override;
	};

	//class RtInitColsPalCommand : public DrawerCommand { public: void Execute(DrawerThread *thread) override; };
	//class DrawColumnHorizPalCommand : public DrawerCommand { public: void Execute(DrawerThread *thread) override; };
	class FillColumnHorizPalCommand : public DrawerCommand
	{
	public:
		void Execute(DrawerThread *thread) override;
		FString DebugInfo() override { return "FillColumnHorizPalCommand"; }
	};

	class PalRtCommand : public DrawerCommand
	{
	public:
		PalRtCommand(int hx, int sx, int yl, int yh);
		FString DebugInfo() override { return "PalRtCommand"; }
	};

	class DrawColumnRt1CopyPalCommand : public PalRtCommand { public: using PalRtCommand::PalRtCommand; void Execute(DrawerThread *thread) override; };
	class DrawColumnRt1PalCommand : public PalRtCommand { public: using PalRtCommand::PalRtCommand; void Execute(DrawerThread *thread) override; };
	class DrawColumnRt4PalCommand : public PalRtCommand { public: using PalRtCommand::PalRtCommand; void Execute(DrawerThread *thread) override; };
	class DrawColumnRt1TranslatedPalCommand : public PalRtCommand { public: using PalRtCommand::PalRtCommand; void Execute(DrawerThread *thread) override; };
	class DrawColumnRt4TranslatedPalCommand : public PalRtCommand { public: using PalRtCommand::PalRtCommand; void Execute(DrawerThread *thread) override; };
	class DrawColumnRt1AddPalCommand : public PalRtCommand { public: using PalRtCommand::PalRtCommand; void Execute(DrawerThread *thread) override; };
	class DrawColumnRt4AddPalCommand : public PalRtCommand { public: using PalRtCommand::PalRtCommand; void Execute(DrawerThread *thread) override; };
	class DrawColumnRt1AddTranslatedPalCommand : public PalRtCommand { public: using PalRtCommand::PalRtCommand; void Execute(DrawerThread *thread) override; };
	class DrawColumnRt4AddTranslatedPalCommand : public PalRtCommand { public: using PalRtCommand::PalRtCommand; void Execute(DrawerThread *thread) override; };
	class DrawColumnRt1ShadedPalCommand : public PalRtCommand { public: using PalRtCommand::PalRtCommand; void Execute(DrawerThread *thread) override; };
	class DrawColumnRt4ShadedPalCommand : public PalRtCommand { public: using PalRtCommand::PalRtCommand; void Execute(DrawerThread *thread) override; };
	class DrawColumnRt1AddClampPalCommand : public PalRtCommand { public: using PalRtCommand::PalRtCommand; void Execute(DrawerThread *thread) override; };
	class DrawColumnRt4AddClampPalCommand : public PalRtCommand { public: using PalRtCommand::PalRtCommand; void Execute(DrawerThread *thread) override; };
	class DrawColumnRt1AddClampTranslatedPalCommand : public PalRtCommand { public: using PalRtCommand::PalRtCommand; void Execute(DrawerThread *thread) override; };
	class DrawColumnRt4AddClampTranslatedPalCommand : public PalRtCommand { public: using PalRtCommand::PalRtCommand; void Execute(DrawerThread *thread) override; };
	class DrawColumnRt1SubClampPalCommand : public PalRtCommand { public: using PalRtCommand::PalRtCommand; void Execute(DrawerThread *thread) override; };
	class DrawColumnRt4SubClampPalCommand : public PalRtCommand { public: using PalRtCommand::PalRtCommand; void Execute(DrawerThread *thread) override; };
	class DrawColumnRt1SubClampTranslatedPalCommand : public PalRtCommand { public: using PalRtCommand::PalRtCommand; void Execute(DrawerThread *thread) override; };
	class DrawColumnRt4SubClampTranslatedPalCommand : public PalRtCommand { public: using PalRtCommand::PalRtCommand; void Execute(DrawerThread *thread) override; };
	class DrawColumnRt1RevSubClampPalCommand : public PalRtCommand { public: using PalRtCommand::PalRtCommand; void Execute(DrawerThread *thread) override; };
	class DrawColumnRt4RevSubClampPalCommand : public PalRtCommand { public: using PalRtCommand::PalRtCommand; void Execute(DrawerThread *thread) override; };
	class DrawColumnRt1RevSubClampTranslatedPalCommand : public PalRtCommand { public: using PalRtCommand::PalRtCommand; void Execute(DrawerThread *thread) override; };
	class DrawColumnRt4RevSubClampTranslatedPalCommand : public PalRtCommand { public: using PalRtCommand::PalRtCommand; void Execute(DrawerThread *thread) override; };
}
