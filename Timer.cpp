#include "stdafx.h"
#include "Timer.h"
Timer::Timer()
{
}


Timer::~Timer()
{
}

void Timer::Init()
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency))
	{
		isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&preTime);
		timeScale = 1.0f / periodFrequency;
	}
	else
	{
		isHardware = false;
		preTime = timeGetTime();
		timeScale = 1.0f / 1000.0f;
	}
	
	frameRate = 0;
	fpsFrameCount = 0;
	fpsTimeElapsed = 0.0f;
}

void Timer::Tick(float fps)
{
	do
	{
		if (isHardware)
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&nowTime);
		}
		else
		{
			nowTime = timeGetTime();
		}
		timeElapsed = (nowTime - preTime) * timeScale;
	} while (timeElapsed < 1.0f / fps);

	preTime = nowTime;
	fpsFrameCount++;
	fpsTimeElapsed += timeElapsed;

	if (fpsTimeElapsed > 1.0f)
	{
		frameRate = fpsFrameCount;
		fpsFrameCount = 0;
		fpsTimeElapsed = 0.0f;
	}
	
}

unsigned int Timer::GetFps()
{
	return (unsigned int)frameRate;
}
