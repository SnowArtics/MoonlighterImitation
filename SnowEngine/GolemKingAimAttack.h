#pragma once
#include "State.h"

using namespace sn;

class GolemKingAimAttack :
	public State
{
public:
	GolemKingAimAttack();
	~GolemKingAimAttack();

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

private:
	float endTime;
	float executionTime;
};

