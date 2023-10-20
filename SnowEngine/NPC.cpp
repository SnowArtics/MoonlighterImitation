#include "NPC.h"

#include "AI.h"
#include "snAnimator.h"
#include "snSceneManager.h"
#include "DungeonMapManager.h"
#include "MonsterHPBar.h"
#include "snCollider2D.h"
#include "snTime.h"
#include "snPlayer.h"
#include "PlayerHP.h"
#include <snAudioSource.h>
#include "snResources.h"
#include "snMeshRenderer.h"
#include<random>
#include "NPCBuy.h"
#include "NPCMove.h"
#include "NPCIdle.h"
#include "ShopManager.h"

NPC::NPC()
	: Monster(false)
	, deadFlag(false)
	, buyGold(0)
{
	tMonInfo monInfo;
	monInfo.fHP = 100.f;

	SetMonInfo(monInfo);

	Transform* tr = GetComponent<Transform>();
	tr->SetScale(Vector3(1.f, 1.f, 0.0f));

	MeshRenderer* mr = AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

	Animator* at = AddComponent<Animator>();

	// 난수 엔진 초기화
	std::random_device rd;
	std::mt19937 mt(rd());

	// 1부터 100 사이의 균일한 정수 분포
	std::uniform_int_distribution<int> dist(3, 3);

	int randomValue = dist(mt);
	switch (randomValue)
	{
	case 1:
	{
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"GirlNPCSprite", L"..\\Resources\\Texture\\Shop\\Girl.png");
		at->Create(L"MOVE_DOWN", atlas, Vector2(0.0f, 0.0f), Vector2(128.f, 128.f), 8);
		at->Create(L"MOVE_LEFT", atlas, Vector2(0.0f, 128.f), Vector2(128.f, 128.f), 8);
		at->Create(L"MOVE_RIGHT", atlas, Vector2(0.0f, 256.f), Vector2(128.f, 128.f), 8);
		at->Create(L"MOVE_UP", atlas, Vector2(0.0f, 384.f), Vector2(128.f, 128.f), 8);

		at->Create(L"IDLE_DOWN", atlas, Vector2(0.0f, 0.0f), Vector2(128.f, 128.f), 1);
		at->Create(L"IDLE_LEFT", atlas, Vector2(0.0f, 128.f), Vector2(128.f, 128.f), 1);
		at->Create(L"IDLE_RIGHT", atlas, Vector2(0.0f, 256.f), Vector2(128.f, 128.f), 1);
		at->Create(L"IDLE_UP", atlas, Vector2(0.0f, 384.f), Vector2(128.f, 128.f), 1);		
	}
	break;
	case 2:
	{
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"GuyNPCSprite", L"..\\Resources\\Texture\\Shop\\Guy.png");
		at->Create(L"MOVE_DOWN", atlas, Vector2(0.0f, 0.0f), Vector2(128.f, 128.f), 8);
		at->Create(L"MOVE_LEFT", atlas, Vector2(0.0f, 128.f), Vector2(128.f, 128.f), 8);
		at->Create(L"MOVE_RIGHT", atlas, Vector2(0.0f, 256.f), Vector2(128.f, 128.f), 8);
		at->Create(L"MOVE_UP", atlas, Vector2(0.0f, 384.f), Vector2(128.f, 128.f), 8);

		at->Create(L"IDLE_DOWN", atlas, Vector2(0.0f, 0.0f), Vector2(128.f, 128.f), 1);
		at->Create(L"IDLE_LEFT", atlas, Vector2(0.0f, 128.f), Vector2(128.f, 128.f), 1);
		at->Create(L"IDLE_RIGHT", atlas, Vector2(0.0f, 256.f), Vector2(128.f, 128.f), 1);
		at->Create(L"IDLE_UP", atlas, Vector2(0.0f, 384.f), Vector2(128.f, 128.f), 1);
	}
	break;
	case 3:
	{
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"HeroNPCSprite", L"..\\Resources\\Texture\\Shop\\Hero.png");
		at->Create(L"MOVE_DOWN", atlas, Vector2(0.0f, 0.0f), Vector2(128.f, 151.5f), 8, 180.f);
		at->Create(L"MOVE_LEFT", atlas, Vector2(0.0f, 151.5f), Vector2(128.f, 151.5f), 8, 180.f);
		at->Create(L"MOVE_RIGHT", atlas, Vector2(0.0f, 303.f), Vector2(128.f, 151.5f), 8, 180.f);
		at->Create(L"MOVE_UP", atlas, Vector2(0.0f, 454.5f), Vector2(128.f, 151.5f), 8, 180.f);

		at->Create(L"IDLE_DOWN", atlas, Vector2(0.0f, 0.0f), Vector2(128.f, 151.5f), 1, 180.f);
		at->Create(L"IDLE_LEFT", atlas, Vector2(0.0f, 151.5f), Vector2(128.f, 151.5f), 1, 180.f);
		at->Create(L"IDLE_RIGHT", atlas, Vector2(0.0f, 303.f), Vector2(128.f, 151.5f), 1, 180.f);
		at->Create(L"IDLE_UP", atlas, Vector2(0.0f, 454.5f), Vector2(128.f, 151.5f), 1, 180.f);
	}
	break;
	default:
		break;
	}

	at->PlayAnimation(L"IDLE_DOWN",true);

	AI* ai = AddComponent<AI>(this);
	ai->AddState(new NPCIdle);
	ai->AddState(new NPCMove);
	ai->AddState(new NPCBuy);

	ai->SetCurState(MON_STATE::IDLE);

	//think Box
	thinkBox = new GameObject();

	mr = thinkBox->AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

	SceneManager::GetActiveScene()->AddGameObject(eLayerType::HitEffect, thinkBox);

	at = thinkBox->AddComponent<Animator>();
	std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"thinkBox", L"..\\Resources\\Texture\\Shop\\thinkBox.png");
	at->Create(L"thinkBox", atlas, Vector2(0.0f, 0.0f), Vector2(26.f, 26.f), 1);

	at->PlayAnimation(L"thinkBox", false);

	thinkBox->GetComponent<Transform>()->SetScale(Vector3(1.5f, 1.5f, 0.0f));

	thinkBox->SetEnable(false);

	//think
	think = new GameObject();

	mr = think->AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

	SceneManager::GetActiveScene()->AddGameObject(eLayerType::HitEffect, think);

	at = think->AddComponent<Animator>();
	atlas = Resources::Load<Texture>(L"think", L"..\\Resources\\Texture\\Shop\\think.png");
	at->Create(L"think", atlas, Vector2(0.0f, 0.0f), Vector2(32.f, 32.f), 3);

	atlas = Resources::Load<Texture>(L"TooCheap", L"..\\Resources\\Texture\\Shop\\tooCheap.png");
	at->Create(L"TooCheap", atlas, Vector2(0.0f, 0.0f), Vector2(32.f, 32.f), 13);

	atlas = Resources::Load<Texture>(L"TooExpensive", L"..\\Resources\\Texture\\Shop\\tooExpensive.png");
	at->Create(L"TooExpensive", atlas, Vector2(0.0f, 0.0f), Vector2(32.f, 32.f),9);

	atlas = Resources::Load<Texture>(L"Cheap", L"..\\Resources\\Texture\\Shop\\Cheap.png");
	at->Create(L"Cheap", atlas, Vector2(0.0f, 0.0f), Vector2(32.f, 32.f), 4);

	at->PlayAnimation(L"think", false);

	think->GetComponent<Transform>()->SetScale(Vector3(1.5f, 1.5f, 0.0f));

	think->SetEnable(false);
}

