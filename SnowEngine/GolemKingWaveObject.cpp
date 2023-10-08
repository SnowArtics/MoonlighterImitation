#include "GolemKingWaveObject.h"

#include "snTime.h"
#include "snMeshRenderer.h"
#include "snResources.h"
#include "snAnimator.h"

GolemKingWaveObject::GolemKingWaveObject()
	: curTime(0.f)
	, endTime(2.4f)
{
	MeshRenderer* mr = AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

	std::shared_ptr<Texture> atlas
		= Resources::Load<Texture>(L"GolemKing_Wave", L"..\\Resources\\Texture\\Dungeon\\Enemy\\GolemKing\\Boss1_Wave.png");
	Animator* at = AddComponent<Animator>();

	at->Create(L"GolemKing_Wave", atlas, Vector2(0.0f, 0.0f), Vector2(350.f, 350.f), 16, 300.f, 0.15f);

	at->PlayAnimation(L"GolemKing_Wave", false);
}

GolemKingWaveObject::~GolemKingWaveObject()
{
}

void GolemKingWaveObject::Initialize()
{
	GameObject::Initialize();
}

void GolemKingWaveObject::Update()
{
	curTime += Time::DeltaTime();
	if (curTime >= endTime) {
		SetState(eState::Dead);
	}

	GameObject::Update();
}

void GolemKingWaveObject::LateUpdate()
{
	GameObject::LateUpdate();
}

void GolemKingWaveObject::Render()
{
	GameObject::Render();
}
