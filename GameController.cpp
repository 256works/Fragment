#include "stdafx.h"
#include "GameController.h"

// 전체 게임을 컨트롤하는 객체

GameController::GameController()
{
	view = FPOINT({0.0, 0.0});
	nowScene = NULL;
	SceneChanger = -1;

	pFactory = NULL;
	pRenderTarget = NULL;
	surface = NULL;
	shakeAmount = 0.0f;
	blurAlpha = 0.0f;
	cursor_dist = CURSOR_DISTANCE;

	bgmHighpass = HIGHPASS_AMOUNT;
	isHighpass = true;
	cursor_angle = 0.0f;
	cursor_alpha = CURSOR_ALPHA_DEFAULT;
	CoInitialize(NULL);
	game_score = 0;
	game_high_score = 0;

	bgm_frequency = FREQUENCY_DEFAULT;
	life = 0;
	Player = NULL;
}


GameController::~GameController()
{
	ReleaseGameInstanceAll();

	for (vector<Scene*>::iterator i = sceneList.begin(); i != sceneList.end();)
	{
		i = sceneList.erase(i);
	}
	sceneList.clear();

	pFactory->Release();
	pRenderTarget->Release();
	dwFactory->Release();
	dwTextFormat->Release();
}


void GameController::D2DDraw()
{
	Sprite::ResetDrawCallCount();
	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(ColorF(0, 0, 0));

	for (vector<GameObject*>::iterator i = objectList.begin(); i != objectList.end(); ++i)
	{
		(*i)->Update();
		(*i)->Draw();
	}
	
	if (SURFACE_BLUR)
	{
		for (float i = 12; i > 0; i -= 1.0f)
		{
			pRenderTarget->SetTransform(Matrix3x2F::Scale(SizeF(1 + (i / 100)*blurAlpha, 1 + (i / 100 * GAME_RATIO)*blurAlpha)) *  Matrix3x2F::Translation(SizeF(GAME_WIDTH / 2, GAME_HEIGHT / 2)));

			pRenderTarget->DrawBitmap(surface, RectF(-GAME_WIDTH / 2, -GAME_HEIGHT / 2, GAME_WIDTH / 2, GAME_HEIGHT / 2),
				0.03f + blurAlpha / 20, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
		}

		pRenderTarget->SetTransform(Matrix3x2F::Identity());

		surface->CopyFromRenderTarget(&Point2U(0, 0), pRenderTarget, &RectU(0, 0, GAME_WIDTH, GAME_HEIGHT));
	}

	Sprite::SetInterpolation(true);

	for (int i = 0; i < 4; ++i)
	{
		float dir = 360.0f * i / 4 + cursor_angle;

		Sprite::DrawSprite(spr::cursor, 0, view.x + mousePos.x + LengthdirX(cursor_dist, dir), view.y + mousePos.y + LengthdirY(cursor_dist, dir), 1.0f, 1.0f, dir - 45.0f, cursor_alpha);
	}
	Sprite::SetInterpolation(false);

	cursor_angle -= 0.5f / cursor_alpha;
	if (cursor_angle < -360.0f)
		cursor_angle += 360.0f;
	if (KEY->isKeyDown(VK_LBUTTON))
	{
		cursor_dist += -cursor_dist / 1.2f;
		cursor_alpha += (1.0f - cursor_alpha) / 2.0f;
	}
	else
	{
		cursor_dist += (CURSOR_DISTANCE -cursor_dist) / 8.0f;
		cursor_alpha += (CURSOR_ALPHA_DEFAULT - cursor_alpha) / 4.0f;
	}

	TIME->ShowFps();

	pRenderTarget->EndDraw();

}

void GameController::UpdateHighpass()
{
	if (isHighpass)
	{
		bgmHighpass += (HIGHPASS_AMOUNT - bgmHighpass) / HIGHPASS_SPEED;
	}
	else
	{
		bgmHighpass += -bgmHighpass / HIGHPASS_SPEED;
	}
	SOUND->DspSetHighpass(bgmHighpass);
	SOUND->SetSoundFrequency(snd::bgm, bgm_frequency);
	bgm_frequency += (FREQUENCY_DEFAULT - bgm_frequency) / BGM_SLOW_TO_NORMAL_SPEED;
	if (bgm_frequency > FREQUENCY_DEFAULT - 1)
		bgm_frequency = FREQUENCY_DEFAULT;
}

void GameController::InitDWrite(TCHAR* font, float size, IDWriteFactory ** factory, IDWriteTextFormat ** format)
{
	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(*factory),
		(IUnknown**)factory
	);

	(*factory)->CreateTextFormat(
		font,
		0,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		size,
		L"ko",
		format
	);

}

