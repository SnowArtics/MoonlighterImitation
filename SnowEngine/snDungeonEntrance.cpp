#include "snDungeonEntrance.h"
#include "snGameObject.h"
#include "snMeshRenderer.h"
#include "snMesh.h"
#include "snMaterial.h"
#include "snTransform.h"
#include "snCamera.h"
#include "snCameraScript.h"
#include "snAnimator.h"

#include "snSceneManager.h"

#include "snResources.h"
#include "snInput.h"
#include "snRenderer.h"

#include "EntranceDoor.h"

#include "snPlayer.h"
#include "snPlayerFSM.h"
#include "snMoveState.h"
#include "snIdleState.h"
#include "snRollState.h"
#include "snSwordState1.h"
#include "snSwordState2.h"
#include "snSwordState3.h"
#include "snBowState.h"
#include "snPlayerCollision.h"
#include "PlayerFollowCamera.h"
#include <snAudioSource.h>
#include <snAudioClip.h>
#include <snAudioListener.h>
#include "PlayerHP.h"

namespace sn {
	DungeonEntrance::DungeonEntrance()
	{
	}
	DungeonEntrance::~DungeonEntrance()
	{
	}
	void DungeonEntrance::Initialize()
	{
		{
			//던전 배경 로딩 //1.171428571428571
			GameObject* Background = new GameObject();
			AddGameObject(eLayerType::Background, Background);
			MeshRenderer* mr = Background->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"DungeonEntranceMaterial01"));
			Background->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			Background->GetComponent<Transform>()->SetScale(Vector3(11.1714f, 10.f, 2.0f));
			Background->GetComponent<Transform>()->SetScale(Vector3(23.42857142857142f, 20.f, 2.0f));
		
			
		}

		{
			//던전 TOP 배경 로딩 //0.71995708154
			GameObject* Background = new GameObject();
			AddGameObject(eLayerType::InteractionUI, Background);
			MeshRenderer* mr = Background->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"DungeonEntranceTopMaterial01"));
			Background->GetComponent<Transform>()->SetPosition(Vector3(0.08f, -0.30f, 0.0f));
			Background->GetComponent<Transform>()->SetScale(Vector3(14.3991416308f, 20.f, 2.0f));
		}

		{
			//슬라임 던전 문
			GameObject* Door = new GameObject();
			AddGameObject(eLayerType::InteractionDoor, Door);

			Door->GetComponent<Transform>()->SetPosition(Vector3(-4.9f, 0.9f, 0.0f));
			Door->GetComponent<Transform>()->SetScale(Vector3(1.3f, 1.3f, 1.0f));

			MeshRenderer* mr = Door->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

			Collider2D* cd = Door->AddComponent<Collider2D>();
			cd->SetCenter(Vector2(0.0f, 0.5f));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"EntranceSlimeDungeonDoor", L"..\\Resources\\Texture\\DungeonEntrance\\Portal1.png");

			Animator* at = Door->AddComponent<Animator>();

			at->Create(L"Door_Open", atlas, Vector2(0.0f, 0.0f), Vector2(44.f, 50.f), 7,60.f);
			at->Create(L"Door_Cycle", atlas, Vector2(0.0f, 50.f), Vector2(44.f, 50.f), 6, 60.f);
			at->Create(L"Door_Close", atlas, Vector2(0.0f, 100.f), Vector2(44.f, 50.f), 7, 60.f);
			at->Create(L"Door_Entrance", atlas, Vector2(0.0f, 150.f), Vector2(44.f, 50.f), 22, 60.f);

			at->PlayAnimation(L"Door_Close", false);

			EntranceDoor* entranceDoor = Door->AddComponent<EntranceDoor>();
			entranceDoor->Init();
		}

