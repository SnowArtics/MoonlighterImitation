#include "GolemKingArmRecover.h"

#include "snTime.h"
#include "snSceneManager.h"

GolemKingArmRecover::GolemKingArmRecover()
	:State(MON_STATE::GOLEMKING_ARM_RECOVER)
	, endTime(1.1f)
	, executionTime(0.f)
{
}

GolemKingArmRecover::~GolemKingArmRecover()
{
}

void GolemKingArmRecover::Update()
{
	executionTime += Time::DeltaTime();

	if (executionTime >= endTime) {
		executionTime = 0.f;
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_IDLE);
	}
}

void GolemKingArmRecover::Enter()
{
}

void GolemKingArmRecover::Exit()
{
}
