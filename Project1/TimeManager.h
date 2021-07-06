#pragma once
#include "pch.h"
#include "SingletonBase.h"

class Timer;
class TimeManager : public SingletonBase<TimeManager>
{
private:
	Timer* timer;
	char strText[256];
	float testTime;
	bool isTestStart;
	bool isGameStart;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update(float lockFPS = 0.0f);
	virtual void Render(HDC hdc);


	float GetWorldCount();
	float GetCurrTime();

	float GetDeltaTime();
	void SetIsTestStart(bool b) { isTestStart = b; }
	void SetIsGameStart(bool _isGameStart) { isGameStart = _isGameStart; }

	void ResetWt();
	Timer* GetTimer() { return timer; }
};

