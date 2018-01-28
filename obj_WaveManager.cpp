#include "stdafx.h"
#include "obj_WaveManager.h"


obj_WaveManager::obj_WaveManager()
{
	type = 0;

	timer = -WAVE_DELAY;
	value = 0;
	count = 0;
	rand_angle = (float)Irand(0, 360);
	angle = 0.0f;
}


obj_WaveManager::~obj_WaveManager()
{
}

void obj_WaveManager::Draw()
{
}

void obj_WaveManager::Update()
{
	if (PLAYER_ISDEAD)
	{
		EndWave();
	}

	//
	if (timer >= 0)
	{
#pragma region
		switch (type)
		{
			// beginner pattern
		case 0:
		{
			if (timer % 20 == 0)
			{
				PosToCenterAround(200.0f, (float)value);
				EnemyCreate(0);
				value += 60;
			}
			if (count >= 6)
			{
				EndWave();
			}
		}
			break;
		case 1:
		{
			if (timer % 20 == 0)
			{
				PosToCenterAround(200.0f, (float)value);
				EnemyCreate(0);
				value += 90;
			}
			if (count >= 4)
			{
				EndWave();
			}
		}
			break;
		case 2:
		{
			if (timer == 0)
			{
				pos.y = GAME_ROOM_HEIGHT / 2 - 300;
				pos.x = GAME_ROOM_WIDTH / 2 - 70;
				EnemyCreate(0);
			}
			if (timer == 5)
			{
				pos.x = GAME_ROOM_WIDTH / 2 + 70;
				EnemyCreate(0);
			}
			if (timer == 30)
			{
				pos.y = GAME_ROOM_HEIGHT / 2 + 300;
				pos.x = GAME_ROOM_WIDTH / 2 - 70;
				EnemyCreate(0);
			}
			if (timer == 35)
			{
				pos.x = GAME_ROOM_WIDTH / 2 + 70;
				EnemyCreate(0);
			}
			if (timer == 60)
			{
				pos.x = GAME_ROOM_WIDTH / 2 + 300;
				pos.y = GAME_ROOM_HEIGHT / 2 - 70;
				EnemyCreate(0);
			}
			if (timer == 65)
			{
				pos.y = GAME_ROOM_HEIGHT / 2 + 70;
				EnemyCreate(0);
			}
			if (timer == 90)
			{
				pos.x = GAME_ROOM_WIDTH / 2 - 300;
				pos.y = GAME_ROOM_HEIGHT / 2 - 70;
				EnemyCreate(0);
			}
			if (timer == 95)
			{
				pos.y = GAME_ROOM_HEIGHT / 2 + 70;
				EnemyCreate(0);
				EndWave();
			}
		}
			break;
		case 3:
		{
			if (timer == 0)
				pos.x = GAME_ROOM_WIDTH / 2 - 200;

			pos.y = GAME_ROOM_HEIGHT / 2;
			if (timer % 10 == 0)
			{
				EnemyCreate(0);
				pos.x += 50;
			}
			if (count >= 9)
				EndWave();
		}
			break;
			// normal pattern
		case 4:
		{
			if (timer % 10 == 0)
			{
				PosToPlayerAround(350, rand_angle);
				EnemyCreate(1);
				rand_angle -= 3.5f;
			}
			if (count >= 8)
				EndWave();
		}
			break;
		case 5:
		{
			if (timer == 0)
				value = 400;
			if (timer % 8 == 0)
			{
				PosToCenterAround((float)value, 45.0f);
				EnemyCreate(1);
				PosToCenterAround((float)value, 180-45);
				EnemyCreate(0);
				value -= 100;
			}
			if (value <= -400)
				EndWave();
		}
			break;
		case 6:
		{
			if (timer == 0)
				value = -400;
			if (timer % 8 == 0)
			{
				PosToCenterAround((float)value, 45.0f);
				EnemyCreate(1);
				PosToCenterAround((float)value, 180.0f - 45.0f);
				EnemyCreate(0);
				value += 100;
			}
			if (value >= 400)
				EndWave();
		}
			break;
		case 7:
		{
			if (timer % 30 == 0)
			{
				PosToCenterAround(300.0f, rand_angle);
				EnemyCreate(1);
				PosToCenterAround(300.0f, rand_angle + 180.0f);
				EnemyCreate(1);

				rand_angle += 20;
			}
			if (count == 9 * 2)
				EndWave();
		}
			break;
		case 8:
		{
			if (timer % 30 == 0)
			{
				PosToCenterAround(300.0f, rand_angle);
				EnemyCreate(1);
				PosToCenterAround(300.0f, rand_angle + 180.0f);
				EnemyCreate(1);

				rand_angle -= 20;
			}
			if (count == 9 * 2)
				EndWave();
		}
			break;
		case 9:
		{
			if (timer == 0)
			{
				value = 100;
			}
			if (timer % 5 == 0)
			{
				PosToCenterAround((float)value, angle);
				EnemyCreate(2);
				angle += 90.0f;
				if (count == 4)
				{
					value += 100;
					angle -= 45.0f;
				}
			}
			if (count >= 8)
			{
				EndWave();
			}
		}
			break;
		case 10:
		{
			for (int i = -300; i <= 300; i += 150)
			{
				pos.y = (float)(GAME_ROOM_HEIGHT / 2 + i);

				pos.x = (float)(GAME_ROOM_WIDTH / 2 + 200);
				EnemyCreate(3);
				pos.x = (float)(GAME_ROOM_WIDTH / 2 - 200);
				EnemyCreate(3);
			}
			EndWave();
		}
			break;
		case 11:
		{
			if (timer == 0)
				value = 200;
			if (timer % 10 == 0)
			{
				PosToCenterAround((float)value, angle);
				if (value == 200)
					EnemyCreate(3);
				else
					EnemyCreate(1);

				angle += 60;
				if (count == 6)
					value = 300;
			}
			if (count >= 12)
			{
				EndWave();
			}
		}
			break;
			// normal pattern 2
		case 12:
		{
			if (timer % 15 == 0)
			{
				int dist = 300;
				pos.x = (float)(GAME_ROOM_WIDTH / 2 - dist);
				pos.y = (float)(GAME_ROOM_HEIGHT / 2 - dist);
				EnemyCreate(1);
				pos.x = (float)(GAME_ROOM_WIDTH / 2 - dist);
				pos.y = (float)(GAME_ROOM_HEIGHT / 2 + dist);
				EnemyCreate(1);
				pos.x = (float)(GAME_ROOM_WIDTH / 2 + dist);
				pos.y = (float)(GAME_ROOM_HEIGHT / 2 - dist);
				EnemyCreate(1);
				pos.x = (float)(GAME_ROOM_WIDTH / 2 + dist);
				pos.y = (float)(GAME_ROOM_HEIGHT / 2 + dist);
				EnemyCreate(1);
			}
			if (count >= 7*4)
			{
				EndWave();
			}
		}
			break;
		case 13:
		{
			pos.x = GAME_ROOM_WIDTH / 2 + 300.0f;

			for (int i = 0; i < 8; i++)
			{
				if (timer%60 == i)
				{
					pos.y = GAME_ROOM_HEIGHT / 2 - 100.0f + 200.0f * ((float)i/7.0f) ;
					EnemyCreate(1);
					break;
				}
			}

			if (timer == 60 * 3 - 10)
				EndWave();
		}
			break;
		case 14:
		{
			pos.x = GAME_ROOM_WIDTH / 2 - 300.0f;

			for (int i = 0; i < 5; i++)
			{
				if (timer % 60 == i*2)
				{
					pos.y = GAME_ROOM_HEIGHT/ 2 - 100.0f + 200.0f * ((float)i / 4.0f);
					EnemyCreate(2);
					break;
				}
			}

			if (timer == 60 * 3 - 10)
				EndWave();
		}
			break;
		case 15:
		{
			if (timer % 17 == 0)
			{
				PosToPlayerAround(0.0f, 0.0f);
				EnemyCreate(3);
			}
			if (count >= 10)
				EndWave();
		}
			break;
		case 16:
		{
			if (timer % 4 == 0)
			{
				PosToCenterAround(350.0f, rand_angle);
				EnemyCreate(0);
				PosToCenterAround(350.0f, rand_angle + 180.0f);
				EnemyCreate(0);

				rand_angle += 66;
			}
			if (count == 20 * 2)
				EndWave();
		}
			break;
		case 17:
		{
			if (timer == 0)
				value = 50;
			if (timer % 10 == 0)
			{
				PosToCenterAround((float)value, rand_angle);
				EnemyCreate(1);

				rand_angle += 30;
				value += 14;
			}
			if (value >= 400)
				EndWave();
		}
			break;
		case 18:
		{
			if (timer == 0)
				value = 400;
			if (timer % 10 == 0)
			{
				PosToCenterAround((float)value, rand_angle);
				EnemyCreate(1);

				rand_angle -= 30;
				value -= 14;
			}
			if (value <= 50)
				EndWave();
		}
			break;
		case 19:
		{
			if (timer == 50)
			{
				for (int i = 0; i < 360; i += 30)
				{
					PosToPlayerAround(100.0f, (float)i);
					EnemyCreate(2);
				}
			}

			if (timer == 150)
			{
				for (int i = 0; i < 360; i += 30)
				{
					PosToPlayerAround(100.0f, (float)i);
					EnemyCreate(2);
				}
			}

			if (timer == 250)
			{
				for (int i = 0; i < 360; i += 30)
				{
					PosToPlayerAround(100.0f, (float)i);
					EnemyCreate(2);
					EndWave();
				}
			}
		}
			break;
		case 20:
		{
			if (timer % 8 == 0)
			{
				PosToCenter();
				pos.x += LengthdirX(300.0f, rand_angle);
				pos.y += LengthdirY(300.0f, rand_angle+45.0f);
				EnemyCreate(1);

				rand_angle += 20;
			}
			if (count >= 17*2)
				EndWave();
		}
			break;
			// hard pattern
		case 21:
		{
			if (timer % 5 == 0)
			{
				PosToCenter();
				pos.x += LengthdirX(300.0f, rand_angle);
				pos.y += LengthdirY(300.0f, rand_angle*2.0f);
				EnemyCreate(1);
				rand_angle += 10;
			}
			if (count >= 70)
				EndWave();
		}
			break;
		case 22:
		{
			if (timer == 0)
				value = 20;
			if (timer % value == 0)
			{
				PosToPlayerAround(250.0f, rand_angle);
				if (count % 2 == 0)
					EnemyCreate(5);
				else
					EnemyCreate(0);

				if (value > 2)
					value--;
				rand_angle += 25.0f;
			}
			if (count >= 30)
				EndWave();
		}
			break;
		case 23:
		{
			if (timer == 0)
			{
				pos.x = GAME_ROOM_WIDTH / 2 + 300;
				pos.y = GAME_ROOM_HEIGHT / 2 - 300;
			}
			if (timer > 30 && count <= 20)
			{
				if (timer % 1 == 0)
				{
					pos.x -= 300/20;
					pos.y += 300/20;
					EnemyCreate(2);
				}
			}

			if (timer == 98)
			{
				pos.x = GAME_ROOM_WIDTH / 2 - 300;
				pos.y = GAME_ROOM_HEIGHT / 2 - 300;
			}

			if (timer > 100 && count <= 40)
			{
				if (timer % 1 == 0)
				{
					pos.x += 300/20;
					pos.y += 300/20;
					EnemyCreate(2);
				}
			}

			if (timer == 168)
			{
				pos.x = GAME_ROOM_WIDTH / 2 - 300;
				pos.y = GAME_ROOM_HEIGHT / 2 + 300;
			}

			if (timer > 170 && count <= 60)
			{
				if (timer % 1 == 0)
				{
					pos.x += 300 / 20;
					pos.y -= 300 / 20;
					EnemyCreate(2);
				}
			}

			if (timer == 238)
			{
				pos.x = GAME_ROOM_WIDTH / 2 + 300;
				pos.y = GAME_ROOM_HEIGHT / 2 + 300;
			}

			if (timer > 240 && count <= 80)
			{
				if (timer % 1 == 0)
				{
					pos.x -= 300 / 20;
					pos.y -= 300 / 20;
					EnemyCreate(2);
				}
			}

			if (count >= 80)
				EndWave();
		}
			break;
		case 24:
		{
			if (timer == 0)
			{
				pos.y = GAME_ROOM_HEIGHT / 2 - 300;
				pos.x = GAME_ROOM_WIDTH / 2 - 70;
				EnemyCreate(4);
			}
			if (timer == 5)
			{
				pos.x = GAME_ROOM_WIDTH / 2 + 70;
				EnemyCreate(4);
			}
			if (timer == 30)
			{
				pos.y = GAME_ROOM_HEIGHT / 2 + 300;
				pos.x = GAME_ROOM_WIDTH / 2 - 70;
				EnemyCreate(4);
			}
			if (timer == 35)
			{
				pos.x = GAME_ROOM_WIDTH / 2 + 70;
				EnemyCreate(4);
			}
			if (timer == 60)
			{
				pos.x = GAME_ROOM_WIDTH / 2 + 300;
				pos.y = GAME_ROOM_HEIGHT / 2 - 70;
				EnemyCreate(4);
			}
			if (timer == 65)
			{
				pos.y = GAME_ROOM_HEIGHT / 2 + 70;
				EnemyCreate(4);
			}
			if (timer == 90)
			{
				pos.x = GAME_ROOM_WIDTH / 2 - 300;
				pos.y = GAME_ROOM_HEIGHT / 2 - 70;
				EnemyCreate(4);
			}
			if (timer == 95)
			{
				pos.y = GAME_ROOM_HEIGHT / 2 + 70;
				EnemyCreate(4);
				timer = -1;
			}
			if (count >= 8 * 4)
				EndWave();
		}
			break;
		case 25:
		{
			if (timer % 5 == 0)
			{
				PosToPlayerAround(0.0f, 0.0f);
				pos.x += LengthdirX(((obj_Player*)(GC->Player))->hspeed * 18.0f, 0);
				pos.y += LengthdirY(((obj_Player*)(GC->Player))->vspeed * 18.0f, 270);

				EnemyCreate(6);
			}
			if (count >= 40)
				EndWave();
		}
			break;
		case 26:
		{
			if (timer % 3 == 0)
			{
				PosToPlayerAround(0.0f, 0.0f);
				pos.x += LengthdirX(((obj_Player*)(GC->Player))->hspeed * 35.0f, 0);
				pos.y += LengthdirY(((obj_Player*)(GC->Player))->vspeed * 35.0f, 270);
				if (count %2 == 0)
					EnemyCreate(4);
				else
					EnemyCreate(3);

			}
			if (count >= 40)
				EndWave();
		}
			break;
		case 27:
		{
			if (timer == 0)
				value = 50;
			if (timer % 3 == 0)
			{
				PosToCenterAround((float)value, rand_angle);
				EnemyCreate(1);

				rand_angle += 30;
				value += 10;
			}
			if (value >= 400)
				EndWave();
		}
			break;
		case 28:
		{
			if (timer % 30 == 0)
			{
				int dist = 200;
				pos.x = (float)(GAME_ROOM_WIDTH / 2 - dist);
				pos.y = (float)(GAME_ROOM_HEIGHT / 2 - dist);
				EnemyCreate(4);
				pos.x = (float)(GAME_ROOM_WIDTH / 2 - dist);
				pos.y = (float)(GAME_ROOM_HEIGHT / 2 + dist);
				EnemyCreate(4);
				pos.x = (float)(GAME_ROOM_WIDTH / 2 + dist);
				pos.y = (float)(GAME_ROOM_HEIGHT / 2 - dist);
				EnemyCreate(4);
				pos.x = (float)(GAME_ROOM_WIDTH / 2 + dist);
				pos.y = (float)(GAME_ROOM_HEIGHT / 2 + dist);
				EnemyCreate(4);
			}
			if (count >= 7 * 4)
			{
				EndWave();
			}
		}
			break;
		case 29:
		{
			pos.x = GAME_ROOM_WIDTH / 2 + 300.0f;

			for (int i = 0; i < 8; i++)
			{
				if (timer % 50 == i)
				{
					pos.y = GAME_ROOM_HEIGHT / 2 - 150.0f + 300.0f * ((float)i / 7.0f);
					EnemyCreate(7);
					break;
				}
			}

			if (timer == 50 * 3 - 5)
				EndWave();
		}
			break;
		case 30:
		{
			pos.x = GAME_ROOM_WIDTH / 2 - 300.0f;

			for (int i = 0; i < 8; i++)
			{
				if (timer % 50 == i)
				{
					pos.y = GAME_ROOM_HEIGHT / 2 - 150.0f + 300.0f * ((float)i / 7.0f);
					EnemyCreate(7);
					break;
				}
			}

			if (timer == 50 * 3 - 5)
				EndWave();
		}
			break;
		case 31:
		{
			if (timer % 4 == 0)
			{
				PosToCenterAround(150.0f, rand_angle);
				EnemyCreate(5);
				PosToCenterAround(150.0f, rand_angle + 180.0f);
				EnemyCreate(5);

				rand_angle += 66;
			}
			if (count == 20 * 2)
				EndWave();
		}
			break;
		case 32:
		{
			if (timer == 30)
			{
				for (int i = 0; i < 360; i += 30)
				{
					PosToPlayerAround(100.0f, (float)i);
					EnemyCreate(4);
				}
			}

			if (timer == 60)
			{
				for (int i = 0; i < 360; i += 30)
				{
					PosToPlayerAround(200.0f, (float)i);
					EnemyCreate(4);
				}
			}

			if (timer == 90)
			{
				for (int i = 0; i < 360; i += 30)
				{
					PosToPlayerAround(300.0f, (float)i);
					EnemyCreate(4);
					EndWave();
				}
			}
		}
			break;
		case 33:
		{
			if (timer % 4 == 0)
			{
				PosToCenter();
				pos.x += LengthdirX(150.0f, rand_angle);
				pos.y += LengthdirY(350.0f, rand_angle - 45.0f);
				EnemyCreate(2);

				rand_angle += 20;
			}
			if (count >= 18 * 4)
				EndWave();
		}
			break;
		case 34:
		{
			if (timer == 0)
				value = 400;
			if (timer % 50 == 0)
			{
				PosToCenterAround((float)value, 0.0f);
				EnemyCreate(7);
				PosToCenterAround((float)value, 90.0f);
				EnemyCreate(7);
				PosToCenterAround((float)value, 180.0f);
				EnemyCreate(7);
				PosToCenterAround((float)value, 270.0f);
				EnemyCreate(7);

				value -= 80;
			}
			if (value == 0)
				EndWave();
		}
			break;
		case 35:
		{
			if (timer % 3 == 0)
			{
				PosToPlayerAround(280, PointDirection(GC->Player->GetPos(), GC->GetMousePos())+180);
				EnemyCreate(2);
			}
			if (count >= 40)
				EndWave();
		}
			break;
		case 36:
		{
			if (timer == 0)
				value = 400;
			if (timer % 4 == 0)
			{
				PosToCenterAround((float)value, 45.0f);
				if (count % 4 > 1)
					EnemyCreate(5);
				else
					EnemyCreate(6);

				PosToCenterAround((float)value, 180 - 45);
				if (count % 4 > 1)
					EnemyCreate(5);
				else
					EnemyCreate(6);
				value -= 50;
			}
			if (value <= -400)
				EndWave();
		}
			break;
		case 37:
		{
			if (timer == 0)
				value = -400;
			if (timer % 4 == 0)
			{
				PosToCenterAround((float)value, 45.0f);
				if (count % 4 > 1)
					EnemyCreate(5);
				else
					EnemyCreate(6);

				PosToCenterAround((float)value, 180 - 45);
				if (count % 4 > 1)
					EnemyCreate(5);
				else
					EnemyCreate(6);
				value += 50;
			}
			if (value >= 400)
				EndWave();
		}
			break;
		case 38:
		{
			if (timer % 3 == 0)
			{
				PosToCenterAround(300.0f, rand_angle);
				EnemyCreate(1);
				PosToCenterAround(300.0f, rand_angle + 180.0f);
				EnemyCreate(1);

				rand_angle += 30;
			}
			if (count == 9*3-1)
				EndWave();
		}
			break;
		case 39:
		{
			for (int i = -300; i <= 300; i += 150)
			{
				pos.x = (float)(GAME_ROOM_WIDTH / 2 + i);

				pos.y = (float)(GAME_ROOM_HEIGHT / 2 + 200);
				EnemyCreate(7);
				pos.y = (float)(GAME_ROOM_HEIGHT / 2 - 200);
				EnemyCreate(7);
			}
			EndWave();
		}
			break;

		default:
			EndWave();
			break;
		}
#pragma endregion enemy generate type
	}
	//

	timer++;
}

