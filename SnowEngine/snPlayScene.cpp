#include "snPlayScene.h"
#include "snTransform.h"
#include "snMeshRenderer.h"
#include "snResources.h"
#include "snMesh.h"
#include "snCameraScript.h"
#include "snCamera.h"
#include "snSceneManager.h"
#include "snGridScript.h"
#include "snObject.h"
#include "snRenderer.h"
#include "snCollider2D.h"
#include "snPlayerMove.h"
#include "snAnimator.h"
#include "snLight.h"
#include "snComputeShader.h"
#include "snCollisionManager.h"
#include "snPaintShader.h"
#include "snParticleSystem.h"
#include "snAudioListener.h"
#include "snAudioClip.h"
#include "snAudioSource.h"

namespace sn {	
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);

		std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
		std::shared_ptr<Texture> paintTexture = Resources::Find<Texture>(L"PaintTexuture");
		paintShader->SetTarget(paintTexture);
		paintShader->OnExcute();

		{
			GameObject* player
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::Player);

			player->SetName(L"Zelda");

			Collider2D* cd = player->AddComponent<Collider2D>();
			cd->SetSize(Vector2(1.2f, 1.2f));

			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

			player->GetComponent<Transform>()->SetPosition(Vector3(-2.0f, 0.0f, 1.0001f));
			//player->GetComponent<Transform>()->SetRotationByAngle(Vector3(0.0f, 0.0f, 45.f));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"LinkSprite", L"..\\Resources\\Texture\\linkSprites.png");

			Animator* at = player->AddComponent<Animator>();
			at->Create(L"Idle", atlas, Vector2(0.0f, 0.0f), Vector2(120.0f, 130.0f), 3, 150.f);

			at->PlayAnimation(L"Idle", true);
			player->AddComponent<PlayerMove>();

			AudioSource* as = player->AddComponent<AudioSource>();
			as->SetClip(Resources::Load<AudioClip>(L"TestSound", L"..\\Resources\\Sound\\0.mp3"));
			as->Play();
		}

		{
			GameObject* player = new GameObject();
			player->SetName(L"Smile");
			AddGameObject(eLayerType::Monster, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
			Collider2D* cd = player->AddComponent<Collider2D>();

			//AudioSource* as = player->AddComponent<AudioSource>();
			//as->SetClip(Resources::Load<AudioClip>(L"TestSound", L"..\\Resources\\Sound\\0.mp3"));
			//as->Play();
			//cd->SetSize(Vector2(1.2f, 1.2f));
			//player->AddComponent<PlayerMove>();
		}

		{
			GameObject* player = new GameObject();
			player->SetName(L"Particle");
			AddGameObject(eLayerType::Monster, player);
			ParticleSystem* mr = player->AddComponent<ParticleSystem>();
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
			player->GetComponent<Transform>()->SetScale(Vector3(0.2f, 0.2f, 0.2f));
			//Collider2D* cd = player->AddComponent<Collider2D>();
			//cd->SetSize(Vector2(1.2f, 1.2f));
			//player->AddComponent<PlayerScript>();
		}

		{
			GameObject* light = new GameObject();
			light->SetName(L"DirectionalLight01");
			AddGameObject(eLayerType::Light, light);
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetColor(Vector4(0.8f, 0.8f, 0.8f, 1.0f));
		}

		{
			GameObject* light = new GameObject();
			light->SetName(L"Smile");
			AddGameObject(eLayerType::Light, light);
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Point);
			lightComp->SetColor(Vector4(1.0f, 0.0f, 1.0f, 1.0f));
			lightComp->SetRadius(2.0f);
		}

		//{
		//	GameObject* player = new GameObject();
		//	player->SetName(L"Smile");
		//	AddGameObject(eLayerType::UI, player);
		//	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
		//	player->GetComponent<Transform>()->SetPosition(Vector3(0.2f, 0.0f, 0.0f));
		//	//player->AddComponent<CameraScript>();
		//}

		//Main Camera
		Camera* cameraComp = nullptr;
		{
			GameObject* camera = new GameObject();
			camera->SetName(L"MainCamera");
			AddGameObject(eLayerType::Camera, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
			renderer::cameras.push_back(cameraComp);
			renderer::mainCamera = cameraComp;

			camera->AddComponent<AudioListener>();
		}

		//UI Camera
		{
			GameObject* camera = new GameObject();
			camera->SetName(L"UICamera");
			AddGameObject(eLayerType::Camera, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			cameraComp->TurnLayerMask(eLayerType::Monster, false);
			//camera->AddComponent<CameraScript>();
		}

		//{
		//	GameObject* grid = new GameObject();
		//	grid->SetName(L"Grid");
		//	AddGameObject(eLayerType::Grid, grid);
		//	MeshRenderer* mr = grid->AddComponent<MeshRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
		//	GridScript* gridSc = grid->AddComponent<GridScript>();
		//	gridSc->SetCamera(cameraComp);
		//}


		//GameObject* player2 = new GameObject();
		//AddGameObject(eLayerType::Player, player2);
		//player2->AddComponent<MeshRenderer>();

		//Transform* tr = player->GetComponent<Transform>();
		//tr->SetPosition(Vector3(0.5f, 0.5f, 0.0f));
		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		//Vector3 pos(600, 450, 0.0f);
		//Vector3 pos2(600, 450, 1000.0f);
		//Viewport viewport;
		//viewport.width = 1920.0f;
		//viewport.height = 1080.0f;
		//viewport.x = 0;
		//viewport.y = 0;
		//viewport.minDepth = 0.0f;
		//viewport.maxDepth = 1.0f;
		//
		//pos = viewport.Unproject(pos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);
		//pos2 = viewport.Unproject(pos2, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);

		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}
	void PlayScene::OnEnter()
	{
			if (GetFlag() == true) {
				Initialize();
				SetFlag(false);
			}
		
	}
}