#include "StageManager.h"

HRESULT StageManager::Init()
{
	stageInfo = new int*[TILE_X];

	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			stageInfo[i][j] = 0;
		}
	}


	return S_OK;
}

void StageManager::Release()
{
	for (int i = 0; i < TILE_Y; ++i)
	{
		delete[] stageInfo[i];
	}
	SAFE_ARR_DELETE(stageInfo);
}

void StageManager::SaveStage(int ** stageInfo)
{
	vecStage.push_back(stageInfo);
}

int** StageManager::GetStageInfo()
{
	
	if (vecStage.empty())
		return nullptr;
	else
	{
		vector<int**>::iterator iter = vecStage.begin();
		stageInfo = vecStage.front();
		vecStage.erase(iter);
	}
		

	return stageInfo;
}

int ** StageManager::GetStageInfo(int idx)
{
	
	if (vecStage.empty())
		return nullptr;
	if (vecStage.at(idx) != 0)
	{
		vector<int**>::iterator iter = vecStage.begin();
		iter += idx;
		stageInfo = vecStage.at(idx);
		vecStage.erase(iter);
	}
	
	return stageInfo;
}

