#pragma once

#include <Windows.h>
#include <map>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <ctime>
using namespace std;

#include "SimpleLog.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "TerrainManager.h"
// enum, struct, .h, #define


typedef struct tagFPOINT
{
	float x;	
	float y;
} FPOINT, *PFPOINT;


#define WINSIZE_X	1280	
#define WINSIZE_Y	720
#define WINSTART_X	50
#define WINSTART_Y	50
#define WINSTART_TILE_MAP_X  225
#define WINSTART_TILE_MAP_Y  26
#define WINSIZE_TILE_MAP_X  1060
#define WINSIZE_TILE_MAP_Y	700

#define PI			3.141592


#define TILESIZE_X	  32
#define TILESIZE_Y	  26			//타일 하나의 사이즈
//타일 하나의 사이즈
#define SAMPLE_TILE_X 3		//샘플타일의 갯수
#define SAMPLE_TILE_Y 2	//샘플 타일의 갯수

#define TILE_X	26			//메인 타일의 갯수
#define TILE_Y	26			//메인 타일의 갯수

enum TERRAIN {
	TR_BLOCK,
	TR_WATER,
	TR_ICE,
	TR_WALL,
	TR_GLASS,
	TR_NONE,
	TR_END
};



typedef struct tagSampleTile
{
	RECT rcTile;
	int frameX;
	int frameY;

}SAMPLE_TILE_INFO;

typedef struct tagTile
{
	TERRAIN terrain;
	RECT rcTile;
	int frameX;
	int frameY;

}TILE_INFO;

typedef struct tagSelectTile
{
	int frameX;
	int frameY;

}SELECT_TILE_INFO;

#define SAFE_DELETE(p)		{ if (p) { delete p; p = NULL; }}
#define SAFE_ARR_DELETE(p)	{ if (p) { delete [] p; p = NULL; }}

#define DEGREE_TO_RADIAN(x)	( x * PI / 180 )
#define RADIAN_TO_DEGREE(x) (int)( x * 180 / PI )

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;