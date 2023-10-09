#include "GolemKingCrystalEnergy.h"

#include "snEnums.h"
#include "snResources.h"
#include "snCollider2D.h"
#include "snMesh.h"
#include "snMeshRenderer.h"

GolemKingCrystalEnergy::GolemKingCrystalEnergy()
	: Item(enums::eItemType::GolemKing_Crystal_Energy)
{
	MeshRenderer* mr = AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"Energy_CrystalItem"));

	Transform* tr = GetComponent<Transform>();
	tr->SetScale(Vector3(0.2f, 0.2f, 0.0f));

	sn::Collider2D* col = AddComponent<sn::Collider2D>();
	col->SetEnable(false);
}

GolemKingCrystalEnergy::~GolemKingCrystalEnergy()
{
}

void GolemKingCrystalEnergy::Initialize()
{
	Item::Initialize();
}

void GolemKingCrystalEnergy::Update()
{
	Item::Update();
}

void GolemKingCrystalEnergy::LateUpdate()
{
	Item::LateUpdate();
}

void GolemKingCrystalEnergy::Render()
{
	Item::Render();
}

void GolemKingCrystalEnergy::OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me)
{
	Item::OnCollisionEnter(other, me);
}

void GolemKingCrystalEnergy::OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me)
{
}

void GolemKingCrystalEnergy::OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me)
{
}
