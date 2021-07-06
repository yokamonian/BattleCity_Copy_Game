#pragma once
#include "pch.h"
#include "Image.h"

class Missile
{
public:
	FPOINT Pos;
	int Speed;
	int currentKeyFrameX;
	int currentKeyFrameY;
	bool isFire;
	int Direction;
	RECT rc;
	Image* image;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	bool GetIsFire() { return isFire; }
	void SetIsFire(bool fire) { isFire = fire; }
	void SetDirection(int direction) { Direction = direction; }
	void SetPos(FPOINT pos) { Pos = pos; }
	FPOINT GetPos() { return Pos; }

	void SetKeyFrame();

};

