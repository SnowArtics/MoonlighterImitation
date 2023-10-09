#include "Fabric.h"

#include "snEnums.h"
#include "snResources.h"
#include "snCollider2D.h"
#include "snMesh.h"
#include "snMeshRenderer.h"

using namespace sn;

Fabric::Fabric()
	: Item(enums::eItemType::Fabric)
{
	MeshRenderer* mr = AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"fabricItem"));

	Transform* tr = GetComponent<Transform>();
	tr->SetScale(Vector3(0.25f, 0.2f, 0.0f));

	sn::Collider2D* col = AddComponent<sn::Collider2D>();
	col->SetEnable(false);
}

Fabric::~Fabric()
{
}

void Fabric::Initialize()
{
	Item::Initialize();
}

void Fabric::Update()
{
	Item::Update();
}

void Fabric::LateUpdate()
{
	Item::LateUpdate();
}

void Fabric::Render()
{
	Item::Render();
}

void Fabric::OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me)
{
	Item::OnCollisionEnter(other, me);
}

void Fabric::OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me)
{
}

void Fabric::OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me)
{
}
