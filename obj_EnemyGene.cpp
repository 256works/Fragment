#include "stdafx.h"
#include "obj_EnemyGene.h"


obj_EnemyGene::obj_EnemyGene()
{
	depth = -10;
	alpha = 1.0f;
	scale = 1.0f;
	warn_cnt = 0;
	enemy_type = Irand(0, 3);
	objectIndex = obj::enemy_gene;
	angle = (float)Irand(0, 360);
}


obj_EnemyGene::~obj_EnemyGene()
{
}

void obj_EnemyGene::Draw()
{
	Sprite::SetInterpolation(true);
	Sprite::DrawSprite(spr::enemy_warning, 0, pos.x, pos.y, 1.0f + scale*0.5f, 1.0f + scale*0.5f, 0.0f, Clamp(0.3f+alpha, 0.0f, 1.0f) BLINK);
	
	Sprite::DrawSprite(spr::enemy_warning, 0, pos.x, pos.y, 1.8f - alpha*0.8f, 1.8f - alpha*0.8f, 0.0f, alpha * 0.6f BLINK);

	Sprite::DrawSprite(spr::enemy_warning_ring, 0, pos.x, pos.y, 1.8f - alpha*0.8f, 1.8f - alpha*0.8f, angle, 0.6f BLINK);

	Sprite::SetInterpolation(false);

	alpha -= 0.08f;
	if (alpha < 0.0f)
	{
		alpha = 1.0f;
		warn_cnt++;
	}

	if (warn_cnt == ENEMY_GENE_WARN_COUNT)
	{
		obj_Enemy* enemy = (obj_Enemy*) GC->InstanceCreate(obj::enemy, (int)pos.x, (int)pos.y);
		enemy->enemy_type = enemy_type;

		InstanceDestroy();
	}

	scale -= scale / 5.0f;

	angle += ENEMY_GENE_ROTATE_SPEED;
}

void obj_EnemyGene::Update()
{

}

void obj_EnemyGene::Init()
{
	SOUND->Play(snd::enemy_warning, 0.5f);

#pragma region
	float distFromCenter = PointDistance(FPOINT({ GAME_ROOM_WIDTH / 2, GAME_ROOM_HEIGHT / 2 }), pos) - BOARD_RADIUS;
	float dirFromCenter = PointDirection(FPOINT({ GAME_ROOM_WIDTH / 2, GAME_ROOM_HEIGHT / 2 }), pos);
	if (distFromCenter > 0)
	{
		pos.x += LengthdirX(-distFromCenter, dirFromCenter);
		pos.y += LengthdirY(-distFromCenter, dirFromCenter);
	}
#pragma endregion Move limit
}