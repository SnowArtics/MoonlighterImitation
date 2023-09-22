#pragma once
#include "State.h"

using namespace sn;

class GolemKingIdle :
    public State
{
public:
	GolemKingIdle();
	~GolemKingIdle();

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();
};

