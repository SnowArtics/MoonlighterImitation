#pragma once
#include "snGameObject.h"

using namespace sn;

class GolemKingRock :
    public sn::GameObject
{
public:
    GolemKingRock();
    virtual ~GolemKingRock();

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
    void SetDestinationPos(Vector3 _des) { desPos = _des; curPos = desPos; curPos.y = desPos.y + 3.f; }

    Vector3 GetDestinationPos() { return desPos; }

private:
    float endTime;
    float executionTime;

    Vector3 curPos;
    Vector3 desPos;

    bool rockTrigger;
};