#include "stdafx.h"
#include "obj_logo.h"


obj_logo::obj_logo()
{
}


obj_logo::~obj_logo()
{
}

void obj_logo::Init()
{

	for (int i = 0; i < 5; ++i)
		logo_alpha[i] = 0.0f;
	logo_alpha_all = 1.0f;

	timer = 0;
}

void obj_logo::Draw()
{
#ifdef _DEBUG
	{
		GC->NextScene();
	}
#endif
	Sprite::SetInterpolation(true);
	for (int i = 0; i < 5; ++i)
	{
		Sprite::DrawSprite(spr::works256, i, GAME_WIDTH / 2, GAME_HEIGHT / 2 +(1-logo_alpha[i])*8, 1.0f, 1.0f, 0.0f, logo_alpha[i] * logo_alpha_all);
	
		if (timer > 30 + i*5)
		{
			logo_alpha[i] += (1.0f- logo_alpha[i]) / 18.0f;
		}
	}
	Sprite::SetInterpolation(false);

	if (timer > 130)
		logo_alpha_all += -logo_alpha_all / 8.0f;

	if (timer > 160)
		GC->NextScene();

	++timer;
}

void obj_logo::Update()
{

}
