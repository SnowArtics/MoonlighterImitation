#include "Shelf.h"
#include <snMeshRenderer.h>
#include "snResources.h"
#include <snAnimator.h>
#include "ObstacleCollider.h"

Shelf::Shelf()
{
	MeshRenderer* mr = AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

	Animator* at = AddComponent<Animator>();
	std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"transparent_space", L"..\\Resources\\Texture\\Item\\transparent_space.png");
	at->Create(L"Transparent", atlas, Vector2(0.0f, 0.0f), Vector2(30.f, 30.f), 1, 90.f);

	atlas = Resources::Load<Texture>(L"Broken_Sword", L"..\\Resources\\Texture\\Item\\Broken_Sword.png");
	at->Create(L"Broken_Sword", atlas, Vector2(0.0f, 0.0f), Vector2(10.f, 10.f), 1, 90.f);

	atlas = Resources::Load<Texture>(L"Crystal_Energy", L"..\\Resources\\Texture\\Item\\Crystal_Energy.png");
	at->Create(L"Crystal_Energy", atlas, Vector2(0.0f, 0.0f), Vector2(10.f, 17.f), 1, 90.f);

	atlas = Resources::Load<Texture>(L"Energy_Crystal", L"..\\Resources\\Texture\\Item\\Energy_Crystal.png");
	at->Create(L"GolemKing_Crystal_Energy", atlas, Vector2(0.0f, 0.0f), Vector2(19.f, 19.f), 1, 90.f);

	atlas = Resources::Load<Texture>(L"fabric", L"..\\Resources\\Texture\\Item\\fabric.png");
	at->Create(L"fabric", atlas, Vector2(0.0f, 0.0f), Vector2(20.f, 16.f), 1, 90.f);

	atlas = Resources::Load<Texture>(L"Golem_Core", L"..\\Resources\\Texture\\Item\\Golem_Core.png");
	at->Create(L"Golem_Core", atlas, Vector2(0.0f, 0.0f), Vector2(13.f, 13.f), 1, 90.f);

	atlas = Resources::Load<Texture>(L"Golem_King_design", L"..\\Resources\\Texture\\Item\\Golem_King_design.png");
	at->Create(L"Golem_King_design", atlas, Vector2(0.0f, 0.0f), Vector2(22.f, 23.f), 1, 90.f);

	atlas = Resources::Load<Texture>(L"golem_pieces", L"..\\Resources\\Texture\\Item\\golem_pieces.png");
	at->Create(L"golem_pieces", atlas, Vector2(0.0f, 0.0f), Vector2(20.f, 17.f), 1, 90.f);

	atlas = Resources::Load<Texture>(L"Reinforced_Steel_G", L"..\\Resources\\Texture\\Item\\Reinforced_Steel_G.png");
	at->Create(L"Reinforced_Steel_G", atlas, Vector2(0.0f, 0.0f), Vector2(15.f, 16.f), 1, 90.f);

	atlas = Resources::Load<Texture>(L"slime_jelly", L"..\\Resources\\Texture\\Item\\slime_jelly.png");
	at->Create(L"slime_jelly", atlas, Vector2(0.0f, 0.0f), Vector2(20.f, 14.f), 1, 90.f);

	at->PlayAnimation(L"Transparent", false);

	//AddComponent<ObstacleCollider>();
}

Shelf::~Shelf()
{
}

void Shelf::Initialize()
{
	GameObject::Initialize();
}

void Shelf::Update()
{
	GameObject::Update();
}

void Shelf::LateUpdate()
{
	GameObject::LateUpdate();
}

void Shelf::Render()
{
	GameObject::Render();
}

void Shelf::OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me)
{
	GameObject::OnCollisionEnter(other, me);
}

void Shelf::OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me)
{
	GameObject::OnCollisionStay(other, me);
}

void Shelf::OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me)
{
	GameObject::OnCollisionExit(other, me);
}
