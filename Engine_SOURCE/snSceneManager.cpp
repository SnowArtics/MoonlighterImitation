#include "snSceneManager.h"
#include "snPlayScene.h"
#include "snTitleScene.h"
#include "snMainScene.h"
#include "snDungeonScene.h"

namespace sn
{
	Scene* SceneManager::mActiveScene = nullptr;
	std::map<std::wstring, Scene*> SceneManager::mScenes;
	void SceneManager::Initialize()
	{
		mActiveScene = new PlayScene();
		mScenes.insert(std::make_pair(L"PlayScene", mActiveScene));

		mActiveScene = new TitleScene();
		mScenes.insert(std::make_pair(L"TitleScene", mActiveScene));

		Scene* mScene = new MainScene();
		mScenes.insert(std::make_pair(L"MainScene", mScene));

		mScene = new DungeonScene();
		mScenes.insert(std::make_pair(L"DungeonScene", mScene));

		mActiveScene->Initialize();
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
	}

	void SceneManager::Render()
	{
		mActiveScene->Render();
	}
	void SceneManager::Release()
	{
		for (auto iter : mScenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
	Scene* SceneManager::LoadScene(std::wstring name)
	{
		std::map<std::wstring, Scene*>::iterator iter = mScenes.find(name);

		if (iter == mScenes.end())
			return nullptr;

		mActiveScene->OnExit();
		mActiveScene = iter->second;
		mActiveScene->OnEnter();

		return iter->second;
	}
}
