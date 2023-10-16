#include "ShopManager.h"

#include "snSceneManager.h"
#include "snMeshRenderer.h"
#include "snTransform.h"
#include "snResources.h"
#include "snInput.h"
#include "snAnimator.h"
#include "snTextManager.h"
#include "InventoryManager.h"

using namespace sn;
using namespace std;

std::pair<int, int> ShopManager::curInvenSlotPos = std::make_pair<int, int>(0, 0);
std::vector<std::vector<InventoryItem>>  ShopManager::shop;

sn::GameObject* ShopManager::pInventoryLeft = nullptr;
sn::GameObject* ShopManager::pShopRight = nullptr;
sn::GameObject* ShopManager::pInventorySlot = nullptr;

sn::GameObject* ShopManager::pRightTopShelf = nullptr;
sn::GameObject* ShopManager::pLeftTopShelf = nullptr;
sn::GameObject* ShopManager::pLeftBottomShelf = nullptr;
sn::GameObject* ShopManager::pRightBottomShelf = nullptr;

int ShopManager::iShopInvenActive = 0;

void ShopManager::Initiailize()
{
	vector<InventoryItem> tempShop(7);

	for (int i = 0; i < 4; i++) {
		shop.push_back(tempShop);
	}
}

void ShopManager::Update()
{
}

void ShopManager::Render()
{
	if (Input::GetKeyDown(eKeyCode::J) && iShopInvenActive == 1)
	{
		pInventoryLeft->SetEnable(true);
		pShopRight->SetEnable(true);
		pInventorySlot->SetEnable(true);
		iShopInvenActive = 2;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 7; j++) {
				if(shop[i][j].slotItem !=nullptr)
					shop[i][j].slotItem->SetEnable(true);
				if (!shop[i][j].isEmpty)
					;
					//TextManager::SetEnable(shop[i][j].slotName, true);
			}
		}
	}
	else if (Input::GetKeyDown(eKeyCode::J) && iShopInvenActive ==2) {
		pInventoryLeft->SetEnable(false);
		pShopRight->SetEnable(false);
		pInventorySlot->SetEnable(false);
		iShopInvenActive = 1;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 7; j++) {
				if (shop[i][j].slotItem != nullptr)
					shop[i][j].slotItem->SetEnable(false);
				//TextManager::SetEnable(shop[i][j].slotName, false);
			}
		}
	}

	if (iShopInvenActive == 2) {
		if (Input::GetKeyDown(eKeyCode::W))
		{
			MoveSlot(SlotMoveDir::UP);
		}
		else if (Input::GetKeyDown(eKeyCode::S))
		{
			MoveSlot(SlotMoveDir::DOWN);
		}
		else if (Input::GetKeyDown(eKeyCode::A))
		{
			MoveSlot(SlotMoveDir::LEFT);
		}
		else if (Input::GetKeyDown(eKeyCode::D))
		{
			MoveSlot(SlotMoveDir::RIGHT);
		}
	}
}

