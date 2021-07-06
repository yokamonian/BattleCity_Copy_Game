#pragma once
#include "pch.h"

#define TILESIZE_X 33
#define TILESIZE_Y 26

#define TILE_X	26
#define TILE_Y	26


class StageManager
{
private:

	int** stageInfo;
	vector<int**> vecStage;
public:
	HRESULT Init();
	void Release();

	void SaveStage(int** stageInfo);

	int** GetStageInfo();
	int** GetStageInfo(int idx);

};

