#pragma once
#include "State.h"

using namespace sn;

class GolemKingDeath01 :
	public State
{
public:
	GolemKingDeath01();
	~GolemKingDeath01();

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

private:
	float endTime;
	float executionTime;
};