void GameController::LoadHighScore()
{
	game_high_score = 0;

	HANDLE file;
	DWORD read;

	file = CreateFile(SAVE_DATA_FNAME, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, &game_high_score, sizeof(game_high_score), &read, NULL);

	CloseHandle(file);
}

void GameController::SaveHighScore()
{
	HANDLE file;
	DWORD write;

	file = CreateFile(SAVE_DATA_FNAME, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, &game_high_score, sizeof(game_high_score), &write, NULL);

	CloseHandle(file);
}

void GameController::SetViewPos(POINT pos)
{
	if (pos.x < 0)
		pos.x = 0;
	if (pos.y < 0)
		pos.y = 0;

	if (pos.x > nowScene->GetMapWidth() - GAME_WIDTH)
		pos.x = nowScene->GetMapWidth() - GAME_WIDTH;
	if (pos.y > nowScene->GetMapHeight() - GAME_HEIGHT)
		pos.y = nowScene->GetMapHeight() - GAME_HEIGHT;

	if (nowScene->GetMapWidth() < GAME_WIDTH)
		pos.x = 0;
	if (nowScene->GetMapHeight() < GAME_HEIGHT)
		pos.y = 0;

	view = FPOINT({ (float)pos.x, (float)pos.y });
}

FPOINT GameController::GetViewPos()
{
	return view;
}

FPOINT GameController::GetMousePos()
{
	return FPOINT({ (float)mousePos.x + view.x, (float)mousePos.y + view.y});
}

void GameController::ChangeScene()
{
	if (SceneChanger != -1)
	{
		ReleaseGameInstanceAll();

		nowSceneIndex = SceneChanger;
		if (nowSceneIndex > (unsigned int)sceneList.max_size() - 1)
			nowSceneIndex = (unsigned int)sceneList.max_size() - 1;
		nowScene = sceneList.at(SceneChanger);
		nowScene->InitScene();

		SetViewPos(POINT({ 0, 0 }));
		SceneChanger = -1;
	}
}

GameObject * GameController::InstanceCreate(obj object, int x, int y, bool forceCreate)
{
	if (SceneChanger == -1 || forceCreate) // 씬 전환 없을 때만 동작함.
	{

		// GameObject 추가시 이곳에 갱신필요
		GameObject* pGObj;

		switch (object)
		{
		case obj::logo:
			pGObj = new obj_logo;
			break;
		case obj::title_manager:
			pGObj = new obj_TitleManager;
			break;
		case obj::game_manager:
			pGObj = new obj_GameManager;
			break;
		case obj::player:
			pGObj = new obj_Player;
			break;
		case obj::bullet:
			pGObj = new obj_Bullet;
			break;
		case obj::game_background:
			pGObj = new obj_GameBackground;
			break;
		case obj::bullet_effect:
			pGObj = new obj_BulletEffect;
			break;
		case obj::explosion:
			pGObj = new obj_Explosion;
			break;
		case obj::enemy:
			pGObj = new obj_Enemy;
			break;
		case obj::enemy_gene:
			pGObj = new obj_EnemyGene;
			break;
		case obj::huge_explosion:
			pGObj = new obj_HugeExplosion;
			break;
		case obj::player_wave:
			pGObj = new obj_PlayerWave;
			break;
		case obj::wave_manager:
			pGObj = new obj_WaveManager;
			break;
		default: // 빈 공간
			return nullptr;
		}

		pGObj->SetPos(POINT({ x, y }));
		pGObj->Init();
		AddQueInstance(pGObj);
		return pGObj;

	}
	return nullptr;
}


