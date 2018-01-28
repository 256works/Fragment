#pragma once
#include "GameObject.h"

#define VIEW_MAX_DIST 200
#define VIEW_PER_PLAYER 2.0f
#define PLAYER_SCALE 0.8f
#define PLAYER_SPEED 4.7f
#define PLAYER_FRICTION 7.0f

#define BOARD_RADIUS 415

#define BULLET_RELOAD_TIME 4
#define BULLET_ANGLE_DEFF (int)2

#define PLAYER_BBOX_SIZE 5

#define VIEW_EASE 3.0f

class obj_Player :
	public GameObject
{
private:
	float playerScale;
	float angle;
	FPOINT viewPos;
	int bullet_time;
	int dead_timer;

	float view_ease;
public:
	bool isDead;
	float hspeed, vspeed;

	obj_Player();
	~obj_Player();

	virtual void Draw();
	virtual void Update();
	virtual void Init();

	void Dead();
	void Replay();
};

