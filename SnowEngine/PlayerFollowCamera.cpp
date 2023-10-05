#include "PlayerFollowCamera.h"
#include "snSceneManager.h"
#include "snGameObject.h"
#include "snTransform.h"

using namespace sn;

PlayerFollowCamera::PlayerFollowCamera()
{
}

PlayerFollowCamera::~PlayerFollowCamera()
{
}

void PlayerFollowCamera::Initialize()
{
}

void PlayerFollowCamera::Update()
{
	Vector3 playerPos = SceneManager::GetActiveScene()->GetPlayer()->GetComponent<Transform>()->GetPosition();
	Transform* tr = GetOwner()->GetComponent<Transform>();
	tr->SetPosition(Vector3(playerPos.x, playerPos.y, tr->GetPosition().z));
}

void PlayerFollowCamera::LateUpdate()
{
}

void PlayerFollowCamera::Render()
{
}