NPC::~NPC()
{
}

void NPC::Initialize()
{
	Monster::Initialize();
}

void NPC::Update()
{
	if (thinkBox != nullptr) {
		Vector3 npcPos = GetComponent<Transform>()->GetPosition();
		Transform* tr = thinkBox->GetComponent<Transform>();
		tr->SetPosition(Vector3(npcPos.x + 0.3f, npcPos.y + 0.3f, npcPos.z));
	}

	if (think != nullptr) {
		Vector3 npcPos = GetComponent<Transform>()->GetPosition();
		Transform* tr = think->GetComponent<Transform>();
		tr->SetPosition(Vector3(npcPos.x + 0.3f, npcPos.y + 0.3f, npcPos.z));
	}

	AI* ai = GetComponent<AI>();
	MonDir monDir = ai->GetCurDir();
	MON_STATE monState = ai->GetCurStateName();

	Transform* monTr = this->GetComponent <Transform>();

	Animator* animator = GetComponent<Animator>();

	if (monDir != ai->GetPrevDir() || monState != ai->GetPrevStateName()) {
		switch (monState) {
		case MON_STATE::IDLE:
		{
			switch (monDir)
			{
			case MonDir::UP:
				animator->PlayAnimation(L"IDLE_UP", true);
				break;
			case MonDir::DOWN:
				animator->PlayAnimation(L"IDLE_DOWN", true);
				break;
			case MonDir::RIGHT:
				animator->PlayAnimation(L"IDLE_RIGHT", true);
				break;
			case MonDir::LEFT:
				animator->PlayAnimation(L"IDLE_LEFT", true);
				break;
			default:
				break;
			}
		}
		break;
		case MON_STATE::MOVE:
		{
			switch (monDir)
			{
			case MonDir::UP:
				animator->PlayAnimation(L"MOVE_UP", true);
				break;
			case MonDir::DOWN:
				animator->PlayAnimation(L"MOVE_DOWN", true);
				break;
			case MonDir::RIGHT:
				animator->PlayAnimation(L"MOVE_RIGHT", true);
				break;
			case MonDir::LEFT:
				animator->PlayAnimation(L"MOVE_LEFT", true);
				break;
			default:
				break;
			}
		}
		break;
		case MON_STATE::BUY:
		{
			switch (monDir)
			{
			case MonDir::UP:
				animator->PlayAnimation(L"GOLEM_MOVE_UP", true);
				break;
			case MonDir::DOWN:
				animator->PlayAnimation(L"GOLEM_MOVE_DOWN", true);
				break;
			case MonDir::RIGHT:
				animator->PlayAnimation(L"GOLEM_MOVE_RIGHT", true);
				break;
			case MonDir::LEFT:
				animator->PlayAnimation(L"GOLEM_MOVE_LEFT", true);
				break;
			default:
				break;
			}
		}
		break;
		default:
			break;
		}
	}

	Monster::Update();
}

void NPC::LateUpdate()
{
	Monster::LateUpdate();
}

void NPC::Render()
{
	Monster::Render();
}

void NPC::OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me)
{
}

void NPC::OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me)
{
}

void NPC::OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me)
{
}

void NPC::GetLootByShopScene()
{
	loot = ShopManager::GetLoot();
	if (loot.size() <= 5) {
		deadFlag = false;
	}
	else {
		deadFlag = true;
	}
}
