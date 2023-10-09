#include "GolemCore.h"

#include "snEnums.h"
#include "snResources.h"
#include "snCollider2D.h"
#include "snMesh.h"
#include "snMeshRenderer.h"

using namespace sn;

GolemCore::GolemCore()
	: Item(enums::eItemType::Golem_Core)
{
	MeshRenderer* mr = AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"Golem_CoreItem"));

	Transform* tr = GetComponent<Transform>();
	tr->SetScale(Vector3(0.2f, 0.2f, 0.0f));

	sn::Collider2D* col = AddComponent<sn::Collider2D>();
	col->SetEnable(false);
}

GolemCore::~GolemCore()
{
}

void GolemCore::Initialize()
{
	Item::Initialize();
}

void GolemCore::Update()
{
	Item::Update();
}

void GolemCore::LateUpdate()
{
	Item::LateUpdate();
}

void GolemCore::Render()
{
	Item::Render();
}

void GolemCore::OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me)
{
	Item::OnCollisionEnter(other, me);
}

void GolemCore::OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me)
{
}

void GolemCore::OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me)
{
}
