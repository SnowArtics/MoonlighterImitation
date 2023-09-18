#include "MiniBossIdle.h"
#include "Monster.h"
#include "snSceneManager.h"
#include "snDungeon.h"
#include "DungeonMapManager.h"

MiniBossIdle::MiniBossIdle()
	:State(MON_STATE::MINIBOSS_IDLE)
{
}

MiniBossIdle::~MiniBossIdle()
{
}

void MiniBossIdle::Update()
{
	std::pair<int, int> monMapPos = GetMonster()->GetMonsterMapPos();
	std::pair<int, int> playerMapPos = DungeonMapManager::GetInst()->GetPlayerMapPos();

	if (monMapPos != playerMapPos)
		return;

	SceneManager::ChangeMonsterState(GetAI(), MON_STATE::MINIBOSS_TRACE);
}

void MiniBossIdle::Enter()
{
}

void MiniBossIdle::Exit()
{
}
