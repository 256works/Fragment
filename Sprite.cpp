#include "stdafx.h"
#include "Sprite.h"

SpriteInfo Sprite::spriteList[SPRITE_MAX];
D2D1_BITMAP_INTERPOLATION_MODE Sprite::interpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR;
ID2D1RenderTarget* Sprite::pRenderTarget = NULL;
int Sprite::drawCallCount = 0;

Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}

void Sprite::AddSprite(spr spriteIndex, const TCHAR * fname, int width, int height, int xorigin, int yorigin, int frameXcount, int frameYcount)
{
	if (spriteIndex == spr::none)
		return;

	spriteList[(unsigned int)spriteIndex].sprite_width	= width;
	spriteList[(unsigned int)spriteIndex].sprite_height	= height;
	spriteList[(unsigned int)spriteIndex].frame_xcount	= frameXcount;
	spriteList[(unsigned int)spriteIndex].frame_ycount	= frameYcount;
	spriteList[(unsigned int)spriteIndex].sprite_origin_pos = POINT({xorigin, yorigin});

	IWICImagingFactory *pWicFactory = NULL;

	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pWicFactory));

	IWICBitmapDecoder *pImageDecoder = NULL;
	IWICBitmapFrameDecode *pWicFrameDecoder = NULL;

	pWicFactory->CreateDecoderFromFilename(fname, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pImageDecoder);

	pImageDecoder->GetFrame(0, &pWicFrameDecoder);

	IWICFormatConverter* pFormatConverter = NULL;
	pWicFactory->CreateFormatConverter(&pFormatConverter);
	pFormatConverter->Initialize(pWicFrameDecoder, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);
	pRenderTarget->CreateBitmapFromWicBitmap(pFormatConverter, NULL, &(spriteList[(unsigned int)spriteIndex].pBmp));

	pWicFactory->Release();
	pImageDecoder->Release();
	pWicFrameDecoder->Release();
	pFormatConverter->Release();
}

void Sprite::DrawSprite(spr spriteIndex, int frameIndex, float x, float y, float xscale, float yscale, float angle, float alpha, float preXscale, float preYscale, float preAngle)
{
	if (alpha < 0.001f)
		return;
	FPOINT p = GC->GetShakePos();
	DrawSpriteFix(spriteIndex, frameIndex, x + p.x, y + p.y, xscale, yscale, angle, alpha, preXscale, preYscale, preAngle);
}

void Sprite::DrawSpriteFix(spr spriteIndex, int frameIndex, float x, float y, float xscale, float yscale, float angle, float alpha, float preXscale, float preYscale, float preAngle)
{
	if (spriteIndex == spr::none || alpha == 0.0f || xscale == 0.0f || yscale == 0.0f)
		return;
	drawCallCount++;

	x -= GC->GetViewPos().x;
	y -= GC->GetViewPos().y;

	SpriteInfo sprite = spriteList[(unsigned int)spriteIndex];

	ID2D1Bitmap* bmpSpr = sprite.pBmp;
	int _spr_wsize = sprite.sprite_width / sprite.frame_xcount;
	int _spr_hsize = sprite.sprite_height / sprite.frame_ycount;
	POINT origin = sprite.sprite_origin_pos;

	int _max_frame = sprite.frame_xcount * sprite.frame_ycount;
	frameIndex %= _max_frame;

	alpha = Clamp(alpha, 0.0, 1.0);

	POINT framePos = {
		(frameIndex % sprite.frame_xcount) * _spr_wsize ,
		((int)frameIndex / sprite.frame_xcount) * _spr_hsize
	};

	pRenderTarget->SetTransform(Matrix3x2F::Scale(SizeF(xscale, yscale)) * Matrix3x2F::Rotation(-angle) * Matrix3x2F::Scale(SizeF( preXscale, preYscale )) * Matrix3x2F::Rotation(-preAngle) *  Matrix3x2F::Translation(SizeF(x, y )));

	pRenderTarget->DrawBitmap(bmpSpr, D2D1::RectF(-(float)(origin.x), -(float)(origin.y), _spr_wsize - (float)(origin.x), _spr_hsize - (float)(origin.y)),
		alpha, interpolationMode,
		D2D1::RectF(
			(float)(framePos.x),
			(float)(framePos.y),
			(float)(framePos.x + _spr_wsize),
			(float)(framePos.y + _spr_hsize)
		));

	pRenderTarget->SetTransform(Matrix3x2F::Identity());
}

void Sprite::DrawSpritePart(spr spriteIndex, int frameIndex, float x, float y, int left, int top, int width, int height, float alpha)
{
	if (spriteIndex == spr::none || alpha == 0.0f)
		return;
	drawCallCount++;

	SpriteInfo sprite = spriteList[(unsigned int)spriteIndex];

	x -= GC->GetViewPos().x;
	y -= GC->GetViewPos().y;

	left = (int)Clamp((float)left, 0.0f, (float)sprite.sprite_width);
	top = (int)Clamp((float)top, 0.0f, (float)sprite.sprite_height);
	width = (int)Clamp((float)width, 0.0f, (float)(sprite.sprite_width - left));
	height = (int)Clamp((float)height, 0.0f, (float)(sprite.sprite_height - top));

	ID2D1Bitmap* bmpSpr = sprite.pBmp;
	int _spr_wsize = sprite.sprite_width / sprite.frame_xcount;
	int _spr_hsize = sprite.sprite_height / sprite.frame_ycount;
	POINT origin = sprite.sprite_origin_pos;

	int _max_frame = sprite.frame_xcount * sprite.frame_ycount;
	frameIndex %= _max_frame;

	alpha = Clamp(alpha, 0.0, 1.0);

	POINT framePos = {
		(frameIndex % sprite.frame_xcount) * _spr_wsize ,
		((int)frameIndex / sprite.frame_xcount) * _spr_hsize
	};

	pRenderTarget->DrawBitmap(bmpSpr, D2D1::RectF(x, y, x+width, y+height),
		alpha, interpolationMode,
		D2D1::RectF(
			framePos.x + (float)left,
			framePos.y + (float)top,
			framePos.x + (float)(left + width),
			framePos.y + (float)(top + height)
		));

}

int Sprite::GetFrameCount(spr spriteIndex)
{
	if (spriteList[(unsigned int)spriteIndex].sprite_width == 0)
		return 1;
	return spriteList[(unsigned int)spriteIndex].frame_xcount*spriteList[(unsigned int)spriteIndex].frame_ycount;
}

void Sprite::SetRenderTarget(ID2D1RenderTarget * target)
{
	pRenderTarget = target;
}

void Sprite::ReleaseSprite()
{
	for (int i = 0; i < SPRITE_MAX; ++i)
	{
		if (spriteList[(unsigned int)i].pBmp != NULL)
		{
			spriteList[(unsigned int)i].pBmp->Release();
			spriteList[(unsigned int)i].pBmp = NULL;
		}
	}
}

void Sprite::SetInterpolation(bool mode)
{
	if (mode)
	{
		interpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR;
	}
	else
	{
		interpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR;
	}
}

void Sprite::ResetDrawCallCount()
{
	drawCallCount = 0;
}

int Sprite::GetDrawCallCount()
{
	return drawCallCount;
}

ID2D1RenderTarget * Sprite::GetRT()
{
	return pRenderTarget;
}

int Sprite::GetWidth(spr spriteIndex)
{
	return spriteList[(unsigned int)spriteIndex].sprite_width;
}

int Sprite::GetHeight(spr spriteIndex)
{
	return spriteList[(unsigned int)spriteIndex].sprite_height;
}
