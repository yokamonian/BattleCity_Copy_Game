#include "Player.h"
#include "Image.h"
#include "Missile.h"
#include "PlayerMissileManager.h"

HRESULT Player::Init()
{
	Pos.x = WINSIZE_X / 2;
	Pos.y = WINSIZE_Y / 2;
	Speed = 8;
	playerstate = Nomal;
	tank = ImageManager::GetSingleton()->AddImage("1P", "Image/PlayerTank.bmp", Pos.x, Pos.y, 500, 260, 8, 5, true, RGB(0, 0, 1));
	currentKeyFrameX = 0, currentKeyFrameY = 0;
	Direction = 0;
	isMove = false;
	missile = new PlayerMissileManager;
	missile->Init();

	return S_OK;
}

void Player::Release()
{
}

void Player::Update()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		SetKeyFrameX(0);
		Pos.y -= Speed;
		if (Pos.y < 60)
		{
			Pos.y = 60;
		}
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		SetKeyFrameX(1);
		Pos.y += Speed;
		if (Pos.y > 670)
		{
			Pos.y = 670;
		}
	}

	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		SetKeyFrameX(2);
		Pos.x += Speed;
		if (Pos.x > 1005)
		{
			Pos.x = 1005;
		}
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		SetKeyFrameX(3);
		Pos.x -= Speed;
		if (Pos.x < 207)
		{
			Pos.x = 207;
		}
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_UP) ||
		KeyManager::GetSingleton()->IsOnceKeyUp(VK_DOWN) ||
		KeyManager::GetSingleton()->IsOnceKeyUp(VK_LEFT) ||
		KeyManager::GetSingleton()->IsOnceKeyUp(VK_RIGHT))
	{
		if (isMove)
		{
			isMove = false;
		}
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		missile->SetDirection(Direction);
		missile->SetPos(Pos);
		missile->Fire();
	}
	if (missile)
	{
		missile->Update();
	}
}

void Player::Render(HDC hdc)
{
	if (missile)
	{
		missile->Render(hdc);
	}
	if (tank)
	{
		tank->FrameRender(hdc, Pos.x, Pos.y, currentKeyFrameX, currentKeyFrameY);
	}
}

void Player::SetKeyFrameX(int idx)
{
	Direction = idx;
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
			currentKeyFrameX = 6;
			break;
		case 3:
			currentKeyFrameX = 2;
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
