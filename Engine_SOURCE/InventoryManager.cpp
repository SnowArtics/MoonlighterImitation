#include "InventoryManager.h"

#include <snGameObject.h>
#include "snSceneManager.h"
#include <snMeshRenderer.h>
#include "snResources.h"

std::pair<int, int> InventoryManager::curInvenPos = std::make_pair<int, int>(0, 0);
std::vector<std::vector<InventoryItem>>  InventoryManager::inven;

void InventoryManager::Initiailize()
{
	for (int i = 0; i < 3; i++) {
		std::vector<InventoryItem> inven1D;
		for (int j = 0; j < 5; j++) {
			InventoryItem mInventoryItem;
			inven1D.push_back(mInventoryItem);
		}
	}
}

void InventoryManager::Update()
{
}

void InventoryManager::Render()
{
}

void InventoryManager::CreateUI()
{
	{
		//牢亥配府 UI 积己
		GameObject* UI = new GameObject();
		UI->SetName(L"InventoryBase");
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, UI);
		MeshRenderer* mr = UI->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"UIInventoryBaseMaterial01"));
		UI->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		UI->GetComponent<Transform>()->SetScale(Vector3(7.576642335766424f, 4.f, 2.0f));
		UI->SetEnable(false);
	}
	{
		//牢亥配府 Slot UI 积己
		GameObject* UI = new GameObject();
		UI->SetName(L"InventorySlot");
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::UI, UI);
		MeshRenderer* mr = UI->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"UIInventoryBaseMaterial01"));
		UI->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		UI->GetComponent<Transform>()->SetScale(Vector3(7.576642335766424f, 4.f, 2.0f));
		UI->SetEnable(false);
	}
}
