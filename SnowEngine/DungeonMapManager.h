#pragma once
#include "snGameObject.h"

#define SINGLE(type) public:\
						static type* GetInst()\
						{\
							static type mgr;\
							return &mgr;\
						}\
					private:\
						type();\
						~type();\

using namespace sn;

class DungeonMapManager
{
	SINGLE(DungeonMapManager);
public:
	void MakeCliffCollider(int _num, GameObject* _background);

};

