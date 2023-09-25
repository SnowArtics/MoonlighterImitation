#include "GolemKingRockAttack.h"

#include "snTime.h"
#include "snSceneManager.h"

#include "snGameObject.h"
#include "GolemKing.h"
#include "snCollider2D.h"

#include <random>

GolemKingRockAttack::GolemKingRockAttack()
	:State(MON_STATE::GOLEMKING_ROCK_ATTACK)
	, endTime(4.3f)
	, executionTime(0.f)
	, colliderTrigger(true)
{
}

GolemKingRockAttack::~GolemKingRockAttack()
{
}

void GolemKingRockAttack::Update()
{
	executionTime += Time::DeltaTime();

	if (executionTime > 1.7f && colliderTrigger)
	{
		GolemKing* golemKing = static_cast<GolemKing*>(GetAI()->GetOwner());
		golemKing->CreateRocks();
		(golemKing->GetComponents<sn::Collider2D>())[1]->SetEnable(true);

		colliderTrigger = false;
	}

	if (executionTime > 4.f && !colliderTrigger) {
		(static_cast<GolemKing*>(GetAI()->GetOwner())->GetComponents<sn::Collider2D>())[1]->SetEnable(false);
	}

	if (executionTime >= endTime) {
		executionTime = 0.f;
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_IDLE);
	}
}

void GolemKingRockAttack::Enter()
{
}

void GolemKingRockAttack::Exit()
{
}
