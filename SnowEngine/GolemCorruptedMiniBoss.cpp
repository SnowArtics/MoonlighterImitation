#include "GolemCorruptedMiniBoss.h"
#include "AI.h"
#include "snAnimator.h"
#include "snSceneManager.h"
#include "DungeonMapManager.h"
#include "snTime.h"
#include "MiniBossHPBar.h"
#include "snPlayer.h"
#include "PlayerHP.h"
#include "snRigidBody.h"
#include "GolemSmashWave.h"
#include "snMeshRenderer.h"
#include "snResources.h"

#include <thread>
#include <random>

GolemCorruptedMiniBoss::GolemCorruptedMiniBoss()
	: firstColliderAttTime(-0.1f)
	, secondColliderAttTime(0.f)
	, waveCreateTime(0.f)
	, waveCreatePos(Vector3(0.0f, 0.0f, 0.f))
{
}

GolemCorruptedMiniBoss::~GolemCorruptedMiniBoss()
{
}

void GolemCorruptedMiniBoss::Initialize()
{
	Monster::Initialize();
}

void GolemCorruptedMiniBoss::Update()
{
	AI* ai = GetComponent<AI>();
	MonDir monDir = ai->GetCurDir();
	MON_STATE monState = ai->GetCurStateName();

	Transform* monTr = this->GetComponent <Transform>();
	sn::Collider2D* collider = this->GetComponent<sn::Collider2D>();
	sn::Collider2D* secondCollider = this->GetComponents<sn::Collider2D>()[1];
	sn::Collider2D* thirdCollider = this->GetComponents<sn::Collider2D>()[2];

	if (firstColliderAttTime >= 0.1f) {
		firstColliderAttTime += Time::DeltaTime();
	}		

	if (firstColliderAttTime > 0.1f) {
		secondCollider->SetEnable(true);
	}

	if (secondColliderAttTime >= 0.1f)
		secondColliderAttTime += Time::DeltaTime();

	if (secondColliderAttTime > 0.5f) {
		thirdCollider->SetEnable(false);
	}

	if (waveCreateTime >= 0.1f)
		waveCreateTime += Time::DeltaTime();

	if (waveCreateTime > 0.7f) {
		CreateWave(waveCreatePos);
		waveCreateTime = 0.f;
	}

	Animator* animator = GetComponent<Animator>();

	if (monDir != ai->GetPrevDir() || monState != ai->GetPrevStateName()) {
		switch (monState)
		{
		case MON_STATE::MINIBOSS_IDLE:
			break;
		case MON_STATE::MINIBOSS_TRACE:
		{
			if (firstColliderAttTime == -0.1f) {
				MiniBossHPBar* miniBossHPBar = GetComponent<MiniBossHPBar>();
				miniBossHPBar->CreateHpBar();
			}

			firstColliderAttTime = 0.f;
			secondColliderAttTime = 0.f;
			waveCreateTime = 0.f;
			secondCollider->SetEnable(false);
			thirdCollider->SetEnable(false);
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
		case MON_STATE::MINIBOSS_ATT:
		{			
				secondColliderAttTime = 0.f;
				waveCreateTime = 0.f;
				firstColliderAttTime = 0.f;
				thirdCollider->SetEnable(false);
				switch (monDir)
				{
				case MonDir::UP:
					animator->PlayAnimation(L"GOLEM_TELEPORT_ATTACK_PREV_UP", false);
					break;
				case MonDir::DOWN:
					animator->PlayAnimation(L"GOLEM_TELEPORT_ATTACK_PREV_DOWN", false);
					break;
				case MonDir::RIGHT:
					animator->PlayAnimation(L"GOLEM_TELEPORT_ATTACK_PREV_RIGHT", false);
					break;
				case MonDir::LEFT:
					animator->PlayAnimation(L"GOLEM_TELEPORT_ATTACK_PREV_LEFT", false);
					break;
				default:
					break;
				}
		}
			break;

		case MON_STATE::MINIBOSS_SMASH:
		{			
				firstColliderAttTime = 0.f;
				if (secondColliderAttTime == 0.f) {
					secondColliderAttTime = 0.1f;
				}
				if (waveCreateTime == 0.f) {
					waveCreateTime = 0.1f;
				}
				secondCollider->SetEnable(false);
				thirdCollider->SetEnable(true);
				Vector3 pos = this->GetComponent<Transform>()->GetPosition();
				//pos.x = pos.x * monsterMapPos.second;
				//pos.y = pos.y * monsterMapPos.first;
				switch (monDir)
				{
				case MonDir::UP:
					thirdCollider->SetSize(Vector2(0.6f, 0.4f));
					thirdCollider->SetCenter(Vector2(0.0f, 0.3f));
					waveCreatePos = Vector3(pos.x + 0.0f, pos.y + 0.3f, -1.0f);
					//CreateWave(Vector3(pos.x+0.0f,pos.y+0.3f,-1.0f));
					animator->PlayAnimation(L"GOLEM_SMASH_UP", true);
					break;
				case MonDir::DOWN:
					thirdCollider->SetSize(Vector2(0.6f, 0.4f));
					thirdCollider->SetCenter(Vector2(0.0f, -0.5f));
					waveCreatePos = Vector3(pos.x + 0.0f, pos.y - 0.5f, -1.0f);
					//CreateWave(Vector3(pos.x + 0.0f, pos.y - 0.5f, -1.0f));
					animator->PlayAnimation(L"GOLEM_SMASH_DOWN", true);
					break;
				case MonDir::RIGHT:
					thirdCollider->SetSize(Vector2(0.4f, 0.6f));
					thirdCollider->SetCenter(Vector2(+0.4f, -0.1f));
					waveCreatePos = Vector3(pos.x + 0.4f, pos.y - 0.1f, -1.0f);
					//CreateWave(Vector3(pos.x + 0.4f, pos.y - 0.1f, -1.0f));
					animator->PlayAnimation(L"GOLEM_SMASH_RIGHT", true);
					break;
				case MonDir::LEFT:
					thirdCollider->SetSize(Vector2(0.4f, 0.6f));
					thirdCollider->SetCenter(Vector2(-0.4f, -0.1f));
					waveCreatePos = Vector3(pos.x - 0.4f, pos.y - 0.1f, -1.0f);
					//CreateWave(Vector3(pos.x - 0.4f, pos.y - 0.1f, -1.0f));
					animator->PlayAnimation(L"GOLEM_SMASH_LEFT", true);
					break;
				default:
					break;
				}
			
		}
			break;
		case MON_STATE::MINIBOSS_TELEPORT_ATTACK:
		{
			secondColliderAttTime = 0.f;
			waveCreateTime = 0.f;
			if (firstColliderAttTime == 0.f) {
				firstColliderAttTime = 0.1f;
			}
			thirdCollider->SetEnable(false);
			switch (monDir)
			{
			case MonDir::UP:
				secondCollider->SetSize(Vector2(0.6f, 0.4f));
				secondCollider->SetCenter(Vector2(0.0f, 0.3f));
				animator->PlayAnimation(L"GOLEM_TELEPORT_ATTACK_UP", false);
				break;
			case MonDir::DOWN:
				secondCollider->SetSize(Vector2(0.6f, 0.4f));
				secondCollider->SetCenter(Vector2(0.0f, -0.5f));
				animator->PlayAnimation(L"GOLEM_TELEPORT_ATTACK_DOWN", false);
				break;
			case MonDir::RIGHT:
				secondCollider->SetSize(Vector2(0.4f, 0.6f));
				secondCollider->SetCenter(Vector2(+0.4f, -0.1f));
				animator->PlayAnimation(L"GOLEM_TELEPORT_ATTACK_RIGHT", false);
				break;
			case MonDir::LEFT:
				secondCollider->SetSize(Vector2(0.4f, 0.6f));
				secondCollider->SetCenter(Vector2(-0.4f, -0.1f));
				animator->PlayAnimation(L"GOLEM_TELEPORT_ATTACK_LEFT", false);
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

void GolemCorruptedMiniBoss::LateUpdate()
{
	Monster::LateUpdate();
}

void GolemCorruptedMiniBoss::Render()
{
	Monster::Render();
}

void GolemCorruptedMiniBoss::OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me)
{
	Monster::OnCollisionEnter(other, me);
	if (other->GetName() == L"SecondCollider") {
		tMonInfo monInfo = GetMonsterInfo();
		monInfo.fHP -= 30.f;
		this->GetComponent<MiniBossHPBar>()->PlayDamage(30.f);
		SetMonsterInfo(monInfo);

		std::vector<std::vector<RoomInfo>> vecRoomInfo = DungeonMapManager::GetInst()->GetRoomInfoArr();

		if (monInfo.fHP <= 0.f) {
			vecRoomInfo[monsterMapPos.first][monsterMapPos.second].monsterNum -= 1;

			if (vecRoomInfo[monsterMapPos.first][monsterMapPos.second].monsterNum <= 0) {
				vecRoomInfo[monsterMapPos.first][monsterMapPos.second].clear = true;
				DungeonMapManager::GetInst()->SetRoomInfoArr(vecRoomInfo);
				DungeonMapManager::GetInst()->SetDungeonClear(true);
			}
		}
	}
	if (other->GetName() == L"FisrtCollider" && me->GetName() == L"Mini_Boss_Second_Collider") {
		snPlayer* player = static_cast<snPlayer*>(other->GetOwner());
		float playerHP = player->GetHP();
		playerHP -= 30.f;
		player->SetHP(playerHP);
		PlayerHP* playerHPComponent = player->GetComponent<PlayerHP>();
		playerHPComponent->PlayDamage(30.f);
	}
	if (other->GetName() == L"FisrtCollider" && me->GetName() == L"Mini_Boss_Third_Collider") {
		snPlayer* player = static_cast<snPlayer*>(other->GetOwner());
		RigidBody* playerRigidBody = player->GetComponent<RigidBody>();
		Transform* playerTr = player->GetComponent<Transform>();
		Vector3 playerPos = playerTr->GetPosition();

		Transform* monTr = GetComponent<Transform>();
		Vector3 monPos = monTr->GetPosition();

		Vector3 dir = playerPos - monPos;
		dir.Normalize();
		float UnStiffness = player->GetUnStiffness();

		playerRigidBody->SetVelocity(dir * UnStiffness);
	}
}

void GolemCorruptedMiniBoss::OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me)
{
}

void GolemCorruptedMiniBoss::OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me)
{
}

void GolemCorruptedMiniBoss::CreateWave(Vector3 _transform)
{
	GolemSmashWave* wave = new GolemSmashWave;
	wave->SetName(L"GolemSmashWave");
	SceneManager::GetActiveScene()->AddGameObject(eLayerType::Projectile, static_cast<GameObject*>(wave));
	Transform* waveTr = wave->GetComponent<Transform>();
	Vector3 wavePos2 = waveTr->GetPosition();
	waveTr->SetPosition(_transform);
	waveTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

	MeshRenderer* meshRenderer = wave->AddComponent<MeshRenderer>();
	meshRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	meshRenderer->SetMaterial(Resources::Find<Material>(L"BossMonsterWave"));
}