void GameController::CheckDestroyInstance()
{
	if (SceneChanger == -1)	// 씬 전환 없을 때만
	{
		for (vector<GameObject*>::iterator i = objectList.begin(); i != objectList.end(); )
		{
			if ((*i)->IsDestroyQue())
			{
				GameObject* _t = *i;
				
				// 충돌 최적화

				switch ((*i)->GetObjType())
				{
				case obj::bullet:
					for (vector<GameObject*>::iterator j = vBullet.begin(); j != vBullet.end(); ++j)
					{
						if ((*i) == (*j))
						{
							vBullet.erase(j);
							break;
						}
					}
					break;
				case obj::enemy:
					for (vector<GameObject*>::iterator j = vEnemy.begin(); j != vEnemy.end(); ++j)
					{
						if ((*i) == (*j))
						{
							vEnemy.erase(j);
							break;
						}
					}
					break;
				}

				//


				i = objectList.erase(i);
				delete _t;
			}
			else
			{
				i++;
			}
		}
	}
	
}

int GameController::GetSceneWidth()
{
	return nowScene->GetMapWidth();
}

int GameController::GetSceneHeight()
{
	return nowScene->GetMapHeight();
}

void GameController::RestartScene()
{
	SceneChanger = nowSceneIndex;
}

void GameController::NextScene()
{
	SceneChanger = nowSceneIndex + 1;
}

void GameController::GotoScene(unsigned int scene_index)
{
	SceneChanger = scene_index;
}

void GameController::UpdateMousePos()
{
	GetCursorPos(&mousePos);
	ScreenToClient(_hWnd, &mousePos);
}

void GameController::AddQueInstance(GameObject * obj)
{
	objectListQue.push_back(obj);
}

void GameController::ReleaseGameInstanceAll()
{
	for (vector<GameObject*>::iterator i = objectList.begin(); i != objectList.end();)
	{
		GameObject* _t = *i;
		i = objectList.erase(i);
		delete _t;
	}

	// 충돌 최적화 벡터
	vBullet.clear();
	vEnemy.clear();
}

void GameController::SetFromQueInstance()
{
	// 실제 생성

	if (SceneChanger == -1)	// 씬 전환 없을 때만
	{
		for (vector<GameObject*>::iterator i = objectListQue.begin(); i != objectListQue.end();)
		{
			int _depth = (*i)->GetDepth();
			vector<GameObject*>::iterator insertPos = objectList.begin();
			while (insertPos != objectList.end())
			{
				int _tDepth = (*insertPos)->GetDepth();
				if (_depth >= _tDepth)
					break;
				insertPos++;
			}
			objectList.insert(insertPos, (*i));


			// 충돌시 최적화, 예외 처리
			switch ((*i)->GetObjType())
			{
			case obj::bullet:
				vBullet.push_back((*i));
				break;
			case obj::enemy:
				vEnemy.push_back((*i));
				break;
			}
			//

			i = objectListQue.erase(i);
		}
		objectListQue.clear();
	}

}

// --

void GameController::UpdateMain()
{
	UpdateMousePos();
	SetShakePos();
	D2DDraw();
	CheckDestroyInstance();
	SetFromQueInstance();
	ChangeScene();
	UpdateHighpass();
}

void GameController::SetBlurAlpha(float amount)
{
	blurAlpha = amount;
}

void GameController::SetHighpass(bool highpass)
{
	isHighpass = highpass;
}

void GameController::UserEvent(GameObject * inst, int eventNum)
{
	if (inst != NULL)
	{
		inst->UserEvent(eventNum);
	}
}

void GameController::SetBgmSlow()
{
	bgm_frequency = FREQUENCY_SLOWER;
}

void GameController::InitGame()
{
	TIME->Init();
	SOUND->Init();
	Sprite::SetRenderTarget(pRenderTarget);

	LoadHighScore();

	InitScene();
	LoadSprite();
	LoadSound();
	SceneChanger = 0;
	ChangeScene();
}

void GameController::InitScene()
{
	// 씬 초기화. sceneList.push_back(Scene) 을 사용하여 씬 리스트를 만듭니다.
	// Scene은 기본 생성자를 통해 생성합니다. Scene(가로 사이즈, 세로 사이즈, 기본 오브젝트)
	// 기본오브젝트는 해당 씬에 들어갈때 자동으로 생성하게됩니다.
	sceneList.push_back(new Scene(GAME_WIDTH, GAME_HEIGHT, obj::logo));
	sceneList.push_back(new Scene(GAME_WIDTH, GAME_HEIGHT, obj::title_manager));
	sceneList.push_back(new Scene(GAME_ROOM_WIDTH, GAME_ROOM_HEIGHT, obj::game_manager));

}

