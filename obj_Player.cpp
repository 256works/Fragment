#include "stdafx.h"
#include "obj_Player.h"


obj_Player::obj_Player()
{
	objectIndex = obj::player;
	spriteIndex = spr::player;
	bbox = { -PLAYER_BBOX_SIZE, -PLAYER_BBOX_SIZE, PLAYER_BBOX_SIZE, PLAYER_BBOX_SIZE };
	depth = 0;
	playerScale = 4.0f;
	hspeed = 0.0f;
	vspeed = 0.0f;
	bullet_time = BULLET_RELOAD_TIME;
	isDead = false;
	dead_timer = 0;
	GC->Player = this;

	view_ease = 20.0f;
}


obj_Player::~obj_Player()
{
	GC->Player = NULL;
}

void obj_Player::Draw()
{
	if (!isDead)
	{
		Sprite::SetInterpolation(true);
		Sprite::DrawSprite(spriteIndex, 0, pos.x, pos.y, playerScale, playerScale, PointDirection(pos, GC->GetMousePos()), 1.0f);
		playerScale += (PLAYER_SCALE - playerScale) / 6.0f;
		Sprite::SetInterpolation(false);
	}

}

void obj_Player::Update()
{
	angle = PointDirection(pos, GC->GetMousePos());

#pragma region
	if (!isDead)
	{
		float mouseDist = PointDistance(pos, GC->GetMousePos());

		viewPos.x += ((pos.x + LengthdirX(Clamp(mouseDist / VIEW_PER_PLAYER, 0, VIEW_MAX_DIST), angle)) - viewPos.x) / view_ease;
		viewPos.y += ((pos.y + LengthdirY(Clamp(mouseDist / VIEW_PER_PLAYER, 0, VIEW_MAX_DIST), angle)) - viewPos.y) / view_ease;
		if (view_ease > VIEW_EASE)
			view_ease -= 0.25f;
		GC->SetViewPos(POINT({ (LONG)viewPos.x - GAME_WIDTH / 2, (LONG)viewPos.y - GAME_HEIGHT / 2 }));
	}

#pragma endregion Set view position
#pragma region
	if (!isDead)
	{
		if (KEY->isKeyDown('W'))
		{
			vspeed += (-PLAYER_SPEED - vspeed) / PLAYER_FRICTION;
		}
		else if (KEY->isKeyDown('S'))
		{
			vspeed += (PLAYER_SPEED - vspeed) / PLAYER_FRICTION;
		}
		else
		{
			vspeed += (0.0f - vspeed) / PLAYER_FRICTION;
		}
		if (KEY->isKeyDown('A'))
		{
			hspeed += (-PLAYER_SPEED - hspeed) / PLAYER_FRICTION;
		}
		else if (KEY->isKeyDown('D'))
		{
			hspeed += (PLAYER_SPEED - hspeed) / PLAYER_FRICTION;
		}
		else
		{
			hspeed += (0.0f - hspeed) / PLAYER_FRICTION;
		}
		pos.x += hspeed;
		pos.y += vspeed;
	}

#pragma endregion Keyboard move
#pragma region
	float distFromCenter = PointDistance(FPOINT({ GAME_ROOM_WIDTH / 2, GAME_ROOM_HEIGHT / 2 }), pos) - BOARD_RADIUS;
	float dirFromCenter = PointDirection(FPOINT({ GAME_ROOM_WIDTH / 2, GAME_ROOM_HEIGHT / 2 }), pos);
	if (distFromCenter > 0)
	{
		pos.x += LengthdirX(-distFromCenter, dirFromCenter);
		pos.y += LengthdirY(-distFromCenter, dirFromCenter);
	}
#pragma endregion Move limit
#pragma region
	if (!isDead)
	{
		if (bullet_time++ > BULLET_RELOAD_TIME)
			bullet_time = BULLET_RELOAD_TIME;
		if (KEY->isKeyDown(VK_LBUTTON))
		{
			if (bullet_time == BULLET_RELOAD_TIME)
			{
				bullet_time = 0;
				SOUND->Play(snd::player_shot, 0.8f);
				obj_Bullet* bullet = (obj_Bullet*)(GC->InstanceCreate(obj::bullet, (int)(pos.x + LengthdirX(10.0f, angle)),
					(int)(pos.y + LengthdirY(10.0f, angle))));
				bullet->angle = angle + (float)Irand(-BULLET_ANGLE_DEFF * 10, BULLET_ANGLE_DEFF * 10) / 10.0f;

			}

		}
	}
#pragma endregion Shoot bullet
#pragma region
	if (isDead)
	{
		dead_timer++;
		if (dead_timer == 50)
		{
			vector<GameObject*> enemyList = GC->vEnemy;
			for (vector<GameObject*>::iterator i = enemyList.begin(); i != enemyList.end(); ++i)
			{
				((obj_Enemy*)(*i))->Dead();
			}
		}

		if (dead_timer == 110)
		{
			if (GC->life > 0)
			{

				Replay();

			}
			else
			{
				// 게임오버
				GC->SetHighpass(true);
				((obj_GameManager*)(GC->GameManager))->isGameover = true;

			}
		}
	}
#pragma endregion Dead Timer

}

void obj_Player::Init()
{
	viewPos.x = pos.x;
	viewPos.y = pos.y;
	GC->SetViewPos(POINT({ (LONG)viewPos.x - GAME_WIDTH / 2, (LONG)viewPos.y - GAME_HEIGHT / 2 }));

}

void obj_Player::Dead()
{
	if (!isDead)
	{
		vector<GameObject*> objList = GC->GetObjectList();
		for (vector<GameObject*>::iterator i = objList.begin(); i != objList.end(); i++)
		{
			if ((*i)->GetObjType() == obj::enemy_gene)
				(*i)->InstanceDestroy();
		}
		isDead = true;
		dead_timer = 0;
		// 이펙트 생성
		GC->InstanceCreate(obj::huge_explosion, (int)(pos.x), (int)(pos.y));

	}
}

void obj_Player::Replay()
{
	vector<GameObject*> enemyList = GC->vEnemy;
	for (vector<GameObject*>::iterator i = enemyList.begin(); i != enemyList.end(); ++i)
	{
		((obj_Enemy*)(*i))->Dead();
	}

	SOUND->Play(snd::re_gen, 0.8f);

	GC->life--;
	pos = {
		GAME_ROOM_WIDTH / 2, GAME_ROOM_HEIGHT / 2
	};
	GC->InstanceCreate(obj::player_wave, (int)pos.x, (int)pos.y);

	((obj_GameManager*)(GC->GameManager))->timer = 0;

	playerScale = 4.0f;
	view_ease = 20.0f;
	isDead = false;
}