void ShopManager::CreateShop()
{
	{
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 5; j++) {
				shop[i][j] = InventoryManager::inven[i][j];
			}
		}

		shop[0][5].pos = Vector3(1.06f, 1.4f, -3.f);
		shop[0][6].pos = Vector3(2.93f, 1.4f, -3.f);
		shop[1][5].pos = Vector3(1.06f, 0.67f, -3.f);
		shop[1][6].pos = Vector3(2.93f, 0.67f, -3.f);
		shop[2][5].pos = Vector3(1.06f, -0.35f, -3.f);
		shop[2][6].pos = Vector3(2.93f, -0.35f, -3.f);
		shop[3][5].pos = Vector3(1.06f, -1.08f, -3.f);
		shop[3][6].pos = Vector3(2.93f, -1.08f, -3.f);

		for (int i = 0; i < 4; i++) {
			
			for (int j = 5; j < 7; j++) {
				shop[i][j].itemCount = 0;
				shop[i][j].itemMaxCount = -1;
				shop[i][j].isEmpty = true;
				shop[i][j]._itemType = eItemType::Broken_Sword;

				if (i == 1 || i == 3) {
					shop[i][j].slotItem = nullptr;
					continue;
				}

				shop[i][j].slotItem = new sn::GameObject();
				shop[i][j].slotItem->GetComponent<Transform>()->SetPosition(shop[i][j].pos);
				shop[i][j].slotItem->SetName(L"SlotItem");
				shop[i][j].slotItem->SetEnable(false);

				MeshRenderer* mr = shop[i][j].slotItem->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

				Animator* at = shop[i][j].slotItem->AddComponent<Animator>();
				std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"transparent_space", L"..\\Resources\\Texture\\Item\\transparent_space.png");
				at->Create(L"Transparent", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 30.f), 1, 90.f);

				atlas = Resources::Load<Texture>(L"Broken_Sword", L"..\\Resources\\Texture\\Item\\Broken_Sword.png");
				at->Create(L"Broken_Sword", atlas, Vector2(0.0f, 0.0f), Vector2(10.f, 10.f), 1, 90.f);

				atlas = Resources::Load<Texture>(L"Crystal_Energy", L"..\\Resources\\Texture\\Item\\Crystal_Energy.png");
				at->Create(L"Crystal_Energy", atlas, Vector2(0.0f, 0.0f), Vector2(10.f, 17.f), 1, 90.f);

				atlas = Resources::Load<Texture>(L"Energy_Crystal", L"..\\Resources\\Texture\\Item\\Energy_Crystal.png");
				at->Create(L"GolemKing_Crystal_Energy", atlas, Vector2(0.0f, 0.0f), Vector2(19.f, 19.f), 1, 90.f);

				atlas = Resources::Load<Texture>(L"fabric", L"..\\Resources\\Texture\\Item\\fabric.png");
				at->Create(L"fabric", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 24.f), 1, 90.f);

				atlas = Resources::Load<Texture>(L"Golem_Core", L"..\\Resources\\Texture\\Item\\Golem_Core.png");
				at->Create(L"Golem_Core", atlas, Vector2(0.0f, 0.0f), Vector2(13.f, 13.f), 1, 90.f);

				atlas = Resources::Load<Texture>(L"Golem_King_design", L"..\\Resources\\Texture\\Item\\Golem_King_design.png");
				at->Create(L"Golem_King_design", atlas, Vector2(0.0f, 0.0f), Vector2(22.f, 23.f), 1, 90.f);

				atlas = Resources::Load<Texture>(L"golem_pieces", L"..\\Resources\\Texture\\Item\\golem_pieces.png");
				at->Create(L"golem_pieces", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 26.f), 1, 90.f);

				atlas = Resources::Load<Texture>(L"Reinforced_Steel_G", L"..\\Resources\\Texture\\Item\\Reinforced_Steel_G.png");
				at->Create(L"Reinforced_Steel_G", atlas, Vector2(0.0f, 0.0f), Vector2(15.f, 16.f), 1, 90.f);

				atlas = Resources::Load<Texture>(L"slime_jelly", L"..\\Resources\\Texture\\Item\\slime_jelly.png");
				at->Create(L"slime_jelly", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 21.f), 1, 90.f);

				at->PlayAnimation(L"Transparent", false);

				switch (shop[i][j]._itemType)
				{
				case sn::enums::eItemType::NONE:
					at->PlayAnimation(L"Transparent", false);
					break;
				case sn::enums::eItemType::Broken_Sword:
					at->PlayAnimation(L"Broken_Sword", false);
					break;
				case sn::enums::eItemType::Crystal_Energy:
					at->PlayAnimation(L"Crystal_Energy", false);
					break;
				case sn::enums::eItemType::GolemKing_Crystal_Energy:
					at->PlayAnimation(L"GolemKing_Crystal_Energy", false);
					break;
				case sn::enums::eItemType::Fabric:
					at->PlayAnimation(L"fabric", false);
					break;
				case sn::enums::eItemType::Golem_Core:
					at->PlayAnimation(L"Golem_Core", false);
					break;
				case sn::enums::eItemType::Golem_King_Design:
					at->PlayAnimation(L"Golem_King_design", false);
					break;
				case sn::enums::eItemType::Golem_Pieces:
					at->PlayAnimation(L"golem_pieces", false);
					break;
				case sn::enums::eItemType::Reinforced_Steel:
					at->PlayAnimation(L"Reinforced_Steel_G", false);
					break;
				case sn::enums::eItemType::Slime_Jelly:
					at->PlayAnimation(L"slime_jelly", false);
					break;
				case sn::enums::eItemType::END:
					at->PlayAnimation(L"Transparent", false);
					break;
				default:
					break;
				}

				//inven[i][j].slotItem->GetComponent<Transform>()->SetParent(pInventory->GetComponent<Transform>());

				SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, shop[i][j].slotItem);
			}
		}
	}
