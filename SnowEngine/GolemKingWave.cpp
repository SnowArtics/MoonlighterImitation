#include "GolemKingWave.h"

#include "snTime.h"
#include "snSceneManager.h"
#include "snGameObject.h"
#include "GolemKing.h"
#include "snCollider2D.h"
#include <snAudioSource.h>
#include "snResources.h"

GolemKingWave::GolemKingWave()
	:State(MON_STATE::GOLEMKING_WAVE)
	, endTime(2.4f)
	, executionTime(0.f)
	, colliderTrigger(true)
{
}

GolemKingWave::~GolemKingWave()
{
}

void GolemKingWave::Update()
{
	if (executionTime == 0.0f) {
		GolemKing* golemKing = static_cast<GolemKing*>(GetAI()->GetOwner());
		golemKing->CreateWave();
	}

	if (executionTime == 0.f) {
		AudioSource* as = GetAI()->GetOwner()->GetComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"golem_dungeon_king_golem_wave", L"..\\Resources\\Sound\\SoundEffect\\GolemKing\\golem_dungeon_king_golem_wave.wav"));
		as->Play();
		as->SetVolume(3);
		as->SetLoop(false);
	}

	executionTime += Time::DeltaTime();

	if (executionTime >= 1.6f && colliderTrigger) {
		GolemKing* golemKing = static_cast<GolemKing*>(GetAI()->GetOwner());
		(golemKing->GetComponents<sn::Collider2D>())[2]->SetEnable(true);
		std::wstring txt = (golemKing->GetComponents<sn::Collider2D>())[2]->GetName();
		colliderTrigger = false;
	}

	if (executionTime >= 1.8f && !colliderTrigger) {
		GolemKing* golemKing = static_cast<GolemKing*>(GetAI()->GetOwner());
		(golemKing->GetComponents<sn::Collider2D>())[2]->SetEnable(false);
	}

	if (executionTime > endTime) {
		colliderTrigger = true;
		executionTime = 0.f;
		GetAI()->ChangeState(MON_STATE::GOLEMKING_IDLE);
	}
}

void GolemKingWave::Enter()
{
}

void GolemKingWave::Exit()
{
}
