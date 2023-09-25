#include "BossCamera.h"

#include "snTransform.h"
#include "snGameObject.h"
#include "snTime.h"
#include "snInput.h"
#include "snSceneManager.h"

BossCamera::BossCamera()
	: curTime(0.0f)
{
}

BossCamera::~BossCamera()
{
}

void BossCamera::Initialize()
{	
}

void BossCamera::Update()
{
	curTime += Time::DeltaTime();

	if (curTime > 5.f) {
		Vector3 playerPos = SceneManager::GetActiveScene()->GetPlayer()->GetComponent<Transform>()->GetPosition();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetPosition(Vector3(playerPos.x, playerPos.y, tr->GetPosition().z));
	}
}

void BossCamera::LateUpdate()
{
}

void BossCamera::Render()
{
}
