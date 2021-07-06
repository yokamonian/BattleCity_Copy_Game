#include "Enemy.h"
#include "Image.h"
#include "Missile.h"

HRESULT Enemy::Init()
{
	Pos.x = WINSIZE_X / 2;
	Pos.y = 60;
	image = ImageManager::GetSingleton()->AddImage("Enemy", "Image/enemy_16_16.bmp", Pos.x, Pos.y, 384, 432, 8, 9, true, RGB(0, 0, 0));
	Speed = 300;
	enemyMissile = new Missile();
	enemyMissile->Init();
	currentKeyFrameX = 4;
	currentKeyFrameY = 0;
	isMove = false;
	increaseNum = 0;
	fireCount = 0;
	return S_OK;
}

void Enemy::Release()
{
}

void Enemy::Update()
{
	fireCount++;
	if (fireCount % 10 <= 8 && !enemyMissile->GetIsFire())
	{
		enemyMissile->SetPos(Pos);
		enemyMissile->SetIsFire(true);
		fireCount = 0;
	}
	if (enemyMissile->GetPos().x < 227 || enemyMissile->GetPos().x > 1070 || enemyMissile->GetPos().y < 15 || enemyMissile->GetPos().y > 711)
	{
		enemyMissile->SetIsFire(false);
	}
}

void Enemy::Render(HDC hdc)
{
	image->FrameRender(hdc, Pos.x, Pos.y, currentKeyFrameX, currentKeyFrameY);
}

void Enemy::SetKeyFrameX(int idx)
{
	if (!isMove)
	{
		switch (idx)
		{
		case 0:
			currentKeyFrameX = 0;
			break;
		case 1:
			currentKeyFrameX = 4;
			break;
		case 2:
			currentKeyFrameX = 2;
			break;
		case 3:
			currentKeyFrameX = 6;
			break;
		}
	}
	else if (isMove)
	{
		switch (idx)
		{
		case 0:
			-(increaseNum);
			currentKeyFrameX += increaseNum;
			break;
		case 1:
			-(increaseNum);
			currentKeyFrameX += increaseNum;
			break;
		case 2:
			-(increaseNum);
			currentKeyFrameX += increaseNum;
			break;
		case 3:
			-(increaseNum);
			currentKeyFrameX += increaseNum;
			break;
		}
	}
}