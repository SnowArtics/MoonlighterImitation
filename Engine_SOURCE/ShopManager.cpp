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
#include <string.h>
#include "snTime.h"

using namespace sn;
using namespace std;

std::pair<int, int> ShopManager::curInvenSlotPos = std::make_pair<int, int>(0, 0);
std::pair<int, int> ShopManager::curPriceSlotPos = std::make_pair<int, int>(0, 0);
std::vector<std::vector<InventoryItem>>  ShopManager::shop;
std::vector<std::vector<PriceSelect>>  ShopManager::price;
std::vector<std::vector<Vector3>>  ShopManager::loot;
std::vector<int>  ShopManager::priceList;

sn::GameObject* ShopManager::pInventoryLeft = nullptr;
sn::GameObject* ShopManager::pShopRight = nullptr;
sn::GameObject* ShopManager::pInventorySlot = nullptr;
sn::GameObject* ShopManager::pPriceSlot = nullptr;

ShelfItem ShopManager::pRightTopShelf;
ShelfItem ShopManager::pLeftTopShelf;
ShelfItem ShopManager::pLeftBottomShelf;
ShelfItem ShopManager::pRightBottomShelf;

int ShopManager::iShopInvenActive = 0;
bool ShopManager::bPriceSelectActive = false;
float ShopManager::time = 0;

