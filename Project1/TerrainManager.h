#pragma once
#include "pch.h"
#include "SingletonBase.h"


class TerrainManager : public SingletonBase<TerrainManager>
{
private:
	queue<TILE_INFO>tileManager;
	vector<queue<TILE_INFO>>stageTileManager;
	int stageNum = 1;
public:
	HRESULT Init();
	void Release();

	void SaveTileInfo(TILE_INFO* tiles, int ArrSize);
	queue<TILE_INFO>* GetStageTerrian(int idx);
	
};

