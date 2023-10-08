#include "GolemKingArmAttack.h"

#include "snTime.h"
#include "snSceneManager.h"
#include <random>
#include "Monster.h"
#include <snAudioSource.h>
#include "snResources.h"

GolemKingArmAttack::GolemKingArmAttack()
	:State(MON_STATE::GOLEMKING_ARM_LAUNCH)
	, endTime(2.0f)
	, executionTime(0.f)
	, soundTrigger(false)
{
}

GolemKingArmAttack::~GolemKingArmAttack()
{
}

void GolemKingArmAttack::Update()
{
	if (executionTime >= 1.5f && !soundTrigger) {
		AudioSource* as = GetAI()->GetOwner()->GetComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"golem_dungeon_king_golem_handcrash_prepare", L"..\\Resources\\Sound\\SoundEffect\\GolemKing\\golem_dungeon_king_golem_handcrash_prepare.wav"));
		as->Play();
		as->SetVolume(3);
		as->SetLoop(false);
		soundTrigger = true;
	}

	executionTime += Time::DeltaTime();

	if (executionTime >= endTime) {
		executionTime = 0.f;
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_ARM_IDLE);
		soundTrigger = false;
	}
}

void GolemKingArmAttack::Enter()
{
}

void GolemKingArmAttack::Exit()
{
}
