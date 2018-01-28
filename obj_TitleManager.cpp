#include "stdafx.h"
#include "obj_TitleManager.h"


obj_TitleManager::obj_TitleManager()
{
}


obj_TitleManager::~obj_TitleManager()
{
}

void obj_TitleManager::Init()
{
#pragma region
	if (!SOUND->isPlaying(snd::bgm))
	{
		SOUND->Play(snd::bgm);
		SOUND->DspHighpassSetting(snd::bgm);
	}
	GC->SetHighpass(true);
#pragma endregion play bgm / fmod set dsp
	
	blur_alpha = TITLE_START_BLUR;
	noise_amt = TITLE_NOISE;
	title_alpha = 0.0f;
	backlight_alpha_deg = 0.0f;
	blinked_alpha = 0.0f;
	ring_scale = 15.0f;
	cloud_scale_deg = 0.0f;
	start_alpha = 0.0f;
	start_xscale = 1.0f;
	start_yscale = 1.0f;
	start_preover = true;
	small_light_alpha_deg = 0.0f;
	start_first_alpha = 0.0f;
	first_alpha = 0.0f;
	timer = 0;
	float angle_start = (float)Irand(0, 360);
	isStarted = false;

	for (int i = 0; i < TITLE_RING_COUNT; ++i)
	{
		ring_angle[i] = angle_start + i * 360.0f / TITLE_RING_COUNT;
		ring_speed_deg[i] = i * 24.0f;
	}
}

