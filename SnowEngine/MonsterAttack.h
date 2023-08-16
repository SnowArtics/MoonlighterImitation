#pragma once
#include "State.h"
class MonsterAttack :
    public State
{
public:
	MonsterAttack();
	~MonsterAttack();

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();
};

