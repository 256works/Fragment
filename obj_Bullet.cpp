#include "stdafx.h"
#include "obj_Bullet.h"


obj_Bullet::obj_Bullet()
{
	objectIndex = obj::bullet;
	spriteIndex = spr::bullet;
	bbox = { -BULLET_BBOX_SIZE, -BULLET_BBOX_SIZE, BULLET_BBOX_SIZE, BULLET_BBOX_SIZE };
	depth = 10;
	angle = 0.0f;
	first_scale = 0.7f;
}


obj_Bullet::~obj_Bullet()
{
}

void obj_Bullet::Draw()
{

	Sprite::SetInterpolation(true);

	Sprite::DrawSprite(spriteIndex, 0, pos.x, pos.y, 1.0f + first_scale, 1.0f + first_scale, angle, 1.0f);
	if (first_scale > 0.01f)
		Sprite::DrawSprite(spriteIndex, 0, pos.x, pos.y, 1.0f + first_scale, 1.0f + first_scale, angle, first_scale);
	first_scale += -first_scale / 4.0f;

	Sprite::SetInterpolation(false);

}

void obj_Bullet::Update()
{
	REPEAT(BULLET_COLLISION_ACCURACY)
	{
		pos.x += LengthdirX(BULLET_SPEED / BULLET_COLLISION_ACCURACY, angle);
		pos.y += LengthdirY(BULLET_SPEED / BULLET_COLLISION_ACCURACY, angle);

		float distFromCenter = PointDistance(FPOINT({ GAME_ROOM_WIDTH / 2, GAME_ROOM_HEIGHT / 2 }), pos) - BOARD_RADIUS;
		float dirFromCenter = PointDirection(FPOINT({ GAME_ROOM_WIDTH / 2, GAME_ROOM_HEIGHT / 2 }), pos);
		if (distFromCenter > 0)
		{
			FPOINT effectPos = {
				GAME_ROOM_WIDTH / 2 + LengthdirX((float)BOARD_RADIUS + 20.0f, dirFromCenter),
				GAME_ROOM_HEIGHT / 2 + LengthdirY((float)BOARD_RADIUS + 20.0f, dirFromCenter)
			};
			obj_BulletEffect* effect = (obj_BulletEffect*) GC->InstanceCreate(obj::bullet_effect, (int)effectPos.x, (int)effectPos.y);
			effect->gravity_angle = angle + 180;
			InstanceDestroy();
		}

	}
}

void obj_Bullet::Init()
{
}

void obj_Bullet::UserEvent(char number)
{
	obj_BulletEffect* effect = (obj_BulletEffect*)GC->InstanceCreate(obj::bullet_effect, (int)pos.x, (int)pos.y);
	effect->gravity_angle = angle + 180;
	InstanceDestroy();
}
