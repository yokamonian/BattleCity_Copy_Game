#include "MapEditor.h"
#include "Image.h"
#include "MacroFunction.h"


HRESULT MapEditor::Init()
{

	mapEditorUi = ImageManager::GetSingleton()->AddImage("맵에디터UI", "Image/ingameUI.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(0, 0, 0));

	sampleTileImage = ImageManager::GetSingleton()->AddImage("샘플타일", "Image/Terrain.bmp", 0.0f, 0.0f, 96, 52, SAMPLE_TILE_X, SAMPLE_TILE_Y, false, RGB(0, 0, 0));
	saveBtn = ImageManager::GetSingleton()->AddImage("세이브버튼", "Image/SaveBtn.bmp", 0, 0, 120, 100, 1, 2, false, RGB(0, 0, 0));
	loadBtn = ImageManager::GetSingleton()->AddImage("로드버튼", "Image/Loadbtn.bmp", 0, 0, 120, 100, 1, 2, false, RGB(0, 0, 0));
	menuPointer = ImageManager::GetSingleton()->AddImage("메뉴선택포인터", "Image/selectPoint.bmp", 130, 60, true, RGB(133, 127, 113));
	samplePicker = ImageManager::GetSingleton()->AddImage("샘플타일포인터", "Image/selectPoint2.bmp", 76, 64, true, RGB(133, 127, 113));
	mainPointer = ImageManager::GetSingleton()->AddImage("메인타일포인터", "Image/selectPoint2.bmp", 38, 32, true, RGB(133, 127, 113));

	//선택한 타일 초기화
	selectTileInfo.frameX = 0;
	selectTileInfo.frameY = 0;

	posNum = 0;
	picXNum = 0;
	picYNum = 0;

	pos = { WINSTART_TILE_MAP_X + (TILESIZE_X / 2) , WINSTART_TILE_MAP_Y + (TILESIZE_Y / 2) };

	////오른쪽에 샘플 타일의 RECT를 설정한다.
	for (int i = 0; i < SAMPLE_TILE_Y; i++)
	{
		for (int j = 0; j < SAMPLE_TILE_X; j++)
		{
			sampleTileInfo[i * SAMPLE_TILE_X + j].frameX = j;
			sampleTileInfo[i * SAMPLE_TILE_X + j].frameY = i;

			SetRect(&sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile,
				(WINSIZE_X - 110) - sampleTileImage->GetWidth() + j * (TILESIZE_X * 2), i * (TILESIZE_Y * 2) + 24,
				(WINSIZE_X - 110) - sampleTileImage->GetWidth() + j * (TILESIZE_X * 2) + (TILESIZE_X * 2),
				i * (TILESIZE_Y * 2) + (TILESIZE_Y * 2) + 24);
		}
	}

	//왼쪽에 메인 타일의 RECT를 설정한다.
	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			SetRect(&tileInfo[i*TILE_X + j].rcTile, WINSTART_TILE_MAP_X + j * TILESIZE_X, WINSTART_TILE_MAP_Y + i * TILESIZE_Y,
				WINSTART_TILE_MAP_X + j * TILESIZE_X + TILESIZE_X, WINSTART_TILE_MAP_Y + i * TILESIZE_Y + TILESIZE_Y);
		}
	}

	//왼쪽에 그려질 내용을 초기화 한다.(기본적으로 잔디로 설정)
	for (int i = 0; i < TILE_X * TILE_Y; i++)
	{
		tileInfo[i].frameX = 3;
		tileInfo[i].frameY = 2;

		tileInfo[i].terrain = TR_NONE;
	}

	saveBtnPos = { 1170, 502 };

	loadBtnPos = { 1170, 572 };




	return S_OK;
}

void MapEditor::Release()
{
}

void MapEditor::Update()
{
	//마우스 왼쪽 버튼을 눌렀을 때
	// 1. 샘플타일 선택 2. 메인타일 선택

	//마우스 왼쪽 버튼을 뗐을 때
	// 1. 샘플타일에서 선택 2. 메인 타일에서 선택

	//마우스가 클릭한 상태로 이동 될 때(드래그)
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		if ((isSamplePick) || (isMainTile))
		{
			isSamplePick = false;
			isMainTile = false;
			isSavePoint = true;
		}
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('C'))
	{
		if ((isSavePoint) || (isMainTile))
		{
			isSamplePick = true;
			isMainTile = false;
			isSavePoint = false;
		}
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('X'))
	{
		if ((isSavePoint) || (isSamplePick))
		{
			isSamplePick = false;
			isMainTile = true;
			isSavePoint = false;
		}
	}

	if (isSavePoint)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN) ||
			(KeyManager::GetSingleton()->IsOnceKeyDown(VK_UP)))
		{
			if (posNum == 0)
				posNum = 1;
			else if (posNum == 1)
				posNum = 0;
		}
		if (posNum == 0 && KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
		{
			Save();
		}
		else if (posNum == 1 && KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
		{
			Load();
		}

	}
	if (isSamplePick)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LEFT))
		{
			picXNum--;
			if (picXNum <= 0)
				picXNum = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RIGHT))
		{
			picXNum++;
			if (picXNum >= 2)
				picXNum = 2;
		}
		if ((KeyManager::GetSingleton()->IsOnceKeyDown(VK_UP)) ||
			(KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN)))
		{
			if (picYNum == 0)
				picYNum = 1;
			else if (picYNum == 1)
				picYNum = 0;
		}
		if (isSamplePick)
		{
			//샘플맵 타일을 선택했을 경우
			if (KeyManager::GetSingleton()->IsOnceKeyDown('Z'))
			{
				for (int i = 0; i < SAMPLE_TILE_X * SAMPLE_TILE_Y; i++)
				{
					//클릭 선택을 위한 값 입력
					selectTileInfo.frameX = picXNum;
					selectTileInfo.frameY = picYNum;

					break;
				}
			}
		}
	}
	if (isMainTile)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LEFT))
		{
			if (pos.x >= WINSTART_TILE_MAP_X + TILESIZE_X)
				pos.x -= TILESIZE_X;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RIGHT))
		{
			if (pos.x <= WINSIZE_TILE_MAP_X - TILESIZE_X)
				pos.x += TILESIZE_X;
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_UP))
		{
			if (pos.y >= WINSTART_TILE_MAP_Y + TILESIZE_Y)
				pos.y -= TILESIZE_Y;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN))
		{
			if (pos.y <= WINSIZE_TILE_MAP_Y - TILESIZE_Y)
				pos.y += TILESIZE_Y;
		}

		//		//선택한 타일을 메인 타일에 입력함
		for (int i = 0; i < TILE_X * TILE_Y; i++)
		{
			if (PtInRect(&tileInfo[i].rcTile, pos))
			{
				if (KeyManager::GetSingleton()->IsOnceKeyDown('Z'))
				{
					tileInfo[i].frameX = selectTileInfo.frameX;
					tileInfo[i].frameY = selectTileInfo.frameY;
					break;
				}
			}
		}
	}





	
}

