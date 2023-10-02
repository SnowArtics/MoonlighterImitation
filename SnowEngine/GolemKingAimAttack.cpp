#include "GolemKingAimAttack.h"

#include "snTime.h"
#include "snSceneManager.h"
#include <random>

GolemKingAimAttack::GolemKingAimAttack()
	:State(MON_STATE::GOLEMKING_AIM_PREPARE)
	, endTime(1.6f)
	, executionTime(0.f)
{
}

GolemKingAimAttack::~GolemKingAimAttack()
{
}

void GolemKingAimAttack::Update()
{
	executionTime += Time::DeltaTime();

	if (executionTime >= endTime) {
		executionTime = 0.f;
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_AIM_CYCLE);
	}
}

void GolemKingAimAttack::Enter()
{
}

void GolemKingAimAttack::Exit()
{
}