void ShopManager::Initiailize()
{
	vector<InventoryItem> tempShop(7);

	for (int i = 0; i < 4; i++) {
		shop.push_back(tempShop);
	}

	vector<Vector3> loot1D;
	loot1D.push_back(Vector3(0.5f, -2.0f, 0.0f));
	loot1D.push_back(Vector3(0.5f, -2.5f, 0.0f));
	loot1D.push_back(Vector3(1.5f, -2.5f, 0.0f));
	loot1D.push_back(Vector3(1.5f, -2.0f, 0.0f));
	loot1D.push_back(Vector3(1.0f, -2.25f, 0.0f));
	loot1D.push_back(Vector3(0.f, -1.5f, 0.0f));
	loot1D.push_back(Vector3(0.f, -1.0f, 0.0f));
	loot1D.push_back(Vector3(-1.5f, -1.0f, 0.0f));
	loot1D.push_back(Vector3(-1.5f, -1.2f, 0.0f));//
	loot1D.push_back(Vector3(-1.5f, -1.0f, 0.0f));
	loot1D.push_back(Vector3(0.f, -1.0f, 0.0f));
	loot1D.push_back(Vector3(0.f, -1.8f, 0.0f));
	loot1D.push_back(Vector3(1.f, -1.6f, 0.0f));
	loot1D.push_back(Vector3(0.7f, -4.0f, 0.0f));

	loot.push_back(loot1D);
	loot1D.clear();
	loot1D.shrink_to_fit();

	loot1D.push_back(Vector3(1.5f, -2.5f, 0.0f));
	loot1D.push_back(Vector3(0.5f, -2.0f, 0.0f));
	loot1D.push_back(Vector3(1.0f, -2.25f, 0.0f));
	loot1D.push_back(Vector3(1.5f, -2.0f, 0.0f));
	loot1D.push_back(Vector3(0.5f, -2.5f, 0.0f));
	loot1D.push_back(Vector3(0.5f, -2.5f, 0.0f));
	loot1D.push_back(Vector3(0.f, -2.7f, 0.0f));
	loot1D.push_back(Vector3(-1.5f, -2.7f, 0.0f));
	loot1D.push_back(Vector3(-1.5f, -2.5f, 0.0f));//
	loot1D.push_back(Vector3(-1.5f, -2.7f, 0.0f));
	loot1D.push_back(Vector3(0.f, -2.7f, 0.0f));
	loot1D.push_back(Vector3(0.5f, -2.5f, 0.0f));
	loot1D.push_back(Vector3(1.f, -1.6f, 0.0f));
	loot1D.push_back(Vector3(0.7f, -4.0f, 0.0f));

	loot.push_back(loot1D);
	loot1D.clear();
	loot1D.shrink_to_fit();

	loot1D.push_back(Vector3(1.0f, -2.25f, 0.0f));
	loot1D.push_back(Vector3(0.5f, -2.0f, 0.0f));
	loot1D.push_back(Vector3(0.5f, -2.0f, 0.0f));
	loot1D.push_back(Vector3(0.5f, -2.5f, 0.0f));
	loot1D.push_back(Vector3(0.5f, -2.5f, 0.0f));
	loot1D.push_back(Vector3(1.5f, -2.5f, 0.0f));
	loot1D.push_back(Vector3(1.5f, -2.5f, 0.0f));
	loot1D.push_back(Vector3(1.5f, -2.0f, 0.0f));
	loot1D.push_back(Vector3(-0.5f, -2.2f, 0.0f));//
	loot1D.push_back(Vector3(1.5f, -2.0f, 0.0f));
	loot1D.push_back(Vector3(1.5f, -2.5f, 0.0f));
	loot1D.push_back(Vector3(1.f, -1.6f, 0.0f));
	loot1D.push_back(Vector3(0.7f, -4.0f, 0.0f));

	loot.push_back(loot1D);
	loot1D.clear();
	loot1D.shrink_to_fit();

	loot1D.push_back(Vector3(1.5f, -2.0f, 0.0f));
	loot1D.push_back(Vector3(0.5f, -2.0f, 0.0f));
	loot1D.push_back(Vector3(1.0f, -2.25f, 0.0f));
	loot1D.push_back(Vector3(1.0f, -2.25f, 0.0f));
	loot1D.push_back(Vector3(1.5f, -2.5f, 0.0f));
	loot1D.push_back(Vector3(1.5f, -2.5f, 0.0f));
	loot1D.push_back(Vector3(1.5f, -2.5f, 0.0f));
	loot1D.push_back(Vector3(0.5f, -2.5f, 0.0f));
	loot1D.push_back(Vector3(-0.5f, -1.6f, 0.0f));//
	loot1D.push_back(Vector3(0.5f, -2.5f, 0.0f));
	loot1D.push_back(Vector3(1.f, -1.6f, 0.0f));
	loot1D.push_back(Vector3(0.7f, -4.0f, 0.0f));

	loot.push_back(loot1D);
	loot1D.clear();
	loot1D.shrink_to_fit();

	loot1D.push_back(Vector3(0.5f, -2.0f, 0.0f));
	loot1D.push_back(Vector3(0.5f, -2.5f, 0.0f));
	loot1D.push_back(Vector3(1.0f, -2.25f, 0.0f));
	loot1D.push_back(Vector3(1.5f, -2.5f, 0.0f));
	loot1D.push_back(Vector3(1.5f, -2.0f, 0.0f));

	loot.push_back(loot1D);
	loot1D.clear();
	loot1D.shrink_to_fit();


	priceList.push_back(0);
	priceList.push_back(180);
	priceList.push_back(125);
	priceList.push_back(3125);
	priceList.push_back(312);
	priceList.push_back(125);
	priceList.push_back(1875);
	priceList.push_back(187);
	priceList.push_back(375);
	priceList.push_back(100);
	priceList.push_back(0);
}

void ShopManager::Update()
{
}

