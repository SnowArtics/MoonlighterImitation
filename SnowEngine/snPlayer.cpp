#include "snPlayer.h"

#include "Monster.h"
#include "snRigidBody.h"
#include "snTransform.h"

using namespace sn;

snPlayer::snPlayer()
{
}

snPlayer::~snPlayer()
{
}

void snPlayer::Initialize()
{
	GameObject::Initialize();
}

void snPlayer::Update()
{
	GameObject::Update();
}

void snPlayer::LateUpdate()
{
	GameObject::LateUpdate();
}

void snPlayer::Render()
{
	GameObject::Render();
}

void snPlayer::OnCollisionEnter(sn::Collider2D* other)
{
	
}

void snPlayer::OnCollisionStay(sn::Collider2D* other)
{
}

void snPlayer::OnCollisionExit(sn::Collider2D* other)
{
}
