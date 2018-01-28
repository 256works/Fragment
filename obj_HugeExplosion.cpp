#include "stdafx.h"
#include "obj_HugeExplosion.h"


obj_HugeExplosion::obj_HugeExplosion()
{
	depth = 15;
	ring_scale = 2.5f;
	ring_out_scale = 0.5f;
	exp_scale = 0.5f;
	exp_scale_increased = 0.0f;
	exp_alpha = HUGEEXPLOSION_ALPHA_INIT;
	exp_blink_alpha = 1.0f;

	exp_blink_speed = HUGEEXPLOSION_BLINK_TIMER_INIT;
	exp_blink_timer = 0;
}


obj_HugeExplosion::~obj_HugeExplosion()
{
}

void obj_HugeExplosion::Draw()
{
	Sprite::SetInterpolation(true);
	Sprite::DrawSprite(spr::explosion2_ring, 0, pos.x, pos.y, ring_scale, ring_scale, 0.0f, 1.0f);
	Sprite::DrawSprite(spr::explosion2_ring, 0, pos.x, pos.y, ring_out_scale, ring_out_scale, 0.0f, Clamp(exp_alpha-1.5f, 0.0f, 0.5f) BLINK);

	Sprite::DrawSprite(spr::explosion2, 0, pos.x, pos.y, exp_scale + exp_scale_increased, exp_scale + exp_scale_increased, 0.0f, Clamp(exp_alpha, 0.0f, 1.0f) * exp_blink_alpha);
	Sprite::SetInterpolation(false);

	ring_scale += -ring_scale / 12.0f;
	if (ring_scale < 0.5f)
		ring_out_scale += (2.0f - ring_out_scale) / 10.0f;
	exp_scale += (1.0f - exp_scale) / 4.0f;
	exp_scale_increased += 0.005f;

	exp_alpha -= 0.05f;

	if (exp_alpha < 0.0f)
		InstanceDestroy();

	if (exp_blink_timer > exp_blink_speed)
	{
		exp_blink_timer = 0;
		if (exp_blink_speed > 2)
			exp_blink_speed -= 1;

		if (exp_blink_alpha == 1.0f)
			exp_blink_alpha = HUGEEXPLOSION_BLINKED_ALPHA;
		else
			exp_blink_alpha = 1.0f;
	}
	exp_blink_timer++;
}

void obj_HugeExplosion::Update()
{
}

void obj_HugeExplosion::Init()
{
	GC->ScreenShake(20);
	GC->SetBgmSlow();
	SOUND->Play(snd::explosion2, 0.8f);
}
