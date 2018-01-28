#pragma once
#define TRANSPARENT_COLOR RGB(255, 0, 255)
#define SPRITE_MAX ((unsigned int)spr::__max_count)

class Sprite
{
public:
	static SpriteInfo spriteList[SPRITE_MAX];
	static D2D1_BITMAP_INTERPOLATION_MODE interpolationMode;
	static ID2D1RenderTarget *pRenderTarget;
	static int drawCallCount;
public:
	Sprite();
	~Sprite();
	static void AddSprite(spr spriteIndex, const TCHAR* fname,
		int width, int height, int xorigin = 0, int yorigin = 0, int frameXcount = 1, int frameYcount = 1);
	static void DrawSprite(spr spriteIndex, int frameIndex, float x, float y, float xscale = 1.0f, float yscale = 1.0f, float angle = 0.0f, float alpha = 1.0f, float preXscale = 1.0f, float preYscale = 1.0f, float preAngle = 0.0f);
	static void DrawSpriteFix(spr spriteIndex, int frameIndex, float x, float y, float xscale = 1.0f, float yscale = 1.0f, float angle = 0.0f, float alpha = 1.0f, float preXscale = 1.0f, float preYscale = 1.0f, float preAngle = 0.0f);
	static void DrawSpritePart(spr spriteIndex, int frameIndex, float x, float y, int left, int top, int width, int height, float alpha = 1.0f);
	static int GetFrameCount(spr spriteIndex);
	static void SetRenderTarget(ID2D1RenderTarget* target);
	static void ReleaseSprite();
	static void SetInterpolation(bool mode);
	static void ResetDrawCallCount();
	static int GetDrawCallCount();
	static ID2D1RenderTarget* GetRT();
	static int GetWidth(spr spriteIndex);
	static int GetHeight(spr spriteIndex);

};