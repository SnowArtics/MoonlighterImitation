#include "MiniBossAttack.h"
#include "Monster.h"
#include "snSceneManager.h"
#include "snDungeon.h"
#include "snGameObject.h"
#include "snTransform.h"
#include "snTime.h"
#include "snCollider2D.h"
#include "snGameObject.h"
#include "snMeshRenderer.h"
#include "snCollider2D.h"

MiniBossAttack::MiniBossAttack()
	: State(MON_STATE::MINIBOSS_ATT)
	, time(0.f)
{
}

MiniBossAttack::~MiniBossAttack()
{
}

void MiniBossAttack::Update()
{
	time += Time::DeltaTime();

	MeshRenderer* meshRenderer = GetAI()->GetOwner()->GetComponent<MeshRenderer>();
	renderer::MonsterCB& monsterCB = meshRenderer->GetMonsterCB();
	monsterCB.teleportState = 1;
	monsterCB.teleportDeltaTime = time;

	tMonInfo monInfo = GetMonster()->GetMonsterInfo();

	sn::Collider2D* col = GetAI()->GetOwner()->GetComponent<sn::Collider2D>();
	col->SetEnable(false);

	if (time >= monInfo.fAttTime - 0.1f + 3.f) {
		time = 0.f;
		monsterCB.teleportState = 0;
		monsterCB.teleportDeltaTime = time;
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::MINIBOSS_TELEPORT_ATTACK);
		col->SetEnable(true);
	}
}

void MiniBossAttack::Enter()
{
}

void MiniBossAttack::Exit()
{
}
