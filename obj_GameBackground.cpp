#include "stdafx.h"
#include "obj_GameBackground.h"


obj_GameBackground::obj_GameBackground()
{
	depth = 100;
	spinlight_angle = (float)Irand(0, 360);
	spinlight_alpha = 1.0f;
	for (int i = 1; i < SPINLIGHT_COUNT; ++i)
	{
		spinlight_alpha_each[i-1] = ((float)i / (float)SPINLIGHT_COUNT) * 0.5f;
	}
	for (int i = 0; i < SPINLIGHT_COUNT; ++i)
	{
		spinlight_alpha_first[i] = -(float)i*1.4f-0.8f;
	}
	hexa_part_pos = 0;
	spinlight_scale_first = 0.8f;
}


obj_GameBackground::~obj_GameBackground()
{
}

void obj_GameBackground::Draw()
{
	// draw background

	Sprite::DrawSprite(spr::title_cloud, 0, VIEW.x + GAME_WIDTH / 2, VIEW.y + GAME_HEIGHT / 2,
		2.0f,
		2.0f,
		180.0f, 0.12f);

	Sprite::SetInterpolation(true);
	Sprite::DrawSprite(spr::game_spin_light, 0, GAME_ROOM_WIDTH / 2, GAME_ROOM_HEIGHT / 2, 4.0f * spinlight_scale_first, 4.0f * spinlight_scale_first, spinlight_angle, spinlight_alpha * spinlight_alpha_first[2] BLINK);
	Sprite::DrawSprite(spr::game_spin_light2, 0, GAME_ROOM_WIDTH / 2, GAME_ROOM_HEIGHT / 2, 4.0f * spinlight_scale_first, 4.0f * spinlight_scale_first, spinlight_angle);
	Sprite::DrawSprite(spr::game_ring, 0, GAME_ROOM_WIDTH / 2, GAME_ROOM_HEIGHT / 2, spinlight_scale_first, spinlight_scale_first, 0.0f, 1.0f * spinlight_alpha_first[0]);
	
	spinlight_scale_first += (1.0f - spinlight_scale_first) / 15.0f;

	for (int i = 1; i < SPINLIGHT_COUNT; ++i)
	{
		Sprite::DrawSprite(spr::game_ring, 0,
			GAME_ROOM_WIDTH  / 2 + (GAME_WIDTH/2 - VIEW.x)  * ((float)i/ 3.5f),
			GAME_ROOM_HEIGHT / 2 + (GAME_HEIGHT/2 - VIEW.y) * ((float)i/ 3.5f),
			1.0f + (float)i/3.8f,
			1.0f + (float)i/3.8f,
			0.0f,
			(spinlight_alpha_each[i-1]*((float)(SPINLIGHT_COUNT -i)*0.2f+0.1f))*spinlight_alpha_first[i] BLINK);
		spinlight_alpha_each[i-1] -= 0.02f;
		if (spinlight_alpha_each[i-1] < 0.3f)
			spinlight_alpha_each[i-1] += 1.0f - 0.3f;
	}
	for (int i = 0; i < SPINLIGHT_COUNT; ++i)
	{
		if (spinlight_alpha_first[i] < 1.0f)
			spinlight_alpha_first[i] += 0.1f;
	}
	FPOINT hexa_pos = {
		GAME_ROOM_WIDTH / 2 - 830 / 2,
		GAME_ROOM_HEIGHT / 2 - 831 / 2,
	};
	Sprite::DrawSprite(spr::hexa_bg, 0, hexa_pos.x, hexa_pos.y, 1.0f, 1.0f, 0.0f, 0.3f);
	Sprite::DrawSpritePart(spr::hexa_bg, 0, hexa_pos.x, hexa_pos.y + (hexa_part_pos < 0.0f ? 0.0f : hexa_part_pos), 0, (int)hexa_part_pos, 830, (int)(HEXA_LIGHT_HEIGHT + (hexa_part_pos < 0 ? hexa_part_pos : 0)), 0.7f BLINK);
	hexa_part_pos += 3.5f;
	if (hexa_part_pos > 831.0f)
		hexa_part_pos = -HEXA_LIGHT_HEIGHT;

	Sprite::SetInterpolation(false);
	spinlight_angle += 2.2f;
	if (spinlight_angle > 360.0f)
		spinlight_angle -= 360.0f;
	spinlight_alpha -= 0.02f;
	if (spinlight_alpha < 0.0f)
		spinlight_alpha = 1.0f;
	
}

void obj_GameBackground::Update()
{
}

void obj_GameBackground::Init()
{
}