#pragma region shelfCreate
	{
		//right top
		pRightTopShelf = new GameObject();
		Transform* tr = pRightTopShelf->GetComponent<Transform>();
		tr->SetPosition(-0.85f, -1.6f, 0.0f);
		tr->SetScale(0.8f, 0.8f, 0.8f);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Obstacle, pRightTopShelf);

		MeshRenderer* mr = pRightTopShelf->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		Animator* at = pRightTopShelf->AddComponent<Animator>();
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"transparent_space", L"..\\Resources\\Texture\\Item\\transparent_space.png");
		at->Create(L"Transparent", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 30.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Broken_Sword", L"..\\Resources\\Texture\\Item\\Broken_Sword.png");
		at->Create(L"Broken_Sword", atlas, Vector2(0.0f, 0.0f), Vector2(10.f, 10.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Crystal_Energy", L"..\\Resources\\Texture\\Item\\Crystal_Energy.png");
		at->Create(L"Crystal_Energy", atlas, Vector2(0.0f, 0.0f), Vector2(10.f, 17.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Energy_Crystal", L"..\\Resources\\Texture\\Item\\Energy_Crystal.png");
		at->Create(L"GolemKing_Crystal_Energy", atlas, Vector2(0.0f, 0.0f), Vector2(19.f, 19.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"fabric", L"..\\Resources\\Texture\\Item\\fabric.png");
		at->Create(L"fabric", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 24.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Golem_Core", L"..\\Resources\\Texture\\Item\\Golem_Core.png");
		at->Create(L"Golem_Core", atlas, Vector2(0.0f, 0.0f), Vector2(13.f, 13.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Golem_King_design", L"..\\Resources\\Texture\\Item\\Golem_King_design.png");
		at->Create(L"Golem_King_design", atlas, Vector2(0.0f, 0.0f), Vector2(22.f, 23.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"golem_pieces", L"..\\Resources\\Texture\\Item\\golem_pieces.png");
		at->Create(L"golem_pieces", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 26.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Reinforced_Steel_G", L"..\\Resources\\Texture\\Item\\Reinforced_Steel_G.png");
		at->Create(L"Reinforced_Steel_G", atlas, Vector2(0.0f, 0.0f), Vector2(15.f, 16.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"slime_jelly", L"..\\Resources\\Texture\\Item\\slime_jelly.png");
		at->Create(L"slime_jelly", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 21.f), 1, 90.f);

		at->PlayAnimation(L"slime_jelly", false);
	}
	{	//left top
		GameObject* pLeftTopShelf = new GameObject();
		Transform* tr = pLeftTopShelf->GetComponent<Transform>();
		tr->SetPosition(-1.55f, -1.6f, 0.0f);
		tr->SetScale(0.8f, 0.8f, 0.8f);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Obstacle, pLeftTopShelf);

		MeshRenderer* mr = pLeftTopShelf->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		Animator* at = pLeftTopShelf->AddComponent<Animator>();
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"transparent_space", L"..\\Resources\\Texture\\Item\\transparent_space.png");
		at->Create(L"Transparent", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 30.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Broken_Sword", L"..\\Resources\\Texture\\Item\\Broken_Sword.png");
		at->Create(L"Broken_Sword", atlas, Vector2(0.0f, 0.0f), Vector2(10.f, 10.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Crystal_Energy", L"..\\Resources\\Texture\\Item\\Crystal_Energy.png");
		at->Create(L"Crystal_Energy", atlas, Vector2(0.0f, 0.0f), Vector2(10.f, 17.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Energy_Crystal", L"..\\Resources\\Texture\\Item\\Energy_Crystal.png");
		at->Create(L"GolemKing_Crystal_Energy", atlas, Vector2(0.0f, 0.0f), Vector2(19.f, 19.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"fabric", L"..\\Resources\\Texture\\Item\\fabric.png");
		at->Create(L"fabric", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 24.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Golem_Core", L"..\\Resources\\Texture\\Item\\Golem_Core.png");
		at->Create(L"Golem_Core", atlas, Vector2(0.0f, 0.0f), Vector2(13.f, 13.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Golem_King_design", L"..\\Resources\\Texture\\Item\\Golem_King_design.png");
		at->Create(L"Golem_King_design", atlas, Vector2(0.0f, 0.0f), Vector2(22.f, 23.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"golem_pieces", L"..\\Resources\\Texture\\Item\\golem_pieces.png");
		at->Create(L"golem_pieces", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 26.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Reinforced_Steel_G", L"..\\Resources\\Texture\\Item\\Reinforced_Steel_G.png");
		at->Create(L"Reinforced_Steel_G", atlas, Vector2(0.0f, 0.0f), Vector2(15.f, 16.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"slime_jelly", L"..\\Resources\\Texture\\Item\\slime_jelly.png");
		at->Create(L"slime_jelly", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 21.f), 1, 90.f);

		at->PlayAnimation(L"slime_jelly", false);
	}
	{	//left bottom
		GameObject* pLeftBottomShelf = new GameObject();
		Transform* tr = pLeftBottomShelf->GetComponent<Transform>();
		tr->SetPosition(-1.55f, -2.2f, 0.0f);
		tr->SetScale(0.8f, 0.8f, 0.8f);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Obstacle, pLeftBottomShelf);

		MeshRenderer* mr = pLeftBottomShelf->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		Animator* at = pLeftBottomShelf->AddComponent<Animator>();
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"transparent_space", L"..\\Resources\\Texture\\Item\\transparent_space.png");
		at->Create(L"Transparent", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 30.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Broken_Sword", L"..\\Resources\\Texture\\Item\\Broken_Sword.png");
		at->Create(L"Broken_Sword", atlas, Vector2(0.0f, 0.0f), Vector2(10.f, 10.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Crystal_Energy", L"..\\Resources\\Texture\\Item\\Crystal_Energy.png");
		at->Create(L"Crystal_Energy", atlas, Vector2(0.0f, 0.0f), Vector2(10.f, 17.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Energy_Crystal", L"..\\Resources\\Texture\\Item\\Energy_Crystal.png");
		at->Create(L"GolemKing_Crystal_Energy", atlas, Vector2(0.0f, 0.0f), Vector2(19.f, 19.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"fabric", L"..\\Resources\\Texture\\Item\\fabric.png");
		at->Create(L"fabric", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 24.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Golem_Core", L"..\\Resources\\Texture\\Item\\Golem_Core.png");
		at->Create(L"Golem_Core", atlas, Vector2(0.0f, 0.0f), Vector2(13.f, 13.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Golem_King_design", L"..\\Resources\\Texture\\Item\\Golem_King_design.png");
		at->Create(L"Golem_King_design", atlas, Vector2(0.0f, 0.0f), Vector2(22.f, 23.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"golem_pieces", L"..\\Resources\\Texture\\Item\\golem_pieces.png");
		at->Create(L"golem_pieces", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 26.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Reinforced_Steel_G", L"..\\Resources\\Texture\\Item\\Reinforced_Steel_G.png");
		at->Create(L"Reinforced_Steel_G", atlas, Vector2(0.0f, 0.0f), Vector2(15.f, 16.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"slime_jelly", L"..\\Resources\\Texture\\Item\\slime_jelly.png");
		at->Create(L"slime_jelly", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 21.f), 1, 90.f);

		at->PlayAnimation(L"slime_jelly", false);
	}
	{	//right bottom
		GameObject* pRightBottomShelf = new GameObject();
		Transform* tr = pRightBottomShelf->GetComponent<Transform>();
		tr->SetPosition(-0.85f, -2.2f, 0.0f);
		tr->SetScale(0.8f, 0.8f, 0.8f);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Obstacle, pRightBottomShelf);

		MeshRenderer* mr = pRightBottomShelf->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		Animator* at = pRightBottomShelf->AddComponent<Animator>();
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"transparent_space", L"..\\Resources\\Texture\\Item\\transparent_space.png");
		at->Create(L"Transparent", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 30.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Broken_Sword", L"..\\Resources\\Texture\\Item\\Broken_Sword.png");
		at->Create(L"Broken_Sword", atlas, Vector2(0.0f, 0.0f), Vector2(10.f, 10.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Crystal_Energy", L"..\\Resources\\Texture\\Item\\Crystal_Energy.png");
		at->Create(L"Crystal_Energy", atlas, Vector2(0.0f, 0.0f), Vector2(10.f, 17.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Energy_Crystal", L"..\\Resources\\Texture\\Item\\Energy_Crystal.png");
		at->Create(L"GolemKing_Crystal_Energy", atlas, Vector2(0.0f, 0.0f), Vector2(19.f, 19.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"fabric", L"..\\Resources\\Texture\\Item\\fabric.png");
		at->Create(L"fabric", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 24.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Golem_Core", L"..\\Resources\\Texture\\Item\\Golem_Core.png");
		at->Create(L"Golem_Core", atlas, Vector2(0.0f, 0.0f), Vector2(13.f, 13.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Golem_King_design", L"..\\Resources\\Texture\\Item\\Golem_King_design.png");
		at->Create(L"Golem_King_design", atlas, Vector2(0.0f, 0.0f), Vector2(22.f, 23.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"golem_pieces", L"..\\Resources\\Texture\\Item\\golem_pieces.png");
		at->Create(L"golem_pieces", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 26.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Reinforced_Steel_G", L"..\\Resources\\Texture\\Item\\Reinforced_Steel_G.png");
		at->Create(L"Reinforced_Steel_G", atlas, Vector2(0.0f, 0.0f), Vector2(15.f, 16.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"slime_jelly", L"..\\Resources\\Texture\\Item\\slime_jelly.png");
		at->Create(L"slime_jelly", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 21.f), 1, 90.f);

		at->PlayAnimation(L"slime_jelly", false);
	}
#pragma endregion

	{
		//왼쪽 인벤토리
		pInventoryLeft = new sn::GameObject();
		pInventoryLeft->SetName(L"ShopLeftBase01");
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, pInventoryLeft);
		MeshRenderer* mr = pInventoryLeft->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"UIInventoryLeftBaseMaterial01"));
		pInventoryLeft->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -2.0f));
		pInventoryLeft->GetComponent<Transform>()->SetScale(Vector3(7.576642335766424f, 4.f, 0.0f));
		pInventoryLeft->SetEnable(false);
		curInvenSlotPos.first = 0;
		curInvenSlotPos.second = 0;
	}
	{
		//오른쪽 샵
		pShopRight = new sn::GameObject();
		pShopRight->SetName(L"ShopRightBase01");
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, pShopRight);
		MeshRenderer* mr = pShopRight->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"UIShopRightBaseMaterial01"));
		pShopRight->GetComponent<Transform>()->SetPosition(Vector3(2.0f, 0.0f, -2.0f));
		pShopRight->GetComponent<Transform>()->SetScale(Vector3(3.722614840989399f, 3.5f, 0.0f));
		pShopRight->SetEnable(false);
		curInvenSlotPos.first = 0;
		curInvenSlotPos.second = 0;
	}
	{
		//인벤토리 Slot UI 생성
		pInventorySlot = new sn::GameObject();
		pInventorySlot->SetName(L"InventorySlot");
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, pInventorySlot);
		MeshRenderer* mr = pInventorySlot->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		Animator* at = pInventorySlot->AddComponent<Animator>();
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"invenSlot", L"..\\Resources\\Texture\\UI\\Inventory\\invenSlot.png");
		at->Create(L"invenSlot", atlas, Vector2(0.0f, 0.0f), Vector2(68.f, 68.f), 1,80.f);

		atlas = Resources::Load<Texture>(L"showcaseSlot", L"..\\Resources\\Texture\\UI\\Inventory\\showcaseSlot.png");
		at->Create(L"showcaseSlot", atlas, Vector2(0.0f, 0.0f), Vector2(258.f, 120.f), 1, 330.f);

		at->PlayAnimation(L"invenSlot", false);

		pInventorySlot->GetComponent<Transform>()->SetPosition(Vector3(-2.86f, 1.1f, -2.0f));
		pInventorySlot->GetComponent<Transform>()->SetScale(Vector3(2.f, 2.f, 2.0f));
		pInventorySlot->GetComponent<Transform>()->SetScale(Vector3(0.6f, 0.6f, 2.0f));
		pInventorySlot->SetEnable(false);
	}
}

void ShopManager::MoveSlot(SlotMoveDir _eSlotMoveDir)
{
	switch (_eSlotMoveDir)
	{
	case UP:
	{
		if (curInvenSlotPos.first != 0) {
			curInvenSlotPos.first -= 1;
		}
	}
	break;
	case DOWN:
	{
		if (curInvenSlotPos.first != 3) {
			curInvenSlotPos.first += 1;
		}
	}
	break;
	case LEFT:
	{
		if (curInvenSlotPos.second != 0) {
			curInvenSlotPos.second -= 1;
		}
	}
	break;
	case RIGHT:
	{
		if (curInvenSlotPos.second != 6) {
			curInvenSlotPos.second += 1;
		}
	}
	break;
	default:
		break;
	}

	Transform* tr = pInventorySlot->GetComponent<Transform>();
	tr->SetPosition(shop[curInvenSlotPos.first][curInvenSlotPos.second].pos);

	if (curInvenSlotPos.first == 1 || curInvenSlotPos.first == 3) {
		if (curInvenSlotPos.second == 5 || curInvenSlotPos.second == 6) {
			tr->SetScale(Vector3(2.0f, 2.0f, 0.0f));
			pInventorySlot->GetComponent<Animator>()->PlayAnimation(L"showcaseSlot", false);
		}
	}
	else {
		tr->SetScale(Vector3(.6f, .6f, 0.0f));
		pInventorySlot->GetComponent<Animator>()->PlayAnimation(L"invenSlot", false);
	}
}
