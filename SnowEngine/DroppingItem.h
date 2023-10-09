#pragma once
#include "snScript.h"
#include "snEnums.h"

class Item;

using namespace sn;

class DroppingItem :
    public Script
{
public:
	DroppingItem(std::vector<enums::eItemType> _eOwnItems);
	~DroppingItem();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	virtual void OnCollisionEnter(sn::Collider2D* other) {};
	virtual void OnCollisionStay(sn::Collider2D* other) {};
	virtual void OnCollisionExit(sn::Collider2D* other) {};

private:
	std::vector<enums::eItemType> eOwnItems;
	std::vector<Item*> pOwnItems;
};

