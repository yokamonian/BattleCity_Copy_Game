#pragma once
#include "pch.h"

class GameNode
{
public:
	virtual HRESULT Init() = 0;
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual void Update();
};

