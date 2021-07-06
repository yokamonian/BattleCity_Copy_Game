#pragma once
#include "Tank.h"

class Enemy;
class EnemyManager : public Tank
{
private:
	Enemy* enemyTank;
	vector<Enemy*> vecEnemys;
	vector<Enemy*>::iterator itEnemy;
	stack<Enemy*> stEnemys;
	int monsterCount = 20;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetId(int id);
	void SetEnemy(int id);
};