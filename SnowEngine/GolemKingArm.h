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

    virtual void OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me);
    virtual void OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me);
    virtual void OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me);

public:
    void SetEndTime(float _endTime) { endTime = _endTime; }
    void SetOwner(GameObject* _owner) { owner = _owner; }

private:
    float curTime;
    float endTime;
    bool changeAnimTrigger;
    bool armDownTrigger;
    int armAttackCount;

    Vector3 curPos;
    Vector3 desPos;

    GameObject* owner;
};

