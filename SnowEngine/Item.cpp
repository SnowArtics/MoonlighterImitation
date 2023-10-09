#include "Item.h"
#include "snTransform.h"
#include "snTime.h"
#include "snCollider2D.h"
#include "snSceneManager.h"

Item::Item(eItemType _itemType)
	: startTime(0.0f)
	, landingTime(1.f)
	, parabolaPeak(0.5f)
	, startPoint()
	, targetPoint()
{
	Transform* tr = GetComponent<Transform>();
	Vector3 pos = tr->GetPosition();
	tr->SetPosition(Vector3(pos.x, pos.y, pos.z - 1));
}

Item::~Item()
{
}

void Item::Initialize()
{
	sn::GameObject::Initialize();
}

void Item::Update()
{
	if (!(startTime > landingTime)) {
		startTime += Time::DeltaTime();
		Vector3 computedPos = ComputeParabolicMotion();
		GetComponent<Transform>()->SetPosition(Vector3(computedPos.x, computedPos.y,SceneManager::GetActiveScene()->GetPlayer()->GetComponent<Transform>()->GetPosition().z));
	}
	else if (startTime > landingTime) {
		sn::Collider2D* col = GetComponent<sn::Collider2D>();
		col->SetEnable(true);

		Transform* playerTr = SceneManager::GetActiveScene()->GetPlayer()->GetComponent<Transform>();
		Vector3 playerPos = playerTr->GetPosition();

		Transform* tr = GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		Vector3 direction = playerPos - pos;
		if (direction.Length() < 1.0f) {
			direction.Normalize();
			pos = pos + direction * 1.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
	}

	sn::GameObject::Update();
}

void Item::LateUpdate()
{
	sn::GameObject::LateUpdate();
}

void Item::Render()
{
	sn::GameObject::Render();
}

void Item::OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me)
{
	GameObject::OnCollisionEnter(other, me);

	if (other->GetName() == L"FisrtCollider") {
		SetState(eState::Dead);
	}
}

void Item::OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me)
{
}

void Item::OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me)
{
}

Vector3 Item::lerp(float alpha)
{
	return Vector3(startPoint.x + (targetPoint.x - startPoint.x) * alpha, startPoint.y + (targetPoint.y - startPoint.y) * alpha, targetPoint.z);
}

Vector3 Item::ComputeParabolicMotion()
{
	float alpha = startTime / landingTime;
	Vector3 midpoint = lerp(alpha);
	float vertical = (1 - 4 * std::pow(alpha - 0.5f, 2)) * parabolaPeak;
	return Vector3(midpoint.x, midpoint.y + vertical, midpoint.z);
}
