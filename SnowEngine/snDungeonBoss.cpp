#include "snDungeonBoss.h"
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

#include "MonFactory.h"
#include "GolemKing.h"

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
#include "snAnimator.h"
#include "PlayerHP.h"
#include "snRigidBody.h"
#include "BossCamera.h"

#include "GolemKingFist.h"
#include <snAudioSource.h>
#include <snAudioListener.h>
#include "snRigidBody.h"
#include <InventoryManager.h>

namespace sn
{
	DungeonBoss::DungeonBoss()
	{
	}
	DungeonBoss::~DungeonBoss()
	{
	}
	void DungeonBoss::Initialize()
	{
		InventoryManager::CreateUI();

		{
			//던전 배경 로딩 //1.7777777777777
			GameObject* Background = new GameObject();
			AddGameObject(eLayerType::Background, Background);
			MeshRenderer* mr = Background->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"DungeonBossRoom01"));
			Background->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			//Background->GetComponent<Transform>()->SetScale(Vector3(6.7f, 4.0f, 2.0f));
			Background->GetComponent<Transform>()->SetScale(Vector3(17.73399014778f, 12.f, 0.0f));
		}

		{
			//보스몹 생성
			GolemKing* pMon = static_cast<GolemKing*>(MonFactory::CreateMonster(MonType::GOLEMKING, Vector2(0.42f, 2.76f)));
			AddGameObject(eLayerType::Monster, static_cast<sn::GameObject*>(pMon));
			pMon->SetName(L"GolemKing");
		}

		//{
		//	//보스 주먹 생성
		//	GolemKingFist* fist = new GolemKingFist;
		//	AddGameObject(eLayerType::Projectile, static_cast<sn::GameObject*>(fist));
		//	fist->SetGolemKingPos(Vector3(0.0f, -1.5f, 0.0f));
		//}

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

			Player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -5.f, 0.0f));
			Player->GetComponent<Transform>()->SetScale(Vector3(1.0f, 1.0f, 1.0f));

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

			Player->AddComponent<RigidBody>();

			AudioSource* as = Player->AddComponent<AudioSource>();
			as->SetClip(Resources::Load<AudioClip>(L"Forbidden Steps", L"..\\Resources\\Sound\\BGM\\Moonlighter OST - 08 - Golem King_256k.mp3"));
			as->Play();
			as->SetLoop(true);

			SetPlayer(Player);
		}
#pragma endregion

		{
			//Main Camera
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 1.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->EnableLayerMasks();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
			camera->AddComponent<BossCamera>();
			renderer::cameras.push_back(cameraComp);
			renderer::mainCamera = cameraComp;
			SetMainCamera(cameraComp);
			camera->AddComponent<AudioListener>();
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
	void DungeonBoss::Update()
	{
		Scene::Update();
	}
	void DungeonBoss::LateUpdate()
	{
		Scene::LateUpdate();
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::SetChangeScene(L"TitleScene");
		}
	}
	void DungeonBoss::Render()
	{
		Scene::Render();
	}
	void DungeonBoss::OnEnter()
	{
		Initialize();
		renderer::mainCamera = GetMainCamera();
	}
	void DungeonBoss::OnExit()
	{
		DestroyAll();
	}
}