#include "MonsterTrace.h"
#include "Monster.h"
#include "snSceneManager.h"
#include "snDungeon.h"
#include "snGameObject.h"
#include "snTransform.h"
#include "snTime.h"
#include <snAudioSource.h>
#include "snResources.h"

using namespace sn;

MonsterTrace::MonsterTrace()
	: State(MON_STATE::TRACE)
	, time(0.f)
	, delayTime(0.f)
{
}

MonsterTrace::~MonsterTrace()
{
}

void MonsterTrace::Update()
{
	if (GetAI()->GetOwner()->GetName() == L"Golem Warrior" && time == 0.f) {
		AudioSource* as = GetAI()->GetOwner()->GetComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"Miniboss_golemwarrior_idle", L"..\\Resources\\Sound\\SoundEffect\\GolemMiniBoss\\Miniboss_golemwarrior_idle.wav"));
		as->Play();
		as->SetVolume(1);
		as->SetLoop(true);
	}

	time += Time::DeltaTime();

	sn::GameObject* player = SceneManager::GetActiveScene()->GetPlayer();
	Transform* playerTr = player->GetComponent<Transform>();
	Vector3 playerPos = playerTr->GetPosition();

	Monster* mon = GetMonster();
	Transform* monTr = mon->GetComponent <Transform>();
	Vector3 monPos = monTr->GetPosition();

	Vector3 moveDir = playerPos - monPos;

	if (abs(moveDir.x) < mon->GetMonsterInfo().fAttRange && abs(moveDir.y) < mon->GetMonsterInfo().fAttRange) {		
		//moveDir = Vector3(0.0f, 0.0f, 0.0f);
		delayTime += Time::DeltaTime();

		if (delayTime >= mon->GetMonsterInfo().fAttDelay && mon->GetMonsterInfo().fAttDelay >= 0.f) {
			SceneManager::ChangeMonsterState(GetAI(), MON_STATE::ATT);
			delayTime = 0.f;

			time = 0.f;
			AudioSource* as = GetAI()->GetOwner()->GetComponent<AudioSource>();
			as->Stop();
		}
	}
	else {
		delayTime = 0.f;
	}
	
	moveDir.Normalize();

	bool upDown = true;
	if (abs(moveDir.x) > abs(moveDir.y)) {
		upDown = false;
	}
	else {
		upDown = true;
	}

	if (upDown) {
		if (moveDir.y < 0.f) {
			GetAI()->SetDir(MonDir::DOWN);
		}
		else {
			GetAI()->SetDir(MonDir::UP);
		}
	}
	else {
		if (moveDir.x < 0.f) {
			GetAI()->SetDir(MonDir::LEFT);
		}
		else {
			GetAI()->SetDir(MonDir::RIGHT);
		}
	}

	monPos += Time::DeltaTime() * moveDir * GetMonster()->GetInfo().fSpeed;

	monTr->SetPosition(monPos);
}

void MonsterTrace::Enter()
{
}

void MonsterTrace::Exit()
{
}
