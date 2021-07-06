#pragma once
#include "pch.h"
#include "ObjectPool.h"
#include "Missile.h"

class PlayerMissileManager : public Missile
{
private:
	FPOINT m_pos;
	int m_direction;
	bool isFire;
	Image* image;
	vector<Missile*> vecMissile;
	vector<Missile*>::iterator itMissile;

	CObjectPool missilepool;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	bool Fire();
	void SetDirection(int direction) { m_direction = direction; }
};

