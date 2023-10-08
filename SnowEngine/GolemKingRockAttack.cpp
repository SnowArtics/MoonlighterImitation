#include "GolemKingRockAttack.h"

#include "snTime.h"
#include "snSceneManager.h"

#include "snGameObject.h"
#include "GolemKing.h"
#include "snCollider2D.h"

#include <random>

#include <snAudioSource.h>
#include "snResources.h"

GolemKingRockAttack::GolemKingRockAttack()
	:State(MON_STATE::GOLEMKING_ROCK_ATTACK)
	, endTime(4.3f)
	, executionTime(0.f)
	, colliderTrigger(true)
	, soundTrigger(false)
{
}

GolemKingRockAttack::~GolemKingRockAttack()
{
}

void GolemKingRockAttack::Update()
{
	if (executionTime >= 0.0f && !soundTrigger) {
		AudioSource* as = GetAI()->GetOwner()->GetComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"golem_dungeon_king_golem_avalanch", L"..\\Resources\\Sound\\SoundEffect\\GolemKing\\golem_dungeon_king_golem_avalanch.wav"));
		as->Play();
		as->SetVolume(3);
		as->SetLoop(false);

		soundTrigger = true;
	}

	executionTime += Time::DeltaTime();

	if (executionTime > 1.5f && colliderTrigger)
	{
		GolemKing* golemKing = static_cast<GolemKing*>(GetAI()->GetOwner());
		golemKing->CreateRocks();
		(golemKing->GetComponents<sn::Collider2D>())[1]->SetEnable(true);	

		colliderTrigger = false;
	}

	if (executionTime > 2.f && !colliderTrigger) {
		(static_cast<GolemKing*>(GetAI()->GetOwner())->GetComponents<sn::Collider2D>())[1]->SetEnable(false);
	}

	if (executionTime >= endTime) {
		colliderTrigger = true;
		executionTime = 0.f;
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_IDLE);
	}
}

void GolemKingRockAttack::Enter()
{
}

void GolemKingRockAttack::Exit()
{
}
