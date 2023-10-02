#pragma once
#include "snGameObject.h"

using namespace sn;

class GolemKingFist :
    public sn::GameObject
{
public:
    GolemKingFist();
    ~GolemKingFist();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

    virtual void OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me);
    virtual void OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me);
    virtual void OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me);

public:
    void RotateAround();
    void Revolution(float _angle);

public:
    void SetGolemKingPos(Vector3 _golemKingPos) { golemKingPos = _golemKingPos; }

    Vector3 GetGolemKingPos() { return golemKingPos; }

private:
    float curTime;
    float endTime;
    bool fistAttackTrigger;

    Vector3 golemKingPos;
    float fistAttackAngle;
    float fistAttackAngleTrigger;

    float velocity;
    float acceleration;
};

