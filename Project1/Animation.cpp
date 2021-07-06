#include "Animation.h"

Animation::Animation()
	: frameCount(0)
	, frameWidth(0)
	, frameHeight(0)
	, isLoop(false)
	, nowPlayIdx(0)
	, isPlaying(false)
	, keyFrameUpdateTime(0.0f)
	, accumulateTime(0.0f)
	
{
}

Animation::~Animation()
{
}

HRESULT Animation::Init(int totalWidth, int totalHeight, int frameWidth, int frameHeight)
{
	// 가로 프레임 수
	int frameWidthCount = totalWidth / frameWidth;

	// 세로 프레임 수 
	int frameHeightCount = totalHeight / frameHeight;

	// 전체 프레임 수
	frameCount = frameWidthCount * frameHeightCount;

	// 프레임 위치 리스트 셋팅
	vecFrameList.clear();
	vecFrameList.resize(frameCount);

	for (int i = 0; i < frameHeightCount; i++)
	{
		for (int j = 0; j < frameWidthCount; j++)
		{
			//POINT framePos = {i * frameHeight, j * frameWidth};

			vecFrameList[i * frameWidthCount + j].x = j * frameWidth;
			vecFrameList[i * frameWidthCount + j].y = i * frameHeight;

			//vecFrameList[i*frameWidthCount + j] = framePos;
		}
	}


	// 기본 플레이 리스트 셋팅
	SetPlayFrame();


	return S_OK;
}

void Animation::SetPlayFrame(bool isReverse, bool isLoop)
{
	this->isLoop = isLoop;

	vecPlayList.clear();

	if (isReverse)
	{
		//정방향
		for (int i = 0; i < frameCount; i++)
		{
			vecPlayList.push_back(i);
		}

		//역방향
		for (int i = frameCount-1; i > 0; i--)
		{
			vecPlayList.push_back(i);
		}
	}
	else
	{
		//정방향
		for (int i = 0; i < frameCount; i++)
		{
			vecPlayList.push_back(i); 
		}
	}


}

void Animation::SetPlayFrame(int startFrame, int endFrame, bool isReverse, bool isLoop)
{
	this->isLoop = isLoop;

	vecPlayList.clear();

	// startFrame이 0보다 크거나 같고 endFrame이 마지막 frame보다 작거나 같을 때

	if (startFrame == endFrame)
	{
		Stop();
		return;
	}

	if (startFrame > endFrame)
	{
		if (isReverse)
		{
			for (int i = startFrame; i < frameCount; i++)
			{
				vecPlayList.push_back(i);
			}

			for (int i = 0; i < endFrame + 1; i++)
			{
				vecPlayList.push_back(i);
			}

			for (int i = endFrame-1; i >- 1; i--)
			{
				vecPlayList.push_back(i);
			}

			for (int i = frameCount - 1; i >= startFrame; i--)
			{
				vecPlayList.push_back(i);
			}


		}
		else
		{
			for (int i = startFrame; i < frameCount; i++)
			{
				vecPlayList.push_back(i);
			}

			for (int i = 0; i < endFrame + 1; i++)
			{
				vecPlayList.push_back(i);
			}
		}
	}
	else
	{
		if (isReverse)
		{
			//정방향
			for (int i = startFrame; i < endFrame + 1; i++)
			{
				vecPlayList.push_back(i);
			}

			//역방향
			for (int i = endFrame - 1; i > startFrame; i--)
			{
				vecPlayList.push_back(i);
			}
		}
		else
		{
			//정방향
			for (int i = startFrame; i < endFrame + 1; i++)
			{
				vecPlayList.push_back(i);
			}
		}
	}
}

void Animation::SetPlayFrame(int * arr, int arrLength, bool isReverse, bool isLoop)
{
	this->isLoop = isLoop;

	vecPlayList.clear();

	if (isReverse)
	{
		for (int i = 0; i < arrLength; i++)
		{
			vecPlayList.push_back(arr[i]);
		}

		for (int i = arrLength - 1; i >= 0; i--)
		{
			vecPlayList.push_back(arr[i]);
		}
	}
	else
	{
		for (int i = 0; i < arrLength; i++)
		{
			vecPlayList.push_back(arr[i]);
		}
	}
}

void Animation::UpdateKeyFrame(float dt)
{
	if (isPlaying)
	{
		accumulateTime += dt;

		if (accumulateTime >= keyFrameUpdateTime)
		{
			nowPlayIdx++;

			if (nowPlayIdx >= vecPlayList.size())
			{
				// 루프일 때
				if (isLoop)
				{
					nowPlayIdx = 0;
				}
				else
				{
					nowPlayIdx--;
					isPlaying = false;
				}
			}

			accumulateTime -= keyFrameUpdateTime;
			/*accumulateTime = 0.0f;*/ //위가 더 정확하다
		}
	}

	
}

void Animation::Start()
{
	nowPlayIdx = 0;
	isPlaying = true;
}

void Animation::Stop()
{
	nowPlayIdx = 0;
	isPlaying = false;

}

void Animation::Pause()
{
	isPlaying = false;
}

void Animation::Resume()
{
	isPlaying = true;
}