#pragma region Player
		{
			//플레이어 생성
			snPlayer* Player = new snPlayer();
			AddGameObject(eLayerType::Player, static_cast<GameObject*>(Player));
			Player->SetName(L"Player");
			Player->AddComponent<PlayerCollision>();
			Collider2D* cd = Player->AddComponent<Collider2D>();
			cd->SetSize(Vector2(0.3f, 0.3f));
			cd->SetName(L"FisrtCollider");
			cd->SetEnable(true);
			Collider2D* cd2 = Player->AddComponent<Collider2D>();
			cd2->SetName(L"SecondCollider");
			//cd2->SetSize(Vector2(0.5f, 0.8f));
			//cd2->SetCenter(Vector2(0.2f, -0.1f));
			cd2->SetEnable(false);
			MeshRenderer* mr = Player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

			//Light* lightComp = Player->AddComponent<Light>();
			//lightComp->SetType(eLightType::Point);
			//lightComp->SetColor(Vector4(0.8f, 0.8f, 0.8f, 1.0f));
			//lightComp->SetRadius(2.0f);

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"WillMoveSprite", L"..\\Resources\\Texture\\Player\\moveState.png");

			Animator* at = Player->AddComponent<Animator>();
			at->Create(L"MOVE_UP", atlas, Vector2(0.0f, 0.0f), Vector2(120.0f, 120.0f), 8);
			at->Create(L"MOVE_DOWN", atlas, Vector2(0.0f, 120.0f), Vector2(120.0f, 120.0f), 8);
			at->Create(L"MOVE_RIGHT", atlas, Vector2(0.0f, 240.0f), Vector2(120.0f, 120.0f), 8);
			at->Create(L"MOVE_LEFT", atlas, Vector2(0.0f, 360.0f), Vector2(120.0f, 120.0f), 8);

			at->Create(L"ROLL_RIGHT", atlas, Vector2(0.0f, 480.0f), Vector2(120.0f, 120.0f), 8, 110.f, 0.06f);
			at->Create(L"ROLL_LEFT", atlas, Vector2(0.0f, 600.0f), Vector2(120.0f, 120.0f), 8, 110.f, 0.06f);
			at->Create(L"ROLL_UP", atlas, Vector2(0.0f, 720.0f), Vector2(120.0f, 120.0f), 8, 110.f, 0.06f);
			at->Create(L"ROLL_DOWN", atlas, Vector2(0.0f, 840.0f), Vector2(120.0f, 120.0f), 8, 110.f, 0.06f);

			at->Create(L"IDLE_RIGHT", atlas, Vector2(0.0f, 960.0f), Vector2(120.0f, 120.0f), 10);
			at->Create(L"IDLE_LEFT", atlas, Vector2(0.0f, 1080.0f), Vector2(120.0f, 120.0f), 10);
			at->Create(L"IDLE_UP", atlas, Vector2(0.0f, 1200.0f), Vector2(120.0f, 120.0f), 10);
			at->Create(L"IDLE_DOWN", atlas, Vector2(0.0f, 1320.0f), Vector2(120.0f, 120.0f), 10);

			atlas = Resources::Load<Texture>(L"WillSwordAttackSprite", L"..\\Resources\\Texture\\Player\\swordState.png");

			at->Create(L"SWORD_UP1", atlas, Vector2(120.0f, 0.0f), Vector2(120.f, 120.f), 5);
			at->Create(L"SWORD_DOWN1", atlas, Vector2(120.0f, 120.0f), Vector2(120.f, 120.f), 5);
			at->Create(L"SWORD_RIGHT1", atlas, Vector2(120.0f, 240.0f), Vector2(120.f, 120.f), 5);
			at->Create(L"SWORD_LEFT1", atlas, Vector2(120.0f, 360.0f), Vector2(120.f, 120.f), 5);

			at->Create(L"SWORD_UP2", atlas, Vector2(720.f, 0.0f), Vector2(120.f, 120.f), 5);
			at->Create(L"SWORD_DOWN2", atlas, Vector2(720.f, 120.0f), Vector2(120.f, 120.f), 5);
			at->Create(L"SWORD_RIGHT2", atlas, Vector2(720.f, 240.0f), Vector2(120.f, 120.f), 5);
			at->Create(L"SWORD_LEFT2", atlas, Vector2(720.f, 360.0f), Vector2(120.f, 120.f), 5);

			atlas = Resources::Load<Texture>(L"WillBowAttackSprite", L"..\\Resources\\Texture\\Player\\bowState.png");

			at->Create(L"BOW_UP", atlas, Vector2(120.0f, 0.0f), Vector2(120.f, 120.f), 7);
			at->Create(L"BOW_DOWN", atlas, Vector2(120.0f, 120.0f), Vector2(120.f, 120.f), 7);
			at->Create(L"BOW_RIGHT", atlas, Vector2(120.0f, 240.0f), Vector2(120.f, 120.f), 7);
			at->Create(L"BOW_LEFT", atlas, Vector2(120.0f, 360.0f), Vector2(120.f, 120.f), 7);

			atlas = Resources::Load<Texture>(L"WILLCHARGE", L"..\\Resources\\bowChargeState.png");

			at->Create(L"BOW_CHARGE", atlas, Vector2(0.0f, 0.0f), Vector2(42.f, 80.f), 26);

			at->PlayAnimation(L"BOW_DOWN", true);

			Player->GetComponent<Transform>()->SetScale(Vector3(1.2f, 1.2f, 1.0f));

			PlayerFSM* playerFSM = Player->AddComponent<PlayerFSM>();
			playerFSM->AddState(new RollState);
			playerFSM->AddState(new MoveState);
			playerFSM->AddState(new SwordState1);
			playerFSM->AddState(new SwordState2);
			playerFSM->AddState(new SwordState3);
			playerFSM->AddState(new BowState);
			playerFSM->AddState(new IdleState);

			PlayerHP* playerHP = Player->AddComponent<PlayerHP>(100.f, 100.f);
			playerHP->CreateHpBar();

			SetPlayer(Player);
		}
