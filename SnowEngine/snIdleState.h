#pragma once
#include "snPlayerState.h"

namespace sn {
	class IdleState : public PlayerState
	{
	public:
		IdleState();
		~IdleState();

	public:
		virtual void Update();
		virtual void Enter();
		virtual void Exit();

	};	
}

