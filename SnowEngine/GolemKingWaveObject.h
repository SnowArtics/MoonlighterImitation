#pragma once
#include "snGameObject.h"

using namespace sn;

class GolemKingWaveObject :
    public sn::GameObject
{
public:
    GolemKingWaveObject();
    ~GolemKingWaveObject();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

private:
    float curTime;
    float endTime;
};

