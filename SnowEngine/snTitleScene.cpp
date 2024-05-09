#include "snTitleScene.h"
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
#include "snRenderer.h"
#include <snAnimator.h>
#include "snLight.h"

#include "TitleDoor.h"
#include <snAudioListener.h>
#include <snAudioSource.h>
#include <snAudioClip.h>

namespace sn
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		{
			//배경1
			GameObject* Background = new GameObject();
			AddGameObject(eLayerType::Background, Background);
			MeshRenderer* mr = Background->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
			Background->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			//Background->GetComponent<Transform>()->SetScale(Vector3(6.7f, 4.0f, 2.0f));
			//Background->GetComponent<Transform>()->SetScale(Vector3(9.77777735f, 5.5f, 2.0f));
			Background->GetComponent<Transform>()->SetScale(Vector3(11.f, 11.f, 2.0f));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"TitleAnimationBackground01", L"..\\Resources\\Texture\\Title\\Main_menu.png");

			Animator* at = Background->AddComponent<Animator>();
			at->Create(L"TitleAnimation01", atlas, Vector2(0.0f, 360.0f), Vector2(640.f, 360.0f), 16, 720.f);
			
			at->PlayAnimation(L"TitleAnimation01", true);
		}

		{
			//배경2
			GameObject* Background = new GameObject();
			AddGameObject(eLayerType::Background, Background);
			MeshRenderer* mr = Background->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
			Background->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			//Background->GetComponent<Transform>()->SetScale(Vector3(6.7f, 4.0f, 2.0f));
			//Background->GetComponent<Transform>()->SetScale(Vector3(9.77777735f, 5.5f, 2.0f));
			Background->GetComponent<Transform>()->SetScale(Vector3(11.f, 11.f, 2.0f));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"TitleAnimationBackground02", L"..\\Resources\\Texture\\Title\\Main_menu.png");

			Animator* at = Background->AddComponent<Animator>();
			at->Create(L"TitleAnimation02", atlas, Vector2(0.0f, 0.0f), Vector2(640.f, 360.0f), 16, 720.f);

			at->PlayAnimation(L"TitleAnimation02", true);
		}

		{
			//로고
			GameObject* Background = new GameObject();
			AddGameObject(eLayerType::Background, Background);
			MeshRenderer* mr = Background->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"LogoMaterial01"));
			Background->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 1.0f, -0.3f));
			//Background->GetComponent<Transform>()->SetScale(Vector3(6.7f, 4.0f, 2.0f));
			Background->GetComponent<Transform>()->SetScale(Vector3(4.f, 2.0f, 2.0f));
		}

		{
			GameObject* Background = new GameObject();
			AddGameObject(eLayerType::Background, Background);
			Background->AddComponent<TitleDoor>();
		}

		{
			//Main Camera
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			//camera->AddComponent<CameraScript>();
			renderer::cameras.push_back(cameraComp);
			renderer::mainCamera = cameraComp;
			SetMainCamera(cameraComp);
			camera->AddComponent<AudioListener>();
		}
		// Light
		{
			GameObject* light = new GameObject();
			light->SetName(L"DirectionalLight01");
			AddGameObject(eLayerType::Light, light);
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetColor(Vector4(0.8f, 0.8f, 0.8f, 1.0f));
		}
		Scene::Initialize();
	}
	void TitleScene::Update()
	{
		Scene::Update();
	}
	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();

		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::SetChangeScene(L"DungeonEntrance");
		}
	}
	void TitleScene::Render()
	{
		Scene::Render();


	}
	void TitleScene::OnEnter()
	{
		Initialize();
		renderer::mainCamera = GetMainCamera();
	}
	void TitleScene::OnExit()
	{
		DestroyAll();
	}
}