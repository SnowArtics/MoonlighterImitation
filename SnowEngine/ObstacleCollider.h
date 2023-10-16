#pragma once
#include "snScript.h"

using namespace sn;
using namespace std;

class ObstacleCollider :
    public Script
{
public:
	ObstacleCollider();
	ObstacleCollider(std::wstring _colName);
	~ObstacleCollider();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	virtual void OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me);
	virtual void OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me);
	virtual void OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me);

private:
	std::map<UINT, Vector3> collisionObjects;
};