void ShopManager::Render()
{
	if (iShopInvenActive == 2&& bPriceSelectActive == false) {
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
		else if (Input::GetKeyDown(eKeyCode::J))
		{
			if ((curInvenSlotPos.first == 1 || curInvenSlotPos.first == 3) && (curInvenSlotPos.second == 5 || curInvenSlotPos.second == 6)&&(shop[curInvenSlotPos.first-1][curInvenSlotPos.second].isEmpty==false)) {
				bPriceSelectActive = true;
				pInventorySlot->SetEnable(false);
				pPriceSlot->SetEnable(true);

				if (curInvenSlotPos.first == 1) {
					if (curInvenSlotPos.second == 5) {
						pPriceSlot->GetComponent<Transform>()->SetPosition(price[0][3].pos);
						curPriceSlotPos.first = 0;
						curPriceSlotPos.second = 3;
					}
					else {
						pPriceSlot->GetComponent<Transform>()->SetPosition(price[0][7].pos);
						curPriceSlotPos.first = 0;
						curPriceSlotPos.second = 7;
					}
				}
				else {
					if (curInvenSlotPos.second == 5) {
						pPriceSlot->GetComponent<Transform>()->SetPosition(price[2][3].pos);
						curPriceSlotPos.first = 2;
						curPriceSlotPos.second = 3;
					}
					else {
						pPriceSlot->GetComponent<Transform>()->SetPosition(price[2][7].pos);
						curPriceSlotPos.first = 2;
						curPriceSlotPos.second = 7;
					}
				}
				return;
			}
		}
	}

	if (bPriceSelectActive == true) {
		if (Input::GetKeyDown(eKeyCode::W))
		{
			MovePriceSlot(SlotMoveDir::UP);
		}
		else if (Input::GetKeyDown(eKeyCode::S))
		{
			MovePriceSlot(SlotMoveDir::DOWN);
		}
		else if (Input::GetKeyDown(eKeyCode::A))
		{
			MovePriceSlot(SlotMoveDir::LEFT);
		}
		else if (Input::GetKeyDown(eKeyCode::D))
		{
			MovePriceSlot(SlotMoveDir::RIGHT);
		}
		else if (Input::GetKeyDown(eKeyCode::J))
		{
			bPriceSelectActive = false;
			pInventorySlot->SetEnable(true);
			pPriceSlot->SetEnable(false);
			return;
		}
	}

	if (Input::GetKeyDown(eKeyCode::J) && iShopInvenActive == 1)
	{
		pInventoryLeft->SetEnable(true);
		pShopRight->SetEnable(true);
		pInventorySlot->SetEnable(true);
		iShopInvenActive = 2;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 7; j++) {
				if (shop[i][j].slotItem != nullptr)
					shop[i][j].slotItem->SetEnable(true);
				if (!shop[i][j].isEmpty)
					TextManager::SetEnable(shop[i][j].slotName, true);
			}
		}

		for (int i = 0; i < price.size(); i++) {
			for (int j = 0; j < price[i].size(); j++) {
				TextManager::SetEnable(price[i][j].textTitle,true);
			}
		}
	}
	else if (Input::GetKeyDown(eKeyCode::J) && iShopInvenActive == 2) {
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

		for (int i = 0; i < price.size(); i++) {
			for (int j = 0; j < price[i].size(); j++) {
				TextManager::SetEnable(price[i][j].textTitle, false);
			}
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

		//가격 위치 생성
	{
		for (int i = 0; i < 4; i++) {
			vector<PriceSelect> priceSelect1D;
			if (i == 0 || i == 2) {
				for (int j = 0; j < 8; j++) {
					if (j < 4) {
						PriceSelect mPriceSelect;
						wstring ItoS = to_wstring(i);
						wstring JtoS = to_wstring(j);
						mPriceSelect.textTitle = ItoS + JtoS + L"PriceSlot";
						mPriceSelect.texPos = Vector3(1144.f + j * 15.f, 360.f + i * 175.f, -2.0f);
						//mPriceSelect.texPos = Vector3(1144.f + j * 15.f, 340.f + i * 175.f, -2.0f);
						mPriceSelect.pos = Vector3(0.96f+j*0.08f, 0.82f + i*-0.875f, -2.0f);

						priceSelect1D.push_back(mPriceSelect);
					}
					else {
						PriceSelect mPriceSelect;
						wstring ItoS = to_wstring(i);
						wstring JtoS = to_wstring(j);
						mPriceSelect.textTitle = ItoS + JtoS + L"PriceSlot";
						mPriceSelect.texPos = Vector3(1457.f + j * 15.f, 360.f + i * 175.f, -2.0f);
						//mPriceSelect.texPos = Vector3(1457.f + j * 15.f, 340.f + i * 175.f, -2.0f);
						mPriceSelect.pos = Vector3(2.82f + (j-4)*0.08f, 0.82f + i * -0.875f, -2.0f);

						priceSelect1D.push_back(mPriceSelect);
					}					
				}
			}
			else {
				for (int j = 0; j < 2; j++) {
					PriceSelect mPriceSelect;
					wstring ItoS = to_wstring(i);
					wstring JtoS = to_wstring(j);
					mPriceSelect.textTitle = ItoS + JtoS + L"PriceSlot";
					mPriceSelect.texPos = Vector3(1150.f +j* 375.f, 262.f+i*175.f, -2.0f);
					mPriceSelect.pos = Vector3(1.0f, 1.0f, -2.0f);

					priceSelect1D.push_back(mPriceSelect);
				}
			}

			price.push_back(priceSelect1D);
		}

		for(int i=0;i<price.size();i++){
			for (int j = 0; j < price[i].size(); j++) {
				if (i == 0 || i == 2) {
						Text text(L"0", price[i][j].texPos.x, price[i][j].texPos.y, 28, TextColor(0.f, 0.f, 0.f, 200.f), false);
						TextManager::InsertText(price[i][j].textTitle, text);
				}
				else {
						Text text(L"0", price[i][j].texPos.x, price[i][j].texPos.y, 30, TextColor(0.f, 0.f, 0.f, 200.f), false);
						TextManager::InsertText(price[i][j].textTitle, text);
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

	{
		//인벤토리 Price Slot UI 생성
		pPriceSlot = new sn::GameObject();
		pPriceSlot->SetName(L"InventoryPriceSlot");
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, pPriceSlot);
		MeshRenderer* mr = pPriceSlot->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"InvenSlotMeterial03"));
		pPriceSlot->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -2.0f));
		pPriceSlot->GetComponent<Transform>()->SetScale(Vector3(0.35f, 1.f, 0.0f));
		pPriceSlot->GetComponent<Transform>()->SetScale(Vector3(0.105f, 0.3f, 0.0f));
		pPriceSlot->SetEnable(false);
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

void ShopManager::MovePriceSlot(SlotMoveDir _eSlotMoveDir)
{
	int leftMoveLimit = 0;
	int rightMoveLimit = 0;

	pair<int, int> resultPos;
	int itemCount = 0;

	int shelfItemPos = 0;

	if (curPriceSlotPos.second < 4) {
		leftMoveLimit = 0;
		rightMoveLimit = 3;
		if (curPriceSlotPos.first == 0) {
			resultPos.first = curPriceSlotPos.first+1;
			resultPos.second = 0;
			itemCount = shop[0][5].itemCount;
			shelfItemPos = 0;
		}
		else {
			resultPos.first = curPriceSlotPos.first+1;
			resultPos.second = 0;
			itemCount = shop[2][5].itemCount;
			shelfItemPos = 1;
		}
	}
	else {
		leftMoveLimit = 4;
		rightMoveLimit = 7;
		if (curPriceSlotPos.first == 0) {
			resultPos.first = curPriceSlotPos.first+1;
			resultPos.second = 1;
			itemCount = shop[0][6].itemCount;
			shelfItemPos = 3;
		}
		else {
			resultPos.first = curPriceSlotPos.first+1;
			resultPos.second = 1;
			itemCount = shop[2][6].itemCount;
			shelfItemPos = 2;
		}
	}

	switch (_eSlotMoveDir)
	{
	case UP:
	{
		wstring stringNum = TextManager::GetText(price[curPriceSlotPos.first][curPriceSlotPos.second].textTitle);
		int num = stoi(stringNum);
		if (num == 9)
			num = 0;
		else
			num++;
		TextManager::ChangeText(price[curPriceSlotPos.first][curPriceSlotPos.second].textTitle, NumToWString(num));

		int resultNum = 0;
		for (int i = 0; i < 4; i++) {
			wstring stringNum01 = TextManager::GetText(price[curPriceSlotPos.first][leftMoveLimit+i].textTitle);
			resultNum += stoi(stringNum01) * (pow(10, 3- i));
		}
		resultNum *= itemCount;
		switch (shelfItemPos) {
		case 0:
			pLeftTopShelf.price = resultNum;
			break;
		case 1:
			pLeftBottomShelf.price = resultNum;
			break;
		case 2:
			pRightBottomShelf.price = resultNum;
			break;
		case 3:
			pRightTopShelf.price = resultNum;
			break;
		}
		TextManager::ChangeText(price[resultPos.first][resultPos.second].textTitle, NumToWString(resultNum));
	}
	break;
	case DOWN:
	{
		wstring stringNum = TextManager::GetText(price[curPriceSlotPos.first][curPriceSlotPos.second].textTitle);
		int num = stoi(stringNum);
		if (num == 0)
			num = 9;
		else
			num--;
		TextManager::ChangeText(price[curPriceSlotPos.first][curPriceSlotPos.second].textTitle, NumToWString(num));

		int resultNum = 0;
		for (int i = 0; i < 4; i++) {
			wstring stringNum01 = TextManager::GetText(price[curPriceSlotPos.first][leftMoveLimit + i].textTitle);
			resultNum += stoi(stringNum01) * (pow(10,3-i));
		}
		resultNum *= itemCount;
		switch (shelfItemPos) {
		case 0:
			pLeftTopShelf.price = resultNum;
			break;
		case 1:
			pLeftBottomShelf.price = resultNum;
			break;
		case 2:
			pRightBottomShelf.price = resultNum;
			break;
		case 3:
			pRightTopShelf.price = resultNum;
			break;
		}
		TextManager::ChangeText(price[resultPos.first][resultPos.second].textTitle, NumToWString(resultNum));
	}
	break;
	case LEFT:
	{
		if (curPriceSlotPos.second != leftMoveLimit) {
			curPriceSlotPos.second -= 1;
		}
	}
	break;
	case RIGHT:
	{
		if (curPriceSlotPos.second != rightMoveLimit) {
			curPriceSlotPos.second += 1;
		}
	}
	break;
	default:
		break;
	}

	Transform* tr = pPriceSlot->GetComponent<Transform>();
	tr->SetPosition(price[curPriceSlotPos.first][curPriceSlotPos.second].pos);
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
					pLeftTopShelf._itemType = shop[i][j]._itemType;
				}
				else if (i == 0 && j == 6) {
					pRightTopShelf.shelfItem->GetComponent<Animator>()->PlayAnimation(changeAnimationName, false);
					pRightTopShelf._itemType = shop[i][j]._itemType;
				}
				else if (i == 2 && j == 5) {
					pLeftBottomShelf.shelfItem->GetComponent<Animator>()->PlayAnimation(changeAnimationName, false);
					pLeftBottomShelf._itemType = shop[i][j]._itemType;
				}
				else if (i == 2 && j == 6) {
					pRightBottomShelf.shelfItem->GetComponent<Animator>()->PlayAnimation(changeAnimationName, false);
					pRightBottomShelf._itemType = shop[i][j]._itemType;
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
				TextManager::ChangeText(price[curInvenSlotPos.first+1][curInvenSlotPos.second-5].textTitle, L"0");

				if (curInvenSlotPos.first == 0 && curInvenSlotPos.second == 5) {
					pLeftTopShelf.shelfItem->GetComponent<Animator>()->PlayAnimation(L"Transparent", false);
					pLeftTopShelf._itemType = eItemType::NONE;
				}
				else if (curInvenSlotPos.first == 0 && curInvenSlotPos.second == 6) {
					pRightTopShelf.shelfItem->GetComponent<Animator>()->PlayAnimation(L"Transparent", false);
					pLeftTopShelf._itemType = eItemType::NONE;
				}
				else if (curInvenSlotPos.first == 2 && curInvenSlotPos.second == 5) {
					pLeftBottomShelf.shelfItem->GetComponent<Animator>()->PlayAnimation(L"Transparent", false);
					pLeftTopShelf._itemType = eItemType::NONE;
				}
				else if (curInvenSlotPos.first == 2 && curInvenSlotPos.second == 6) {
					pRightBottomShelf.shelfItem->GetComponent<Animator>()->PlayAnimation(L"Transparent", false);
					pLeftTopShelf._itemType = eItemType::NONE;
				}

				return;
			}
		}
	}
	return;
}

