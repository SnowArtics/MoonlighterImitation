#include "GolemPieces.h"

#include "snEnums.h"
#include "snResources.h"
#include "snCollider2D.h"
#include "snMesh.h"
#include "snMeshRenderer.h"

using namespace sn;

GolemPieces::GolemPieces()
	: Item(enums::eItemType::Golem_Pieces)
{
	MeshRenderer* mr = AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"golem_piecesItem"));

	Transform* tr = GetComponent<Transform>();
	tr->SetScale(Vector3(0.230769228f, 0.2f, 0.0f));

	sn::Collider2D* col = AddComponent<sn::Collider2D>();
	col->SetEnable(false);
}

GolemPieces::~GolemPieces()
{
}

void GolemPieces::Initialize()
{
	Item::Initialize();
}

void GolemPieces::Update()
{
	Item::Update();
}

void GolemPieces::LateUpdate()
{
	Item::LateUpdate();
}

void GolemPieces::Render()
{
	Item::Render();
}

void GolemPieces::OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me)
{
	Item::OnCollisionEnter(other, me);
}

void GolemPieces::OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me)
{
}

void GolemPieces::OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me)
{
}
