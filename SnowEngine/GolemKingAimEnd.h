#pragma once
#include "State.h"

using namespace sn;

class GolemKingAimEnd :
    public State
{
public:
	GolemKingAimEnd();
	~GolemKingAimEnd();

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

private:
	float endTime;
	float executionTime;
};

