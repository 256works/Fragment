#include "stdafx.h"
#include "obj_Explosion.h"


obj_Explosion::obj_Explosion()
{
	depth = 20;
	scale = 1.0f;
	alpha = 1.0f;
}


obj_Explosion::~obj_Explosion()
{
}

void obj_Explosion::Draw()
{
	Sprite::DrawSprite(spr::explosion, 0, pos.x, pos.y, pow(scale, 2) *1.1f, pow(scale, 2) *1.1f, 0.0f, alpha*0.3f);
	Sprite::DrawSprite(spr::explosion, 0, pos.x, pos.y, scale, scale, 0.0f, 0.8f*alpha);
	Sprite::DrawSprite(spr::explosion, 0, pos.x, pos.y, 1.5f - scale / 1.4f, 1.5f - scale / 1.4f, 0.0f, alpha - 0.3f);
}

void obj_Explosion::Update()
{
	scale += (EXPLOSION_FINAL_SIZE - scale) / EXPLOSION_SCALE_EASE_SPEED;
	alpha += -alpha / EXPLOSION_ALPHA_EASE_SPEED;

	if (alpha < 0.01f)
		InstanceDestroy();
}

void obj_Explosion::Init()
{
	SOUND->Play(snd::explosion, 0.8f);
	GC->ScreenShake(EXPLOSION_SCREEN_SHAKE_AMOUNT);
}
