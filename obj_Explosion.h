#pragma once
#include "GameObject.h"

#define EXPLOSION_SCALE_EASE_SPEED 8.0f
#define EXPLOSION_ALPHA_EASE_SPEED 10.0f
#define EXPLOSION_FINAL_SIZE 1.5f

#define EXPLOSION_SCREEN_SHAKE_AMOUNT 4

class obj_Explosion :
	public GameObject
{
private:
	float scale;
	float alpha;
public:
	obj_Explosion();
	~obj_Explosion();

	virtual void Draw();
	virtual void Update();
	virtual void Init();
};

