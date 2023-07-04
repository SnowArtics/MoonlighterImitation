#include "snScene.h"

namespace sn {
	sn::Scene::Scene()
	{
		for (int i = 0; i < (int)sn::enums::eLayerType::End; i++) {
			Layer* layer = new Layer();
			mLayers.push_back(layer);
		}
	}

	sn::Scene::~Scene()
	{
		for (int i = 0; i < (int)sn::enums::eLayerType::End; i++) {
			delete mLayers[i];
		}
	}

	void sn::Scene::Initialize()
	{
		for (Layer* layer : mLayers)
		{
			layer->Initialize();
		}
	}

	void sn::Scene::Update()
	{
		for (Layer* layer : mLayers)
		{
			layer->Update();
		}
	}

	void sn::Scene::LateUpdate()
	{
		for (Layer* layer : mLayers)
		{
			layer->LateUpdate();
		}
	}

	void sn::Scene::Render()
	{
		for (Layer* layer : mLayers)
		{
			layer->Render();
		}
	}
	void Scene::OnEnter()
	{
	}
	void Scene::OnExit()
	{
	}
	void Scene::AddGameObject(eLayerType type, GameObject* gameObj)
	{
		mLayers[(int)type]->AddGameObject(gameObj);
	}
}
