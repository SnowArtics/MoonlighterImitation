#pragma once
#include "../Engine_SOURCE/snScript.h"

enum class MON_STATE {
	IDLE,//대기
	WALK, //걷기
	TRACE,//쫓기
	ATT,	//가까운 상대 공격
	TARGET_ATT,// 지정한 타겟공격
	DEAD,//사망
	END,
};

class Monster;
class State;

class AI : public sn::Script
{
public:
	AI();
	~AI();

public:
	virtual void Update();

public:
	void AddState(State* _pState);
	State* GetState(MON_STATE _eState);
	void SetCurState(MON_STATE _eState);

	void ChangeState(MON_STATE _eNextState);

	Monster* GetOwner() { return m_pOwner; }

private:
	std::map<MON_STATE, State*>	m_mapState;
	State* m_pCurState;
	Monster* m_pOwner;

	friend class Monster;
};