#include "GolemKingRockAttack.h"

#include "snTime.h"
#include "snSceneManager.h"
#include <random>

GolemKingRockAttack::GolemKingRockAttack()
	:State(MON_STATE::GOLEMKING_ROCK_ATTACK)
	, endTime(4.3f)
	, executionTime(0.f)
{
}

GolemKingRockAttack::~GolemKingRockAttack()
{
}

void GolemKingRockAttack::Update()
{
	executionTime += Time::DeltaTime();

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
