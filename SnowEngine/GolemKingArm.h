#pragma once
#include "snGameObject.h"

using namespace sn;

class GolemKingArm :
    public sn::GameObject
{
public:
    GolemKingArm();
    ~GolemKingArm();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

public:
    void SetEndTime(float _endTime) { endTime = _endTime; }

private:
    float curTime;
    float endTime;
    bool changeAnimTrigger;
};

