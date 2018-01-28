#include "stdafx.h"
#include "obj_GameManager.h"


obj_GameManager::obj_GameManager()
{
	depth = -1000;
	score = 0;
	_scorePos_x = GAME_WIDTH / 2;
	
	ready_pos_deff = 1.0f;
	ready_pos = READY_START_POS;
	ready_xscale = ready_yscale = 1.0f;
	GC->life = PLAYER_LIFE;

	isHighscore = false;
	isGameover = false;

	gameover_first = false;

	highscore_alpha = 1.0f;

	wavewarn_alpha = 0.0f;
	wavewarn_alpha_all = 0.0f;
	wavewarn_xscale = 0.0f;
	wavewarn_yscale = 0.0f;

	timer = 0;
	level = 0;

	current_wave = NULL;
	black_alpha = 0.0f;
	GC->GameManager = this;
}


obj_GameManager::~obj_GameManager()
{
	GC->GameManager = NULL;

}

void obj_GameManager::Draw()
{
	Sprite::DrawSprite(spr::game_backlight, 0, VIEW.x + GAME_WIDTH / 2, VIEW.y + GAME_HEIGHT / 2, 4.0f, 4.0f, 0.0f, 1.0f BLINK);
#pragma region
	if (wavewarn_alpha_all > 0.0f)
	{
		Sprite::DrawSprite(spr::wave_warn, 0, VIEW.x + GAME_WIDTH / 2, VIEW.y + GAME_HEIGHT - WAVE_WARNING_LABEL_SPACE, wavewarn_xscale, wavewarn_yscale, 0.0f, Clamp(wavewarn_alpha_all, 0.0f, 1.0f) * 1.0f BLINK);
		Sprite::DrawSprite(spr::wave_warn, 0, VIEW.x + GAME_WIDTH / 2, VIEW.y + GAME_HEIGHT - WAVE_WARNING_LABEL_SPACE, (1.1f - wavewarn_alpha * 0.1f) * wavewarn_xscale, wavewarn_yscale, 0.0f, Clamp(wavewarn_alpha_all, 0.0f, 1.0f) * wavewarn_alpha BLINK);

		wavewarn_alpha += -wavewarn_alpha / 8.0f;
		if (wavewarn_alpha < 0.005f)
			wavewarn_alpha = 1.0f;
		wavewarn_xscale += (1.0f - wavewarn_xscale) / 6.0f;
		wavewarn_yscale += (1.0f - wavewarn_yscale) / 4.0f;
		wavewarn_alpha_all -= 0.05f;
	}
#pragma endregion Draw Wave warning
#pragma region
	Sprite::DrawSprite(spr::titlebg, 0, VIEW.x, VIEW.y, 2.0f, 2.0f, 0.0f, black_alpha*0.6f);
	Sprite::DrawSprite(spr::gameover, 0, VIEW.x + GAME_WIDTH/2, VIEW.y + GAME_HEIGHT/2 - gameover_alpha*10.0f+10.0f, 1.0f, 1.0f, 0.0f, black_alpha * gameover_alpha);
	Sprite::DrawSprite(spr::retry, 0, VIEW.x + GAME_WIDTH / 2, VIEW.y + GAME_HEIGHT / 2 + 90 - retry_alpha*4.0f+4.0f, 1.0f, 1.0f, 0.0f, black_alpha * retry_alpha);
	if (isGameover && !isHighscore)
	{
		Sprite::DrawSprite(spr::highscored, 0, VIEW.x + GAME_WIDTH / 2, VIEW.y + SCORE_LABLE_SPACE + 65, 1.0f, 1.0f, 0.0f, black_alpha*retry_alpha);
	
		FPOINT scorePos = {
			GAME_WIDTH / 2,
			VIEW.y + SCORE_LABLE_SPACE + SCORE_LABLE_SPACE_TO_NUMBER + 68
		};

		int score_num_length = 1;
		unsigned long _scr = GC->game_high_score;

		while ((_scr /= 10) >= 1)
		{
			score_num_length++;
		}

		scorePos.x -= (float)(score_num_length - 1)*(float)SCORE_NUM2_SPACE / 2;

		for (int i = 0; i < score_num_length; ++i)
		{
			Sprite::DrawSprite(spr::score_num2, (int)(GC->game_high_score / pow(10, score_num_length - i - 1)), VIEW.x + scorePos.x + i*SCORE_NUM2_SPACE, scorePos.y, 1.0f, 1.0f, 0.0f, black_alpha*retry_alpha);
		}
	}
#pragma endregion Draw Gameover
#pragma region
	Sprite::DrawSprite(spr::score, 0, VIEW.x + GAME_WIDTH / 2, VIEW.y + SCORE_LABLE_SPACE);

	FPOINT scorePos = {
		GAME_WIDTH / 2,
		VIEW.y + SCORE_LABLE_SPACE + SCORE_LABLE_SPACE_TO_NUMBER
	};

	int score_num_length = 1;
	//int num_format_space = 0;
	unsigned long _scr = score;

	while ((_scr /= 10) >= 1)
	{
		score_num_length++;
	}

	scorePos.x -= (float)(score_num_length - 1)*(float)SCORE_NUM_SPACE / 2;
	_scorePos_x += (scorePos.x - _scorePos_x) / 5.0f;

	for (int i = 0; i < score_num_length; ++i)
	{
		Sprite::DrawSprite(spr::score_num, (int)(score / pow(10, score_num_length - i - 1)), VIEW.x + _scorePos_x + i*SCORE_NUM_SPACE, scorePos.y);
	}

	if (isHighscore)
	{
		Sprite::DrawSprite(spr::highscored, 0, VIEW.x + GAME_WIDTH / 2, VIEW.y + SCORE_LABLE_SPACE + 48, 1.0f, 1.0f, 0.0f, 1.0f BLINK);
		Sprite::DrawSprite(spr::highscored, 0, VIEW.x + GAME_WIDTH / 2, VIEW.y + SCORE_LABLE_SPACE + 48, 1.5f-highscore_alpha*0.5f, 1.0f, 0.0f, highscore_alpha BLINK);

		highscore_alpha += -highscore_alpha / 8.0f;
		if (highscore_alpha < 0.005f)
			highscore_alpha = 1.0f;
	}

#pragma endregion Draw Score
#pragma region
	FPOINT lifePos = {
		VIEW.x + GAME_WIDTH / 2 - GC->life*(LIFE_SPACE / 2),
		VIEW.y + GAME_HEIGHT - LIFE_SPACE
	};
	for (int i = 0; i < GC->life; ++i)
	{
		Sprite::DrawSprite(spr::life, 0, lifePos.x + i*LIFE_SPACE, lifePos.y);
	}
#pragma endregion Draw life icon
#pragma region
	Sprite::SetInterpolation(true);
	if (ready_yscale > 0.0005f)
	{
		FPOINT __readyPos = {
			VIEW.x + GAME_WIDTH / 2 - READY_WIDTH / 2 + ready_pos,
			VIEW.y + GAME_HEIGHT / 2 - READY_HEIGHT / 2
		};

		if (ready_pos_deff > 0.001f)
		{
			for (int i = 0; i < READY_HEIGHT; ++i)
			{
				Sprite::DrawSpritePart(spr::ready, 0, __readyPos.x - READY_SKEW*(READY_HEIGHT-i)*ready_pos_deff - ready_pos_deff*30.0f, __readyPos.y + i, 0, i, READY_WIDTH, 1);
			}
			ready_pos_deff += -ready_pos_deff / READY_SKEW_EASE_SPEED;
		}
		else
		{
			Sprite::DrawSprite(spr::ready, 0, __readyPos.x + READY_WIDTH / 2, __readyPos.y + READY_HEIGHT / 2, ready_xscale, ready_yscale, 0.0f, ready_yscale);
			ready_xscale += 0.08f;
			ready_yscale += -ready_yscale / 6.0f;
		}
		
		ready_pos += READY_SPEED * (pow(ready_xscale, 4));
	}
	Sprite::SetInterpolation(false);
#pragma endregion Draw get ready

}

