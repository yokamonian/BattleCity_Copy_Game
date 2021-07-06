#pragma once
#include "SingletonBase.h"
#include <Windows.h>
#include <map>

using namespace std;

class GameNode;
class SceneManager : public SingletonBase<SceneManager>
{
private:
	map<string, GameNode*> mapSceneDatas;
	map<string, GameNode*> mapLoadingSceneDatas;

public:
	static GameNode* currentScene; //멤버 변수로 되어있기 때문에 접근할 때 전역변수와 차이점이 있다.
	static GameNode* loadingScene;
	static GameNode* readyScene;	

public:

	HRESULT Init();		// 멤버 변수 초기화, 메모리 할당
	void Release();		// 메모리 해제
	void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)

	// 씬 추가
	GameNode* AddScene(string key, GameNode* scene); //키와 scene을 넣으면 map에 저장할 함수
	GameNode* AddLoadingScene(string key, GameNode* scene); //키와 scene을 넣으면 map에 저장할 함수
	

	// 씬 체인지
	HRESULT ChangeScene(string sceneName);
	HRESULT ChangeScene(string sceneName, string loadingSceneName);

	SceneManager();
	virtual ~SceneManager();
};

