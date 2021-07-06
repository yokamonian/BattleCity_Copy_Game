#include "BattleScene.h"
#include "Image.h"
#include "Player.h"

BattleScene* BattleScene::instance = 0;

HRESULT BattleScene::Init()
{
	instance = this;
	sampleTileImage = ImageManager::GetSingleton()->AddImage("샘플타일", "Image/Terrain.bmp", 0.0f, 0.0f, 96, 52, SAMPLE_TILE_X, SAMPLE_TILE_Y, false, RGB(0, 0, 0));
	Ui = ImageManager::GetSingleton()->AddImage("UI", "Image/ingameUI.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(0, 0, 0));
	tank = new Player();
	tank->Init();
	monsterCount = 20;
	stageNum = 0;
	LoadScene(stageNum);

	

	return S_OK;
}

void BattleScene::Release()
{
	tank->Release();
	SAFE_DELETE(tank);
}

void BattleScene::Update()
{
	
	if (tank)
		tank->Update();
	if (monsterCount <= 0)
	{
		monsterCount = 20;
		stageNum++;
		LoadScene(stageNum);
	}

}

void BattleScene::Render(HDC hdc)
{
	if (Ui)
		Ui->Render(hdc, WINSIZE_X / 2, WINSIZE_Y / 2);
	for (int i = 0; i < TILE_X * TILE_Y; i++)
	{
		sampleTileImage->FrameRender(hdc,
			tileInfo[i].rcTile.left + (TILESIZE_X / 2),
			tileInfo[i].rcTile.top + (TILESIZE_Y / 2)
			, tileInfo[i].frameX, tileInfo[i].frameY);
	}
	tank->Render(hdc);

}

void BattleScene::LoadScene(int stageIdx)
{
	switch (stageIdx)
	{
	case 0:
		DWORD readByte;
		HANDLE hFile;
		hFile = CreateFile("Save/saveMapData.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); // 파일이름위치/ 읽음/ 
		ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &readByte, NULL);
		CloseHandle(hFile);
		break;
	case 1:
		DWORD readByte;
		HANDLE hFile;
		hFile = CreateFile("Save/gg.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); // 파일이름위치/ 읽음/ 
		ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &readByte, NULL);
		CloseHandle(hFile);
		break;
	case 2:
		DWORD readByte;
		HANDLE hFile;
		hFile = CreateFile("Save/ggggg.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); // 파일이름위치/ 읽음/ 
		ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &readByte, NULL);
		CloseHandle(hFile);
		break;
	}

}
