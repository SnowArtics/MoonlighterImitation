#include "MiniBossSmash.h"
#include "Monster.h"
#include "snSceneManager.h"
#include "snDungeon.h"
#include "snGameObject.h"
#include "snTransform.h"
#include "snTime.h"
#include "snCollider2D.h"
#include "snGameObject.h"
#include <snAudioSource.h>
#include "snResources.h"

MiniBossSmash::MiniBossSmash()
	: State(MON_STATE::MINIBOSS_SMASH)
	, time(0.f)
{
}

MiniBossSmash::~MiniBossSmash()
{
}

void MiniBossSmash::Update()
{
	if (time == 0.f) {
		AudioSource* as = GetAI()->GetOwner()->GetComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"Miniboss_golemwarrior_maze", L"..\\Resources\\Sound\\SoundEffect\\GolemCorruptedMiniBoss\\Miniboss_golemwarrior_maze.wav"));
		as->Play();
		as->SetVolume(3);
		as->SetLoop(false);
	}

	time += Time::DeltaTime();

	tMonInfo monInfo = GetMonster()->GetMonsterInfo();

	if (time >= monInfo.fAttTime - 0.1f) {
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::MINIBOSS_TRACE);
		time = 0.f;
	}
}

void MiniBossSmash::Enter()
{
}

void MiniBossSmash::Exit()
{
}
