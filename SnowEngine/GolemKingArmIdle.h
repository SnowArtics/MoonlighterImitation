#pragma once
#include "State.h"

using namespace sn;

class GolemKingArmIdle :
    public State
{
public:
	GolemKingArmIdle();
	~GolemKingArmIdle();

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

private:
	float endTime;
	float executionTime;
};

