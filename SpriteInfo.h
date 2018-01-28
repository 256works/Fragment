#pragma once
#include "stdafx.h"

class SpriteInfo
{
public:
	ID2D1Bitmap* pBmp;
	POINT sprite_origin_pos;
	int sprite_width;
	int sprite_height;
	int max_frame;
	int frame_xcount;
	int frame_ycount;

	SpriteInfo()
	{
		pBmp = NULL;
		sprite_origin_pos = POINT({ 0, 0 });
		sprite_width = 0;
		sprite_height = 0;
		max_frame = 0;
		frame_xcount = 1;
		frame_ycount = 1;
	}
};