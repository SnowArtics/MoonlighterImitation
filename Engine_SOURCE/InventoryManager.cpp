#include "InventoryManager.h"

#include "snSceneManager.h"
#include "snMeshRenderer.h"
#include "snTransform.h"
#include "snResources.h"
#include "snInput.h"
#include "snAnimator.h"
#include "snTextManager.h"

std::pair<int, int> InventoryManager::curInvenSlotPos = std::make_pair<int, int>(0, 0);
std::vector<std::vector<Vector3>> InventoryManager::vInventorySlotPos;
std::vector<std::vector<InventoryItem>>  InventoryManager::inven;
sn::GameObject* InventoryManager::pInventory = nullptr;
sn::GameObject* InventoryManager::pInventoryLeft = nullptr;
sn::GameObject* InventoryManager::pInventorySlot = nullptr;
bool InventoryManager::bInvenActive = false;

using namespace sn;
using namespace std;

void InventoryManager::Initiailize()
{
	//인벤토리 slot 포즈를 저장하는 벡터 생성
	std::vector<Vector3> m_vInventorySlotPos;
	m_vInventorySlotPos.push_back(Vector3(-2.86f, 1.1f, -2.0f));
	m_vInventorySlotPos.push_back(Vector3(-2.34f, 1.1f, -2.0f));
	m_vInventorySlotPos.push_back(Vector3(-1.82f, 1.1f, -2.0f));
	m_vInventorySlotPos.push_back(Vector3(-1.3f, 1.1f, -2.0f));
	m_vInventorySlotPos.push_back(Vector3(-0.78f, 1.1f, -2.0f));
	
	vInventorySlotPos.push_back(m_vInventorySlotPos);

	for (int i = 0; i < 3; i++) {
		std::vector<Vector3> m_vInventorySlotPos01;
		for (int j = 0; j < 5; j++) {
			m_vInventorySlotPos01.push_back(Vector3(-2.86f + 0.52f * j, 0.48f - 0.5f * i, -2.0f));
		}
		vInventorySlotPos.push_back(m_vInventorySlotPos01);
	}

	//InventoryItem Vector 생성

	for (int i = 0; i < 4; i++) {
		std::vector<InventoryItem> inven1D;
		for (int j = 0; j < 5; j++) {
			InventoryItem mInventoryItem;
			mInventoryItem.pos = vInventorySlotPos[i][j];
			mInventoryItem.isEmpty = true;
			mInventoryItem._itemType = eItemType::NONE;
			mInventoryItem.itemCount = 0;
			mInventoryItem.itemMaxCount = 0;

			wstring ItoS = to_wstring(i);
			wstring JtoS = to_wstring(j);
			mInventoryItem.slotName = ItoS + JtoS + L"InvenSlot";

			inven1D.push_back(mInventoryItem);
		}
		inven.push_back(inven1D);
	}

	//InventoryItem에 해당하는 텍스트 위치 생성
	std::vector < vector<Vector2>> texPos2D;
	std::vector<Vector2> texPos1D01;

	for (int i = 0; i < 5; i++) {
		texPos1D01.push_back(Vector2(415.f + i * 103.f, 315.f));
	}

	texPos2D.push_back(texPos1D01);

	for (int i = 0; i < 3; i++) {
		std::vector<Vector2> texPos1D02;
		for (int j = 0; j < 5; j++) {
			texPos1D02.push_back(Vector2(415.f + j * 103.f, 435.f + i * 103.f));
		}
		texPos2D.push_back(texPos1D02);
	}

	//InventoryItem에 해당하는 텍스트 생성

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++) {
			Text text(L"0", texPos2D[i][j].x, texPos2D[i][j].y, 25, TextColor(0.f, 0.f, 0.f, 255.f), false);
			TextManager::InsertText(inven[i][j].slotName, text);
		}
	}
}

void InventoryManager::Update()
{
	
}

