#pragma once
#include "snMath.h"

class Monster;

enum class MonType {
	GOLEM,
	SLIME,
	BABYSLIME,
	FYLINGREPAIRGOLEM,
};

class MonFactory
{
public:
	MonFactory() {};
	~MonFactory() {};

public:
	static Monster* CreateMonster(MonType _eType, sn::math::Vector2 _vPos);

	friend class Monster;
};
