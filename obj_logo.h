#pragma once
#include "GameObject.h"
class obj_logo :
	public GameObject
{
private:
	float logo_alpha[5];
	float logo_alpha_all;
	int timer;
public:
	obj_logo();
	~obj_logo();

	virtual void Init();
	virtual void Draw();
	virtual void Update();
};

