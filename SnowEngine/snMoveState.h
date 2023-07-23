#pragma once
#include "snPlayerState.h"

namespace sn {

    class MoveState :
        public PlayerState
    {
	public:
		MoveState();
		~MoveState();

	public:
		virtual void Update();
		virtual void Enter();
		virtual void Exit();
    };

}
