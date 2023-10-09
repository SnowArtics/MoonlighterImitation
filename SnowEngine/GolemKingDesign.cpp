#include "GolemKingDesign.h"

#include "snEnums.h"
#include "snResources.h"
#include "snCollider2D.h"
#include "snMesh.h"
#include "snMeshRenderer.h"

using namespace sn;

GolemKingDesign::GolemKingDesign()
	: Item(enums::eItemType::Golem_King_Design)
{
	MeshRenderer* mr = AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"Golem_King_designItem"));

	Transform* tr = GetComponent<Transform>();
	tr->SetScale(Vector3(0.2f, 0.20909088f, 0.0f));

	sn::Collider2D* col = AddComponent<sn::Collider2D>();
	col->SetEnable(false);
}

GolemKingDesign::~GolemKingDesign()
{
}

void GolemKingDesign::Initialize()
{
	Item::Initialize();
}

void GolemKingDesign::Update()
{
	Item::Update();
}

void GolemKingDesign::LateUpdate()
{
	Item::LateUpdate();
}

void GolemKingDesign::Render()
{
	Item::Render();
}

void GolemKingDesign::OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me)
{
	Item::OnCollisionEnter(other, me);
}

void GolemKingDesign::OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me)
{
}

void GolemKingDesign::OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me)
{
}
