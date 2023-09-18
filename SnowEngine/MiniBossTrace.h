#pragma once
#include "State.h"

using namespace sn;

class MiniBossTrace :
	public State
{
public:
	MiniBossTrace();
	~MiniBossTrace();

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

private:
	float time;
	float delayTime;
};

