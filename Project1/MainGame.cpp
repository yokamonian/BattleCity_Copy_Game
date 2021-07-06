#include "MainGame.h"
#include "Image.h"
#include "TitleScene.h"
#include "MapEditor.h"
#include "BattleScene.h"

HRESULT MainGame::Init()
{
	hdc = GetDC(g_hWnd);

	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	TimeManager::GetSingleton()->Init();
	SoundManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();
	TerrainManager::GetSingleton()->Init();

	title = new TitleScene();
	SceneManager::GetSingleton()->AddScene("인트로", title);

	mapEditor = new MapEditor();
	SceneManager::GetSingleton()->AddScene("맵에디터", mapEditor);

	battle = new BattleScene();
	SceneManager::GetSingleton()->AddScene("배틀", battle);
	SceneManager::GetSingleton()->ChangeScene("배틀");

	isInit = true; 
	return S_OK;
}

void MainGame::Release()
{
	TerrainManager::GetSingleton()->Release();
	TerrainManager::GetSingleton()->ReleaseSingleton();

	SceneManager::GetSingleton()->Release();
	SceneManager::GetSingleton()->ReleaseSingleton();

	SoundManager::GetSingleton()->Release();
	SoundManager::GetSingleton()->ReleaseSingleton();

	TimeManager::GetSingleton()->Release();
	TimeManager::GetSingleton()->ReleaseSingleton();

	ImageManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->ReleaseSingleton();

	KeyManager::GetSingleton()->Release();
	KeyManager::GetSingleton()->ReleaseSingleton();

	backBuffer->Release();
	delete backBuffer;

	ReleaseDC(g_hWnd, hdc);
}


void MainGame::Update()
{
	SceneManager::GetSingleton()->Update();

	InvalidateRect(g_hWnd, NULL, false); //backbuffer에 넣어준 후에는 false로 만들어주기
}

void MainGame::Render()
{
	SceneManager::GetSingleton()->Render(backBuffer->GetMemDC());
	backBuffer->Render(hdc, 0, 0);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}



MainGame::MainGame()
	: isInit(false)
{
}


MainGame::~MainGame()
{
}
