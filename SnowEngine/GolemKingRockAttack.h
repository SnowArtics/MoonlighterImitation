#pragma once
#include "State.h"

using namespace sn;

class GolemKingRockAttack :
    public State
{
public:
	GolemKingRockAttack();
	~GolemKingRockAttack();

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

private:
	float endTime;
	float executionTime;
	bool colliderTrigger;
};

