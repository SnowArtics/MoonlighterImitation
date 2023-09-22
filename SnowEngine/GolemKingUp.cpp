#include "GolemKingUp.h"

#include "snTime.h"
#include "snSceneManager.h"

GolemKingUp::GolemKingUp()
	:State(MON_STATE::GOLEMKING_UP)
	, endTime(3.2f)
	, executionTime(0.f)
{
}

GolemKingUp::~GolemKingUp()
{	
}

void GolemKingUp::Update()
{
	executionTime += Time::DeltaTime();

	if (executionTime >= endTime) {
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_IDLE);
	}
}

void GolemKingUp::Enter()
{
}

void GolemKingUp::Exit()
{
}
