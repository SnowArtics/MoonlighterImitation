#pragma once
#include "State.h"

using namespace sn;

class GolemKingAimCycle :
    public State
{
public:
	GolemKingAimCycle();
	~GolemKingAimCycle();

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

private:
	float endTime;
	float executionTime;
};

