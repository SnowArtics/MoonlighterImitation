#pragma once
#include "snGameObject.h"
#include "snEnums.h"

using namespace sn;

class Item :
    public sn::GameObject
{
public:
	Item(eItemType _itemType);
	virtual ~Item();

	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

	virtual void OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me);
	virtual void OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me);
	virtual void OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me);

public:
	void SetStartTime(float _startTime) { startTime = _startTime; }
	void SetLandingTime(float _landingTime) { landingTime = _landingTime; }
	void SetParabolaPeak(float _parabolaPeak) { parabolaPeak = _parabolaPeak; }
	void SetStartPoint(Vector3 _startPoint) { startPoint = _startPoint; }
	void SetTargetPoint(Vector3 _targetPoint) { targetPoint = _targetPoint; }

public:
	Vector3 lerp(float alpha);
	Vector3 ComputeParabolicMotion();

private:
	float startTime;
	float landingTime;
	float parabolaPeak;
	Vector3 startPoint;
	Vector3 targetPoint;
};

