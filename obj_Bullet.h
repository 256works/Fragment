#pragma once
#include "GameObject.h"

#define BULLET_SPEED 20.0f
#define BULLET_COLLISION_ACCURACY 3

#define BULLET_BBOX_SIZE 6

class obj_Bullet :
	public GameObject
{
public:
	float first_scale;
public:
	float angle;
	obj_Bullet();
	~obj_Bullet();

	virtual void Draw();
	virtual void Update();
	virtual void Init();
	virtual void UserEvent(char number);
};

