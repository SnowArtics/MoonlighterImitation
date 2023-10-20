#pragma once
#include "State.h"
class NPCMove :
    public State
{
public:
	NPCMove();
	~NPCMove();

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();
};

