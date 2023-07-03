#include "snVillageScene.h"
#include "snGameObject.h"
#include "snMeshRenderer.h"
#include "snMesh.h"
#include "snMaterial.h"
#include "snTransform.h"
#include "snCamera.h"
#include "snCameraScript.h"

#include "snSceneManager.h"

#include "snResources.h"
#include "snInput.h"

namespace sn
{
	VillageScene::VillageScene()
	{
	}
	VillageScene::~VillageScene()
	{
	}
	void VillageScene::Initialize()
	{
		{
			//��� �̹���1 ����
			GameObject* Background = new GameObject();
			AddGameObject(eLayerType::Background, Background);
			MeshRenderer* mr = Background->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"VillageBackgroundMaterial01"));
			Background->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			//Background->GetComponent<Transform>()->SetScale(Vector3(6.7f, 4.0f, 2.0f));
			Background->GetComponent<Transform>()->SetScale(Vector3(19.495792f, 16.f, 2.0f));
		}

		{
			//Main Camera
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			camera->AddComponent<CameraScript>();
		}
	}
	void VillageScene::Update()
	{
		Scene::Update();
	}
	void VillageScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void VillageScene::Render()
	{
		Scene::Render();
		//if (Input::GetKeyDown(eKeyCode::SPACE))
		//{
		//	SceneManager::LoadScene(L"DungeonScene");
		//}
	}
	void VillageScene::OnEnter()
	{
		Initialize();
	}
	void VillageScene::OnExit()
	{
	}
}