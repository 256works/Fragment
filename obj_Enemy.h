#pragma once
#include "GameObject.h"

#define ENEMY_BBOX_SIZE 20
#define ENEMY_IMAGE_ROTATE_SPEED 3.0f
#define ENEMY_HP 3

#define FORCE_MOVE_FRICTION 4.0f
#define FORCE_MOVE_AMOUNT 4.5f
#define OVERED_ENEMY_MOVE_SPEED 1.0f

#define ENEMY_SCORE 100

#define ENEMY0_SPEED 2.0f
#define ENEMY1_SPEED 3.5f

#define ENEMY2_GRAVITY_SPEED 0.2f
#define ENEMY2_GRAVITY_MAXSPEED 6.5f

#define ENEMY3_TIMER 30
#define ENEMY3_MOVE_DISTANCE_ONCE 120.0f
#define ENEMY3_EASE 22.0f

#define ENEMY4_TIMER 55
#define ENEMY4_MOVE_DISTANCE_ONCE 300.0f
#define ENEMY4_EASE 18.0f

#define ENEMY5_SPEED 4.5f
#define ENEMY5_ROTATE_SPEED 1.5f

#define ENEMY6_TIMER 15
#define ENEMY6_MOVE_DISTANCE_ONCE 85.0f
#define ENEMY6_EASE 6.0f

#define ENEMY7_MOVE_TIME 120
#define ENEMY7_GRAVITY_SPEED 0.6f
#define ENEMY7_GRAVITY_MAXSPEED 11.0f

class obj_Enemy :
	public GameObject
{
private:
	float alpha;
	float angle_speed_deg;
	float angle;
	int hp;
	float scale;
	FPOINT force_to;
	float direction;
	int timer;
	FPOINT toPos;
	FPOINT gravity_speed;
	bool rotate_to;
public:
	char enemy_type;

	obj_Enemy();
	~obj_Enemy();

	virtual void Draw();
	virtual void Update();
	virtual void Init();

	void Dead();

	virtual void CollisionEvent(obj object, GameObject* inst);
};

