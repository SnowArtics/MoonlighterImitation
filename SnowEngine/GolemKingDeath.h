#pragma once
#include "State.h"

using namespace sn;

class GolemKingDeath :
	public State
{
public:
	GolemKingDeath();
	~GolemKingDeath();

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

private:
	float endTime;
	float executionTime;
};

