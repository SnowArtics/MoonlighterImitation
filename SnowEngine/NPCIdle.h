#pragma once
#include "State.h"
class NPCIdle :
    public State
{
public:
	NPCIdle();
	~NPCIdle();

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

private:
	float time;
};