void obj_GameManager::Update()
{
	// score controll
	REPEAT((int)(GC->game_score - score)/SCORE_SPEED +1)
	{
		if (GC->game_score > score)
		{
			++score;
		}

		if (GC->game_high_score <= GC->game_score && GC->game_score != 0)
		{
			isHighscore = true;
		}
	}

	// wave setting
	if (!current_wave && !PLAYER_ISDEAD)
	{
		if (timer > 130)
		{
			char type;

			// 레벨에 따라 wave create 타입 설정
			if (level < 2)
			{
				type = (char)Irand(0, 3);
			}
			else if (level < 6)
			{
				type = (char)Irand(4, 11);
			}
			else if (level < 15)
			{
				type = (char)Irand(12, 20);
			}
			else
			{
				type = (char)Irand(21, 39);
			}
			//

			WaveCreate(type);
			timer = 0;
		}
		timer++;
	}

#pragma region
	if (isGameover)
	{
		if (!gameover_first)
		{
			gameover_alpha = 0.0f;
			retry_alpha = 0.0f;
			gameover_first = true;

			if (isHighscore)
			{
				GC->game_high_score = GC->game_score;
				GC->SaveHighScore();
			}
		}
		if (black_alpha < 1.0f)
		{
			black_alpha += 0.05f;
		}
		else
		{
			// retry

			if (KEY->isKeyPressed(VK_SPACE))
			{
				RetryGame();
			}
		}

		if (black_alpha > 0.5f)
		{
			gameover_alpha += (1.0f - gameover_alpha) / 20.0f;
		}
		if (black_alpha > 0.8f)
		{
			retry_alpha += (1.0f - retry_alpha) / 20.0f;
		}
	}
	else
	{
		black_alpha += -black_alpha/10.0f;
		gameover_first = false;
	}
#pragma endregion Gameover check

}

