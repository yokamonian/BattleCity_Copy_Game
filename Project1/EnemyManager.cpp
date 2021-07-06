#include "EnemyManager.h"
#include "Enemy.h"

HRESULT EnemyManager::Init()
{
	for (int i = 0; i < monsterCount; i++)
	{
		enemyTank = new Enemy();
		stEnemys.push(enemyTank);
	}

	return S_OK;
}

void EnemyManager::Release()
{
	while (!stEnemys.empty())
	{
		stEnemys.pop();
	}
}

void EnemyManager::Update()
{
	if (vecEnemys.size() > 0)
	{
		for (itEnemy = vecEnemys.begin(); itEnemy != vecEnemys.end(); itEnemy++)
		{
			(*itEnemy)->Update();
		}
	}
}

void EnemyManager::Render(HDC hdc)
{
	if (vecEnemys.size() > 0)
	{
		for (itEnemy = vecEnemys.begin(); itEnemy != vecEnemys.end(); itEnemy++)
		{
			(*itEnemy)->Render(hdc);
		}
	}
}

void EnemyManager::SetId(int id)
{
	switch (id)
	{
	case 1:
		this->ID = id;
		this->Speed = 3;
		this->currentKeyFrameY = 0;
		break;
	case 2:
		this->ID = id;
		this->AttackSpeed = 3;
		this->currentKeyFrameY = 1;
		break;
	case 3:
		this->ID = id;
		this->HP = 3;
		this->currentKeyFrameY = 2;
		break;
	default:
		break;
	}
}

void EnemyManager::SetEnemy(int id)
{
	Enemy* monster;
	monster = stEnemys.top();
	stEnemys.pop();
	vecEnemys.push_back(monster);
}