void GameController::LoadSprite()
{
#pragma region
	// gameRes에서 추가한 상수 값에 해당하는 리소스 불러오기 (Sprite::AddSprite 사용)
	Sprite::AddSprite(spr::works256, L"res/256works.png", 785, 91, 157/2, 91/2, 5);
	Sprite::AddSprite(spr::cursor, L"res/cursor.png", 31, 31, 2, 31-2);
	Sprite::AddSprite(spr::titlebg, L"res/bg.png", 960/2, 540/2);
	Sprite::AddSprite(spr::titlelogo, L"res/title.png", 268, 75);
	Sprite::AddSprite(spr::title_start, L"res/title_start.png", 912, 65, 912/4, 65/2, 2);
	Sprite::AddSprite(spr::title_cloud, L"res/title_cloud.png", 480, 270, 480/2, 270/2);
	Sprite::AddSprite(spr::title_ring, L"res/title_ring.png", 162, 163, 3, 163-3);
	Sprite::AddSprite(spr::title_copyright, L"res/copyright.png", 338, 8, 338/2, 8/2);
	Sprite::AddSprite(spr::title_backlight, L"res/title_backlight.png", 240, 135, 240 / 2, 135 / 2);
	Sprite::AddSprite(spr::game_backlight, L"res/game_backlight.png", 240, 135, 240 / 2, 135 / 2);
	Sprite::AddSprite(spr::title_start_backlight, L"res/title_start_backlight.png", 480, 69, 480/2, 69/2);
	Sprite::AddSprite(spr::title_small_light, L"res/title_small_light.png", 133, 128, 133/2, 128/2);
	Sprite::AddSprite(spr::player, L"res/player.png", 68, 64, 68/2, 64/2);
	Sprite::AddSprite(spr::game_ring, L"res/game_board.png", 918, 918, 918 / 2, 918 / 2);
	Sprite::AddSprite(spr::game_spin_light, L"res/spin_light.png", 480, 268, 480/2, 268/2);
	Sprite::AddSprite(spr::game_spin_light2, L"res/spin_light2.png", 266, 143, 266 / 2, 143 / 2);
	Sprite::AddSprite(spr::bullet, L"res/bullet.png", 60, 41, 60/2, 41/2);
	Sprite::AddSprite(spr::score, L"res/score.png", 131, 20, 131/2, 20/2);
	Sprite::AddSprite(spr::score_num, L"res/score_number.png", 270, 34, 27 / 2, 20 / 2, 10);
	Sprite::AddSprite(spr::score_num2, L"res/score_number2.png", 211, 27, 211/10/2, 27 / 2, 10);
	Sprite::AddSprite(spr::hexa_bg, L"res/hexapattern.png", 830, 831);
	Sprite::AddSprite(spr::bullet_effect, L"res/bullet_effect.png", 33, 30, 17, 18);
	Sprite::AddSprite(spr::life, L"res/life.png", 21, 22, 21/2, 22/2);
	Sprite::AddSprite(spr::enemy, L"res/enemy.png", 608, 76, 608/8/2, 76/2, 8);
	Sprite::AddSprite(spr::explosion, L"res/explosion.png", 92, 92, 92/2, 92/2);
	Sprite::AddSprite(spr::ready, L"res/ready.png", 418, 55, 418/2, 55/2);
	Sprite::AddSprite(spr::enemy_warning, L"res/enemy_warning.png", 48, 48, 24, 24);
	Sprite::AddSprite(spr::enemy_warning_ring, L"res/enemy_warn_ring.png", 142, 52, 142/2, 52/2);
	Sprite::AddSprite(spr::explosion2, L"res/explosion2.png", 200, 200, 100, 100);
	Sprite::AddSprite(spr::explosion2_ring, L"res/explosion2_ring.png", 291, 291, 291/2, 291/2);
	Sprite::AddSprite(spr::wave_warn, L"res/wave_warn.png", 367, 32, 367/2, 32/2);
	Sprite::AddSprite(spr::highscored, L"res/highscored.png", 97, 17, 97 / 2, 17 / 2);
	Sprite::AddSprite(spr::retry, L"res/retry_msg.png", 260, 32, 260/2, 32/2);
	Sprite::AddSprite(spr::gameover, L"res/gameover.png", 503, 64, 503 / 2, 64 / 2);

#pragma endregion load sprites


}

