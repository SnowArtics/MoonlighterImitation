#pragma once
#include "State.h"

using namespace sn;

class MiniBossTeleportAttack :
    public State
{
public:
	MiniBossTeleportAttack();
	~MiniBossTeleportAttack();

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

private:
	float time;
};

