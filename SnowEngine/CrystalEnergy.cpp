#include "CrystalEnergy.h"

#include "snEnums.h"
#include "snResources.h"
#include "snCollider2D.h"
#include "snMesh.h"
#include "snMeshRenderer.h"

using namespace sn;

CrystalEnergy::CrystalEnergy()
	: Item(enums::eItemType::Crystal_Energy)
{
	MeshRenderer* mr = AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"Crystal_Energy_Item"));

	Transform* tr = GetComponent<Transform>();
	tr->SetScale(Vector3(0.2f, 0.34f, 0.0f));

	sn::Collider2D* col = AddComponent<sn::Collider2D>();
	col->SetEnable(false);
}

CrystalEnergy::~CrystalEnergy()
{
}

void CrystalEnergy::Initialize()
{
	Item::Initialize();
}

void CrystalEnergy::Update()
{
	Item::Update();
}

void CrystalEnergy::LateUpdate()
{
	Item::LateUpdate();
}

void CrystalEnergy::Render()
{
	Item::Render();
}

void CrystalEnergy::OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me)
{
	Item::OnCollisionEnter(other, me);
}

void CrystalEnergy::OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me)
{
}

void CrystalEnergy::OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me)
{
}
