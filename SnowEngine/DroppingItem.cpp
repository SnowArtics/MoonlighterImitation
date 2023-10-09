#include "DroppingItem.h"

#include "snGameObject.h"
#include "Item.h"
#include "BrokenSword.h"
#include "CrystalEnergy.h"
#include "GolemKingCrystalEnergy.h"
#include "Fabric.h"
#include "GolemCore.h"
#include "GolemKingDesign.h"
#include "GolemPieces.h"
#include "ReinforcedSteel.h"
#include "SlimeJelly.h"
#include "snSceneManager.h"

#include <random>

DroppingItem::DroppingItem(std::vector<enums::eItemType> _eOwnItems)
	: eOwnItems(_eOwnItems)
{
	for (int i = 0; i < eOwnItems.size(); i++) {
		GameObject* pItem = nullptr;

		switch (eOwnItems[i])
		{
		case eItemType::Broken_Sword:
		{
			pItem = new BrokenSword();

			SceneManager::GetActiveScene()->AddGameObject(sn::eLayerType::Item, pItem);
			pItem->SetState(sn::GameObject::eState::Paused);
		}
		break;
		case eItemType::Crystal_Energy:
		{
			pItem = new CrystalEnergy();

			SceneManager::GetActiveScene()->AddGameObject(sn::eLayerType::Item, pItem);
			pItem->SetState(sn::GameObject::eState::Paused);
		}
		break;
		case eItemType::GolemKing_Crystal_Energy:
		{
			pItem = new GolemKingCrystalEnergy();

			SceneManager::GetActiveScene()->AddGameObject(sn::eLayerType::Item, pItem);
			pItem->SetState(sn::GameObject::eState::Paused);
		}
		break;
		case eItemType::Fabric:
		{
			pItem = new Fabric();

			SceneManager::GetActiveScene()->AddGameObject(sn::eLayerType::Item, pItem);
			pItem->SetState(sn::GameObject::eState::Paused);
		}
		break;
		case eItemType::Golem_Core:
		{
			pItem = new GolemCore();

			SceneManager::GetActiveScene()->AddGameObject(sn::eLayerType::Item, pItem);
			pItem->SetState(sn::GameObject::eState::Paused);
		}
		break;
		case eItemType::Golem_King_Design:
		{
			pItem = new GolemKingDesign();

			SceneManager::GetActiveScene()->AddGameObject(sn::eLayerType::Item, pItem);
			pItem->SetState(sn::GameObject::eState::Paused);
		}
		break;
		case eItemType::Golem_Pieces:
		{
			pItem = new GolemPieces();

			SceneManager::GetActiveScene()->AddGameObject(sn::eLayerType::Item, pItem);
			pItem->SetState(sn::GameObject::eState::Paused);
		}
		break;
		case eItemType::Reinforced_Steel:
		{
			pItem = new ReinforcedSteel();

			SceneManager::GetActiveScene()->AddGameObject(sn::eLayerType::Item, pItem);
			pItem->SetState(sn::GameObject::eState::Paused);
		}
		break;
		case eItemType::Slime_Jelly:
		{
			pItem = new SlimeJelly();

			SceneManager::GetActiveScene()->AddGameObject(sn::eLayerType::Item, pItem);
			pItem->SetState(sn::GameObject::eState::Paused);
		}
		break;
		default:
			break;
		}

		pOwnItems.push_back(static_cast<Item*>(pItem));
	}
}

DroppingItem::~DroppingItem()
{
}

void DroppingItem::Initialize()
{
	
}

void DroppingItem::Update()
{
	// 랜덤 엔진 초기화
	std::default_random_engine engine(std::random_device{}());

	// 실수 분포 정의: [0.0, 1.0] 범위
	std::uniform_real_distribution<float> distribution(-0.3, 0.3);

	if (GetOwner() != nullptr &&GetOwner()->GetState() == sn::GameObject::eState::Dead) {
		Vector3 ownPos = GetOwner()->GetComponent<Transform>()->GetPosition();

		for (int i = 0; i < pOwnItems.size(); i++) {
			float randomNumX = distribution(engine);
			float randomNumY = distribution(engine);

			pOwnItems[i]->GetComponent<Transform>()->SetPosition(Vector3(ownPos.x + randomNumX, ownPos.y + randomNumY, ownPos.z-1.f));
			pOwnItems[i]->SetState(sn::GameObject::eState::Active);
			pOwnItems[i]->SetStartTime(0.0f);
			pOwnItems[i]->SetStartPoint(ownPos);
			pOwnItems[i]->SetTargetPoint(Vector3(ownPos.x + randomNumX, ownPos.y + randomNumY, ownPos.z - 1.f));
			pOwnItems[i]->SetParabolaPeak(0.5f);
		}
	}
}

void DroppingItem::LateUpdate()
{
}

void DroppingItem::Render()
{
}
