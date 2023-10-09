#pragma once
#include "snGameObject.h"
#include "snEnums.h"

using namespace sn;

class InventorySquare :
    public sn::GameObject
{
public:
	InventorySquare();
	virtual ~InventorySquare();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

private:
	eItemType itemType;

};