void obj_WaveManager::Init()
{
}

void obj_WaveManager::EnemyCreate(char enemyType)
{
	obj_EnemyGene* enemy_gene = (obj_EnemyGene*) GC->InstanceCreate(obj::enemy_gene, (int)pos.x, (int)pos.y);
	enemy_gene->enemy_type = enemyType;
	count++;
}

bool obj_WaveManager::CheckOutside()
{
	float distFromCenter = PointDistance(FPOINT({ GAME_ROOM_WIDTH / 2, GAME_ROOM_HEIGHT / 2 }), pos) - BOARD_RADIUS;
	float dirFromCenter = PointDirection(FPOINT({ GAME_ROOM_WIDTH / 2, GAME_ROOM_HEIGHT / 2 }), pos);
	if (distFromCenter > 0)
	{
		return true;
	}
	return false;
}

void obj_WaveManager::PosToCenter()
{
	pos = {
		GAME_ROOM_WIDTH / 2, GAME_ROOM_HEIGHT / 2
	};
}

void obj_WaveManager::PosToCenterAround(float distance, float direction)
{
	PosToCenter();
	pos = {
		pos.x + LengthdirX(distance, direction),
		pos.y + LengthdirY(distance, direction)
	};
}

void obj_WaveManager::PosToPlayerAround(float distance, float direction)
{
	pos = GC->Player->GetPos();
	pos = {
		pos.x + LengthdirX(distance, direction),
		pos.y + LengthdirY(distance, direction)
	};
}

void obj_WaveManager::EndWave()
{
	InstanceDestroy();
	((obj_GameManager*)parent)->current_wave = NULL;
}
