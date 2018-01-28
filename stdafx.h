// stdafx.h 
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <math.h>
#include <vector>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include "inc/fmod.hpp"
#pragma comment(lib, "lib/fmodex_vc.lib")

#include <wincodec.h>
#include <d2d1.h>
#include <d2d1_1.h>
#include <dwrite.h>
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")

#define GAME_WIDTH 960	// 게임화면 가로 사이즈
#define GAME_HEIGHT 540 // 게임화면 세로 사이즈

#define GAME_ROOM_WIDTH 1920
#define GAME_ROOM_HEIGHT 1080

#define GAME_RATIO GAME_WIDTH/GAME_HEIGHT
#define GAME_FPS 60.0f

#define FREQUENCY_DEFAULT 44100.0f
#define FREQUENCY_SLOWER 8000.0f

#define CURSOR_VISIBLE false
#define SOUND_MUTE false
#define SURFACE_BLUR true

#define REPEAT(x) for(int repeat = 0; repeat < x; ++repeat)

using namespace std;
using namespace FMOD;
using namespace D2D1;

extern HINSTANCE hInst;
extern HWND hWnd;

#define KEY KeyController::GetSingleton()
#define GC GameController::GetSingleton()
#define TIME TimeController::GetSingleton()
#define SOUND SoundController::GetSingleton()

#define VIEW GC->GetViewPos()

#include "fpoint.h"
#include "commonFunction.h"

#include "SpriteInfo.h"
#include "gameRes.h"
#include "Sprite.h"
#include "GameObject.h"

#include "Scene.h"

#include "Timer.h"
#include "SingletonBase.h"
#include "KeyController.h"
#include "GameController.h"
#include "TimeController.h"
#include "SoundController.h"

// -- 게임 오브젝트 추가 생성시 여기에 include
#include "obj_logo.h"
#include "obj_TitleManager.h"
#include "obj_WaveManager.h"
#include "obj_GameManager.h"
#include "obj_Player.h"
#include "obj_GameBackground.h"
#include "obj_Bullet.h"
#include "obj_BulletEffect.h"
#include "obj_Explosion.h"
#include "obj_Enemy.h"
#include "obj_EnemyGene.h"
#include "obj_HugeExplosion.h"
#include "obj_PlayerWave.h"
//

