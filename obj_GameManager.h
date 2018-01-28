#pragma once
#include "GameObject.h"

#define BLINK *(Irand(0, 3) == 0 ? 1.0f : 0.8f)
#define SCORE_SPEED 4
#define SCORE_NUM_SPACE 16
#define SCORE_NUM2_SPACE 12
#define SCORE_LABLE_SPACE 14.0f
#define SCORE_LABLE_SPACE_TO_NUMBER 17.0f
#define READY_SPEED 0.5f
#define READY_START_POS -35.0f

#define PLAYER_LIFE 3
#define LIFE_ICON_SPACE 20.0f
#define LIFE_SPACE 16.0f

#define READY_WIDTH 418
#define READY_HEIGHT 55
#define READY_SKEW 1.8f
#define READY_SKEW_EASE_SPEED 15.0f

#define WAVE_WARNING_LABEL_SPACE 64

class obj_GameManager :
	public GameObject
{
private:
	unsigned long score;
	float ready_pos_deff;
	float ready_pos;
	float _scorePos_x;
	float ready_xscale, ready_yscale;
	float highscore_alpha;
	float wavewarn_alpha, wavewarn_alpha_all;
	float wavewarn_xscale, wavewarn_yscale;
	float black_alpha;

	float gameover_alpha;
	float retry_alpha;

	bool gameover_first;

public:
	int level;
	int timer;
	bool isHighscore;
	bool isGameover;

	obj_WaveManager* current_wave;

	obj_GameManager();
	~obj_GameManager();

	virtual void Draw();
	virtual void Update();
	virtual void Init();

	void WaveWaring();
	void WaveCreate(char type);
	void RetryGame();
};

