#include "GolemKingFist.h"

#include "snTime.h"
#include "snMeshRenderer.h"
#include "snAnimator.h"
#include "snResources.h"
#include "snTexture.h"
#include "snCollider2D.h"
#include "snTransform.h"
#include "snSceneManager.h"
#include "snPlayer.h"
#include "PlayerHP.h"

float CalculateAngle(Vector3 from, Vector3 to) {
	float deltaX = to.x - from.x;
	float deltaY = to.y - from.y;
	return std::atan2(deltaY, deltaX) * 180.0f / PI;
}

GolemKingFist::GolemKingFist()
	: curTime(0.f)
	, endTime(11.f)
	, golemKingPos(Vector3(0.0f, 0.0f,0.0f))
	, fistAttackTrigger(true)
	, fistAttackAngle(0.f)
	, fistAttackAngleTrigger(true)
	, velocity(10.f)
	, acceleration(100.f)
{
	MeshRenderer* mr = AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

	std::shared_ptr<Texture> atlas
		= Resources::Load<Texture>(L"GolemKing_Fist", L"..\\Resources\\Texture\\Dungeon\\Enemy\\GolemKing\\Fist.png");
	Animator* at = AddComponent<Animator>();

	//at->Create(L"GolemKingFist", atlas, Vector2(654.f, 382.f), Vector2(-109.f, 45.f), 6);
	//at->Create(L"GolemKingFist", atlas, Vector2(545.f, 382.f), Vector2(109.f, 382.f), 1, 840.f, 0.1f, Vector2(0.0f,0.28f));
	at->Create(L"GolemKingFist01", atlas, Vector2(545.f, 382.f), Vector2(109.f, 382.f), 1, 840.f, 0.1f, Vector2(0.0f,0.28f));

	at->Create(L"GolemKingFistFinal01", atlas, Vector2(0.f, 382.f), Vector2(109.f, 382.f), 1, 840.f, 0.1f, Vector2(0.0f, 0.26f));

	at->Create(L"GolemKingFistRecover01", atlas, Vector2(0.f, 382.f), Vector2(109.f, 382.f), 6, 840.f, 0.1f, Vector2(0.0f, 0.26f));

	at->PlayAnimation(L"GolemKingFist01", true);

	sn::Collider2D* collider = AddComponent<sn::Collider2D>();
	collider->SetCenter(Vector2(0.0f, 0.0f));
	collider->SetSize(Vector2(0.05f, 1.0f));
	collider->SetEnable(false);

	Transform* tr = GetComponent<Transform>();
	tr->SetScale(Vector3(10.0f, 10.0f, 0.0f));
}

GolemKingFist::~GolemKingFist()
{
}

void GolemKingFist::Initialize()
{
	GameObject::Initialize();
}

void GolemKingFist::Update()
{
	curTime += Time::DeltaTime();

	if (curTime >= endTime) {
		SetState(eState::Dead);
	}

	if (curTime >= 10.4f) {
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector3(10.0f, 10.0f, 0.0f));

		Animator* at = GetComponent<Animator>();
		at->PlayAnimation(L"GolemKingFistRecover01", false);

		sn::Collider2D* collider = GetComponent<sn::Collider2D>();
		collider->SetEnable(false);
	}
	else if (curTime >= 6.f/* && fistAttackTrigger*/) {

		velocity += acceleration * Time::DeltaTime();

		if (fistAttackAngle > -19.f) {
			fistAttackAngleTrigger = false;
			velocity = 10.f;
		}
		else if (fistAttackAngle < -161.f) {
			fistAttackAngleTrigger = true;
			velocity = 10.f;
		}

		Revolution(fistAttackAngle);

		if (fistAttackAngleTrigger) {
			fistAttackAngle += velocity * Time::DeltaTime();
		}
		else {
			fistAttackAngle -= velocity * Time::DeltaTime();
		}

		GetComponent<Transform>()->SetRotation(0.0f, 0.0f, (fistAttackAngle+90.f)/50.f);

	}
	else if (curTime >= 5.f) {
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector3(10.0f, 20.0f, 0.0f));

		Animator* at = GetComponent<Animator>();
		at->PlayAnimation(L"GolemKingFistFinal01", false);

		sn::Collider2D* collider = GetComponent<sn::Collider2D>();
		collider->SetEnable(true);
	}
	else if (curTime < 5.f) {
		Transform* playerTr = SceneManager::GetActiveScene()->GetPlayer()->GetComponent<Transform>();
		Vector3 playerPos = playerTr->GetPosition();

		Transform* fistTr = GetComponent<Transform>();
		Vector3 fistPos = fistTr->GetPosition();

		float absAngle = CalculateAngle(fistPos, playerPos) + 90.f;

		fistTr->SetRotationByAngle(Vector3(0.0f, 0.0f, absAngle));

		RotateAround();
	}
	
	GameObject::Update();
}

void GolemKingFist::LateUpdate()
{
	GameObject::LateUpdate();
}

void GolemKingFist::Render()
{
	GameObject::Render();
}

void GolemKingFist::RotateAround() {
	Transform* playerTr = SceneManager::GetActiveScene()->GetPlayer()->GetComponent<Transform>();
	Vector3 playerPos = playerTr->GetPosition();

	//Vector3 dirPos = golemKingPos - playerPos;
	Vector3 dirPos = playerPos - golemKingPos;
	dirPos.Normalize();

	dirPos = dirPos * 0.1f + Vector3(golemKingPos.x-1.f,golemKingPos.y + 0.6f,golemKingPos.z);

	fistAttackAngle = CalculateAngle(Vector3(golemKingPos.x - 1.f, golemKingPos.y + 0.6f, golemKingPos.z), playerPos);
	
	Transform* tr = GetComponent<Transform>();
	tr->SetPosition(dirPos);
}

void GolemKingFist::Revolution(float _angle)
{
	float angleInRadians = XMConvertToRadians(_angle);

	float deltaX = 0.2f * cos(angleInRadians);
	float deltaY = 0.2f * sin(angleInRadians);

	Vector3 resultPoint = Vector3(golemKingPos.x - 1.f, golemKingPos.y + 0.8f, golemKingPos.z) + Vector3(deltaX, deltaY, 0.f);
	GetComponent<Transform>()->SetPosition(resultPoint);
}

void GolemKingFist::OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me)
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

void GolemKingFist::OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me)
{
}

void GolemKingFist::OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me)
{
}
