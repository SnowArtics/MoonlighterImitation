#include "GolemKingUp.h"

#include "snTime.h"
#include "snSceneManager.h"
#include <snAudioSource.h>
#include "snResources.h"
#include "Monster.h"

GolemKingUp::GolemKingUp()
	:State(MON_STATE::GOLEMKING_UP)
	, endTime(3.2f)
	, executionTime(0.f)
{
}

GolemKingUp::~GolemKingUp()
{	
}

void GolemKingUp::Update()
{
	if (executionTime == 0.f) {
		AudioSource* as = GetAI()->GetOwner()->GetComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"golem_dungeon_king_golem_awake", L"..\\Resources\\Sound\\SoundEffect\\GolemKing\\golem_dungeon_king_golem_awake.wav"));
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

void GolemKingUp::Enter()
{
}

void GolemKingUp::Exit()
{
}
