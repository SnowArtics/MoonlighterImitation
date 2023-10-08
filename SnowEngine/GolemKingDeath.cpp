#include "GolemKingDeath.h"

#include "snTime.h"
#include "Monster.h"
#include "snTransform.h"
#include "snSceneManager.h"
#include <snAudioSource.h>
#include "snResources.h"

using namespace sn;

GolemKingDeath::GolemKingDeath()
	:State(MON_STATE::GOLEMKING_DEATH)
	, endTime(4.1f)
	, executionTime(0.f)
{
}

GolemKingDeath::~GolemKingDeath()
{
}

void GolemKingDeath::Update()
{
	if (executionTime == 0.f) {
		Transform *ownerTr = GetAI()->GetOwner()->GetComponent<Transform>();
		Vector3 ownerPos = ownerTr->GetPosition();

		ownerPos.y += -0.5f;

		ownerTr->SetPosition(ownerPos);
	}

	if (executionTime == 0.f) {
		AudioSource* as = GetAI()->GetOwner()->GetComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"golem_dungeon_king_golem_death", L"..\\Resources\\Sound\\SoundEffect\\GolemKing\\golem_dungeon_king_golem_death.wav"));
		as->Play();
		as->SetVolume(3);
		as->SetLoop(false);
	}

	executionTime += Time::DeltaTime();

	if (executionTime >= endTime) {
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_DEATH01);
		executionTime = 0.f;
	}
}

void GolemKingDeath::Enter()
{
}

void GolemKingDeath::Exit()
{
}
