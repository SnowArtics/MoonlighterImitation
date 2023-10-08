#include "GolemKingAimAttack.h"

#include "snTime.h"
#include "snSceneManager.h"
#include "Monster.h"
#include <snAudioSource.h>
#include "snResources.h"
#include <random>

GolemKingAimAttack::GolemKingAimAttack()
	:State(MON_STATE::GOLEMKING_AIM_PREPARE)
	, endTime(1.6f)
	, executionTime(0.f)
{
}

GolemKingAimAttack::~GolemKingAimAttack()
{
}

void GolemKingAimAttack::Update()
{
	if (executionTime == 0.f) {
		AudioSource* as = GetAI()->GetOwner()->GetComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"golem_dungeon_king_golem_slimearm_prepare", L"..\\Resources\\Sound\\SoundEffect\\GolemKing\\golem_dungeon_king_golem_slimearm_prepare.wav"));
		as->Play();
		as->SetVolume(3);
		as->SetLoop(false);
	}

	executionTime += Time::DeltaTime();

	if (executionTime >= endTime) {
		executionTime = 0.f;
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_AIM_CYCLE);
	}
}

void GolemKingAimAttack::Enter()
{
}

void GolemKingAimAttack::Exit()
{
}
