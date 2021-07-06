#pragma once
#include "pch.h"
#include "GameNode.h"


class Image;
class Player;
class BattleScene : public GameNode
{
private:
	Image* SpreiteTerrain;
	Image* sampleTileImage;
	Image* Ui;
	TILE_INFO tileInfo[TILE_X*TILE_Y];
	Player* tank;
	int** stageInfo;
	int stageNum;
	int monsterCount;
	static BattleScene* instance;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void LoadScene(int stageIdx);
};

