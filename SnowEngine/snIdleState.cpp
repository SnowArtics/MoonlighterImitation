#include "snIdleState.h"
#include "..\Engine_SOURCE\snTime.h"
#include "..\Engine_SOURCE\snInput.h"
#include "InventoryManager.h"
#include "ShopManager.h"
#include <snRigidBody.h>

IdleState::IdleState()
	: PlayerState(PLAYER_STATE::IDLE)
{
}

IdleState::~IdleState()
{
}

void IdleState::Update()
{
	if (Input::GetKey(eKeyCode::A) && Input::GetKey(eKeyCode::D)) {
		return;
	}
	if (Input::GetKey(eKeyCode::W) && Input::GetKey(eKeyCode::S)) {
		return;
	}

	if (!InventoryManager::GetInvenActive() && ShopManager::GetShopInvenActive() != 2) {
		if (Input::GetKey(eKeyCode::A))
		{
			GetPlayerFSM()->ChangeState(PLAYER_STATE::MOVE);
			GetPlayerFSM()->SetDirection(PLAYER_DIR::LEFT);
		}
		if (Input::GetKey(eKeyCode::D))
		{
			GetPlayerFSM()->ChangeState(PLAYER_STATE::MOVE);
			GetPlayerFSM()->SetDirection(PLAYER_DIR::RIGHT);
		}
		if (Input::GetKey(eKeyCode::S))
		{
			GetPlayerFSM()->ChangeState(PLAYER_STATE::MOVE);
			GetPlayerFSM()->SetDirection(PLAYER_DIR::DOWN);
		}
		if (Input::GetKey(eKeyCode::W))
		{
			GetPlayerFSM()->ChangeState(PLAYER_STATE::MOVE);
			GetPlayerFSM()->SetDirection(PLAYER_DIR::UP);
		}

		if (Input::GetKeyDown(eKeyCode::SPACE) && GetPlayerFSM()->IsKeyPresent(PLAYER_STATE::ROLL) && ShopManager::GetShopInvenActive() != 2)
			GetPlayerFSM()->ChangeState(PLAYER_STATE::ROLL);

		if (Input::GetKeyDown(eKeyCode::J) && GetPlayerFSM()->GetWeaponType() == WEAPON_TYPE::SHORT_SWORD && GetPlayerFSM()->IsKeyPresent(PLAYER_STATE::ATTSWORD1) && ShopManager::GetShopInvenActive() != 2)
			GetPlayerFSM()->ChangeState(PLAYER_STATE::ATTSWORD1);
		if (Input::GetKeyDown(eKeyCode::J) && GetPlayerFSM()->GetWeaponType() == WEAPON_TYPE::BOW && ShopManager::GetShopInvenActive() != 2)
			GetPlayerFSM()->ChangeState(PLAYER_STATE::ATTBOW);
	}
}

void IdleState::Enter()
{
}

void IdleState::Exit()
{
}
