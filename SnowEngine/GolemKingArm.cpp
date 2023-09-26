#include "GolemKingArm.h"

#include "snTime.h"
#include "snMeshRenderer.h"
#include "snAnimator.h"
#include "snResources.h"
#include "snTexture.h"
#include "snCollider2D.h"
#include "snTransform.h"
#include "snSceneManager.h"

#include <random>

GolemKingArm::GolemKingArm()
	: curTime(0.f)
	, endTime(15.f)
	, changeAnimTrigger(true)
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
		= Resources::Load<Texture>(L"GolemKingArm_Shadow", L"..\\Resources\\Texture\\Dungeon\\Enemy\\GolemKing\\Boss1_Punch_Shadow.png");
	Animator* at = AddComponent<Animator>();

	at->Create(L"Rock_Shadow", atlas, Vector2(0.0f, 0.0f), Vector2(64.f, 45.f), 1);

	atlas = Resources::Load<Texture>(L"GolemKingArm", L"..\\Resources\\Texture\\Dungeon\\Enemy\\GolemKing\\hand.png");
	at->Create(L"GolemKingArm", atlas, Vector2(0.0f, 0.0f), Vector2(120.f, 120.f), 19);

	at->PlayAnimation(L"Rock_Shadow", true);

	sn::Collider2D* collider = AddComponent<sn::Collider2D>();
	collider->SetCenter(Vector2(0.0f, 0.0f));
	collider->SetEnable(false);
}

GolemKingArm::~GolemKingArm()
{
}

void GolemKingArm::Initialize()
{
}

void GolemKingArm::Update()
{
	curTime += Time::DeltaTime();

	Transform* tr = GetComponent<Transform>();

	int intTime = curTime;
	if ((intTime % 3) == 0 && !changeAnimTrigger) {
		Animator* at = AddComponent<Animator>();
		at->PlayAnimation(L"Rock_Shadow", true);
		tr->SetScale(Vector3(0.1f, 0.1f, 0.0f));
		changeAnimTrigger = true;
		Transform* playerTr = SceneManager::GetActiveScene()->GetPlayer()->GetComponent<Transform>();
		tr->SetPosition(playerTr->GetPosition());
	}
	else if((curTime - intTime)<1.4f){
		Vector3 scale = tr->GetScale();
		scale.x += Time::DeltaTime();
		scale.y += Time::DeltaTime();
		tr->SetScale(Vector3(scale.x, scale.y, scale.z));

		Transform* playerTr = SceneManager::GetActiveScene()->GetPlayer()->GetComponent<Transform>();
		tr->SetPosition(playerTr->GetPosition());
	}
	else if ((curTime - intTime) >= 1.4f && changeAnimTrigger) {
		Animator* at = AddComponent<Animator>();
		at->PlayAnimation(L"GolemKingArm", true);
		changeAnimTrigger = false;
	}

	if (curTime >= endTime) {
		SetState(eState::Dead);
	}
}

void GolemKingArm::LateUpdate()
{
}

void GolemKingArm::Render()
{
}
