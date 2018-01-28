#include "stdafx.h"
#include "TimeController.h"


TimeController::TimeController()
{
}


TimeController::~TimeController()
{
}

void TimeController::Init()
{
	timer = new Timer;
	timer->Init();
}

void TimeController::Release()
{
	if (timer != NULL)
	{
		delete timer;
		timer = NULL;
	}
}

void TimeController::Update(float fps)
{
	if (timer != NULL)
	{
		timer->Tick(fps);
	}
}

void TimeController::ShowFps()
{
#ifdef _DEBUG
	{
		TCHAR str[50], str2[50], str3[50];
		int fps = timer->GetFps();
		swprintf_s(str, 50, L"FPS : %d", fps);
		GC->DWriteText(str, FPOINT({VIEW.x + 2, VIEW.y + 2}));

		int insCnt = GC->GetObjectList().size();
		swprintf_s(str2, 50, L"Game Instance °³¼ö : %d", insCnt);
		GC->DWriteText(str2, FPOINT({VIEW.x + 2,VIEW.y + 2 + 16 }));

		int dccnt = Sprite::GetDrawCallCount();
		swprintf_s(str3, 50, L"Sprite Draw È½¼ö : %d", dccnt);
		GC->DWriteText(str3, FPOINT({VIEW.x + 2,VIEW.y + 2 + 32 }));
	}
#endif
}
