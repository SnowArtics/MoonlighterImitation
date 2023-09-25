#include "GolemKing.h"

#include "AI.h"
#include "snAnimator.h"

#include "snSceneManager.h"
#include "GolemKingRock.h"
#include "snTransform.h"
#include "Monster.h"
#include "snTime.h"
#include "MiniBossHPBar.h"

#include "snMeshRenderer.h"
#include "snCollider2D.h"
#include "snAnimator.h"
#include "snResources.h"
#include "snTexture.h"
#include <random>

GolemKing::GolemKing()
	:curTime(0.0f)
	, bossHPBarTrigger(true)
{
	//rockPoses.push_back(Vector3(0.4f, -1.0f, -1.0f));
	//rockPoses.push_back(Vector3(-0.1f, -0.5f, -1.0f));

	Vector3 monPos = Vector3(0.42f, 2.76f, 0.0f);
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 21; i++) {
			Vector3 rockPos;
			rockPos.x = monPos.x + (3.5f + j*1.25f) * cos(XMConvertToRadians(-i * 7.5f - 15.f));
			rockPos.y = monPos.y + (4.f+j*1.75f) * sin(XMConvertToRadians(-i * 7.5f - 15.f));
			rockPos.z = 0.0f;

			rockPoses.push_back(rockPos);
		}
	}
}

GolemKing::~GolemKing()
{
}

void GolemKing::Initialize()
{
	Monster::Initialize();
}

void GolemKing::Update()
{
	if (GetMonsterInfo().fHP <= 0.f) {
		GetComponent<AI>()->ChangeState(MON_STATE::GOLEMKING_DEATH);
	}

	curTime += Time::DeltaTime();
	if (curTime > 3.2f && bossHPBarTrigger) { // 3.2檬饶 UI 积己(BossUp Animation 场唱绊 UI 积己)
		GetComponent<MiniBossHPBar>()->CreateHpBar();
		bossHPBarTrigger = false;
	}

	AI* ai = GetComponent<AI>();
	MON_STATE monState = ai->GetCurStateName();

	Animator* animator = GetComponent<Animator>();

	if (monState != ai->GetPrevStateName()) {
		switch (monState)
		{
		case MON_STATE::GOLEMKING_UP:
		{
			animator->PlayAnimation(L"GOLEMKING_UP", false);
		}
		break;
		case MON_STATE::GOLEMKING_IDLE:
		{
			animator->PlayAnimation(L"GOLEMKING_IDLE", true);
		}
			break;
		case MON_STATE::GOLEMKING_ROCK_ATTACK:
		{
			animator->PlayAnimation(L"GOLEMKING_ROCK_ATTACK", false);
		}
		break;
		case MON_STATE::GOLEMKING_ARM_ATTACK:
		{
			animator->PlayAnimation(L"GOLEMKING_ARM_LAUNCH", false);
		}
		break;
		case MON_STATE::GOLEMKING_AIM_ATTACK:
		{
			animator->PlayAnimation(L"GOLEMKING_AIM_PREPARE", false);
		}
		break;
		case MON_STATE::DEAD:
			break;
		default:
			break;
		}


	}

	Monster::Update();
}

void GolemKing::LateUpdate()
{
	Monster::LateUpdate();
}

void GolemKing::Render()
{
	Monster::Render();
}

void GolemKing::CreateRocks()
{
	for (int i = 0; i < rockPoses.size(); i++) {
		GolemKingRock* golemKingRock = new GolemKingRock;
		Transform* tr = golemKingRock->GetComponent<Transform>();
		tr->SetScale(Vector3(0.7f, 0.7f, 0.0f));
		tr->SetPosition(rockPoses[i]);
		golemKingRock->SetDestinationPos(rockPoses[i]);
		//tr->SetPosition(Vector3(0.42f, -1.0f, -1.0f));
		//golemKingRock->SetDestinationPos(Vector3(0.42, -1.0f, -1.0f));

		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Obstacle, static_cast<GameObject*>(golemKingRock));
	}
}

void GolemKing::OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me)
{
	Monster::OnCollisionEnter(other, me);
	if (other->GetName() == L"SecondCollider") {
		tMonInfo monInfo = GetMonsterInfo();
		monInfo.fHP -= 30.f;
		this->GetComponent<MiniBossHPBar>()->PlayDamage(30.f);
		SetMonsterInfo(monInfo);
	}
}

void GolemKing::OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me)
{
}

void GolemKing::OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me)
{
}
