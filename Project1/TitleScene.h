#pragma once
#include "GameNode.h"

class Image;


class TitleScene : public GameNode
{
private:
	Image* bg;
	Image* tank;
	FPOINT menuPointer;
	FPOINT pos;
	int elapsedTime;
	int currFrameX;
	bool isRender = false;
	FPOINT menuPos[3] = { {480.0f, 425.0f}, {480.0f, 475.0f} ,{480.0f, 525.0f} };
	int menuNum;
	int addFrameX;
public:

	virtual HRESULT Init();		// 멤버 변수 초기화, 메모리 할당
	virtual void Release();		// 메모리 해제
	virtual void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)
	
	/*static void click1();
	static void click2();*/

	TitleScene();
	virtual ~TitleScene();
};

