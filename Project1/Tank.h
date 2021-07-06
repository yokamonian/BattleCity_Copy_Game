#pragma once
#include "pch.h"

class Tank
{
protected:
	int ID = 0;
	int HP = 1;
	int AttackSpeed = 1;
	int Speed = 1;
	FPOINT Pos;
	int currentKeyFrameX;
	int currentKeyFrameY;

public:
	virtual HRESULT Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
};