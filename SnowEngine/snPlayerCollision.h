#pragma once
#include "snScript.h"

using namespace sn;

class PlayerCollision :
    public Script
{
public:
	PlayerCollision();
	~PlayerCollision();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	virtual void OnCollisionEnter(sn::Collider2D* other);
	virtual void OnCollisionStay(sn::Collider2D* other);
	virtual void OnCollisionExit(sn::Collider2D* other);
};

