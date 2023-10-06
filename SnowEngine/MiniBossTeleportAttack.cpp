#include "MiniBossTeleportAttack.h"
#include "snTime.h"
#include "snSceneManager.h"
#include "Monster.h"
#include "snGameObject.h"
#include "snTransform.h"
#include <snAudioSource.h>
#include "snResources.h"

MiniBossTeleportAttack::MiniBossTeleportAttack()
	: State(MON_STATE::MINIBOSS_TELEPORT_ATTACK)
	, time(0.f)
{
}

MiniBossTeleportAttack::~MiniBossTeleportAttack()
{
}

void MiniBossTeleportAttack::Update()
{
	if (time == 0.f) {
		AudioSource* as = GetAI()->GetOwner()->GetComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"Miniboss_golemwarrior_sword_corrupted_finish", L"..\\Resources\\Sound\\SoundEffect\\GolemCorruptedMiniBoss\\Miniboss_golemwarrior_sword_corrupted_finish.wav"));
		as->Play();
		as->SetVolume(1);
		as->SetLoop(false);
	}

	time += Time::DeltaTime();	

	if (time >= 1.0f) {
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::MINIBOSS_TRACE);
		time = 0.f;
	}
}

void MiniBossTeleportAttack::Enter()
{
	Vector3 playerPos = SceneManager::GetActiveScene()->GetPlayer()->GetComponent<Transform>()->GetPosition();
	GetAI()->GetOwner()->GetComponent<Transform>()->SetPosition(playerPos);
}

void MiniBossTeleportAttack::Exit()
{
}
