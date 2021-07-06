#pragma once
#include "Tank.h"

enum PlayerState
{
	Nomal,
	Speed,
	AttackSpeed,
	Pig,
	END
};

class Image;
class PlayerMissileManager;
class Player : public Tank
{
private:
	Image* tank;
	PlayerMissileManager* missile;
	int increaseNum = -1;
	PlayerState playerstate;
	bool isMove;
	int Direction;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetKeyFrameX(int idx);
	PlayerMissileManager* GetPMM() { return missile; }
};

