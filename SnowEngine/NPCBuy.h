#pragma once
#include "State.h"
class NPCBuy :
    public State
{
public:
	NPCBuy();
	~NPCBuy();

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

private:
	float time;
	bool thinkAnimTrigger;
	int pos;
};

