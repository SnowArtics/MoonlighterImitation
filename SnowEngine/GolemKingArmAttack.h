#pragma once
#include "State.h"

using namespace sn;

class GolemKingArmAttack :
	public State
{
public:
	GolemKingArmAttack();
	~GolemKingArmAttack();

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

private:
	float endTime;
	float executionTime;
	bool soundTrigger;
};

