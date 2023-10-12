#include "ObstacleCollider.h"

#include "snGameObject.h"
#include "snPlayer.h"
#include "snCollider2D.h"
#include "snRigidBody.h"

ObstacleCollider::ObstacleCollider()
{
	if (GetOwner()->GetComponent<sn::Collider2D>() == nullptr) {
		GetOwner()->AddComponent<sn::Collider2D>();
	}
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
	RigidBody* rb = other->GetOwner()->GetComponent<RigidBody>();
	Vector3 velocity = rb->GetVelocity();
	collisionObjects.insert(pair<UINT, Vector3>(other->GetColliderID(), velocity));
}

void ObstacleCollider::OnCollisionStay(sn::Collider2D* other)
{
	auto it = collisionObjects.find(other->GetColliderID());
}

void ObstacleCollider::OnCollisionExit(sn::Collider2D* other)
{
	collisionObjects.erase(other->GetColliderID());
}
