#include "GolemKingFist.h"

#include "snTime.h"
#include "snMeshRenderer.h"
#include "snAnimator.h"
#include "snResources.h"
#include "snTexture.h"
#include "snCollider2D.h"
#include "snTransform.h"
#include "snSceneManager.h"

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
{
	MeshRenderer* mr = AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

	std::shared_ptr<Texture> atlas
		= Resources::Load<Texture>(L"GolemKing_Fist", L"..\\Resources\\Texture\\Dungeon\\Enemy\\GolemKing\\Fist.png");
	Animator* at = AddComponent<Animator>();

	//at->Create(L"GolemKingFist", atlas, Vector2(654.f, 382.f), Vector2(-109.f, 45.f), 6);
	//at->Create(L"GolemKingFist", atlas, Vector2(545.f, 382.f), Vector2(109.f, 382.f), 1, 840.f, 0.1f, Vector2(0.0f,0.28f));
	at->Create(L"GolemKingFist01", atlas, Vector2(0.f, 382.f), Vector2(109.f, 382.f), 1, 840.f, 0.1f, Vector2(0.0f,0.28f));

	at->Create(L"GolemKingFistFinal01", atlas, Vector2(0.f, 382.f), Vector2(109.f, 382.f), 1, 840.f, 0.1f, Vector2(0.0f, 0.26f));

	at->PlayAnimation(L"GolemKingFist01", true);

	sn::Collider2D* collider = AddComponent<sn::Collider2D>();
	collider->SetCenter(Vector2(0.0f, 0.0f));
	collider->SetSize(Vector2(0.05f, 1.0f));
	collider->SetEnable(true);

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

	if (curTime >= 5.f/* && fistAttackTrigger*/) {
		fistAttackTrigger = false;
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector3(10.0f, 20.0f, 0.0f));

		Animator* at = GetComponent<Animator>();
		at->PlayAnimation(L"GolemKingFistFinal01", true);

		if (fistAttackAngle > -19.f) {
			fistAttackAngleTrigger = false;
		}
		else if (fistAttackAngle < -161.f) {
			fistAttackAngleTrigger = true;
		}

		Revolution(fistAttackAngle);

		if (fistAttackAngleTrigger) {
			fistAttackAngle += 100.0f * Time::DeltaTime();
		}
		else {
			fistAttackAngle -= 100.0f * Time::DeltaTime();
		}

		GetComponent<Transform>()->SetRotation(0.0f, 0.0f, (fistAttackAngle+90.f)/50.f);

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

	fistAttackAngle = CalculateAngle(Vector3(golemKingPos.x - 1.f, golemKingPos.y + 0.9f, golemKingPos.z), dirPos);

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
}

void GolemKingFist::OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me)
{
}

void GolemKingFist::OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me)
{
}
