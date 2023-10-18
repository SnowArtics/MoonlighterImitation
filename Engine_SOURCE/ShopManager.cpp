﻿#include "ShopManager.h"

#include "snSceneManager.h"
#include "snMeshRenderer.h"
#include "snTransform.h"
#include "snResources.h"
#include "snInput.h"
#include "snAnimator.h"
#include "snTextManager.h"
#include "InventoryManager.h"
#include "snTextManager.h"

using namespace sn;
using namespace std;

std::pair<int, int> ShopManager::curInvenSlotPos = std::make_pair<int, int>(0, 0);
std::vector<std::vector<InventoryItem>>  ShopManager::shop;
std::vector<std::vector<PriceSelect>>  ShopManager::price;

sn::GameObject* ShopManager::pInventoryLeft = nullptr;
sn::GameObject* ShopManager::pShopRight = nullptr;
sn::GameObject* ShopManager::pInventorySlot = nullptr;

ShelfItem ShopManager::pRightTopShelf;
ShelfItem ShopManager::pLeftTopShelf;
ShelfItem ShopManager::pLeftBottomShelf;
ShelfItem ShopManager::pRightBottomShelf;

int ShopManager::iShopInvenActive = 0;
bool ShopManager::bPriceSelectActive = false;

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
					TextManager::SetEnable(shop[i][j].slotName, true);
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
				TextManager::SetEnable(shop[i][j].slotName, false);
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
		else if (Input::GetKeyDown(eKeyCode::K)) {
			if (curInvenSlotPos.second < 5)
				SetShopShelf();
			else
				BackShopShelf();
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
				if(i%2!=1)
					shop[i][j].isEmpty = true;
				else
					shop[i][j].isEmpty = false;

				shop[i][j]._itemType = eItemType::NONE;

				wstring ItoS = to_wstring(i);
				wstring JtoS = to_wstring(j);
				shop[i][j].slotName = ItoS + JtoS + L"InvenSlot";

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
				at->Create(L"fabric", atlas, Vector2(0.0f, 0.0f), Vector2(20.f, 16.f), 1, 90.f);

				atlas = Resources::Load<Texture>(L"Golem_Core", L"..\\Resources\\Texture\\Item\\Golem_Core.png");
				at->Create(L"Golem_Core", atlas, Vector2(0.0f, 0.0f), Vector2(13.f, 13.f), 1, 90.f);

				atlas = Resources::Load<Texture>(L"Golem_King_design", L"..\\Resources\\Texture\\Item\\Golem_King_design.png");
				at->Create(L"Golem_King_design", atlas, Vector2(0.0f, 0.0f), Vector2(22.f, 23.f), 1, 90.f);

				atlas = Resources::Load<Texture>(L"golem_pieces", L"..\\Resources\\Texture\\Item\\golem_pieces.png");
				at->Create(L"golem_pieces", atlas, Vector2(0.0f, 0.0f), Vector2(20.f, 17.f), 1, 90.f);

				atlas = Resources::Load<Texture>(L"Reinforced_Steel_G", L"..\\Resources\\Texture\\Item\\Reinforced_Steel_G.png");
				at->Create(L"Reinforced_Steel_G", atlas, Vector2(0.0f, 0.0f), Vector2(15.f, 16.f), 1, 90.f);

				atlas = Resources::Load<Texture>(L"slime_jelly", L"..\\Resources\\Texture\\Item\\slime_jelly.png");
				at->Create(L"slime_jelly", atlas, Vector2(0.0f, 0.0f), Vector2(20.f, 14.f), 1, 90.f);

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
	{
		//텍스트 위치 생성
		std::vector < vector<Vector2>> texPos2D;
		std::vector<Vector2> texPos1D01;
		for (int i = 0; i < 4; i++) {			
			for (int j = 0; j < 2; j++) {
				if (i % 2 != 1)
					texPos1D01.push_back(Vector2(1200.f + j * 375.f, 275.f + i*175.f));
				else
					texPos1D01.push_back(Vector2(1030.f + j * 375.f, 255.f + i * 176.f));
			}
			texPos2D.push_back(texPos1D01);
			texPos1D01.clear();
			texPos1D01.shrink_to_fit();
		}

		//텍스트 생성
		for (int i = 0; i < 4; i++) {
			for (int j = 5; j < 7; j++) {
				if (i % 2 != 1) {
					Text text(L"0", texPos2D[i][j - 5].x, texPos2D[i][j - 5].y, 25, TextColor(255.f, 255.f, 255.f, 255.f), false);
					TextManager::InsertText(shop[i][j].slotName, text);
				}
				else {
					Text text(L"합계:", texPos2D[i][j - 5].x, texPos2D[i][j - 5].y, 30, TextColor(255.f, 255.f, 255.f, 255.f), false);
					TextManager::InsertText(shop[i][j].slotName, text);
				}				
			}
		}
	}
#pragma region shelfCreate
	{
		//right top
		pRightTopShelf.shelfItem = new GameObject();
		Transform* tr = pRightTopShelf.shelfItem->GetComponent<Transform>();
		tr->SetPosition(-0.9f, -1.65f, 0.0f);
		tr->SetScale(1.5f, 1.5f, 0.8f);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Obstacle, pRightTopShelf.shelfItem);

		MeshRenderer* mr = pRightTopShelf.shelfItem->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		Animator* at = pRightTopShelf.shelfItem->AddComponent<Animator>();
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"transparent_space", L"..\\Resources\\Texture\\Item\\transparent_space.png");
		at->Create(L"Transparent", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 30.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Broken_Sword", L"..\\Resources\\Texture\\Item\\Broken_Sword.png");
		at->Create(L"Broken_Sword", atlas, Vector2(0.0f, 0.0f), Vector2(10.f, 10.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Crystal_Energy", L"..\\Resources\\Texture\\Item\\Crystal_Energy.png");
		at->Create(L"Crystal_Energy", atlas, Vector2(0.0f, 0.0f), Vector2(10.f, 17.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Energy_Crystal", L"..\\Resources\\Texture\\Item\\Energy_Crystal.png");
		at->Create(L"GolemKing_Crystal_Energy", atlas, Vector2(0.0f, 0.0f), Vector2(19.f, 19.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"fabric", L"..\\Resources\\Texture\\Item\\fabric.png");
		at->Create(L"fabric", atlas, Vector2(0.0f, 0.0f), Vector2(20.f, 16.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Golem_Core", L"..\\Resources\\Texture\\Item\\Golem_Core.png");
		at->Create(L"Golem_Core", atlas, Vector2(0.0f, 0.0f), Vector2(13.f, 13.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Golem_King_design", L"..\\Resources\\Texture\\Item\\Golem_King_design.png");
		at->Create(L"Golem_King_design", atlas, Vector2(0.0f, 0.0f), Vector2(22.f, 23.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"golem_pieces", L"..\\Resources\\Texture\\Item\\golem_pieces.png");
		at->Create(L"golem_pieces", atlas, Vector2(0.0f, 0.0f), Vector2(20.f, 17.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Reinforced_Steel_G", L"..\\Resources\\Texture\\Item\\Reinforced_Steel_G.png");
		at->Create(L"Reinforced_Steel_G", atlas, Vector2(0.0f, 0.0f), Vector2(15.f, 16.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"slime_jelly", L"..\\Resources\\Texture\\Item\\slime_jelly.png");
		at->Create(L"slime_jelly", atlas, Vector2(0.0f, 0.0f), Vector2(20.f, 14.f), 1, 90.f);

		at->PlayAnimation(L"Transparent", false);
	}
	{	//left top
		pLeftTopShelf.shelfItem = new GameObject();
		Transform* tr = pLeftTopShelf.shelfItem->GetComponent<Transform>();
		tr->SetPosition(-1.5f, -1.65f, 0.0f);
		tr->SetScale(1.5f, 1.5f, 0.8f);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Obstacle, pLeftTopShelf.shelfItem);

		MeshRenderer* mr = pLeftTopShelf.shelfItem->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		Animator* at = pLeftTopShelf.shelfItem->AddComponent<Animator>();
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"transparent_space", L"..\\Resources\\Texture\\Item\\transparent_space.png");
		at->Create(L"Transparent", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 30.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Broken_Sword", L"..\\Resources\\Texture\\Item\\Broken_Sword.png");
		at->Create(L"Broken_Sword", atlas, Vector2(0.0f, 0.0f), Vector2(10.f, 10.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Crystal_Energy", L"..\\Resources\\Texture\\Item\\Crystal_Energy.png");
		at->Create(L"Crystal_Energy", atlas, Vector2(0.0f, 0.0f), Vector2(10.f, 17.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Energy_Crystal", L"..\\Resources\\Texture\\Item\\Energy_Crystal.png");
		at->Create(L"GolemKing_Crystal_Energy", atlas, Vector2(0.0f, 0.0f), Vector2(19.f, 19.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"fabric", L"..\\Resources\\Texture\\Item\\fabric.png");
		at->Create(L"fabric", atlas, Vector2(0.0f, 0.0f), Vector2(20.f, 16.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Golem_Core", L"..\\Resources\\Texture\\Item\\Golem_Core.png");
		at->Create(L"Golem_Core", atlas, Vector2(0.0f, 0.0f), Vector2(13.f, 13.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Golem_King_design", L"..\\Resources\\Texture\\Item\\Golem_King_design.png");
		at->Create(L"Golem_King_design", atlas, Vector2(0.0f, 0.0f), Vector2(22.f, 23.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"golem_pieces", L"..\\Resources\\Texture\\Item\\golem_pieces.png");
		at->Create(L"golem_pieces", atlas, Vector2(0.0f, 0.0f), Vector2(20.f, 17.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Reinforced_Steel_G", L"..\\Resources\\Texture\\Item\\Reinforced_Steel_G.png");
		at->Create(L"Reinforced_Steel_G", atlas, Vector2(0.0f, 0.0f), Vector2(15.f, 16.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"slime_jelly", L"..\\Resources\\Texture\\Item\\slime_jelly.png");
		at->Create(L"slime_jelly", atlas, Vector2(0.0f, 0.0f), Vector2(20.f, 14.f), 1, 90.f);

		at->PlayAnimation(L"Transparent", false);
	}
	{	//left bottom
		pLeftBottomShelf.shelfItem = new GameObject();
		Transform* tr = pLeftBottomShelf.shelfItem->GetComponent<Transform>();
		tr->SetPosition(-1.5f, -2.15f, 0.0f);
		tr->SetScale(1.5f, 1.5f, 0.8f);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Obstacle, pLeftBottomShelf.shelfItem);

		MeshRenderer* mr = pLeftBottomShelf.shelfItem->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		Animator* at = pLeftBottomShelf.shelfItem->AddComponent<Animator>();
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"transparent_space", L"..\\Resources\\Texture\\Item\\transparent_space.png");
		at->Create(L"Transparent", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 30.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Broken_Sword", L"..\\Resources\\Texture\\Item\\Broken_Sword.png");
		at->Create(L"Broken_Sword", atlas, Vector2(0.0f, 0.0f), Vector2(10.f, 10.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Crystal_Energy", L"..\\Resources\\Texture\\Item\\Crystal_Energy.png");
		at->Create(L"Crystal_Energy", atlas, Vector2(0.0f, 0.0f), Vector2(10.f, 17.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Energy_Crystal", L"..\\Resources\\Texture\\Item\\Energy_Crystal.png");
		at->Create(L"GolemKing_Crystal_Energy", atlas, Vector2(0.0f, 0.0f), Vector2(19.f, 19.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"fabric", L"..\\Resources\\Texture\\Item\\fabric.png");
		at->Create(L"fabric", atlas, Vector2(0.0f, 0.0f), Vector2(20.f, 16.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Golem_Core", L"..\\Resources\\Texture\\Item\\Golem_Core.png");
		at->Create(L"Golem_Core", atlas, Vector2(0.0f, 0.0f), Vector2(13.f, 13.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Golem_King_design", L"..\\Resources\\Texture\\Item\\Golem_King_design.png");
		at->Create(L"Golem_King_design", atlas, Vector2(0.0f, 0.0f), Vector2(22.f, 23.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"golem_pieces", L"..\\Resources\\Texture\\Item\\golem_pieces.png");
		at->Create(L"golem_pieces", atlas, Vector2(0.0f, 0.0f), Vector2(20.f, 17.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Reinforced_Steel_G", L"..\\Resources\\Texture\\Item\\Reinforced_Steel_G.png");
		at->Create(L"Reinforced_Steel_G", atlas, Vector2(0.0f, 0.0f), Vector2(15.f, 16.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"slime_jelly", L"..\\Resources\\Texture\\Item\\slime_jelly.png");
		at->Create(L"slime_jelly", atlas, Vector2(0.0f, 0.0f), Vector2(20.f, 14.f), 1, 90.f);

		at->PlayAnimation(L"Transparent", false);
	}
	{	//right bottom
		pRightBottomShelf.shelfItem = new GameObject();
		Transform* tr = pRightBottomShelf.shelfItem->GetComponent<Transform>();
		tr->SetPosition(-0.9f, -2.15f, 0.0f);
		tr->SetScale(1.5f, 1.5f, 0.8f);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Obstacle, pRightBottomShelf.shelfItem);

		MeshRenderer* mr = pRightBottomShelf.shelfItem->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		Animator* at = pRightBottomShelf.shelfItem->AddComponent<Animator>();
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"transparent_space", L"..\\Resources\\Texture\\Item\\transparent_space.png");
		at->Create(L"Transparent", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 30.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Broken_Sword", L"..\\Resources\\Texture\\Item\\Broken_Sword.png");
		at->Create(L"Broken_Sword", atlas, Vector2(0.0f, 0.0f), Vector2(10.f, 10.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Crystal_Energy", L"..\\Resources\\Texture\\Item\\Crystal_Energy.png");
		at->Create(L"Crystal_Energy", atlas, Vector2(0.0f, 0.0f), Vector2(10.f, 17.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Energy_Crystal", L"..\\Resources\\Texture\\Item\\Energy_Crystal.png");
		at->Create(L"GolemKing_Crystal_Energy", atlas, Vector2(0.0f, 0.0f), Vector2(19.f, 19.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"fabric", L"..\\Resources\\Texture\\Item\\fabric.png");
		at->Create(L"fabric", atlas, Vector2(0.0f, 0.0f), Vector2(20.f, 16.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Golem_Core", L"..\\Resources\\Texture\\Item\\Golem_Core.png");
		at->Create(L"Golem_Core", atlas, Vector2(0.0f, 0.0f), Vector2(13.f, 13.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Golem_King_design", L"..\\Resources\\Texture\\Item\\Golem_King_design.png");
		at->Create(L"Golem_King_design", atlas, Vector2(0.0f, 0.0f), Vector2(22.f, 23.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"golem_pieces", L"..\\Resources\\Texture\\Item\\golem_pieces.png");
		at->Create(L"golem_pieces", atlas, Vector2(0.0f, 0.0f), Vector2(20.f, 17.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"Reinforced_Steel_G", L"..\\Resources\\Texture\\Item\\Reinforced_Steel_G.png");
		at->Create(L"Reinforced_Steel_G", atlas, Vector2(0.0f, 0.0f), Vector2(15.f, 16.f), 1, 90.f);

		atlas = Resources::Load<Texture>(L"slime_jelly", L"..\\Resources\\Texture\\Item\\slime_jelly.png");
		at->Create(L"slime_jelly", atlas, Vector2(0.0f, 0.0f), Vector2(20.f, 14.f), 1, 90.f);

		at->PlayAnimation(L"Transparent", false);
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

	if ((curInvenSlotPos.first == 1 || curInvenSlotPos.first == 3)&&(curInvenSlotPos.second == 5 || curInvenSlotPos.second == 6)) {
		tr->SetScale(Vector3(2.0f, 2.0f, 0.0f));
		pInventorySlot->GetComponent<Animator>()->PlayAnimation(L"showcaseSlot", false);
	}
	else {
		tr->SetScale(Vector3(.6f, .6f, 0.0f));
		pInventorySlot->GetComponent<Animator>()->PlayAnimation(L"invenSlot", false);
	}
}

void ShopManager::SetShopShelf()
{
	if (shop[curInvenSlotPos.first][curInvenSlotPos.second].isEmpty == true)
		return;

	for (int i = 0; i < 4; i++) {
		for (int j = 5; j < 7; j++) {
			if (i % 2 != 1 && shop[i][j].isEmpty == true) {
				shop[i][j].isEmpty = false;
				shop[i][j].itemCount = shop[curInvenSlotPos.first][curInvenSlotPos.second].itemCount;
				shop[i][j].itemMaxCount = shop[curInvenSlotPos.first][curInvenSlotPos.second].itemMaxCount;
				shop[i][j]._itemType = shop[curInvenSlotPos.first][curInvenSlotPos.second]._itemType;
				TextManager::ChangeText(shop[i][j].slotName, NumToWString(shop[i][j].itemCount));
				TextManager::SetEnable(shop[i][j].slotName, true);

				std::wstring changeAnimationName;

				switch (shop[i][j]._itemType)
				{
				case sn::enums::eItemType::NONE:
					break;
				case sn::enums::eItemType::Broken_Sword:
					shop[i][j].slotItem->GetComponent<Animator>()->PlayAnimation(L"Broken_Sword", false);
					changeAnimationName = L"Broken_Sword";
					break;
				case sn::enums::eItemType::Crystal_Energy:
					shop[i][j].slotItem->GetComponent<Animator>()->PlayAnimation(L"Crystal_Energy", false);
					changeAnimationName = L"Crystal_Energy";
					break;
				case sn::enums::eItemType::GolemKing_Crystal_Energy:
					shop[i][j].slotItem->GetComponent<Animator>()->PlayAnimation(L"GolemKing_Crystal_Energy", false);
					changeAnimationName = L"GolemKing_Crystal_Energy";
					break;
				case sn::enums::eItemType::Fabric:
					shop[i][j].slotItem->GetComponent<Animator>()->PlayAnimation(L"fabric", false);
					changeAnimationName = L"fabric";
					break;
				case sn::enums::eItemType::Golem_Core:
					shop[i][j].slotItem->GetComponent<Animator>()->PlayAnimation(L"Golem_Core", false);
					changeAnimationName = L"Golem_Core";
					break;
				case sn::enums::eItemType::Golem_King_Design:
					shop[i][j].slotItem->GetComponent<Animator>()->PlayAnimation(L"Golem_King_design", false);
					changeAnimationName = L"Golem_King_design";
					break;
				case sn::enums::eItemType::Golem_Pieces:
					shop[i][j].slotItem->GetComponent<Animator>()->PlayAnimation(L"golem_pieces", false);
					changeAnimationName = L"golem_pieces";
					break;
				case sn::enums::eItemType::Reinforced_Steel:
					shop[i][j].slotItem->GetComponent<Animator>()->PlayAnimation(L"Reinforced_Steel_G", false);
					changeAnimationName = L"Reinforced_Steel_G";
					break;
				case sn::enums::eItemType::Slime_Jelly:
					shop[i][j].slotItem->GetComponent<Animator>()->PlayAnimation(L"slime_jelly", false);
					changeAnimationName = L"slime_jelly";
					break;
				case sn::enums::eItemType::END:
					break;
				default:
					break;
				}

				shop[curInvenSlotPos.first][curInvenSlotPos.second].isEmpty = true;
				shop[curInvenSlotPos.first][curInvenSlotPos.second].itemCount = 0;
				shop[curInvenSlotPos.first][curInvenSlotPos.second].itemMaxCount = -1;
				shop[curInvenSlotPos.first][curInvenSlotPos.second]._itemType = eItemType::NONE;
				shop[curInvenSlotPos.first][curInvenSlotPos.second].slotItem->GetComponent<Animator>()->PlayAnimation(L"Transparent", false);
				TextManager::ChangeText(shop[curInvenSlotPos.first][curInvenSlotPos.second].slotName, NumToWString(shop[curInvenSlotPos.first][curInvenSlotPos.second].itemCount));
				TextManager::SetEnable(shop[curInvenSlotPos.first][curInvenSlotPos.second].slotName, false);
			
				InventoryManager::inven[curInvenSlotPos.first][curInvenSlotPos.second] = shop[curInvenSlotPos.first][curInvenSlotPos.second];

				if (i == 0 && j == 5) {
					pLeftTopShelf.shelfItem->GetComponent<Animator>()->PlayAnimation(changeAnimationName, false);
				}
				else if (i == 0 && j == 6) {
					pRightTopShelf.shelfItem->GetComponent<Animator>()->PlayAnimation(changeAnimationName, false);
				}
				else if (i == 2 && j == 5) {
					pLeftBottomShelf.shelfItem->GetComponent<Animator>()->PlayAnimation(changeAnimationName, false);
				}
				else if (i == 2 && j == 6) {
					pRightBottomShelf.shelfItem->GetComponent<Animator>()->PlayAnimation(changeAnimationName, false);
				}

				return;
			}
		}
	}
	return;
}

void ShopManager::BackShopShelf() {
	if (curInvenSlotPos.first == 1 || curInvenSlotPos.first == 3)
		return;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			if (i % 2 != 1 && shop[i][j].isEmpty == true) {
				shop[i][j].isEmpty = false;
				shop[i][j].itemCount = shop[curInvenSlotPos.first][curInvenSlotPos.second].itemCount;
				shop[i][j].itemMaxCount = shop[curInvenSlotPos.first][curInvenSlotPos.second].itemMaxCount;
				shop[i][j]._itemType = shop[curInvenSlotPos.first][curInvenSlotPos.second]._itemType;
				TextManager::ChangeText(shop[i][j].slotName, NumToWString(shop[i][j].itemCount));
				TextManager::SetEnable(shop[i][j].slotName, true);

				switch (shop[i][j]._itemType)
				{
				case sn::enums::eItemType::NONE:
					break;
				case sn::enums::eItemType::Broken_Sword:
					shop[i][j].slotItem->GetComponent<Animator>()->PlayAnimation(L"Broken_Sword", false);
					break;
				case sn::enums::eItemType::Crystal_Energy:
					shop[i][j].slotItem->GetComponent<Animator>()->PlayAnimation(L"Crystal_Energy", false);
					break;
				case sn::enums::eItemType::GolemKing_Crystal_Energy:
					shop[i][j].slotItem->GetComponent<Animator>()->PlayAnimation(L"GolemKing_Crystal_Energy", false);
					break;
				case sn::enums::eItemType::Fabric:
					shop[i][j].slotItem->GetComponent<Animator>()->PlayAnimation(L"fabric", false);
					break;
				case sn::enums::eItemType::Golem_Core:
					shop[i][j].slotItem->GetComponent<Animator>()->PlayAnimation(L"Golem_Core", false);
					break;
				case sn::enums::eItemType::Golem_King_Design:
					shop[i][j].slotItem->GetComponent<Animator>()->PlayAnimation(L"Golem_King_design", false);
					break;
				case sn::enums::eItemType::Golem_Pieces:
					shop[i][j].slotItem->GetComponent<Animator>()->PlayAnimation(L"golem_pieces", false);
					break;
				case sn::enums::eItemType::Reinforced_Steel:
					shop[i][j].slotItem->GetComponent<Animator>()->PlayAnimation(L"Reinforced_Steel_G", false);
					break;
				case sn::enums::eItemType::Slime_Jelly:
					shop[i][j].slotItem->GetComponent<Animator>()->PlayAnimation(L"slime_jelly", false);
					break;
				case sn::enums::eItemType::END:
					break;
				default:
					break;
				}

				InventoryManager::inven[i][j] = shop[i][j];

				shop[curInvenSlotPos.first][curInvenSlotPos.second].isEmpty = true;
				shop[curInvenSlotPos.first][curInvenSlotPos.second].itemCount = 0;
				shop[curInvenSlotPos.first][curInvenSlotPos.second].itemMaxCount = -1;
				shop[curInvenSlotPos.first][curInvenSlotPos.second]._itemType = eItemType::NONE;
				shop[curInvenSlotPos.first][curInvenSlotPos.second].slotItem->GetComponent<Animator>()->PlayAnimation(L"Transparent", false);
				TextManager::ChangeText(shop[curInvenSlotPos.first][curInvenSlotPos.second].slotName, NumToWString(shop[curInvenSlotPos.first][curInvenSlotPos.second].itemCount));
				TextManager::SetEnable(shop[curInvenSlotPos.first][curInvenSlotPos.second].slotName, false);

				if (curInvenSlotPos.first == 0 && curInvenSlotPos.second == 5) {
					pLeftTopShelf.shelfItem->GetComponent<Animator>()->PlayAnimation(L"Transparent", false);
				}
				else if (curInvenSlotPos.first == 0 && curInvenSlotPos.second == 6) {
					pRightTopShelf.shelfItem->GetComponent<Animator>()->PlayAnimation(L"Transparent", false);
				}
				else if (curInvenSlotPos.first == 2 && curInvenSlotPos.second == 5) {
					pLeftBottomShelf.shelfItem->GetComponent<Animator>()->PlayAnimation(L"Transparent", false);
				}
				else if (curInvenSlotPos.first == 2 && curInvenSlotPos.second == 6) {
					pRightBottomShelf.shelfItem->GetComponent<Animator>()->PlayAnimation(L"Transparent", false);
				}

				return;
			}
		}
	}
	return;
}