#include "ObstacleCollider.h"

#include "snGameObject.h"
#include "snPlayer.h"
#include "snCollider2D.h"
#include "snRigidBody.h"
#include "Monster.h"
#include "ShopManager.h"

ObstacleCollider::ObstacleCollider()
{
}

ObstacleCollider::ObstacleCollider(std::wstring _colName)
{
}

ObstacleCollider::~ObstacleCollider()
{
}

void ObstacleCollider::Initialize()
{
}

void ObstacleCollider::Update()
{
}

void ObstacleCollider::LateUpdate()
{
}

void ObstacleCollider::Render()
{
}

void ObstacleCollider::OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me)
{
	//Player와 Monster만 충돌 계산
	if (!dynamic_cast<snPlayer*>(other->GetOwner()) && !dynamic_cast<Monster*>(other->GetOwner())) {
		return;
	}

	ShopManager::SetShopInvenActive(1);

	if (!(GetOwner()->GetComponent<sn::Collider2D>()->GetColliderID() == me->GetColliderID()))
		return;


	RigidBody* rb = other->GetOwner()->GetComponent<RigidBody>();
	if (rb == nullptr) {
		return;
	}
	Vector3 velocity = rb->GetVelocity();

	if (velocity.x != 0.0f && velocity.y != 0.f) {//대각선으로 해당 오브젝트에 접촉할때,
		Vector3 otherPos = other->GetOwner()->GetComponent<Transform>()->GetPosition();
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		Vector3 posDirection = otherPos - pos;

		sn::Collider2D* otherCol = other->GetOwner()->GetComponent<sn::Collider2D>();
		Vector3 otherColPos = otherCol->GetPos();
		Vector2 otherColSize = otherCol->GetSize();

		Vector3 otherRightTop = Vector3(otherColPos.x + otherColSize.x / 2, otherColPos.y + otherColSize.y / 2, otherColPos.z);
		Vector3 otherLeftTop = Vector3(otherColPos.x - otherColSize.x / 2, otherColPos.y + otherColSize.y / 2, otherColPos.z);
		Vector3 otherLeftBottom = Vector3(otherColPos.x - otherColSize.x / 2, otherColPos.y - otherColSize.y / 2, otherColPos.z);
		Vector3 otherRightBottom = Vector3(otherColPos.x + otherColSize.x / 2, otherColPos.y - otherColSize.y / 2, otherColPos.z);

		sn::Collider2D* col = GetOwner()->GetComponent<sn::Collider2D>();
		Vector3 colPos = col->GetPos();
		Vector2 colSize = col->GetSize();

		Vector3 rightTop = Vector3(colPos.x + colSize.x / 2, colPos.y + colSize.y / 2, colPos.z);
		Vector3 leftTop = Vector3(colPos.x - colSize.x / 2, colPos.y + colSize.y / 2, colPos.z);
		Vector3 leftBottom = Vector3(colPos.x - colSize.x / 2, colPos.y - colSize.y / 2, colPos.z);
		Vector3 rightBottom = Vector3(colPos.x + colSize.x / 2, colPos.y - colSize.y / 2, colPos.z);

		if (posDirection.x >= 0.0f && posDirection.y >= 0.0f) { //1사분면
			float xGap = abs(otherLeftBottom.x - rightTop.x);
			float yGap = abs(otherLeftBottom.y - rightTop.y);

			if (xGap>=yGap) {
				velocity.x = 0.0f;
			}
			else {
				velocity.y = 0.0f;
			}
		}
		else if (posDirection.x < 0.0f && posDirection.y >= 0.0f) { //2사분면
			float xGap = abs(otherRightBottom.x - leftTop.x);
			float yGap = abs(otherRightBottom.y - leftTop.y);

			if (xGap >= yGap) {
				velocity.x = 0.0f;
			}
			else {
				velocity.y = 0.0f;
			}
		}
		else if (posDirection.x < 0.0f && posDirection.y < 0.0f) { //3사분면
			float xGap = abs(otherRightTop.x - leftBottom.x);
			float yGap = abs(otherRightTop.y - leftBottom.y);

			if (xGap >= yGap) {
				velocity.x = 0.0f;
			}
			else {
				velocity.y = 0.0f;
			}
		}
		else if (posDirection.x >= 0.0f && posDirection.y < 0.0f) { //4사분면
			float xGap = abs(otherLeftTop.x - rightBottom.x);
			float yGap = abs(otherLeftTop.y - rightBottom.y);

			if (xGap >= yGap) {
				velocity.x = 0.0f;
			}
			else {
				velocity.y = 0.0f;
			}
		}
	}
	
	collisionObjects.insert(pair<UINT, Vector3>(other->GetColliderID(), velocity));
}

void ObstacleCollider::OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me)
{
	auto it = collisionObjects.find(other->GetColliderID());
	if (it == collisionObjects.end())
		return;

	RigidBody* rb = other->GetOwner()->GetComponent<RigidBody>();
	Vector3 velocity = rb->GetVelocity();
	
	if (it->second.x < 0.0f) {
		if(velocity.x <0.0f)
			rb->SetVelocity(Vector3(velocity.x + velocity.x * -1.f, velocity.y, velocity.z));
	}
	if (it->second.x > 0.0f) {
		if (velocity.x > 0.0f)
			rb->SetVelocity(Vector3(velocity.x + velocity.x * -1.f, velocity.y, velocity.z));
	}
	if (it->second.y < 0.0f) {
		if (velocity.y < 0.0f)
			rb->SetVelocity(Vector3(velocity.x, velocity.y + velocity.y * -1.f, velocity.z));
	}
	if (it->second.y > 0.0f) {
		if (velocity.y > 0.0f)
			rb->SetVelocity(Vector3(velocity.x, velocity.y + velocity.y * -1.f, velocity.z));
	}
}

void ObstacleCollider::OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me)
{
	//Player와 Monster만 충돌 계산
	if (!dynamic_cast<snPlayer*>(other->GetOwner()) && !dynamic_cast<Monster*>(other->GetOwner())) {
		return;
	}

	ShopManager::SetShopInvenActive(0);
	collisionObjects.erase(other->GetColliderID());
}
