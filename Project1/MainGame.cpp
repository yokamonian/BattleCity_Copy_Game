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
	SceneManager::GetSingleton()->AddScene("��Ʈ��", title);

	mapEditor = new MapEditor();
	SceneManager::GetSingleton()->AddScene("�ʿ�����", mapEditor);

	battle = new BattleScene();
	SceneManager::GetSingleton()->AddScene("��Ʋ", battle);
	SceneManager::GetSingleton()->ChangeScene("��Ʋ");

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

	InvalidateRect(g_hWnd, NULL, false); //backbuffer�� �־��� �Ŀ��� false�� ������ֱ�
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
