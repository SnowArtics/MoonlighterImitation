#pragma once
#include "State.h"

using namespace sn;

class MiniBossSmash :
    public State
{
public:
	MiniBossSmash();
	~MiniBossSmash();

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

private:
	float time;
};

