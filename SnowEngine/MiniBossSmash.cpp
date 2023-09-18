#include "MiniBossSmash.h"
#include "Monster.h"
#include "snSceneManager.h"
#include "snDungeon.h"
#include "snGameObject.h"
#include "snTransform.h"
#include "snTime.h"
#include "snCollider2D.h"
#include "snGameObject.h"

MiniBossSmash::MiniBossSmash()
	: State(MON_STATE::MINIBOSS_SMASH)
	, time(0.f)
{
}

MiniBossSmash::~MiniBossSmash()
{
}

void MiniBossSmash::Update()
{
	time += Time::DeltaTime();

	tMonInfo monInfo = GetMonster()->GetMonsterInfo();

	if (time >= monInfo.fAttTime - 0.1f) {
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::MINIBOSS_TRACE);
		time = 0.f;
	}
}

void MiniBossSmash::Enter()
{
}

void MiniBossSmash::Exit()
{
}
