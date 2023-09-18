#pragma once
#include "State.h"

using namespace sn;

class MiniBossAttack :
    public State
{
public:
	MiniBossAttack();
	~MiniBossAttack();

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

private:
	float time;
};

