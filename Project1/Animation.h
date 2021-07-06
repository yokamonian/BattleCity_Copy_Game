#pragma once
#include "pch.h"

class Animation
{
private:
	// key frame 위치 리스트->   //시작하는 위치를 지정할 수 있는 인덱스.
	vector<POINT> vecFrameList;	

	// 플레이 리스트 -> //몇 번 키 프레임을 지정할 수 있는가 0번 5개 넣고 1,2,3,4,5,6 까지 넣으면 이렇게 재생되게 -->플레이 리스트를 만든다.
	vector<int> vecPlayList;

	int frameCount;		// 전체 프레임 수
	int frameWidth;		// 프레임 가로크기
	int frameHeight;	// 프레임 세로 크기

	bool isLoop;		// 반복 되는지 여부
	int nowPlayIdx;		// 현재 플레이 프레임 인덱스
	bool isPlaying;		// 현재 플레이 중인지 여부

	float keyFrameUpdateTime;   // 업데이트 기준 시간 //누적된 값이 얘를 초과하면 다음 프레임으로 넘기자
	float accumulateTime;		//누적 시간

public:
	Animation();
	~Animation();

	HRESULT Init(int totalWidth, int totalHeight, int frameWidth, int frameHeight);
	void SetPlayFrame(bool isReverse = FALSE, bool isLoop = FALSE);
	void SetPlayFrame(int startFrame, int endFrame, bool isReverse = FALSE, bool isLoop = FALSE);
	void SetPlayFrame(int* arr, int arrLength, bool isReverse = FALSE, bool isLoop = FALSE);
	void UpdateKeyFrame(float dt); //얘가 업데이트가 되는 기준(TimeManager의 elapsedTime), 

	void SetUpdateTime(int fps) { keyFrameUpdateTime = 1.0f / fps; } // 케릭터들마다 진행되는 속도를 다르게 할 수 있다.

	POINT GetFramePos() { return vecFrameList[vecPlayList[nowPlayIdx]]; }

	void Start();
	void Stop();
	void Pause();
	void Resume();
};

