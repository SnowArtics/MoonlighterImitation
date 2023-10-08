#include "GolemKingAimEnd.h"

#include "snTime.h"
#include "snSceneManager.h"
#include "Monster.h"
#include <snAudioSource.h>
#include "snResources.h"

GolemKingAimEnd::GolemKingAimEnd()
	:State(MON_STATE::GOLEMKING_AIM_END)
	, endTime(3.2f)
	, executionTime(0.f)
{
}

GolemKingAimEnd::~GolemKingAimEnd()
{
}

void GolemKingAimEnd::Update()
{
	if (executionTime == 0.f) {
		AudioSource* as = GetAI()->GetOwner()->GetComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"golem_dungeon_king_golem_slimearm_end", L"..\\Resources\\Sound\\SoundEffect\\GolemKing\\golem_dungeon_king_golem_slimearm_end.wav"));
		as->Play();
		as->SetVolume(3);
		as->SetLoop(false);
	}

	executionTime += Time::DeltaTime();

	if (executionTime >= endTime) {
		executionTime = 0.f;
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_IDLE);
	}
}

void GolemKingAimEnd::Enter()
{
}

void GolemKingAimEnd::Exit()
{
}