void GameController::LoadSound()
{
#pragma region
	// gameRes에서 추가한 상수 값에 해당하는 리소스 불러오기 (SOUND->AddSound 사용)
	SOUND->AddSound(snd::bgm, "res/bgm.ogg", true, true);
	SOUND->AddSound(snd::buttonhover, "res/buttonhover.ogg", false, false);
	SOUND->AddSound(snd::game_start, "res/start.ogg", false, false);
	SOUND->AddSound(snd::player_shot, "res/shot.ogg", false, false);
	SOUND->AddSound(snd::explosion, "res/explosion.ogg", false, false);
	SOUND->AddSound(snd::explosion2, "res/explosion2.ogg", false, false);
	SOUND->AddSound(snd::enemy_hit, "res/hit.ogg", false, false);
	SOUND->AddSound(snd::enemy_warning, "res/warn.ogg", false, false);
	SOUND->AddSound(snd::wave_warning, "res/wave_siren.ogg", false, false);
	SOUND->AddSound(snd::get_ready, "res/getready.ogg", false, false);
	SOUND->AddSound(snd::re_gen, "res/re.ogg", false, false);
#pragma endregion load sounds

}

LRESULT GameController::MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	_hWnd = hWnd;
	switch (message)
	{
	case WM_CREATE:
		D2D1CreateFactory(D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);

		pFactory->CreateHwndRenderTarget(RenderTargetProperties(),
			HwndRenderTargetProperties(hWnd, SizeU(GAME_WIDTH, GAME_HEIGHT),
				D2D1_PRESENT_OPTIONS_IMMEDIATELY),
			&pRenderTarget);

		D2D1_SIZE_F d2dSize = pRenderTarget->GetSize();
		_d2dRate.x = d2dSize.width / GAME_WIDTH;
		_d2dRate.y = d2dSize.height / GAME_HEIGHT;

		pRenderTarget->CreateBitmap(SizeU(GAME_WIDTH, GAME_HEIGHT),
			BitmapProperties(PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE), 96.0f, 96.0f),
			&surface);

		srand((unsigned int)time(NULL));

		// DirectWrite로 그릴 폰트 설정
		InitDWrite(L"맑은 고딕", 12.0f, &dwFactory, &dwTextFormat);

		InitGame();

		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);

		TIME->Release();
		TIME->ReleaseSingleton();
		KEY->ReleaseSingleton();
		SOUND->Release();
		SOUND->ReleaseSingleton();
		Sprite::ReleaseSprite();
		surface->Release();
		ReleaseSingleton();
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		default:
			break;
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

vector<GameObject*>& GameController::GetObjectList()
{
	return objectList;
}

void GameController::DWriteText(TCHAR * text, FPOINT pos)
{
	pos.x -= GetViewPos().x;
	pos.y -= GetViewPos().y;

	ID2D1SolidColorBrush* brush_white, *brush_black;
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f), &brush_white);
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f), &brush_black);

	pRenderTarget->DrawTextW(
		text,
		wcslen(text),
		dwTextFormat,
		D2D1::RectF(pos.x+1, pos.y+1, GAME_WIDTH - pos.x +1, GAME_HEIGHT - pos.y +1),
		brush_black
	);

	pRenderTarget->DrawTextW(
		text,
		wcslen(text),
		dwTextFormat,
		D2D1::RectF(pos.x , pos.y, GAME_WIDTH-pos.x, GAME_HEIGHT-pos.y),
		brush_white
	);
}

void GameController::SetShakePos()
{
	shakeAmount += -shakeAmount / SHAKE_EASE;
	blurAlpha += -blurAlpha / 12.0f;
	if (shakeAmount < 0.1f) shakeAmount = 0.0f;
	shakePos = FPOINT({
		(float)Irand((int)-shakeAmount, (int)shakeAmount), (float)Irand((int)-shakeAmount, (int)shakeAmount)
	});
}

FPOINT GameController::GetShakePos()
{
	return shakePos;
}

void GameController::ScreenShake(int amount)
{
	shakeAmount = (float)amount;
	blurAlpha = amount/8.0f;
}
