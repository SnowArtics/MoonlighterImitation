#pragma once
#include "..\Engine_SOURCE\snSceneManager.h"
#include "snPlayScene.h"
#include "snTitleScene.h"
#include "snVillageScene.h"
#include "snDungeonScene.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\SnowEngine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\SnowEngine.lib")
#endif

namespace sn
{
	void InitializeScenes()
	{
		//PlayScene* playScene = new PlayScene();
		SceneManager::CreateScene<PlayScene>(L"PlayScene");

		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<VillageScene>(L"VillageScene");
		SceneManager::CreateScene<DungeonScene>(L"DungeonScene");

		SceneManager::LoadScene(L"TitleScene");
	}
}