#pragma once
#include "GameObject.h"
class obj_BulletEffect :
	public GameObject
{
private:
	float alpha;
	float angle;
	float speed;
public:
	float gravity_angle;

	obj_BulletEffect();
	~obj_BulletEffect();

	virtual void Draw();
	virtual void Update();
};

