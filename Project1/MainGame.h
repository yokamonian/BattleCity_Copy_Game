#pragma once
#include "GameNode.h"


class Image;
class GameNode;
class MainGame : public GameNode
{
private:
	bool isInit;
	Image* bg;
	Image* backBuffer;
	HDC hdc;

	GameNode* title;
	GameNode* mapEditor;
	GameNode* battle;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

