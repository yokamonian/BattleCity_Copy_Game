#pragma once
#include "Tank.h"

class Image;
class Missile;
class Enemy : public Tank
{
private:
	Image* image;
	bool isMove;
	int increaseNum;
	int currFrameY = 0;
	bool isDamaged = false;
	Missile* enemyMissile;
	int fireCount;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetKeyFrameX(int idx);
	void SetKeyFrameY(int idx) { currFrameY = idx; }
	Missile* GetEMissile() { return enemyMissile; }
};

