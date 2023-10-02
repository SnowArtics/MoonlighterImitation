#include "GolemKingAimCycle.h"

#include "snTime.h"
#include "snSceneManager.h"
#include "GolemKing.h"

GolemKingAimCycle::GolemKingAimCycle()
	:State(MON_STATE::GOLEMKING_AIM_CYCLE)
	, endTime(5.0f)
	, executionTime(0.f)
{
}

GolemKingAimCycle::~GolemKingAimCycle()
{
}

void GolemKingAimCycle::Update()
{
	if (executionTime == 0.0f) {
		GolemKing* golemKing = static_cast<GolemKing*>(GetAI()->GetOwner());
		golemKing->CreateFist();
	}

	executionTime += Time::DeltaTime();

	if (executionTime >= endTime) {
		executionTime = 0.f;
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_AIM_SHOOT);
	}
}

void GolemKingAimCycle::Enter()
{
}

void GolemKingAimCycle::Exit()
{
}
