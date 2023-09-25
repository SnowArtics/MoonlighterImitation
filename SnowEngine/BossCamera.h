#pragma once
#include "snScript.h"

using namespace sn;

class BossCamera :
    public Script
{
public:
	BossCamera();
	~BossCamera();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	float curTime;
};

