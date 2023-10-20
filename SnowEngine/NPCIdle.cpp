#include "NPCIdle.h"
#include "Monster.h"
#include "NPC.h"
#include "snSceneManager.h"
#include "snDungeon.h"
#include "snGameObject.h"
#include "snTransform.h"
#include "snTime.h"
#include <snAudioSource.h>
#include "snResources.h"
#include "snTime.h"

NPCIdle::NPCIdle()
	:State(MON_STATE::IDLE)
	, time(0.0f)
{
}

NPCIdle::~NPCIdle()
{
}

void NPCIdle::Update()
{
	Monster* mon = GetMonster();
	NPC* npc = static_cast<NPC*>(mon);
	Transform* monTr = mon->GetComponent <Transform>();
	Vector3 monPos = monTr->GetPosition();

	if (npc->GetLootProgress() != 0) {
		time += Time::DeltaTime();
		if (time >= 3.0f) {
			SceneManager::ChangeMonsterState(GetAI(), MON_STATE::MOVE);
			time = 0.0f;
		}
	}

	if (npc->GetLootProgress() == 0) {
		npc->GetLootByShopScene();
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::MOVE);
	}
}

void NPCIdle::Enter()
{
}

void NPCIdle::Exit()
{
}
