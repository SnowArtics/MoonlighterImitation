#include "SlimeJelly.h"

#include "snEnums.h"
#include "snResources.h"
#include "snCollider2D.h"
#include "snMesh.h"
#include "snMeshRenderer.h"

using namespace sn;

SlimeJelly::SlimeJelly()
	: Item(enums::eItemType::Slime_Jelly)
{
	MeshRenderer* mr = AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"slime_jellyItem"));

	Transform* tr = GetComponent<Transform>();
	tr->SetScale(Vector3(0.1428571428571429f, 0.1f, 0.0f));

	sn::Collider2D* col = AddComponent<sn::Collider2D>();
	col->SetEnable(false);
}

SlimeJelly::~SlimeJelly()
{
}

void SlimeJelly::Initialize()
{
	Item::Initialize();
}

void SlimeJelly::Update()
{
	Item::Update();
}

void SlimeJelly::LateUpdate()
{
	Item::LateUpdate();
}

void SlimeJelly::Render()
{
	Item::Render();
}

void SlimeJelly::OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me)
{
	Item::OnCollisionEnter(other, me);
}

void SlimeJelly::OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me)
{
}

void SlimeJelly::OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me)
{
}
