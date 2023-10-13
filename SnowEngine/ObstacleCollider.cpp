#include "ObstacleCollider.h"

#include "snGameObject.h"
#include "snPlayer.h"
#include "snCollider2D.h"
#include "snRigidBody.h"
#include "Monster.h"

ObstacleCollider::ObstacleCollider()
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

void ObstacleCollider::OnCollisionEnter(sn::Collider2D* other)
{
	//Player와 Monster만 충돌 계산
	if (!dynamic_cast<snPlayer*>(other->GetOwner()) && !dynamic_cast<Monster*>(other->GetOwner())) {
		return;
	}

	RigidBody* rb = other->GetOwner()->GetComponent<RigidBody>();
	if (rb == nullptr) {
		return;
	}
	Vector3 velocity = rb->GetVelocity();
	
	collisionObjects.insert(pair<UINT, Vector3>(other->GetColliderID(), velocity));
}

void ObstacleCollider::OnCollisionStay(sn::Collider2D* other)
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

void ObstacleCollider::OnCollisionExit(sn::Collider2D* other)
{
	collisionObjects.erase(other->GetColliderID());
}
