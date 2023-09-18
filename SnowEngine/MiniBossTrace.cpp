#include "MiniBossTrace.h"
#include "Monster.h"
#include "snSceneManager.h"
#include "snDungeon.h"
#include "snGameObject.h"
#include "snTransform.h"
#include "snTime.h"
#include "MiniBossAttack.h"
#include "MiniBossSmash.h"

#include <random>

MiniBossTrace::MiniBossTrace()
	: State(MON_STATE::MINIBOSS_TRACE)
	, time(0.f)
	, delayTime(0.f)
{
}

MiniBossTrace::~MiniBossTrace()
{
}

void MiniBossTrace::Update()
{
	time += Time::DeltaTime();

	sn::GameObject* player = SceneManager::GetActiveScene()->GetPlayer();
	Transform* playerTr = player->GetComponent<Transform>();
	Vector3 playerPos = playerTr->GetPosition();

	Monster* mon = GetMonster();
	Transform* monTr = mon->GetComponent < Transform>();
	Vector3 monPos = monTr->GetPosition();

	Vector3 moveDir = playerPos - monPos;

	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> distribution(1, 2);

	int randomNum = distribution(gen); // randomNums이 1일때 휘두르기 공격, 2일때 충격파 공격


	if (abs(moveDir.x) < mon->GetMonsterInfo().fAttRange && abs(moveDir.y) < mon->GetMonsterInfo().fAttRange) {
		//moveDir = Vector3(0.0f, 0.0f, 0.0f);
		delayTime += Time::DeltaTime();

		if (delayTime >= mon->GetMonsterInfo().fAttDelay && mon->GetMonsterInfo().fAttDelay >= 0.f) {
			delayTime = 0.f;
			if (randomNum == 1) {
				SceneManager::ChangeMonsterState(GetAI(), MON_STATE::MINIBOSS_ATT);
			}
			else if (randomNum == 2) {
				SceneManager::ChangeMonsterState(GetAI(), MON_STATE::MINIBOSS_SMASH);
			}
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

void MiniBossTrace::Enter()
{
}

void MiniBossTrace::Exit()
{
}
