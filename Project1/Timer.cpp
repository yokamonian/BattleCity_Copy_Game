#include "Timer.h"
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")


HRESULT Timer::Init()
{
	frameRate = 0;
	FPSFrameCount = 0;
	FPSTimeElapsed = 0;
	worldTime = 0;
	
	// QueryPerformanceFrequency = 주파수 주기 // QueryPerformanceCount = 누적주파수
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency))
	{
		isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
		timeScale = 1.0f / periodFrequency;
	}
	else
	{
		isHardware = false;
		lastTime = timeGetTime();
		timeScale = 0.001f;
	}
	return S_OK;
}

void Timer::Tick(float lockFPS)
{
	if (isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	}
	else
	{
		currTime = timeGetTime();
	}
	timeElapsed = (currTime - lastTime) * timeScale;

	if (lockFPS > 0.0f)
	{
		while (timeElapsed < (1.0f / lockFPS))
		{
			if (isHardware)
			{
				QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
			}
			else
			{
				currTime = timeGetTime();
			}
			timeElapsed = (currTime - lastTime) * timeScale;
		}
	}

	if(isGameStart)
		worldTime += timeElapsed;

	FPSFrameCount++;
	FPSTimeElapsed += timeElapsed;

	if (FPSTimeElapsed > 1.0f)
	{
		frameRate = FPSFrameCount;
		FPSFrameCount = 0;
		FPSTimeElapsed = 0;
	}

	lastTime = currTime;
}

Timer::Timer()
{
}


Timer::~Timer()
{
}
