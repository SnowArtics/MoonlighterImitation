#include "GolemKingDeath01.h"

#include "snTime.h"
#include "Monster.h"

using namespace sn;

GolemKingDeath01::GolemKingDeath01()
	:State(MON_STATE::GOLEMKING_DEATH01)
	, endTime(4.1f)
	, executionTime(0.f)
{
}

GolemKingDeath01::~GolemKingDeath01()
{
}

void GolemKingDeath01::Update()
{
	if (executionTime == 0.f) {
		Transform* ownerTr = GetAI()->GetOwner()->GetComponent<Transform>();
		Vector3 ownerPos = ownerTr->GetPosition();

		ownerPos.y += -0.2f;

		ownerTr->SetPosition(ownerPos);
	}

	executionTime += Time::DeltaTime();

	if (executionTime >= endTime) {
		//GetAI()->GetOwner()->SetState(sn::GameObject::eState::Dead);
		//executionTime = 0.f;
	}
}

void GolemKingDeath01::Enter()
{
}

void GolemKingDeath01::Exit()
{
}
