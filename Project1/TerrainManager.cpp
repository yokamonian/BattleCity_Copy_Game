#include "TerrainManager.h"

HRESULT TerrainManager::Init()
{
	return S_OK;
}

void TerrainManager::Release()
{
	while (!stageTileManager.empty())
	{
		stageTileManager.pop_back();
	}
	while (!tileManager.empty())
	{
		tileManager.pop();
	}
}

void TerrainManager::SaveTileInfo(TILE_INFO * tiles, int ArrSize)
{
	stageNum++;
	for (int i = 0; i < ArrSize; i++)
	{
		tileManager.push(tiles[i]);
	}
	stageTileManager.push_back(tileManager);
	while (!tileManager.empty())
	{
		tileManager.pop();
	}
}

queue<TILE_INFO>* TerrainManager::GetStageTerrian(int idx)
{
	if (stageTileManager.empty())
		return nullptr;
	tileManager = stageTileManager.at(idx);
	return &tileManager;
}
