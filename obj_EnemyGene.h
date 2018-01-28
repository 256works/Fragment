#pragma once
#include "GameObject.h"

#define ENEMY_GENE_WARN_COUNT 4
#define ENEMY_GENE_ROTATE_SPEED 4.0f


class obj_EnemyGene :
	public GameObject
{
private:
	float alpha;
	float scale;
	float angle;
	int warn_cnt;
public:
	char enemy_type;

	obj_EnemyGene();
	~obj_EnemyGene();

	virtual void Draw();
	virtual void Update();
	virtual void Init();
};

