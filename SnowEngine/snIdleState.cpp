#include "snIdleState.h"
#include "snPlayerFSM.h"
#include "snTime.h"
#include "snInput.h"

	IdleState::IdleState()
		: PlayerState(PLAYER_STATE::IDLE)
	{
	}
	IdleState::~IdleState()
	{
	}
	void IdleState::Update()
	{
		

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			GetPlayerFSM()->ChangeState(PLAYER_STATE::MOVE);
			GetPlayerFSM()->SetDirection(PLAYER_DIR::LEFT);
		}
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			GetPlayerFSM()->ChangeState(PLAYER_STATE::MOVE);
			GetPlayerFSM()->SetDirection(PLAYER_DIR::RIGHT);
		}
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			GetPlayerFSM()->ChangeState(PLAYER_STATE::MOVE);
			GetPlayerFSM()->SetDirection(PLAYER_DIR::DOWN);
		}
		if (Input::GetKeyDown(eKeyCode::UP))
		{
			GetPlayerFSM()->ChangeState(PLAYER_STATE::MOVE);
			GetPlayerFSM()->SetDirection(PLAYER_DIR::UP);
		}

		if (Input::GetKey(eKeyCode::SPACE))
			GetPlayerFSM()->ChangeState(PLAYER_STATE::ROLL);		
	}
	void IdleState::Enter()
	{
	}
	void IdleState::Exit()
	{
	}


