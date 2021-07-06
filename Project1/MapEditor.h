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
	//���� Ÿ���� ���� (���� ������ ����Ʈ, rect ����)
	SAMPLE_TILE_INFO sampleTileInfo[SAMPLE_TILE_X * SAMPLE_TILE_Y];

	//���� Ÿ���� ���� (rect ����, ���� Ÿ���� ���� ������ ����Ʈ, Ÿ���� �Ӽ�)
	TILE_INFO tileInfo[TILE_X*TILE_Y];

	//���õ� Ÿ���� ���� (���� ������ ����Ʈ)
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


