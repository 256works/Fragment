#pragma once
#include "GameObject.h"

#define SPINLIGHT_COUNT 5
#define HEXA_LIGHT_HEIGHT 300.0f

class obj_GameBackground :
	public GameObject
{
private:
	float spinlight_angle;
	float spinlight_alpha;
	float spinlight_alpha_each[SPINLIGHT_COUNT-1];

	float spinlight_alpha_first[SPINLIGHT_COUNT];
	float spinlight_scale_first;
	float hexa_part_pos;
public:
	obj_GameBackground();
	~obj_GameBackground();

	virtual void Draw();
	virtual void Update();
	virtual void Init();
};

