#include "NPCMove.h"
#include "Monster.h"
#include "NPC.h"
#include "snSceneManager.h"
#include "snDungeon.h"
#include "snGameObject.h"
#include "snTransform.h"
#include "snTime.h"
#include <snAudioSource.h>
#include "snResources.h"
#include "snTextManager.h"
#include "InventoryManager.h"

using namespace sn;
using namespace std;

NPCMove::NPCMove()
	:State(MON_STATE::MOVE)
{
}

NPCMove::~NPCMove()
{
}

void NPCMove::Update()
{
	Monster* mon = GetMonster();
	NPC* npc = static_cast<NPC*>(mon);
	Transform* npcTr = npc->GetComponent <Transform>();
	Vector3 npcPos = npcTr->GetPosition();

	int lootProgress = npc->GetLootProgress();
	vector<Vector3> loot = npc->GetLoot();

	Vector3 direction = loot[lootProgress] - npcPos;

	direction.Normalize();

	npcPos += Time::DeltaTime() * direction * 2.0f;

	if (abs(loot[lootProgress].x - npcPos.x) < 0.1f && abs(loot[lootProgress].y - npcPos.y) < 0.1f) {
		lootProgress++;
		npc->SetLootProgress(lootProgress);
		if (lootProgress < 6)
		{
			SceneManager::ChangeMonsterState(GetAI(), MON_STATE::IDLE);
		}
		else if (lootProgress == loot.size() - 1 && loot.size()>9) {
			SceneManager::ChangeMonsterState(GetAI(), MON_STATE::IDLE);
			int buyGold = npc->GetBuyGold();
			int previousGold = std::stoi(TextManager::GetText((InventoryManager::GetMoneyTitle())));
			buyGold += previousGold;
			TextManager::ChangeText(InventoryManager::GetMoneyTitle(), std::to_wstring(buyGold));
		}
		else if (lootProgress == 9) {
			SceneManager::ChangeMonsterState(GetAI(), MON_STATE::BUY);
		}
	}

	bool upDown = true;
	if (abs(direction.x) > abs(direction.y)) {
		upDown = false;
	}
	else {
		upDown = true;
	}

	if (upDown) {
		if (direction.y < 0.f) {
			GetAI()->SetDir(MonDir::DOWN);
		}
		else {
			GetAI()->SetDir(MonDir::UP);
		}
	}
	else {
		if (direction.x < 0.f) {
			GetAI()->SetDir(MonDir::LEFT);
		}
		else {
			GetAI()->SetDir(MonDir::RIGHT);
		}
	}

	if (lootProgress >= loot.size() && lootProgress > 5) {
		npc->SetEnable(false);
		npc->SetState(sn::GameObject::eState::Dead);
	}
	else if(lootProgress >= loot.size() && lootProgress ==5){
		lootProgress = 0;
		npc->SetLootProgress(lootProgress);
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::IDLE);
	}

	npcTr->SetPosition(npcPos);
}

void NPCMove::Enter()
{
}

void NPCMove::Exit()
{
}
