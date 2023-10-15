#pragma once
#include "snGameObject.h"
#include "snCollider2D.h"

using namespace sn;

class Shelf :
    public sn::GameObject
{
public:
	Shelf();
	virtual ~Shelf();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

	virtual void OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me);
	virtual void OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me);
	virtual void OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me);
};