#pragma endregion

		{
			//인벤토리 UI 생성
			GameObject* UI = new GameObject();
			UI->SetName(L"InventoryBase");
			AddGameObject(eLayerType::UI, UI);
			MeshRenderer* mr = UI->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"UIInventoryBaseMaterial01"));
			UI->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			UI->GetComponent<Transform>()->SetScale(Vector3(7.576642335766424f, 4.f, 2.0f));
			UI->SetEnable(false);
		}
		{
			//UI 생성 부분
			{
				GameObject* UI = new GameObject();
				AddGameObject(eLayerType::UI, UI);
				MeshRenderer* mr = UI->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"UIBaseMaterial01"));
				UI->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
				UI->GetComponent<Transform>()->SetScale(Vector3(9.599958f, 5.4f, 2.0f));
			}
			{
				GameObject* UI = new GameObject();
				AddGameObject(eLayerType::UI, UI);
				MeshRenderer* mr = UI->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"UIBaseMaterial02"));
				UI->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
				UI->GetComponent<Transform>()->SetScale(Vector3(9.599958f, 5.4f, 2.0f));
			}
			{
				//UI 우측 상단 무기 UI 생성
				GameObject* UI = new GameObject();
				AddGameObject(eLayerType::UI, UI);
				MeshRenderer* mr = UI->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"UIBaseMaterial02"));
				UI->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
				UI->GetComponent<Transform>()->SetScale(Vector3(9.599958f, 5.4f, 2.0f));
			}
			{
				GameObject* UI = new GameObject();
				AddGameObject(eLayerType::UI, UI);
				MeshRenderer* mr = UI->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"UIGoldMaterial01"));
				UI->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
				UI->GetComponent<Transform>()->SetScale(Vector3(9.599958f, 5.4f, 2.0f));
			}
			{
				GameObject* UI = new GameObject();
				AddGameObject(eLayerType::UI, UI);
				MeshRenderer* mr = UI->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"UIWeaponMaterial02"));
				UI->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
				UI->GetComponent<Transform>()->SetScale(Vector3(9.599958f, 5.4f, 2.0f));
			}
			{
				GameObject* UI = new GameObject();
				AddGameObject(eLayerType::UI, UI);
				MeshRenderer* mr = UI->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"UIWeaponMaterial01"));
				UI->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
				UI->GetComponent<Transform>()->SetScale(Vector3(9.599958f, 5.4f, 2.0f));
			}
		}
		{
			//Main Camera
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
			camera->AddComponent<PlayerFollowCamera>();
			camera->AddComponent<AudioListener>();
			renderer::cameras.push_back(cameraComp);
			renderer::mainCamera = cameraComp;
			SetMainCamera(cameraComp);

			AudioSource* as = camera->AddComponent<AudioSource>();
			as->SetClip(Resources::Load<AudioClip>(L"dungeon_entrance_wind_ambient", L"..\\Resources\\Sound\\BGM\\dungeon_entrance_wind_ambient.wav"));
			as->Play();
			as->SetLoop(true);
		}

		//UI Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->DisableLayerMasks();
			cameraComp->TurnLayerMask(eLayerType::UI, true);			
			//camera->AddComponent<CameraScript>();
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
	void DungeonEntrance::Update()
	{
		Scene::Update();
	}
	void DungeonEntrance::LateUpdate()
	{
		Scene::LateUpdate();
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::SetChangeScene(L"DungeonScene01");
		}
		if (Input::GetKeyDown(eKeyCode::I))
		{
			GameObject* inven = Scene::Find(L"InventoryBase");
			std::wstring asdf = inven->GetName();
			if (inven->GetEnable() == true) inven->SetEnable(false);
			else inven->SetEnable(true);
		}
	}
	void DungeonEntrance::Render()
	{
		Scene::Render();
	}
	void DungeonEntrance::OnEnter()
	{
		Initialize();
		renderer::mainCamera = GetMainCamera();
	}
	void DungeonEntrance::OnExit()
	{
		DestroyAll();
	}
}