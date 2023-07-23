#include "snPlayerFSM.h"
#include <map>

#include "snPlayerState.h"

namespace sn {
	PlayerFSM::PlayerFSM()
		:Component(eComponentType::FSM)
		, m_pOwner(nullptr)
		, curState(nullptr)
	{
	}
	PlayerFSM::~PlayerFSM()
	{
		for (auto it = m_mapeState.begin(); it != m_mapeState.end();) {
			it = m_mapeState.erase(it);			
		}
	}
	void PlayerFSM::Update()
	{
		curState->Update();
	}

	void PlayerFSM::AddState(PlayerState* _pState)
	{
		PlayerState* pState = GetState(_pState->GetState());
		if (pState != nullptr)
			return;

		// Implement AddState function
		m_mapeState.insert(std::make_pair(_pState->GetState(), _pState));
		_pState->SetPlayerFSM(this);
	}

	PlayerState* PlayerFSM::GetState(PLAYER_STATE _state)
	{
		auto state = m_mapeState.find(_state);
		if (state == m_mapeState.end())
			return nullptr;

		return state->second;
	}

}