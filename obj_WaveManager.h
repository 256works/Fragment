#pragma once
#include "GameObject.h"

#define WAVE_DELAY 80

class obj_WaveManager :
	public GameObject
{
private:
	int timer;
	int value;
	int count;
	float rand_angle;
	float angle;
public:
	GameObject* parent;
	char type;

	obj_WaveManager();
	~obj_WaveManager();

	virtual void Draw();
	virtual void Update();
	virtual void Init();

	void EnemyCreate(char enemyType);
	bool CheckOutside();

	void PosToCenter();
	void PosToCenterAround(float distance, float direction);
	void PosToPlayerAround(float distance, float direction);
	void EndWave();

};