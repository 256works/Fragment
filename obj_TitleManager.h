#pragma once
#include "GameObject.h"

#define TITLE_NOISE 80
#define TITLE_START_BLUR 1.0f
#define TITLE_RING_COUNT 8
#define BLINK_ALPHA 0.8f
#define TITLE_RING_SCALE 3.3f
#define __BLINK *(Irand(0, 3) == 0 ? 1.0f : blinked_alpha)
#define START_TIME_DELAY 60

class obj_TitleManager :
	public GameObject
{
private:
	float blur_alpha;
	float noise_amt;
	float title_alpha;
	float ring_angle[TITLE_RING_COUNT];
	float ring_speed_deg[TITLE_RING_COUNT];
	float backlight_alpha_deg;
	float blinked_alpha;
	float ring_scale;
	float cloud_scale_deg;

	float start_alpha;
	float start_xscale;
	float start_yscale;
	bool start_preover;
	float small_light_alpha_deg;
	float start_first_alpha;
	float first_alpha;

	int timer;
	int start_timer;
	bool isStarted;
public:
	obj_TitleManager();
	~obj_TitleManager();

	virtual void Init();
	virtual void Draw();
	virtual void Update();
};

