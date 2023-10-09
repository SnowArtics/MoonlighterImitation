#include "BrokenSword.h"

#include "snEnums.h"
#include "snResources.h"
#include "snCollider2D.h"
#include "snMesh.h"
#include "snMeshRenderer.h"

using namespace sn;

BrokenSword::BrokenSword()
	: Item(sn::enums::eItemType::Broken_Sword)
{
	MeshRenderer* mr = AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"Broken_Sword_Item"));
	
	Transform* tr = GetComponent<Transform>();
	tr->SetScale(Vector3(0.2f, 0.2f, 0.0f));

	sn::Collider2D* col = AddComponent<sn::Collider2D>();
	col->SetEnable(false);
}

BrokenSword::~BrokenSword()
{
}

void BrokenSword::Initialize()
{
	Item::Initialize();
}

void BrokenSword::Update()
{
	Item::Update();
}

void BrokenSword::LateUpdate()
{
	Item::LateUpdate();
}

void BrokenSword::Render()
{
	Item::Render();
}

void BrokenSword::OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me)
{
	Item::OnCollisionEnter(other, me);
}

void BrokenSword::OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me)
{
}

void BrokenSword::OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me)
{
}
