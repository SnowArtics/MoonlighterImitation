#pragma once
#include "snScript.h"

using namespace sn;

class PlayerFollowCamera :
    public sn::Script
{
public:
	PlayerFollowCamera();
	~PlayerFollowCamera();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
};

