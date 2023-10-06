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
#include "snPlayer.h"
#include "PlayerHP.h"

GolemKingArm::GolemKingArm()
	: curTime(0.f)
	, endTime(15.f)
	, changeAnimTrigger(false)
	, armAttackCount(0)
	, armDownTrigger(false)
	, desPos(Vector3(0.0f, 0.0f, 0.0f))
	, curPos(Vector3(0.0f, 0.0f, 0.0f))
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
	collider->SetSize(Vector2(0.2f, 0.4f));
	collider->SetEnable(false);
}

GolemKingArm::~GolemKingArm()
{
}

void GolemKingArm::Initialize()
{
	GameObject::Initialize();
}

void GolemKingArm::Update()
{
	if (owner->GetComponent<AI>()->GetCurStateName() == MON_STATE::GOLEMKING_DEATH) {
		SetState(eState::Dead);
	}

	curTime += Time::DeltaTime();

	Transform* tr = GetComponent<Transform>();

	int intTime = curTime;

	if ((curTime - (intTime/3*3)) > 1.6f && (curTime - (intTime / 3 * 3)) <= 1.8f) {
		sn::Collider2D* collider = GetComponent<sn::Collider2D>();
		collider->SetEnable(true);
	}
	else if ((curTime - (intTime / 3 * 3)) > 1.8f) {
		sn::Collider2D* collider = GetComponent<sn::Collider2D>();
		collider->SetEnable(false);
	}

	if ((intTime % 3) == 0 && !changeAnimTrigger) {
		Animator* at = GetComponent<Animator>();
		at->PlayAnimation(L"Rock_Shadow", true);
		tr->SetScale(Vector3(0.1f, 0.1f, 0.0f));
		changeAnimTrigger = true;
		armDownTrigger = false;
		Transform* playerTr = SceneManager::GetActiveScene()->GetPlayer()->GetComponent<Transform>();
		tr->SetPosition(playerTr->GetPosition());
	}
	else if((curTime - /*((curTime - intTime)+(armAttackCount*3))*/ (armAttackCount *3))<1.4f&&changeAnimTrigger){
		Vector3 scale = tr->GetScale();
		scale.x += Time::DeltaTime();
		scale.y += Time::DeltaTime();
		tr->SetScale(Vector3(scale.x, scale.y, scale.z));

		Transform* playerTr = SceneManager::GetActiveScene()->GetPlayer()->GetComponent<Transform>();
		tr->SetPosition(Vector3(playerTr->GetPosition().x, playerTr->GetPosition().y-0.2f, playerTr->GetPosition().z));
		desPos = Vector3(playerTr->GetPosition().x, playerTr->GetPosition().y, playerTr->GetPosition().z);
		curPos = desPos;
		curPos.y += 3.f;
	}
	else if ((curTime - (armAttackCount * 3)) >= 1.4f && changeAnimTrigger) {
		if (armDownTrigger == false) {
			Animator* at = GetComponent<Animator>();
			at->PlayAnimation(L"GolemKingArm", true);
			armDownTrigger = true;
		}

		curPos.y -= Time::DeltaTime() * 20.f;
		if (curPos.y <= desPos.y) {
			curPos = desPos;
			armAttackCount++;
			changeAnimTrigger = false;
		}
		tr->SetPosition(curPos);
	}

	if (curTime >= endTime) {
		SetState(eState::Dead);
	}

	GameObject::Update();
}

void GolemKingArm::LateUpdate()
{
	GameObject::LateUpdate();
}

void GolemKingArm::Render()
{
	GameObject::Render();
}

void GolemKingArm::OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me)
{
	GameObject::OnCollisionEnter(other, me);

	if (other->GetName() == L"FisrtCollider") {
		snPlayer* player = static_cast<snPlayer*>(other->GetOwner());
		float playerHP = player->GetHP();
		playerHP -= 30.f;
		player->SetHP(playerHP);
		PlayerHP* playerHPComponent = player->GetComponent<PlayerHP>();
		playerHPComponent->PlayDamage(30.f);
	}
}

void GolemKingArm::OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me)
{
}

void GolemKingArm::OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me)
{
}
