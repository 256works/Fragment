#pragma once
#include "SingletonBase.h"
class TimeController :
	public SingletonBase<TimeController>
{
private:
	Timer* timer;
public:
	TimeController();
	~TimeController();

	void Init();
	void Release();
	void Update(float fps = 60.0f);
	void ShowFps();
};

