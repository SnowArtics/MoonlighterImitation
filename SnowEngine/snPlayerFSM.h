#pragma once

#include <map>
#include <snComponent.h>
#include "snPlayerState.h"

class GameObject;

namespace sn {
	enum class PLAYER_STATE {
		IDLE,
		MOVE,
		ROLL,
		DEAD,
	};

	class PlayerState; // Forward declaration

	class PlayerFSM : public Component
	{
	public:
		PlayerFSM();
		~PlayerFSM();

	public:
		virtual void Update();

	public:
		void AddState(PlayerState* _pState);
		PlayerState* GetState(PLAYER_STATE _state);

	private:
		std::map<PLAYER_STATE, PlayerState*> m_mapeState;
		GameObject* m_pOwner;
		PlayerState* curState;
	};
};