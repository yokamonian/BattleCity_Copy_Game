#include "Missile.h"
#include "Image.h"

HRESULT Missile::Init()
{
	image = ImageManager::GetSingleton()->AddImage("bullet", "Image/missile.bmp", 0, 0, 84, 21, 4, 1, true, RGB(0, 0, 1));
	currentKeyFrameX = 0;
	currentKeyFrameY = 0;
	Pos = { 0,0 };
	Speed = 10;
	//rc = { 0,0,0,0 };
	return S_OK;
}

void Missile::Release()
{
}

void Missile::Update()
{
	if (isFire)
	{
		
		switch (Direction)
		{
		case 0:
			SetKeyFrame();
			Pos.y -= Speed;
			break;
		case 1:
			SetKeyFrame();
			Pos.y += Speed;
			break;
		case 2:
			SetKeyFrame();
			Pos.x += Speed;
			break;
		case 3:
			SetKeyFrame();
			Pos.x -= Speed;
			break;
		}
	}
	//if (Pos.y <= 200)
	//{
	//	idx++;
	//	if (idx < 30)
	//	{
	//		idx = 3;
	//	}
	//	rc = { (int)Pos.x - idx, (int)Pos.y - idx, (int)Pos.x + idx, (int)Pos.y + idx };
	//}

	
}

void Missile::Render(HDC hdc)
{
	if (image)
	{
		if (isFire)
		{
			image->FrameRender(hdc, Pos.x, Pos.y, currentKeyFrameX, currentKeyFrameY);
			//Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
		}
	}
	
}

void Missile::SetKeyFrame()
{
	switch (Direction)
	{
	case 0:
		currentKeyFrameX = 0;
		break;
	case 1:
		currentKeyFrameX = 2;
		break;
	case 2:
		currentKeyFrameX = 3;
		break;
	case 3:
		currentKeyFrameX = 1;
		break;
	}
}

