#pragma once
#include "State.h"

using namespace sn;

class GolemKingArmRecover :
    public State
{
public:
	GolemKingArmRecover();
	~GolemKingArmRecover();

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

private:
	float endTime;
	float executionTime;
};