void ShopManager::SetPrice() {

}

vector<Vector3> ShopManager::GetLoot() {
	if (pLeftTopShelf.price != 0) {
		pLeftTopShelf.realPrice = pLeftTopShelf.price;
		pLeftTopShelf.price = 0;
		return loot[0];
	}
	else if (pLeftBottomShelf.price != 0) {
		pLeftBottomShelf.realPrice = pLeftBottomShelf.price;
		pLeftBottomShelf.price = 0;
		return loot[1];
	}
	else if (pRightBottomShelf.price != 0) {
		pRightBottomShelf.realPrice = pRightBottomShelf.price;
		pRightBottomShelf.price = 0;
		return loot[2];
	}
	else if (pRightTopShelf.price != 0) {
		pRightTopShelf.realPrice = pRightTopShelf.price;
		pRightTopShelf.price = 0;
		return loot[3];
	}
	else {
		return loot[4];
	}
}

int ShopManager::SearchGoods(int _pos) {
	int resultPrice;

	switch (_pos)
	{
	case 0:
	{
		resultPrice = priceList[(int)pLeftTopShelf._itemType];
	}
	break;
	case 1:
	{
		resultPrice = priceList[(int)pLeftBottomShelf._itemType];
	}
	break;
	case 2:
	{
		resultPrice = priceList[(int)pRightBottomShelf._itemType];
	}
	break;
	case 3:
	{
		resultPrice = priceList[(int)pRightTopShelf._itemType];
	}
	break;
	default:
		break;
	}

	return resultPrice;
}

