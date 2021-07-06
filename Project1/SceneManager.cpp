#include "SceneManager.h"
#include "GameNode.h"

GameNode* SceneManager::currentScene = nullptr;
GameNode* SceneManager::loadingScene = nullptr;
GameNode* SceneManager::readyScene = nullptr;

//콜백 함수
// 변경할 메인씬을 초기화 하는 것.
DWORD CALLBACK LoadingThread(LPVOID pvParam)
{
	// 쓰레드 종료 시점 (방법)
	/*
		1. 호출된 함수가 반환이 될 때 (우리가 사용할 방법)
		2. 호출된 함수 내부에서 ExitThread()를 호출했을 때
		3. 동일한 프로세스나 다른 프로세스에서 TerminateThread()를 호출했을 때
		4. 현재 쓰레드가 포함된 프로세스가 종료될 때
	*/

	SceneManager::readyScene->Init();
	SceneManager::currentScene = SceneManager::readyScene;

	SceneManager::loadingScene->Release();
	SceneManager::loadingScene = nullptr;
	SceneManager::readyScene = nullptr;

	return 0;
}

SceneManager::SceneManager()
{

}
SceneManager::~SceneManager()
{

}

HRESULT SceneManager::Init()
{
	return S_OK;
}

void SceneManager::Release()
{
}

void SceneManager::Update()
{
	if (currentScene)
	{
		currentScene->Update();
	}
}

void SceneManager::Render(HDC hdc)
{
	if (currentScene)
	{
		currentScene->Render(hdc);
	}
}

GameNode * SceneManager::AddScene(string key, GameNode * scene)
{
	if (scene == nullptr)
		return nullptr;
	
	mapSceneDatas.insert(pair<string, GameNode*>(key, scene)); // <string, GameNode*타입이고,> ( key, scene ) 씬을 초기화 해서 맵에다가 insert를 한다.

	return scene;
}

GameNode * SceneManager::AddLoadingScene(string key, GameNode * scene)
{
	if (scene == nullptr)
		return nullptr;

	mapLoadingSceneDatas.insert(pair<string, GameNode*>(key, scene)); // <string, GameNode*타입이고,> ( key, scene ) 씬을 초기화 해서 맵에다가 insert를 한다.

	return scene;
}

HRESULT SceneManager::ChangeScene(string sceneName) //키를 들고와서
{
	map<string, GameNode*>::iterator it;

	it = mapSceneDatas.find(sceneName);

	if (it == mapSceneDatas.end()) //없으면 SceneChange에 실패했다를 알려주고.
	{
		return E_FAIL;
	}

	if (it->second == currentScene) return S_OK; //씬 체인지 동작 없이 S_OK를 리턴해주자.

	if (SUCCEEDED(it->second->Init())) //바꿀려고 하는 씬
	{
		if (currentScene) //현재 씬은 릴리즈를 해주고
		{
			currentScene->Release();
		}


		currentScene = it->second;
		return S_OK;
	}

	return E_FAIL;
}

HRESULT SceneManager::ChangeScene(string sceneName, string loadingSceneName)
{
	map<string, GameNode*>::iterator it;

	it = mapSceneDatas.find(sceneName);

	if (it == mapSceneDatas.end()) //없으면 SceneChange에 실패했다를 알려주고.
	{
		return E_FAIL;
	}

	if (it->second == currentScene) return S_OK; //씬 체인지 동작 없이 S_OK를 리턴해주자.

	// change 중간에 들어갈 로딩씬
	map<string, GameNode*>::iterator itLoading;
	itLoading = mapLoadingSceneDatas.find(loadingSceneName);

	if (itLoading == mapLoadingSceneDatas.end())
	{
		return ChangeScene(sceneName);
	}

	if (SUCCEEDED(itLoading->second->Init())) //바꿀려고 하는 씬
	{
		if (currentScene) //현재 씬은 릴리즈를 해주고
		{
			currentScene->Release();
		}

		readyScene = it->second;
		loadingScene = itLoading->second;

		currentScene = loadingScene;
		 
		// 멀티쓰레드로 체인지할 메인씬을 초기화한다.   // 멀티쓰레드가 처리할 함수의 주소
		HANDLE hThread;
		DWORD loadThredID;
		//hThread= CreateThread(NULL, 0, func, NULL, 0, &loadThredID);
		//CloseHandle(hThread);
		// 함수이름이 곧 함수의 포인터니까
		CloseHandle(CreateThread(NULL, 0, LoadingThread, NULL, 0, &loadThredID));  //쓰레드를 다시 닫아준다.

		return S_OK;
	}

	return E_FAIL;
}

