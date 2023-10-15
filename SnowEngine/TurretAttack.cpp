#include "TurretAttack.h"
#include "Monster.h"
#include "snSceneManager.h"
#include "snDungeon.h"
#include "snGameObject.h"
#include "snTransform.h"
#include "snTime.h"
#include "snCollider2D.h"
#include <snAudioSource.h>
#include "snResources.h"

TurretAttack::TurretAttack()
	: State(MON_STATE::ATT)
	, time(0.f)
{
}

TurretAttack::~TurretAttack()
{
}

void TurretAttack::Update()
{
	if (time == 0.f) {
		AudioSource* as = GetAI()->GetOwner()->GetComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"golem_turret_attack01", L"..\\Resources\\Sound\\SoundEffect\\GolemTurret\\golem_turret_attack01.wav"));
		as->Play();
		as->SetVolume(3);
		as->SetLoop(false);
	}

	time += Time::DeltaTime();

	sn::GameObject* player = SceneManager::GetActiveScene()->GetPlayer();
	Transform* playerTr = player->GetComponent<Transform>();
	Vector3 playerPos = playerTr->GetPosition();

	Monster* mon = GetMonster();
	Transform* monTr = mon->GetComponent <Transform>();
	Vector3 monPos = monTr->GetPosition();

	Vector3 moveDir = playerPos - monPos;

	tMonInfo monInfo = GetMonster()->GetMonsterInfo();

	if (time >= monInfo.fAttTime - 0.1f) {
		SceneManager::ChangeMonsterState(GetAI(), MON_STATE::TRACE);
		time = 0.f;
	}

	moveDir.Normalize();

	monPos += Time::DeltaTime() * moveDir * GetMonster()->GetInfo().fSpeed;

	monTr->SetPosition(monPos);
}

void TurretAttack::Enter()
{
}

void TurretAttack::Exit()
{
}
