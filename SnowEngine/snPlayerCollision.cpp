#include "snPlayerCollision.h"
#include "snGameObject.h"
#include "snPlayerFSM.h"
#include "snCollider2D.h"

using namespace sn;

PlayerCollision::PlayerCollision()
{
}

PlayerCollision::~PlayerCollision()
{
}

void PlayerCollision::Initialize()
{
}

void PlayerCollision::Update()
{
}

void PlayerCollision::LateUpdate()
{
}

void PlayerCollision::Render()
{
}

void PlayerCollision::OnCollisionEnter(sn::Collider2D* other)
{
	PlayerFSM* playerFSM = GetOwner()->GetComponent<PlayerFSM>();

	std::wstring otherName = other->GetName();

	if (otherName == L"WallUpCollider") {
		playerFSM->SetCanMove(PLAYER_DIR::UP, false);
	}
	else if (otherName == L"WallDownCollider") {
		playerFSM->SetCanMove(PLAYER_DIR::DOWN, false);
	}
	else if (otherName == L"WallLeftCollider") {
		playerFSM->SetCanMove(PLAYER_DIR::LEFT, false);
	}
	else if (otherName == L"WallRightCollider") {
		playerFSM->SetCanMove(PLAYER_DIR::RIGHT, false);
	}
}

void PlayerCollision::OnCollisionStay(sn::Collider2D* other)
{
}

void PlayerCollision::OnCollisionExit(sn::Collider2D* other)
{
	PlayerFSM* playerFSM = GetOwner()->GetComponent<PlayerFSM>();

	std::wstring otherName = other->GetName();

	if (otherName == L"WallUpCollider") {
		playerFSM->SetCanMove(PLAYER_DIR::UP, true);
	}
	else if (otherName == L"WallDownCollider") {
		playerFSM->SetCanMove(PLAYER_DIR::DOWN, true);
	}
	else if (otherName == L"WallLeftCollider") {
		playerFSM->SetCanMove(PLAYER_DIR::LEFT, true);
	}
	else if (otherName == L"WallRightCollider") {
		playerFSM->SetCanMove(PLAYER_DIR::RIGHT, true);
	}
}
