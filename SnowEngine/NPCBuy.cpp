#include "NPCBuy.h"
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
#include "snAnimator.h"
#include "ShopManager.h"

using namespace sn;
using namespace std;

NPCBuy::NPCBuy()
	:State(MON_STATE::BUY)
	, time(0.0f)
	, thinkAnimTrigger(false)
{
}

NPCBuy::~NPCBuy()
{
}

void NPCBuy::Update()
{
	Monster* mon = GetMonster();
	NPC* npc = static_cast<NPC*>(mon);

	sn::GameObject* thinkBox = npc->GetThinkBox();
	sn::GameObject* think = npc->GetThink();

	thinkBox->SetEnable(true);
	think->SetEnable(true);

	time += Time::DeltaTime();

	if (time < 2.0f&&thinkAnimTrigger == false) {
		Animator* at = think->GetComponent<Animator>();
		at->PlayAnimation(L"think", true);
		thinkAnimTrigger = true;
	}
	if (time >= 2.0f && thinkAnimTrigger) {
		vector<Vector3> loot = npc->GetLoot();
		int appropriatePrice = 0;
		int realPrice = 0;
		if (loot[8].y < - 1.1f && loot[8].y > -1.3f) {
			appropriatePrice = ShopManager::SearchGoods(0);
			realPrice = ShopManager::GetLeftTopShelf().realPrice;
			pos = 0;
		}
		else if (loot[8].y < -2.4f && loot[8].y > -2.6f) {
			appropriatePrice = ShopManager::SearchGoods(1);
			realPrice = ShopManager::GetLeftBottomShelf().realPrice;
			pos = 1;
		}
		else if (loot[8].y < -2.1f && loot[8].y > -2.3f) {
			appropriatePrice = ShopManager::SearchGoods(2);
			realPrice = ShopManager::GetRightBottomShelf().realPrice;
			pos = 2;
		}
		else if (loot[8].y < -1.5f && loot[8].y > -1.7f) {
			appropriatePrice = ShopManager::SearchGoods(3);
			realPrice = ShopManager::GetRightTopShelf().realPrice;
			pos = 3;
		}

		npc->SetBuyGold(realPrice);

		if (realPrice < appropriatePrice - 30.f) {
			Animator* at = think->GetComponent<Animator>();
			at->PlayAnimation(L"TooCheap", false);
		}else if (realPrice > appropriatePrice + 30.f) {
			Animator* at = think->GetComponent<Animator>();
			at->PlayAnimation(L"TooExpensive", false);
		}
		else {
			Animator* at = think->GetComponent<Animator>();
			at->PlayAnimation(L"Cheap", false);
		}
		thinkAnimTrigger = false;
	}

	if (time >= 3.0f && thinkAnimTrigger == false) {
		thinkBox->SetEnable(false);
		think->SetEnable(false);
		ShopManager::BuyGoods(pos);
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::MOVE);
	}
}

void NPCBuy::Enter()
{
}

void NPCBuy::Exit()
{
}
