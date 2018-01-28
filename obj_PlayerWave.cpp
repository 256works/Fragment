#include "stdafx.h"
#include "obj_PlayerWave.h"


obj_PlayerWave::obj_PlayerWave()
{
	depth = 2;
	alpha = 1.0f;
	scale = 0.5f;
}


obj_PlayerWave::~obj_PlayerWave()
{
}

void obj_PlayerWave::Draw()
{
	Sprite::DrawSprite(spr::explosion2_ring, 0, pos.x, pos.y, scale, scale, 0.0f, alpha BLINK);
}

void obj_PlayerWave::Update()
{
	scale += (1.5f - scale) / 10.0f;
	alpha -= 0.02f;
	if (alpha < 0)
		InstanceDestroy();
}

void obj_PlayerWave::Init()
{

}
