#pragma once
#include "snGameObject.h"
#include "AI.h"

using namespace sn;

class Projectile :
    public GameObject
{
public:
    Projectile();
    ~Projectile();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

public:
    virtual void OnCollisionEnter(sn::Collider2D* other);
    virtual void OnCollisionStay(sn::Collider2D* other);
    virtual void OnCollisionExit(sn::Collider2D* other);

public:
    void SetDir(MonDir _dir) { dir = _dir; }
    void SetSpeed(float _speed) { speed = _speed; }

private:
    MonDir dir;
    float speed;
    bool dead;
    float deadTime;
};

