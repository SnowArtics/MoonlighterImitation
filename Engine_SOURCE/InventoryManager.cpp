#include "InventoryManager.h"

#include "snSceneManager.h"
#include "snMeshRenderer.h"
#include "snTransform.h"
#include "snResources.h"
#include "snInput.h"

std::pair<int, int> InventoryManager::curInvenSlotPos = std::make_pair<int, int>(0, 0);
std::vector<std::vector<Vector3>> InventoryManager::vInventorySlotPos;
std::vector<std::vector<InventoryItem>>  InventoryManager::inven;
sn::GameObject* InventoryManager::pInventory = nullptr;
sn::GameObject* InventoryManager::pInventorySlot = nullptr;
bool InventoryManager::bInvenActive = false;

using namespace sn;

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
			m_vInventorySlotPos01.push_back(Vector3(-2.86f + 0.52f * j, 0.48f - 0.62f * i, -2.0f));
		}
		vInventorySlotPos.push_back(m_vInventorySlotPos01);
	}

	for (int i = 0; i < 4; i++) {
		std::vector<InventoryItem> inven1D;
		for (int j = 0; j < 5; j++) {
			InventoryItem mInventoryItem;
			mInventoryItem.pos = vInventorySlotPos[i][j];
			inven1D.push_back(mInventoryItem);
		}
		inven.push_back(inven1D);
	}
}

void InventoryManager::Update()
{
	
}

void InventoryManager::Render()
{
	if (Input::GetKeyDown(eKeyCode::I))
	{
		if (pInventory->GetEnable() == true) {
			pInventory->SetEnable(false);
			pInventorySlot->SetEnable(false);
			bInvenActive = false;
		}
		else {
			pInventory->SetEnable(true);
			pInventorySlot->SetEnable(true);
			bInvenActive = true;
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
	}
	{
		//인벤토리 Slot UI 생성
		pInventorySlot = new sn::GameObject();
		pInventorySlot->SetName(L"InventorySlot");
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, pInventorySlot);
		MeshRenderer* mr = pInventorySlot->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"InvenSlotMeterial01"));
		pInventorySlot->GetComponent<Transform>()->SetPosition(Vector3(-2.86f, 1.1f, -2.0f));
		pInventorySlot->GetComponent<Transform>()->SetPosition(Vector3(-2.86f, 0.48f, -2.0f));
		pInventorySlot->GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 2.0f));
		pInventorySlot->SetEnable(false);
	}
}

void InventoryManager::ShowUI()
{
}

void InventoryManager::MoveSlot(SlotMoveDir _eSlotMoveDir)
{
}
