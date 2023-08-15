#pragma once
#include "../Engine_SOURCE/snGameObject.h"

struct tMonInfo
{
    float      fSpeed;           // 속도
    float      fHP;              // 체력
    float      fRecogRange;      // 인지 범위
    float      fAttRange;        // 공격 범위
    float      fAtt;             // 공격력
};

class AI;

class Monster : public sn::GameObject
{
public:
    Monster();
    ~Monster();

public:
    virtual void Update();

public:
    float GetSpeed() { return m_tInfo.fSpeed; }
    void SetSpeed(float _f) { m_tInfo.fSpeed = _f; }
    const tMonInfo& GetInfo() { return m_tInfo; }

private:
    void SetMonInfo(const tMonInfo& _info) { m_tInfo = _info; }

private:
    tMonInfo    m_tInfo;
    AI* m_pAI;
};