#pragma once
#include "../Engine_SOURCE/State.h"

using namespace sn;

class MiniBossIdle :
	public State
{
public:
	MiniBossIdle();
	~MiniBossIdle();

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();
};

