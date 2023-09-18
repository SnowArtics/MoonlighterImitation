#include "MiniBossTeleportAttack.h"
#include "snTime.h"
#include "snSceneManager.h"
#include "Monster.h"
#include "snGameObject.h"
#include "snTransform.h"

MiniBossTeleportAttack::MiniBossTeleportAttack()
	: State(MON_STATE::MINIBOSS_TELEPORT_ATTACK)
	, time(0.f)
{
}

MiniBossTeleportAttack::~MiniBossTeleportAttack()
{
}

void MiniBossTeleportAttack::Update()
{
	time += Time::DeltaTime();	

	if (time >= 1.0f) {
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::MINIBOSS_TRACE);
		time = 0.f;
	}
}

void MiniBossTeleportAttack::Enter()
{
	Vector3 playerPos = SceneManager::GetActiveScene()->GetPlayer()->GetComponent<Transform>()->GetPosition();
	GetAI()->GetOwner()->GetComponent<Transform>()->SetPosition(playerPos);
}

void MiniBossTeleportAttack::Exit()
{
}
