#pragma once
#include "snPlayerState.h"

namespace sn {

    class RollState :
        public PlayerState
    {
	public:
		RollState();
		~RollState();

	public:
		virtual void Update();
		virtual void Enter();
		virtual void Exit();
    };

}
