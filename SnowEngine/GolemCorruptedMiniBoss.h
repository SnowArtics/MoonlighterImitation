#pragma once
#include "Monster.h"

using namespace sn;

class GolemCorruptedMiniBoss : public Monster
{
public:
    GolemCorruptedMiniBoss();
    ~GolemCorruptedMiniBoss();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

public:
    virtual void OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me);
    virtual void OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me);
    virtual void OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me);

public:
    void CreateWave(Vector3 _transform);

private:
    float firstColliderAttTime;
    float secondColliderAttTime;
    float waveCreateTime;
    Vector3 waveCreatePos;
};

