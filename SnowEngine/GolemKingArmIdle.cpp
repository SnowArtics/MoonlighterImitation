#include "GolemKingArmIdle.h"

#include "snTime.h"
#include "snSceneManager.h"
#include "GolemKing.h"

GolemKingArmIdle::GolemKingArmIdle()
	:State(MON_STATE::GOLEMKING_ARM_IDLE)
	, endTime(15.0f)
	//, endTime(15.0f)
	, executionTime(0.f)
{
}

GolemKingArmIdle::~GolemKingArmIdle()
{
}

void GolemKingArmIdle::Update()
{
	if (executionTime == 0.f) {
		GolemKing* golemKing = static_cast<GolemKing*>(GetAI()->GetOwner());
		golemKing->CreateArm();
	}

	executionTime += Time::DeltaTime();

	if (executionTime >= endTime) {
		executionTime = 0.f;
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_ARM_RECOVER);
	}
}

void GolemKingArmIdle::Enter()
{
}

void GolemKingArmIdle::Exit()
{
}
