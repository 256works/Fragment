#pragma once
#include "GameObject.h"

#define HUGEEXPLOSION_BLINKED_ALPHA 0.4f
#define HUGEEXPLOSION_BLINK_TIMER_INIT 8
#define HUGEEXPLOSION_ALPHA_INIT 4.0f

class obj_HugeExplosion :
	public GameObject
{
private:
	float ring_out_scale;
	float ring_scale;
	float exp_scale;
	float exp_scale_increased;
	float exp_alpha;

	float exp_blink_alpha;
	int exp_blink_speed;
	int exp_blink_timer;
public:
	obj_HugeExplosion();
	~obj_HugeExplosion();

	virtual void Draw();
	virtual void Update();
	virtual void Init();
};

