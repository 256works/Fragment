#include "stdafx.h"
#include "obj_Enemy.h"


obj_Enemy::obj_Enemy()
{
	objectIndex = obj::enemy;
	spriteIndex = spr::enemy;
	bbox = { -ENEMY_BBOX_SIZE, -ENEMY_BBOX_SIZE, ENEMY_BBOX_SIZE, ENEMY_BBOX_SIZE };
	depth = -4;

	enemy_type = Irand(0, 3);
	angle = 0.0f;
	angle_speed_deg = 0.0f;
	hp = ENEMY_HP;
	alpha = 1.0f;
	force_to = { 0.0f, 0.0f };
	scale = 3.0f;

	direction = (float)Irand(0, 360);

	timer = 0;
	toPos = pos;
	gravity_speed = { 0.0f, 0.0f };

	if (Irand(0, 1) == 0)
		rotate_to = true;
	else
		rotate_to = false;

}


obj_Enemy::~obj_Enemy()
{

}

void obj_Enemy::Draw()
{
	Sprite::SetInterpolation(true);
	Sprite::DrawSprite(spriteIndex, enemy_type, pos.x, pos.y, scale, scale, angle, alpha);
	Sprite::SetInterpolation(false);

	angle += ENEMY_IMAGE_ROTATE_SPEED * (LengthdirX(0.2f, angle_speed_deg) + 0.8f);
	angle_speed_deg += 5.0f;
	if (angle > 360.0f)
		angle -= 360.0f;
	if (angle_speed_deg > 360.0f)
		angle_speed_deg -= 360.0f;
	scale += (1.0f - scale) / 6.0f;
}

