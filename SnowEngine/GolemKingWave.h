#pragma once
#include "State.h"

using namespace sn;

class GolemKingWave :
    public State
{
public:
	GolemKingWave();
	~GolemKingWave();

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

private:
	float endTime;
	float executionTime;
};

