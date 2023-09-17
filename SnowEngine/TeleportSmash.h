#pragma once
#include "State.h"

using namespace sn;

class TeleportSmash :
    public State
{
public:
	TeleportSmash();
	~TeleportSmash();

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();
};