void InventoryManager::Render()
{
	if (pInventory != nullptr && Input::GetKeyDown(eKeyCode::I))
	{
		if (pInventory->GetEnable() == true) {
			pInventory->SetEnable(false);
			pInventorySlot->SetEnable(false);
			bInvenActive = false;

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 5; j++) {
					inven[i][j].slotItem->SetEnable(false);
					TextManager::SetEnable(inven[i][j].slotName, false);
				}
			}
		}
		else {
			pInventory->SetEnable(true);
			pInventorySlot->SetEnable(true);
			bInvenActive = true;

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 5; j++) {
					inven[i][j].slotItem->SetEnable(true);
					if(!inven[i][j].isEmpty)
						TextManager::SetEnable(inven[i][j].slotName, true);
				}
			}
		}
	}

	if (bInvenActive == true) {
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

void InventoryManager::CreateUI()
{
	{
		//인벤토리 UI 생성
		pInventory = new sn::GameObject();
		pInventory->SetName(L"InventoryBase");
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, pInventory);
		MeshRenderer* mr = pInventory->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"UIInventoryBaseMaterial01"));
		pInventory->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -2.0f));
		pInventory->GetComponent<Transform>()->SetScale(Vector3(7.576642335766424f, 4.f, 2.0f));
		pInventory->SetEnable(false);
		bInvenActive = false;
		curInvenSlotPos.first = 0;
		curInvenSlotPos.second = 0;
	}
	{
		//인벤토리 UI 생성
		pInventoryLeft = new sn::GameObject();
		pInventoryLeft->SetName(L"InventoryBase");
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, pInventoryLeft);
		MeshRenderer* mr = pInventoryLeft->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"UIInventoryLeftBaseMaterial01"));
		pInventoryLeft->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -2.0f));
		pInventoryLeft->GetComponent<Transform>()->SetScale(Vector3(7.576642335766424f, 4.f, 2.0f));
		pInventoryLeft->SetEnable(false);
		bInvenActive = false;
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
		mr->SetMaterial(Resources::Find<Material>(L"InvenSlotMeterial01"));
		pInventorySlot->GetComponent<Transform>()->SetPosition(Vector3(-2.86f, 1.1f, -2.0f));/*
		pInventorySlot->GetComponent<Transform>()->SetPosition(Vector3(-2.86f, 0.48f, -2.0f));
		pInventorySlot->GetComponent<Transform>()->SetPosition(Vector3(-2.86f, -0.02f, -2.0f));*/
		pInventorySlot->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 2.0f));
		pInventorySlot->SetEnable(false);
	}
	{
		//인벤토리 slot 생성
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 5; j++) {
				inven[i][j].slotItem = new sn::GameObject();
				inven[i][j].slotItem->GetComponent<Transform>()->SetPosition(inven[i][j].pos);
				inven[i][j].slotItem->SetName(L"SlotItem");
				inven[i][j].slotItem->SetEnable(false);

				MeshRenderer* mr = inven[i][j].slotItem->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

				Animator* at = inven[i][j].slotItem->AddComponent<Animator>();
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

				//inven[i][j].slotItem->GetComponent<Transform>()->SetParent(pInventory->GetComponent<Transform>());

				SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, inven[i][j].slotItem);
			}
		}
	}
}

void InventoryManager::ShowUI()
{
}

void InventoryManager::MoveSlot(SlotMoveDir _eSlotMoveDir)
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
		if (curInvenSlotPos.second != 4) {
			curInvenSlotPos.second += 1;
		}
	}
		break;
	default:
		break;
	}

	Transform* tr = pInventorySlot->GetComponent<Transform>();
	tr->SetPosition(inven[curInvenSlotPos.first][curInvenSlotPos.second].pos);
}

bool InventoryManager::InputItem(eItemType _itemType)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			if (inven[i][j].isEmpty == true) {
				inven[i][j].isEmpty = false;
				inven[i][j].itemCount = 1;
				inven[i][j]._itemType = _itemType;

				Animator* at = inven[i][j].slotItem->GetComponent<Animator>();

				switch (_itemType)
				{
				case sn::enums::eItemType::NONE:
					at->PlayAnimation(L"Transparent", false);
					inven[i][j].itemMaxCount = 0;
					break;
				case sn::enums::eItemType::Broken_Sword:
					at->PlayAnimation(L"Broken_Sword", false);
					inven[i][j].itemMaxCount = 10;
					break;
				case sn::enums::eItemType::Crystal_Energy:
					at->PlayAnimation(L"Crystal_Energy", false);
					inven[i][j].itemMaxCount = 5;
					break;
				case sn::enums::eItemType::GolemKing_Crystal_Energy:
					at->PlayAnimation(L"GolemKing_Crystal_Energy", false);
					inven[i][j].itemMaxCount = 1;
					break;
				case sn::enums::eItemType::Fabric:
					at->PlayAnimation(L"fabric", false);
					inven[i][j].itemMaxCount = 10;
					break;
				case sn::enums::eItemType::Golem_Core:
					at->PlayAnimation(L"Golem_Core", false);
					inven[i][j].itemMaxCount = 5;
					break;
				case sn::enums::eItemType::Golem_King_Design:
					at->PlayAnimation(L"Golem_King_design", false);
					inven[i][j].itemMaxCount = 5;
					break;
				case sn::enums::eItemType::Golem_Pieces:
					at->PlayAnimation(L"golem_pieces", false);
					inven[i][j].itemMaxCount = 10;
					break;
				case sn::enums::eItemType::Reinforced_Steel:
					at->PlayAnimation(L"Reinforced_Steel_G", false);
					inven[i][j].itemMaxCount = 5;
					break;
				case sn::enums::eItemType::Slime_Jelly:
					at->PlayAnimation(L"slime_jelly", false);
					inven[i][j].itemMaxCount = 10;
					break;
				case sn::enums::eItemType::END:
					break;
				default:
					break;
				}

				wstring test = NumToWString(inven[i][j].itemCount);
				TextManager::ChangeText(inven[i][j].slotName, NumToWString(inven[i][j].itemCount));
				if(pInventory->GetEnable()==true)
					TextManager::SetEnable(inven[i][j].slotName, true);

				return true;
			}
			else if (inven[i][j]._itemType == _itemType && inven[i][j].itemMaxCount != inven[i][j].itemCount) {
				inven[i][j].itemCount++;
				TextManager::ChangeText(inven[i][j].slotName, NumToWString(inven[i][j].itemCount));
				return true;
			}
		}
		if (i == 3) {
			return false;
		}
	}
}

bool InventoryManager::InputItemToPos(std::pair<int, int> _invenPos, eItemType _itemType)
{
	return false;
}
