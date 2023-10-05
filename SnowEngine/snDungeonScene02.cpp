#include "snDungeonScene02.h"
#include "snGameObject.h"
#include "snMeshRenderer.h"
#include "snMesh.h"
#include "snMaterial.h"
#include "snTransform.h"
#include "snCamera.h"
#include "snCameraScript.h"
#include "snAnimator.h"
#include "snRigidBody.h"

#include "snPlayerFSM.h"
#include "snMoveState.h"
#include "snIdleState.h"
#include "snRollState.h"
#include "snSwordState1.h"
#include "snSwordState2.h"
#include "snSwordState3.h"
#include "snBowState.h"
#include "snPlayerCollision.h"

#include "snSceneManager.h"
#include "snCollisionManager.h"

#include "snResources.h"
#include "snInput.h"

#include <random>
#include "snRenderer.h"

#include "MazeMaker.h"
#include "DungeonMapManager.h"
#include "snDungeonCamera.h"
#include "snDungeonDoor.h"
#include "MonFactory.h"
#include "Monster.h"

#include "snPlayer.h"
#include "PlayerHP.h"

namespace sn {
	DungeonScene02::DungeonScene02()
	{
	}
	DungeonScene02::~DungeonScene02()
	{
	}
	void DungeonScene02::Initialize()
	{
		SceneManager::GetActiveScene()->SetName(L"DungeonScene02");

		DungeonMapManager::GetInst()->Init();

		CollisionManager::SetLayer(eLayerType::Background, eLayerType::Door, false);

		MazeMaker::GetInst()->Init();
		MazeMaker::GetInst()->BackTracking(2, 1);
		arr = MazeMaker::GetInst()->GetDirArr();
		DungeonMapManager::GetInst()->SetDungeonArr(arr);
		std::pair<int, int> firstPlayerPos = MazeMaker::GetInst()->GetStartPos();
		DungeonMapManager::GetInst()->SetPlayerMapPos(firstPlayerPos);
		DungeonMapManager::GetInst()->SetPlayerMapSpawnPos(firstPlayerPos);

		std::vector<std::wstring> DungeonName;
		DungeonName.push_back(L"DungeonBackgroundMaterial00-1");
		DungeonName.push_back(L"DungeonBackgroundMaterial01-1");
		DungeonName.push_back(L"DungeonBackgroundMaterial02-1");
		DungeonName.push_back(L"DungeonBackgroundMaterial03-1");
		DungeonName.push_back(L"DungeonBackgroundMaterial04-1");
		DungeonName.push_back(L"DungeonBackgroundMaterial05-1");
		DungeonName.push_back(L"DungeonBackgroundMaterial06-1");
		DungeonName.push_back(L"DungeonBackgroundMaterial07-1");
		DungeonName.push_back(L"DungeonBackgroundMaterial08-1");
		DungeonName.push_back(L"DungeonBackgroundMaterial09-1");
		DungeonName.push_back(L"DungeonBackgroundMaterial10-1");
		DungeonName.push_back(L"DungeonBackgroundMaterial11-1");
		DungeonName.push_back(L"DungeonBackgroundMaterial12-1");
		DungeonName.push_back(L"DungeonBackgroundMaterial13-1");

		std::shuffle(DungeonName.begin(), DungeonName.end(), std::default_random_engine());

		DungeonMapManager::GetInst()->SetDungeonName(DungeonName);

		DungeonMapManager::GetInst()->MakeDungeonBackground(DungeonMapManager::GetInst()->GetPlayerMapPos().first, DungeonMapManager::GetInst()->GetPlayerMapPos().second);

		DungeonMapManager::GetInst()->MakeDoor(DungeonMapManager::GetInst()->GetPlayerMapPos().first, DungeonMapManager::GetInst()->GetPlayerMapPos().second, -1);

		//DungeonMapManager::GetInst()->MakeDungeonBackgrounds(DungeonName);

		//DungeonMapManager::GetInst()->MakeDoors();

#pragma region Object
		//오브젝트를 랜덤으로 생성

		// 시드값을 현재 시간으로 설정
		std::random_device rd;
		// 랜덤 엔진 생성
		std::mt19937 mt(rd());
		// 균일 분포를 가진 랜덤 숫자 생성기 생성 (0 이상 99 이하)
		std::uniform_real_distribution<float> distX(1.f, 8.f);
		std::uniform_real_distribution<float> distY(0.5f, 5.0f);

		{
			GameObject* Object = new GameObject();
			AddGameObject(eLayerType::Obstacle, Object);
			MeshRenderer* mr = Object->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"FountainMaterial"));

			Object->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 10.0f, -1.f));
			float YToXRatio = mr->GetMaterial()->GetTexture()->GetYToXRatio();
			Object->GetComponent<Transform>()->SetScale(Vector3(0.2f * YToXRatio, 0.2f, 0.0f));
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
			cameraComp->EnableLayerMasks();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
			camera->AddComponent<DungeonCamera>();
			renderer::cameras.push_back(cameraComp);
			renderer::mainCamera = cameraComp;
			SetMainCamera(cameraComp);
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

			Player->GetComponent<Transform>()->SetPosition(Vector3(DungeonMapManager::GetInst()->GetPlayerMapPos().second * 9.72f, DungeonMapManager::GetInst()->GetPlayerMapPos().first * -5.45f, 0.0f));
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

			SetPlayer(Player);
		}
#pragma endregion

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
	void DungeonScene02::Update()
	{
		Scene::Update();
	}
	void DungeonScene02::LateUpdate()
	{
		Scene::LateUpdate();
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::SetChangeScene(L"DungeonScene03");
		}
		if (Input::GetKeyDown(eKeyCode::I))
		{
			GameObject* inven = Scene::Find(L"InventoryBase");
			std::wstring asdf = inven->GetName();
			if (inven->GetEnable() == true) inven->SetEnable(false);
			else inven->SetEnable(true);
		}
	}
	void DungeonScene02::Render()
	{
		Scene::Render();
	}
	void DungeonScene02::OnEnter()
	{
		Initialize();
		renderer::mainCamera = GetMainCamera();
	}
	void DungeonScene02::OnExit()
	{
		DestroyAll();
	}
}