#pragma once
#include "snScript.h"

using namespace sn;

class EntranceDoor :
    public Script
{
public:
	EntranceDoor();
	~EntranceDoor();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	virtual void OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me);
	virtual void OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me);
	virtual void OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me);

	void Init();

private:
	float time;
	char doorState; // 0 is close, 1 is cycle, 2 is open, 3 is enter

	sn::GameObject* enterUI;
};

