#include "GolemKingRock.h"

#include "snTime.h"
#include "snMeshRenderer.h"
#include "snAnimator.h"
#include "snResources.h"
#include "snTexture.h"
#include "snCollider2D.h"
#include "snTransform.h"
#include <snAudioSource.h>
#include "snResources.h"

#include <random>

using namespace sn;

GolemKingRock::GolemKingRock()
	:endTime(10.f)
	, executionTime(0.f)
	, desPos(Vector3(0.0f, 0.0f, 0.0f))
	, curPos(Vector3(0.0f, 0.0f, 0.0f))
	, rockTrigger(true)
{
	MeshRenderer* mr = AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

	//랜덤 패턴 시작
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> distribution(1, 4);

	int randomNum = distribution(gen); // randomNums이 1일때 주먹 휘두르기, 2일때 충격파, 3일때 손 발사, 4일때 레이저 발사

	std::shared_ptr<Texture> atlas
		= Resources::Load<Texture>(L"GolemKingRock_Shadow", L"..\\Resources\\Texture\\Dungeon\\Enemy\\GolemKing\\Boss1_Punch_Shadow.png");
	Animator* at = AddComponent<Animator>();

	at->Create(L"Rock_Shadow", atlas, Vector2(0.0f, 0.0f), Vector2(64.f, 45.f), 1);

		atlas = Resources::Load<Texture>(L"GolemKingRock01", L"..\\Resources\\Texture\\Dungeon\\Enemy\\GolemKing\\Golem_King_Rock_01.png");
		at->Create(L"GolemKingRock01", atlas, Vector2(0.0f, 0.0f), Vector2(100.f, 109.f), 1);
		atlas = Resources::Load<Texture>(L"GolemKingRock02", L"..\\Resources\\Texture\\Dungeon\\Enemy\\GolemKing\\Golem_King_Rock_02.png");
		at->Create(L"GolemKingRock02", atlas, Vector2(0.0f, 0.0f), Vector2(100.f, 108.f), 1);
		atlas = Resources::Load<Texture>(L"GolemKingRock03", L"..\\Resources\\Texture\\Dungeon\\Enemy\\GolemKing\\Golem_King_Rock_03.png");
		at->Create(L"GolemKingRock03", atlas, Vector2(0.0f, 0.0f), Vector2(100.f, 109.f), 1);
		atlas = Resources::Load<Texture>(L"GolemKingRock04", L"..\\Resources\\Texture\\Dungeon\\Enemy\\GolemKing\\Golem_King_Rock_04.png");
		at->Create(L"GolemKingRock04", atlas, Vector2(0.0f, 0.0f), Vector2(100.f, 106.f), 1);

	at->PlayAnimation(L"Rock_Shadow", true);

	sn::Collider2D* collider = AddComponent<sn::Collider2D>();
	collider->SetCenter(Vector2(0.0f, 0.0f));
	collider->SetEnable(false);
}

GolemKingRock::~GolemKingRock()
{
}

void GolemKingRock::Initialize()
{	
	GameObject::Initialize();
}

void GolemKingRock::Update()
{
	executionTime += Time::DeltaTime();

	if (executionTime > 1.0f && executionTime < 1.1f) {
		Transform* tr = GetComponent<Transform>();
		Vector3 curScale = tr->GetScale();
		curScale.x += Time::DeltaTime();
		curScale.y += Time::DeltaTime();

		tr->SetScale(curScale);
	}

	if (executionTime >= 1.1f && rockTrigger) {
		Animator* at = GetComponent<Animator>();
		at->PlayAnimation(L"GolemKingRock01", true);
		curPos.y -= Time::DeltaTime() * 20.f;
		if (curPos.y <= desPos.y) {
			curPos = desPos;
			rockTrigger = false;
		}
		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(curPos);
		tr->SetScale(Vector3(0.7f, 0.7f, 0.0f));
	}

	if (executionTime >= endTime) {
		SetState(eState::Dead);
	}

	GameObject::Update();
}

void GolemKingRock::LateUpdate()
{
	GameObject::LateUpdate();
}

void GolemKingRock::Render()
{
	GameObject::Render();
}

void GolemKingRock::OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me)
{
	GameObject::OnCollisionEnter(other, me);
}

void GolemKingRock::OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me)
{
}

void GolemKingRock::OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me)
{
}
