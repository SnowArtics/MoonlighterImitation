#pragma once
#include "State.h"

using namespace sn;

class GolemKingUp :
    public State
{
public:
	GolemKingUp();
	~GolemKingUp();

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

private:
	float endTime;
	float executionTime;
};