void MapEditor::Render(HDC hdc)
{
	//바탕색 칠하기
	//PatBlt(hdc, 0, 0, WINSIZE_TILE_MAP_X, WINSIZE_TILE_MAP_Y, WHITENESS);
	if (mapEditorUi)	mapEditorUi->Render(hdc, WINSIZE_X / 2, WINSIZE_Y / 2);
	//오른쪽 타일맵 샘플 그리기
	sampleTileImage->ScaleRender(hdc, WINSIZE_X - sampleTileImage->GetWidth() - 62, 50, 2.0f);
	if (isSamplePick)
	{
		samplePicker->Render(hdc, samplePicPos[picYNum][picXNum].x, samplePicPos[picYNum][picXNum].y);
	}
	//선택한 타일
	sampleTileImage->FrameRender(hdc, WINSIZE_X - sampleTileImage->GetWidth() - 94, 150,
		selectTileInfo.frameX, selectTileInfo.frameY);




	//eraseImage->Render(hdc, 650, 590);


	if (saveBtn)		saveBtn->FrameRender(hdc, saveBtnPos.x, saveBtnPos.y, 0, 0);
	if (loadBtn)		loadBtn->FrameRender(hdc, loadBtnPos.x, loadBtnPos.y, 0, 0);
	if (isSavePoint)
	{
		if (menuPointer)	menuPointer->Render(hdc, saveBtnPos.x, menuSelectPos[posNum].y);
	}

	//왼쪽 메인 타일 맵
	for (int i = 0; i < TILE_X * TILE_Y; i++)
	{
		sampleTileImage->FrameRender(hdc,
			tileInfo[i].rcTile.left + (TILESIZE_X / 2),
			tileInfo[i].rcTile.top + (TILESIZE_Y / 2)
			, tileInfo[i].frameX, tileInfo[i].frameY);
	}
	if (isMainTile)
	{
		mainPointer->Render(hdc, pos.x, pos.y);
	}
}

void MapEditor::Save()
{
	for (int i = 0; i < TILE_X * TILE_Y; i++)
	{
		if (tileInfo[i].frameX == 0 && tileInfo[i].frameY == 0)
		{
			tileInfo[i].terrain = TR_BLOCK;
		}
		else if (tileInfo[i].frameX == 1 && tileInfo[i].frameY == 0)
		{
			tileInfo[i].terrain = TR_WATER;
		}
		else if (tileInfo[i].frameX == 2 && tileInfo[i].frameY == 0)
		{
			tileInfo[i].terrain = TR_ICE;
		}
		else if (tileInfo[i].frameX == 0 && tileInfo[i].frameY == 1)
		{
			tileInfo[i].terrain = TR_WALL;
		}
		else if (tileInfo[i].frameX == 1 && tileInfo[i].frameY == 1)
		{
			tileInfo[i].terrain = TR_GLASS;
		}
		else if (tileInfo[i].frameX == 2 && tileInfo[i].frameY == 1)
		{
			tileInfo[i].terrain = TR_NONE;
		}
	}

	OPENFILENAME OFN;
	char lpstrFile[MAX_PATH] = "";
	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = g_hWnd;
	OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 256;
	OFN.lpstrInitialDir = "C:\\";
	GetOpenFileName(&OFN);



	DWORD writtenByte;
	HANDLE hFile = CreateFile(lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &writtenByte, NULL);
	CloseHandle(hFile);




}

void MapEditor::Load()
{
	OPENFILENAME OFN;
	char lpstrFile[MAX_PATH] = "";
	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = g_hWnd;
	OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 256;
	OFN.lpstrInitialDir = "C:\\Users\teakgeun\Downloads\API_form_ver5\Project1\Save";
	GetOpenFileName(&OFN);

	DWORD ReadByte;
	HANDLE hFile = CreateFile(lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &ReadByte, NULL);
	CloseHandle(hFile);



}



//void MapEditor::Erase()
//{
//	for (int i = 0; i < TILE_X * TILE_Y; i++)
//	{
//		tileInfo[i].frameX = 3;
//		tileInfo[i].frameY = 0;
//		tileInfo[i].objFrameX = 3;
//		tileInfo[i].objFrameY = 0;
//		tileInfo[i].terrain = TR_GRASS;
//		tileInfo[i].mapObject = OBJ_NULL;
//	}
//}

MapEditor::MapEditor()
{
}

MapEditor::~MapEditor()
{
}
