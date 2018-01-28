#pragma once
#include "GameObject.h"
class obj_PlayerWave :
	public GameObject
{
private:
	float alpha;
	float scale;
public:
	obj_PlayerWave();
	~obj_PlayerWave();

	virtual void Draw();
	virtual void Update();
	virtual void Init();
};

