#include "TitleScene.h"
#include "Image.h"


HRESULT TitleScene::Init()
{
	menuNum = 0;
	pos = { 0, WINSIZE_Y };
	menuPointer = { 0.0f, 0.0f };
	bg = ImageManager::GetSingleton()->AddImage("인트로", "Image/intro.bmp", WINSIZE_X, WINSIZE_Y);
	tank = ImageManager::GetSingleton()->AddImage("탱크", "Image/PlayerTank.bmp", 
		menuPointer.x, menuPointer.y, 320, 200, 8, 5, true, RGB( 0, 0, 0));

	elapsedTime = 0;
	currFrameX = 6;
	addFrameX = -1;
	return S_OK;
}

void TitleScene::Release()
{
	
}

void TitleScene::Update()
{
	menuPointer = menuPos[menuNum];
	elapsedTime++;
	if (elapsedTime % 3 == 2)
	{
		addFrameX = -(addFrameX);
		elapsedTime = 0;
		currFrameX += addFrameX;
	}
	if (pos.y >= 0)
		pos.y -= 5;
	if (pos.y < 0)
	{
		pos.y = 0;
		isRender = true;

		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN))
		{
			menuNum++;
			if (menuNum > 2)
			{
				menuNum = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_UP))
		{
			menuNum--;
			if (menuNum < 0)
			{
				menuNum = 2;
			}
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
		{
			switch (menuNum)
			{
			case 0:
				break;
			case 1:
				SceneManager::GetSingleton()->ChangeScene("인트로", "맵에디터");
				break;
			case 2:
				break;
			}
		}
	}

}

void TitleScene::Render(HDC hdc)
{
	if (bg)
	{
		bg->Render(hdc, pos.x, pos.y);
	}
	if (tank && isRender == true)
	{
		tank->FrameRender(hdc, menuPointer.x, menuPointer.y, currFrameX, 0);
		//tank->Render(hdc, menuPointer.x, menuPointer.y);
	}

}

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}
