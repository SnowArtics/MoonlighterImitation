#include "GolemKingAimShoot.h"

#include "snTime.h"
#include "snSceneManager.h"

GolemKingAimShoot::GolemKingAimShoot()
	:State(MON_STATE::GOLEMKING_AIM_SHOOT)
	, endTime(6.f)
	, executionTime(0.f)
{
}

GolemKingAimShoot::~GolemKingAimShoot()
{
}

void GolemKingAimShoot::Update()
{
	executionTime += Time::DeltaTime();

	if (executionTime >= endTime) {
		executionTime = 0.f;
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_AIM_END);
	}
}

void GolemKingAimShoot::Enter()
{
}

void GolemKingAimShoot::Exit()
{
}