void obj_Enemy::Update()
{
	alpha += (1.0f - alpha) / 4.0f;

	UseCollision(obj::bullet, GC->vBullet);
	UseCollision(obj::enemy, GC->vEnemy);
	UseCollision(GC->Player);

	// death
	if (hp <= 0)
	{
		GC->game_score += ENEMY_SCORE + (((obj_GameManager*)(GC->GameManager))->level-1)*10;
		Dead();
	}

	pos.x += force_to.x;
	pos.y += force_to.y;

	force_to.x += -force_to.x / FORCE_MOVE_FRICTION;
	force_to.y += -force_to.y / FORCE_MOVE_FRICTION;

#pragma region
	float distFromCenter = PointDistance(FPOINT({ GAME_ROOM_WIDTH / 2, GAME_ROOM_HEIGHT / 2 }), pos) - BOARD_RADIUS;
	float dirFromCenter = PointDirection(FPOINT({ GAME_ROOM_WIDTH / 2, GAME_ROOM_HEIGHT / 2 }), pos);
	if (distFromCenter > 0)
	{
		pos.x += LengthdirX(-distFromCenter, dirFromCenter);
		pos.y += LengthdirY(-distFromCenter, dirFromCenter);

		switch (enemy_type)
		{
		case 0: // circle
			direction = (dirFromCenter + 180) + (float)Irand(-15, 15);
			break;
		case 1: // pentagon
			break;
		case 2: // triangle
			gravity_speed = { 0.0f, 0.0f };
			break;
		case 3: // diamond
			direction = (dirFromCenter + 180) + (float)Irand(-15, 15);
			break;
		case 4: // star
			direction = (dirFromCenter + 180) + (float)Irand(-15, 15);
			break;
		case 5: // sun
			direction = (dirFromCenter + 180) + (float)Irand(-15, 15);
			break;
		case 6: // hexagon
			direction = (dirFromCenter + 180) + (float)Irand(-15, 15);
			break;
		case 7: // line
			gravity_speed = { 0.0f, 0.0f };
			break;
		}
	}
#pragma endregion Move Limit
#pragma region
	if (!PLAYER_ISDEAD)
	{
		switch (enemy_type)
		{
		case 0: // circle
			pos.x += LengthdirX(ENEMY0_SPEED, direction);
			pos.y += LengthdirY(ENEMY0_SPEED, direction);
			break;
		case 1: // pentagon
			direction = PointDirection(pos, GC->Player->GetPos());
			pos.x += LengthdirX(ENEMY1_SPEED, direction);
			pos.y += LengthdirY(ENEMY1_SPEED, direction);
			break;
		case 2: // triangle
			direction = PointDirection(pos, GC->Player->GetPos());
			gravity_speed = {
				gravity_speed.x + LengthdirX(ENEMY2_GRAVITY_SPEED, direction),
				gravity_speed.y + LengthdirY(ENEMY2_GRAVITY_SPEED, direction)
			};
			pos.x += gravity_speed.x;
			pos.y += gravity_speed.y;

			if (abs(gravity_speed.x) > ENEMY2_GRAVITY_MAXSPEED)
			{
				if (gravity_speed.x > 0)
					gravity_speed.x = ENEMY2_GRAVITY_MAXSPEED;
				else
					gravity_speed.x = -ENEMY2_GRAVITY_MAXSPEED;

			}
			if (abs(gravity_speed.y) > ENEMY2_GRAVITY_MAXSPEED)
			{
				if (gravity_speed.y > 0)
					gravity_speed.y = ENEMY2_GRAVITY_MAXSPEED;
				else
					gravity_speed.y = -ENEMY2_GRAVITY_MAXSPEED;
			}

			break;
		case 3: // diamond
			timer++;
			if (timer > ENEMY3_TIMER)
			{
				timer = 0;
				direction = PointDirection(pos, GC->Player->GetPos());
				toPos = {
					pos.x + LengthdirX(ENEMY3_MOVE_DISTANCE_ONCE, direction),
					pos.y + LengthdirY(ENEMY3_MOVE_DISTANCE_ONCE, direction),
				};
			}
			pos.x += (toPos.x - pos.x) / ENEMY3_EASE;
			pos.y += (toPos.y - pos.y) / ENEMY3_EASE;

			break;
		case 4: // star
			timer++;
			if (timer > ENEMY4_TIMER)
			{
				timer = 0;
				direction = PointDirection(pos, GC->Player->GetPos());
				toPos = {
					pos.x + LengthdirX(ENEMY4_MOVE_DISTANCE_ONCE, direction),
					pos.y + LengthdirY(ENEMY4_MOVE_DISTANCE_ONCE, direction),
				};
			}
			pos.x += (toPos.x - pos.x) / ENEMY4_EASE;
			pos.y += (toPos.y - pos.y) / ENEMY4_EASE;

			break;
		case 5: // sun
			pos.x += LengthdirX(ENEMY5_SPEED, direction);
			pos.y += LengthdirY(ENEMY5_SPEED, direction);
			if (rotate_to)
			{
				direction += ENEMY5_ROTATE_SPEED;
			}
			else
			{
				direction -= ENEMY5_ROTATE_SPEED;
			}
			if (direction >= 360.0f)
				direction -= 360.0f;
			if (direction <= 0.0f)
				direction += 360.0f;
			break;
		case 6: // hexagon
			timer++;
			if (timer > ENEMY6_TIMER)
			{
				timer = 0;
				direction = (float)Irand(0, 360);
				toPos = {
					pos.x + LengthdirX(ENEMY6_MOVE_DISTANCE_ONCE, direction),
					pos.y + LengthdirY(ENEMY6_MOVE_DISTANCE_ONCE, direction),
				};
			}
			pos.x += (toPos.x - pos.x) / ENEMY6_EASE;
			pos.y += (toPos.y - pos.y) / ENEMY6_EASE;

			break;
		case 7: // line
			timer++;
			if (timer > ENEMY7_MOVE_TIME)
			{
				direction = PointDirection(pos, GC->Player->GetPos());
				gravity_speed = {
					gravity_speed.x + LengthdirX(ENEMY7_GRAVITY_SPEED, direction),
					gravity_speed.y + LengthdirY(ENEMY7_GRAVITY_SPEED, direction)
				};
				pos.x += gravity_speed.x;
				pos.y += gravity_speed.y;

				if (abs(gravity_speed.x) > ENEMY7_GRAVITY_MAXSPEED)
				{
					if (gravity_speed.x > 0)
						gravity_speed.x = ENEMY7_GRAVITY_MAXSPEED;
					else
						gravity_speed.x = -ENEMY7_GRAVITY_MAXSPEED;

				}
				if (abs(gravity_speed.y) > ENEMY7_GRAVITY_MAXSPEED)
				{
					if (gravity_speed.y > 0)
						gravity_speed.y = ENEMY7_GRAVITY_MAXSPEED;
					else
						gravity_speed.y = -ENEMY7_GRAVITY_MAXSPEED;
				}
			}
			
			break;
		}
	}

#pragma endregion Enemy Moving
}

void obj_Enemy::Init()
{
	toPos = pos;
}

void obj_Enemy::Dead()
{
	GC->InstanceCreate(obj::explosion, (int)pos.x, (int)pos.y);
	InstanceDestroy();
}

void obj_Enemy::CollisionEvent(obj object, GameObject * inst)
{
	switch (object)
	{
	case obj::bullet:

		GC->UserEvent(inst, 0);
		SOUND->Play(snd::enemy_hit, 0.5f);
		hp -= 1;
		alpha = 0.5f;
		force_to.x = LengthdirX(FORCE_MOVE_AMOUNT, ((obj_Bullet*)inst)->angle);
		force_to.y = LengthdirY(FORCE_MOVE_AMOUNT, ((obj_Bullet*)inst)->angle);
		break;
	case obj::enemy:
	{
		float directionToOtherEnemy = PointDirection(pos, inst->GetPos());
		pos.x += LengthdirX(OVERED_ENEMY_MOVE_SPEED, directionToOtherEnemy + 180.0f);
		pos.y += LengthdirY(OVERED_ENEMY_MOVE_SPEED, directionToOtherEnemy + 180.0f);
	}
		break;
	case obj::player:
		((obj_Player*)inst)->Dead();
		break;
	default:
		return;
	}
}
