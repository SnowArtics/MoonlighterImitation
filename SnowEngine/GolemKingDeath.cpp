#include "GolemKingDeath.h"

#include "snTime.h"
#include "Monster.h"
#include "snTransform.h"
#include "snSceneManager.h"

using namespace sn;

GolemKingDeath::GolemKingDeath()
	:State(MON_STATE::GOLEMKING_DEATH)
	, endTime(4.1f)
	, executionTime(0.f)
{
}

GolemKingDeath::~GolemKingDeath()
{
}

void GolemKingDeath::Update()
{
	if (executionTime == 0.f) {
		Transform *ownerTr = GetAI()->GetOwner()->GetComponent<Transform>();
		Vector3 ownerPos = ownerTr->GetPosition();

		ownerPos.y += -0.5f;

		ownerTr->SetPosition(ownerPos);
	}

	executionTime += Time::DeltaTime();

	if (executionTime >= endTime) {
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_DEATH01);
		executionTime = 0.f;
	}
}

void GolemKingDeath::Enter()
{
}

void GolemKingDeath::Exit()
{
}
