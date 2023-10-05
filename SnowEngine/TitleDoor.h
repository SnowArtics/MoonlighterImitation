#pragma once
#include "snScript.h"

using namespace sn;

class TitleDoor : public Script
{
public:
	TitleDoor();
	~TitleDoor();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	float startTime;
	float endTime;
	bool doorOpenTrigger;
	bool BGMTrigger;
	bool TextTrigger;
	float TextAlbedo;

	sn::GameObject* leftDoor;
	sn::GameObject* rightDoor;
	sn::GameObject* middleLine;
};

