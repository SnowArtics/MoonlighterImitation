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
	, enterFlag(false)
	, randomNum(0)
{
}

MiniBossAttack::~MiniBossAttack()
{
}

void MiniBossAttack::Update()
{
	if (enterFlag == false) {
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_int_distribution<> distribution(1, 2);

		randomNum = distribution(gen); // randomNums이 1일때 휘두르기 공격, 2일때 충격파 공격
		enterFlag = true;
	}

	time += Time::DeltaTime();

	MeshRenderer* meshRenderer = GetAI()->GetOwner()->GetComponent<MeshRenderer>();
	renderer::MonsterCB& monsterCB = meshRenderer->GetMonsterCB();
	
	if (randomNum == 1) {
		monsterCB.teleportState = 1;
		monsterCB.teleportDeltaTime = time;
	}
	else {
		monsterCB.teleportState = 0;
		monsterCB.teleportDeltaTime = time;
		int a = 0;
	}

	GolemCorruptedMiniBoss* miniBoss = static_cast<GolemCorruptedMiniBoss*>(GetAI()->GetOwner());
	miniBoss->SetRandomNum(randomNum);	

	tMonInfo monInfo = GetMonster()->GetMonsterInfo();

	float attTime = 0.f;

	if (randomNum == 1) {
		attTime = monInfo.fAttTime - 0.1f + 3.f;
	}
	else if (randomNum == 2) {
		attTime = monInfo.fAttTime - 0.1f;
	}	

	if (time >= attTime) {
		time = 0.f;
		monsterCB.teleportState = 0;
		monsterCB.teleportDeltaTime = time;
		enterFlag = false;
		randomNum = 0;
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::TRACE);
	}
}

void MiniBossAttack::Enter()
{
}

void MiniBossAttack::Exit()
{
}
