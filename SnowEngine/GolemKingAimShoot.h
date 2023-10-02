#pragma once
#include "State.h"

using namespace sn;

class GolemKingAimShoot :
    public State
{
public:
	GolemKingAimShoot();
	~GolemKingAimShoot();

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

private:
	float endTime;
	float executionTime;
};

