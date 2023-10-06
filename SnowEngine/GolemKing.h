#pragma once
#include "Monster.h"

using namespace sn;

class GolemKing :
    public Monster
{
public:
    GolemKing();
    ~GolemKing();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

public:
    void CreateRocks();
    void CreateWave();
    void CreateArm();
    void CreateFist();

public:
    virtual void OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me);
    virtual void OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me);
    virtual void OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me);

private:
    std::vector<Vector3> rockPoses;
    float curTime;

    bool bossHPBarTrigger;
    bool deadTrigger;
};

