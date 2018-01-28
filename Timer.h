#pragma once
class Timer
{
private:
	bool isHardware;
	float timeScale;
	float timeElapsed;

	__int64 nowTime;
	__int64 preTime;
	__int64 periodFrequency;

	unsigned long frameRate;
	unsigned long fpsFrameCount;

	float fpsTimeElapsed;

public:
	Timer();
	~Timer();

	void Init();
	void Tick(float fps = 60.0f);
	unsigned int GetFps();
};

