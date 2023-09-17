#include "MiniBossAttack.h"
#include "Monster.h"
#include "snSceneManager.h"
#include "snDungeon.h"
#include "snGameObject.h"
#include "snTransform.h"
#include "snTime.h"
#include "snCollider2D.h"
#include "snGameObject.h"
#include "GolemCorruptedMiniBoss.h"
#include "snMeshRenderer.h"

#include <random>

MiniBossAttack::MiniBossAttack()
	: State(MON_STATE::ATT)
	, time(0.f)
{
}

MiniBossAttack::~MiniBossAttack()
{
}

void MiniBossAttack::Update()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> distribution(1, 2);

	int randomNum = distribution(gen); // randomNums이 1일때 휘두르기 공격, 2일때 충격파 공격

	GolemCorruptedMiniBoss* miniBoss = static_cast<GolemCorruptedMiniBoss*>(GetAI()->GetOwner());
	miniBoss->SetRandomNum(randomNum);

	time += Time::DeltaTime();

	MeshRenderer* meshRenderer = GetAI()->GetOwner()->GetComponent<MeshRenderer>();
	renderer::MonsterCB& monsterCB = meshRenderer->GetMonsterCB();
	monsterCB.teleportState = 1;
	monsterCB.teleportDeltaTime = time;

	sn::GameObject* player = SceneManager::GetActiveScene()->GetPlayer();
	Transform* playerTr = player->GetComponent<Transform>();
	Vector3 playerPos = playerTr->GetPosition();

	Monster* mon = GetMonster();
	Transform* monTr = mon->GetComponent <Transform>();
	Vector3 monPos = monTr->GetPosition();

	Vector3 moveDir = playerPos - monPos;

	tMonInfo monInfo = GetMonster()->GetMonsterInfo();

	if (time >= monInfo.fAttTime - 0.1f) {
		time = 0.f;
		monsterCB.teleportState = 0;
		monsterCB.teleportDeltaTime = time;
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::TRACE);
	}
}

void MiniBossAttack::Enter()
{
}

void MiniBossAttack::Exit()
{
}