void obj_TitleManager::Draw()
{
#pragma region
	Sprite::DrawSprite(spr::titlebg, 0, 0, 0, 2.0f, 2.0f);
	Sprite::DrawSprite(spr::title_cloud, 0, GAME_WIDTH / 2, GAME_HEIGHT / 2,
		2.0f + (LengthdirY(0.5f, cloud_scale_deg) + 0.5f),
		2.0f + (LengthdirY(0.5f, cloud_scale_deg) + 0.5f),
		0.0f, first_alpha * 0.12f * (LengthdirY(0.5f, cloud_scale_deg) + 0.5f));
	Sprite::DrawSprite(spr::title_cloud, 0, GAME_WIDTH / 2, GAME_HEIGHT / 2,
		2.0f + (LengthdirY(0.2f, cloud_scale_deg + 40) + 0.2f),
		2.0f + (LengthdirY(0.2f, cloud_scale_deg + 40) + 0.2f),
		180.0f, first_alpha * 0.12f* (LengthdirY(0.5f, cloud_scale_deg + 180) + 0.5f));
	cloud_scale_deg += 0.7f;
	if (cloud_scale_deg > 360.0f)
		cloud_scale_deg -= 360.0f;

	Sprite::DrawSprite(spr::title_small_light, 0, 687, 369, 2.0f + LengthdirX(1.0f, small_light_alpha_deg - 120), 2.0f + LengthdirX(1.0f, small_light_alpha_deg - 120), 0.0f, (LengthdirX(0.5f, small_light_alpha_deg)+0.8f) __BLINK);
	small_light_alpha_deg += 1.5f;
	if (small_light_alpha_deg > 360.0f)
		small_light_alpha_deg -= 360.0f;
#pragma endregion bg
#pragma region
	Sprite::SetInterpolation(true);
	for (int i = 0; i < TITLE_RING_COUNT; ++i)
	{
		float scale = ((float)i / TITLE_RING_COUNT)*ring_scale + 0.5f;
		float alpha = ((TITLE_RING_COUNT-(float)i) / TITLE_RING_COUNT) + 0.2f;
		FPOINT pos = { LengthdirX(-scale*10, ring_speed_deg[i]) - i*12 + 160, LengthdirY(-scale*10, ring_speed_deg[i]) - i*12 +80};
		Sprite::DrawSprite(spr::title_ring, 0, GAME_WIDTH / 2 + pos.x, GAME_HEIGHT / 2 + pos.y, scale, scale, ring_angle[i], Clamp(alpha, 0.0f, 1.0f)__BLINK, 1.0f, 0.85f, 45.0f);
		
		Sprite::DrawSprite(spr::title_ring, 0, GAME_WIDTH / 2 + pos.x, GAME_HEIGHT / 2 + pos.y, scale + 0.5f, scale +0.5f, ring_angle[i] + 180, 0.35f*Clamp(alpha, 0.0f, 1.0f)__BLINK, 1.0f, 0.85f, 45.0f);
		
		ring_angle[i] += LengthdirX(0.7f, ring_speed_deg[i])+0.7f + 0.7f;
		ring_speed_deg[i] += 1.5f;

		if (ring_angle[i] > 360.0f)
			ring_angle[i] -= 360.0f;
		if (ring_speed_deg[i] > 360.0f)
			ring_speed_deg[i] -= 360.0f;

	}
	Sprite::SetInterpolation(false);
#pragma endregion rotate rings
#pragma region
	Sprite::DrawSprite(spr::title_start_backlight, 0, 480, 170 + 30, 2.0f, 2.0f, 0.0f, first_alpha __BLINK);
	POINT titlePos = { 352, 133 + 30 };
	float rand_glitch = (Irand(0, 20) == 0) ? 6.0f : 0.0f;
	Sprite::SetInterpolation(true);
	for (int i = 0; i < Sprite::GetHeight(spr::titlelogo); ++i)
	{
		float rand = ((float)Irand(-100, 100))/100.0f;
		float rand_alpha = (Irand(0, 25) != 0) ? 1.0f : 0.85f;
		Sprite::DrawSpritePart(spr::titlelogo, 0, (float)titlePos.x + rand*noise_amt + rand*rand_glitch, (float)titlePos.y + i, 0, i, Sprite::GetWidth(spr::titlelogo), 1, title_alpha * rand_alpha - (rand_glitch/6.0f)*0.1f);
	}
#pragma endregion game title
#pragma region
	POINT startBtnPos = { GAME_WIDTH / 2, 445 - 25 };
	RECT btnBbox = { startBtnPos.x - 348/2, startBtnPos.y - 42/2,
		startBtnPos.x + 348/2, startBtnPos.y + 42/2 };

	Sprite::DrawSprite(spr::title_start, 0, (float)startBtnPos.x, (float)startBtnPos.y + (1 - start_first_alpha)*8.0f, 1.0f, 1.0f, 0.0f, start_first_alpha * first_alpha);
	if (timer > 30)
		start_first_alpha += (1.0f - start_first_alpha) / 12.0f;
	Sprite::SetInterpolation(false);
	if (!isStarted)
	{
		if (PtInRect(&btnBbox, POINT({ (LONG)(GC->GetMousePos().x), (LONG)(GC->GetMousePos().y) })))
		{
			if (start_preover)
			{
				start_xscale = 2.0f;
				start_yscale = 0.0f;
				start_preover = false;
				SOUND->Play(snd::buttonhover, 0.35f);
			}
			start_alpha += (1.0f - start_alpha) / 10.0f;
			if (KEY->isKeyPressed(VK_LBUTTON))
			{
				start_timer = timer;
				isStarted = true;
				SOUND->Play(snd::game_start, 0.5f);
			}
		}
		else
		{
			start_alpha += -start_alpha / 8.0f;
			start_preover = true;
		}
		first_alpha += (1.0f - first_alpha) / 17.0f;
	}
	else
	{
		start_alpha = ((timer % 8) < 4 ? 0.3f : 0.1f);
		first_alpha += - first_alpha / 27.0f;

		if (timer > start_timer + START_TIME_DELAY)
			GC->NextScene();
	}

	start_xscale += (1.0f - start_xscale) / 3.0f;
	start_yscale += (1.0f - start_yscale) / 3.0f;

	Sprite::DrawSprite(spr::title_start, 1, (float)startBtnPos.x - 1, (float)startBtnPos.y + (1 - start_first_alpha)*8.0f, start_xscale, start_yscale, 0.0f, start_alpha __BLINK);
#pragma endregion start button
	
	Sprite::DrawSprite(spr::title_copyright, 0, GAME_WIDTH/2, 526);

	Sprite::DrawSprite(spr::title_backlight, 0, GAME_WIDTH / 2, GAME_HEIGHT / 2, 4.0f, 4.0f, 0.0f, (LengthdirX(0.3f, backlight_alpha_deg) + 0.7f)__BLINK);
	
	++timer;
}

void obj_TitleManager::Update()
{
	GC->SetBlurAlpha(blur_alpha);
	if (!isStarted)
	{
		blur_alpha += (0.05f - blur_alpha) / 20.0f;
		noise_amt += (0.5f - noise_amt) / 13.0f;
		title_alpha += (1 - title_alpha) / 11.0f;
		blinked_alpha += (BLINK_ALPHA - blinked_alpha) / 50.0f;
		ring_scale += (TITLE_RING_SCALE - ring_scale) / 40.0f;
	}
	else
	{
		blur_alpha += (0.1f - blur_alpha) / 20.0f;
		noise_amt += (0.5f - noise_amt) / 13.0f;
		title_alpha += (0.0f - title_alpha) / 11.0f;
		blinked_alpha += (0.3f - blinked_alpha) / 50.0f;
		ring_scale += (15.0f - ring_scale) / 80.0f;
	}


	backlight_alpha_deg += 2.0f;
}
