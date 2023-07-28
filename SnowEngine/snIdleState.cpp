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

		if (Input::GetKey(eKeyCode::SPACE))
			GetPlayerFSM()->ChangeState(PLAYER_STATE::ROLL);		
	}
	void IdleState::Enter()
	{
	}
	void IdleState::Exit()
	{
	}


