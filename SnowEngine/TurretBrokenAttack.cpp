#include "TurretBrokenAttack.h"
#include "Monster.h"
#include "snSceneManager.h"
#include "snDungeon.h"
#include "snGameObject.h"
#include "snTransform.h"
#include "snTime.h"
#include "snCollider2D.h"
#include <snAudioSource.h>
#include "snResources.h"

TurretBrokenAttack::TurretBrokenAttack()
	: State(MON_STATE::ATT)
	, time(0.f)
{
}

TurretBrokenAttack::~TurretBrokenAttack()
{
}

void TurretBrokenAttack::Update()
{
	//망치 슬라임 사운드 부분
	/*if (GetAI()->GetOwner()->GetName()== L"SlimeHermit" && time == 0.f) {
		AudioSource* as = GetAI()->GetOwner()->GetComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"golem_dungeon_slime_attack", L"..\\Resources\\Sound\\SoundEffect\\SlimeHermit\\golem_dungeon_slime_attack.wav"));
		as->Play();
		as->SetVolume(4);
		as->SetLoop(false);
	}*/

	time += Time::DeltaTime();

	GameObject* player = SceneManager::GetActiveScene()->GetPlayer();
	Transform* playerTr = player->GetComponent<Transform>();
	Vector3 playerPos = playerTr->GetPosition();

	Monster* mon = GetMonster();
	Transform* monTr = mon->GetComponent <Transform>();
	Vector3 monPos = monTr->GetPosition();

	Vector3 moveDir = playerPos - monPos;

	tMonInfo monInfo = GetMonster()->GetMonsterInfo();

	if (time >= monInfo.fAttTime - 0.1f) {
		time = 0.f;
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::TRACE);
	}
}

void TurretBrokenAttack::Enter()
{
}

void TurretBrokenAttack::Exit()
{
}
