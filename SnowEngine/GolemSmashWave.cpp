#include "GolemSmashWave.h"

#include "snGameObject.h"
#include "snTime.h"
#include "snPlayer.h"
#include "snSceneManager.h"
#include "MiniBossHPBar.h"
#include "PlayerHP.h"

using namespace sn;

GolemSmashWave::GolemSmashWave()
	: time(0.0f)
{
}

GolemSmashWave::~GolemSmashWave()
{
}

void GolemSmashWave::Initialize()
{
	GameObject::Initialize();
}

void GolemSmashWave::Update()
{
	time += Time::DeltaTime();

	if (time >= 10.f) {
		SetState(sn::GameObject::eState::Dead);
	}

	Vector3 scaleIncrease = Vector3(3.0f * Time::DeltaTime(), 3.0f * Time::DeltaTime(), 0.f);

	Transform* tr = GetComponent<Transform>();
	Vector3 pos = tr->GetPosition();
	Vector3 scale = tr->GetScale();


	tr->SetScale(scale + scaleIncrease);

	float cycleDistance = (scale.x + scaleIncrease.x) / 2.f;

	Transform* playerTr = SceneManager::GetActiveScene()->GetPlayer()->GetComponent<Transform>();
	Vector3 playerPos = playerTr->GetPosition();

	//Vector3 playerDir = playerPos - pos;
	float playerDistance = std::sqrt(std::pow(playerPos.x - pos.x, 2) + std::pow(playerPos.y - pos.y, 2));

	if (abs(playerDistance - cycleDistance) < 0.05f) {
		sn::Collider2D* playerCol = SceneManager::GetActiveScene()->GetPlayer()->GetComponent<sn::Collider2D>();
		if (playerCol->GetEnable() == true){
			OnCollisionEnter(playerCol);
		}
	}

	GameObject::Update();
}

void GolemSmashWave::LateUpdate()
{
	GameObject::LateUpdate();
}

void GolemSmashWave::Render()
{
	GameObject::Render();
}

void GolemSmashWave::OnCollisionEnter(sn::Collider2D* other)
{
	snPlayer* player = static_cast<snPlayer*>(other->GetOwner());
	float playerHP = player->GetHP();
	playerHP -= 30.f;
	player->SetHP(playerHP);
	PlayerHP* playerHPComponent = player->GetComponent<PlayerHP>();
	playerHPComponent->PlayDamage(30.f);
}

void GolemSmashWave::OnCollisionStay(sn::Collider2D* other)
{
}

void GolemSmashWave::OnCollisionExit(sn::Collider2D* other)
{
}
