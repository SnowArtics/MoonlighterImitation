#include "ReinforcedSteel.h"

#include "snEnums.h"
#include "snResources.h"
#include "snCollider2D.h"
#include "snMesh.h"
#include "snMeshRenderer.h"

using namespace sn;

ReinforcedSteel::ReinforcedSteel()
	: Item(enums::eItemType::Reinforced_Steel)
{
	MeshRenderer* mr = AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"Reinforced_Steel_GItem"));

	Transform* tr = GetComponent<Transform>();
	tr->SetScale(Vector3(0.2f, 0.2133333332f, 0.0f));

	sn::Collider2D* col = AddComponent<sn::Collider2D>();
	col->SetEnable(false);
}

ReinforcedSteel::~ReinforcedSteel()
{
}

void ReinforcedSteel::Initialize()
{
	Item::Initialize();
}

void ReinforcedSteel::Update()
{
	Item::Update();
}

void ReinforcedSteel::LateUpdate()
{
	Item::LateUpdate();
}

void ReinforcedSteel::Render()
{
	Item::Render();
}

void ReinforcedSteel::OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me)
{
	Item::OnCollisionEnter(other, me);
}

void ReinforcedSteel::OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me)
{
}

void ReinforcedSteel::OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me)
{
}
