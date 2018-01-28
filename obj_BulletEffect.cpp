#include "stdafx.h"
#include "obj_BulletEffect.h"


obj_BulletEffect::obj_BulletEffect()
{
	alpha = 1.0f;
	angle = (float)Irand(0, 360);
	depth = 8;
	speed = 3.0f;
	gravity_angle = 0.0f;
}

obj_BulletEffect::~obj_BulletEffect()
{
}

void obj_BulletEffect::Draw()
{
	Sprite::DrawSprite(spr::bullet_effect, 0, pos.x, pos.y, (1.0f - alpha)*0.8f+0.5f, (1.0f - alpha)*0.8f+0.5f, angle, alpha*0.7f);
}

void obj_BulletEffect::Update()
{
	if (alpha > 0.0f)
	{
		alpha -= 0.1f;
	}
	else
	{
		InstanceDestroy();
	}
	speed += -speed/8.0f;
	pos.x += LengthdirX(speed, gravity_angle);
	pos.y += LengthdirY(speed, gravity_angle);

}
