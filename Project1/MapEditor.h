#pragma once
#include "pch.h"
#include "GameNode.h"


class Button;
class MapEditor : public GameNode
{
private:
	Image* sampleTileImage;
	Image* eraseImage;
	Image* mapEditorUi;
	Image* saveBtn;
	Image* loadBtn;
	Image* menuPointer;
	Image* samplePicker;
	Image* mainPointer;
	FPOINT samplePos;
	FPOINT samplePicPos[2][3] = {{{1106, 50},{1170, 50}, {1234, 50}}, {{ 1106, 102 }, { 1170, 102 }, { 1234, 102 }}};
	POINT pos;
	FPOINT saveBtnPos;
	FPOINT loadBtnPos;
	FPOINT menuSelectPos[2] = { {1170, 502}, {1170, 572} };
	int posNum;
	int picXNum;
	int picYNum;

	bool isSavePoint = false;
	bool isSamplePick = true;
	bool isMainTile = false;
	//샘플 타일의 정보 (시작 프레임 포인트, rect 정보)
	SAMPLE_TILE_INFO sampleTileInfo[SAMPLE_TILE_X * SAMPLE_TILE_Y];

	//메인 타일의 정보 (rect 정보, 샘플 타일의 시작 프레임 포인트, 타일의 속성)
	TILE_INFO tileInfo[TILE_X*TILE_Y];

	//선택된 타일의 정보 (시작 프레임 포인트)
	SELECT_TILE_INFO selectTileInfo;


	int minX, maxX, minY, maxY;

	bool isDownSampleArea;



	Button* saveButton;
	Button* loadButton;


	OPENFILENAME opn;

public:

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void Save();
	void Load();
	void Erase();

	MapEditor();
	~MapEditor();
};


