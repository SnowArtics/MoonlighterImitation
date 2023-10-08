#include "GolemKingAimShoot.h"

#include "snTime.h"
#include "snSceneManager.h"
#include "Monster.h"
#include <snAudioSource.h>
#include "snResources.h"

GolemKingAimShoot::GolemKingAimShoot()
	:State(MON_STATE::GOLEMKING_AIM_SHOOT)
	, endTime(6.f)
	, executionTime(0.f)
{
}

GolemKingAimShoot::~GolemKingAimShoot()
{
}

void GolemKingAimShoot::Update()
{
	if (executionTime == 0.f) {
		AudioSource* as = GetAI()->GetOwner()->GetComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"golem_dungeon_king_golem_slimearm", L"..\\Resources\\Sound\\SoundEffect\\GolemKing\\golem_dungeon_king_golem_slimearm.wav"));
		as->Play();
		as->SetVolume(3);
		as->SetLoop(false);
	}

	executionTime += Time::DeltaTime();

	if (executionTime >= endTime) {
		executionTime = 0.f;
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_AIM_END);
	}
}

void GolemKingAimShoot::Enter()
{
}

void GolemKingAimShoot::Exit()
{
}
