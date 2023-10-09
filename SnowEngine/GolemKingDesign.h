#pragma once
#include "Item.h"

using namespace sn;

class GolemKingDesign :
    public Item
{
public:
	GolemKingDesign();
	virtual ~GolemKingDesign();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

	virtual void OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me);
	virtual void OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me);
	virtual void OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me);
};

