#include "GolemKingArmAttack.h"

#include "snTime.h"
#include "snSceneManager.h"
#include <random>

GolemKingArmAttack::GolemKingArmAttack()
	:State(MON_STATE::GOLEMKING_ARM_LAUNCH)
	, endTime(2.0f)
	, executionTime(0.f)
{
}

GolemKingArmAttack::~GolemKingArmAttack()
{
}

void GolemKingArmAttack::Update()
{
	executionTime += Time::DeltaTime();

	if (executionTime >= endTime) {
		executionTime = 0.f;
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_ARM_IDLE);
	}
}

void GolemKingArmAttack::Enter()
{
}

void GolemKingArmAttack::Exit()
{
}
