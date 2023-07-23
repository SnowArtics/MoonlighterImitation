#include "snPlayerState.h"

#include "snPlayerFSM.h"

namespace sn
{
	PlayerState::PlayerState(PLAYER_STATE _state)
		: state(_state)
		, playerFSM(nullptr)
	{
	}
	PlayerState::~PlayerState()
	{
	}
}