#include "GolemKingAimEnd.h"

#include "snTime.h"
#include "snSceneManager.h"

GolemKingAimEnd::GolemKingAimEnd()
	:State(MON_STATE::GOLEMKING_AIM_END)
	, endTime(3.2f)
	, executionTime(0.f)
{
}

GolemKingAimEnd::~GolemKingAimEnd()
{
}

void GolemKingAimEnd::Update()
{
	executionTime += Time::DeltaTime();

	if (executionTime >= endTime) {
		executionTime = 0.f;
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_IDLE);
	}
}

void GolemKingAimEnd::Enter()
{
}

void GolemKingAimEnd::Exit()
{
}