void ShopManager::BuyGoods(int _pos) {
	switch (_pos)
	{
	case 0:
	{
		pLeftTopShelf.shelfItem->GetComponent<Animator>()->PlayAnimation(L"Transparent", false);
		pLeftTopShelf.price = 0;
		pLeftTopShelf.realPrice = 0;
		pLeftTopShelf._itemType = eItemType::NONE;

		shop[0][5].isEmpty = true;
		shop[0][5].slotItem->GetComponent<Animator>()->PlayAnimation(L"Transparent", false);
		shop[0][5].itemCount = 0;
		shop[0][5].itemMaxCount = -1;
		shop[0][5]._itemType = eItemType::NONE;

		TextManager::ChangeText(price[1][0].textTitle, L"0");
	}
		break;
	case 1:
	{
		pLeftBottomShelf.shelfItem->GetComponent<Animator>()->PlayAnimation(L"Transparent", false);
		pLeftBottomShelf.price = 0;
		pLeftBottomShelf.realPrice = 0;
		pLeftBottomShelf._itemType = eItemType::NONE;

		shop[2][5].isEmpty = true;
		shop[2][5].slotItem->GetComponent<Animator>()->PlayAnimation(L"Transparent", false);
		shop[2][5].itemCount = 0;
		shop[2][5].itemMaxCount = -1;
		shop[2][5]._itemType = eItemType::NONE;

		TextManager::ChangeText(price[3][0].textTitle, L"0");
	}
		break;
	case 2:
	{
		pRightBottomShelf.shelfItem->GetComponent<Animator>()->PlayAnimation(L"Transparent", false);
		pRightBottomShelf.price = 0;
		pRightBottomShelf.realPrice = 0;
		pRightBottomShelf._itemType = eItemType::NONE;

		shop[2][6].isEmpty = true;
		shop[2][6].slotItem->GetComponent<Animator>()->PlayAnimation(L"Transparent", false);
		shop[2][6].itemCount = 0;
		shop[2][6].itemMaxCount = -1;
		shop[2][6]._itemType = eItemType::NONE;

		TextManager::ChangeText(price[3][1].textTitle, L"0");
	}
		break;
	case 3:
	{
		pRightTopShelf.shelfItem->GetComponent<Animator>()->PlayAnimation(L"Transparent", false);
		pRightTopShelf.price = 0;
		pRightTopShelf.realPrice = 0;
		pRightTopShelf._itemType = eItemType::NONE;

		shop[0][6].isEmpty = true;
		shop[0][6].slotItem->GetComponent<Animator>()->PlayAnimation(L"Transparent", false);
		shop[0][6].itemCount = 0;
		shop[0][6].itemMaxCount = -1;
		shop[0][6]._itemType = eItemType::NONE;

		TextManager::ChangeText(price[1][1].textTitle, L"0");
	}
		break;
	default:
		break;
	}
}

void ShopManager::CreateNPC() {
	
}