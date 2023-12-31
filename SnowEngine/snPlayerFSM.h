#pragma once
#include "..\Engine_SOURCE\snComponent.h"

using namespace sn;

enum class PLAYER_STATE {
	IDLE,
	MOVE,
	ROLL,
	DEAD,
	ATTSWORD1,
	ATTSWORD2,
	ATTSWORD3,
	ATTBOW,
	END,
};

enum class PLAYER_DIR {
	UP,
	DOWN,
	RIGHT,
	LEFT,
	END,
};

enum class WEAPON_TYPE {
	SHORT_SWORD,
	BOW,
};

class PlayerState;

class PlayerFSM :
    public Component
{
public:
	PlayerFSM();
	~PlayerFSM();

public:
	virtual void Update();

public:
	void ChangeState(PLAYER_STATE _pState);
	void AddState(PlayerState* _pState);

	void SetOwner(sn::GameObject* _m_pOwner) { m_pOwner = _m_pOwner; }
	void SetDirection(PLAYER_DIR _dir) { curDir = _dir; }
	void SetWeaponType(WEAPON_TYPE _weaponType) { weaponType = _weaponType; }
	void SetCanMove(PLAYER_DIR _playerDir, bool _canMove);

	PlayerState* GetState(PLAYER_STATE _state);
	sn::GameObject* GetOwner() { return m_pOwner; }
	PLAYER_DIR GetDirection() { return curDir; }
	std::vector<PLAYER_DIR>& GetActionDir() { return actionDir; }
	WEAPON_TYPE GetWeaponType() { return weaponType; }
	bool GetCanMove(PLAYER_DIR _playerDir);
	bool IsKeyPresent(PLAYER_STATE _state) { if (m_mapeState.find(_state) == m_mapeState.end()) return false; else return true; }

private:
	std::map<PLAYER_STATE, PlayerState*>	m_mapeState;
	sn::GameObject* m_pOwner;
	PlayerState* curState;
	PLAYER_STATE							eCurState;
	PLAYER_STATE							ePrevState;

	PLAYER_DIR									curDir;
	PLAYER_DIR									prevDir;

	int										curAttState;
	int										prevAttState;

	WEAPON_TYPE								weaponType;

	std::vector<PLAYER_DIR>			actionDir;

	std::bitset<4> canMove;
};

