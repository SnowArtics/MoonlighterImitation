#pragma once
#include "snComponent.h"

using namespace sn;

class GameObject;

class PlayerHP :
    public Component
{
public:
	PlayerHP();
	PlayerHP(float _fullHP, float _realHP);
	~PlayerHP();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

public:
	void CreateHpBar();
	void PlayDamage(float _damage);

public:
	void SetRealHP(float _realHP) { realHP = _realHP; }
	void SetFullHP(float _fullHP) { fullHP = _fullHP; }

private:
	sn::GameObject* playerHPBarRed;
	sn::GameObject* playerHPBarWhite;
	sn::GameObject* playerHitScreen;

	float fakeHP;
	float realHP;
	float fullHP;

	float hitTime;
	float absoluteTime;
};