void obj_GameManager::Init()
{
	GC->game_score = 0;
	GC->SetHighpass(false);

	GC->InstanceCreate(obj::game_background, 0, 0, true);
	GC->InstanceCreate(obj::player, GAME_ROOM_WIDTH/2, GAME_ROOM_HEIGHT/2, true);
	GC->InstanceCreate(obj::player_wave, GAME_ROOM_WIDTH / 2, GAME_ROOM_HEIGHT / 2, true);

	SOUND->Play(snd::get_ready, 0.4f);
}

void obj_GameManager::WaveWaring()
{
	wavewarn_alpha = 1.0f;
	wavewarn_alpha_all = 8.0f;
	wavewarn_xscale = 2.5f;
	wavewarn_yscale = 0.0f;

	SOUND->Play(snd::wave_warning, 0.8f);
}

void obj_GameManager::WaveCreate(char type)
{
	if (!current_wave && GC->vEnemy.size() <= 3 && !PLAYER_ISDEAD )
	{
		WaveWaring();

		current_wave = (obj_WaveManager*)(GC->InstanceCreate(obj::wave_manager, 0, 0));
		current_wave->parent = this;
		current_wave->type = type;
		level++;
	}
}

void obj_GameManager::RetryGame()
{
	isGameover = false;
	isHighscore = false;

	GC->SetHighpass(false);
	((obj_Player*)(GC->Player))->Replay();

	SOUND->Play(snd::get_ready, 0.4f);

	GC->game_score = 0;
	_scorePos_x = GAME_WIDTH / 2;
	score = 0;
	level = 0;
	GC->life = PLAYER_LIFE;
}
