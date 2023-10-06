#include "FylingRepairGolem.h"
#include "AI.h"
#include "snAnimator.h"
#include "snTransform.h"
#include "snSceneManager.h"
#include "DungeonMapManager.h"
#include "MonsterHPBar.h"
#include "snPlayer.h"
#include "PlayerHP.h"
#include <snAudioSource.h>
#include "snResources.h"
#include "snTime.h"
#include "snAudioSource.h"

using namespace sn;

FylingRepairGolem::FylingRepairGolem()
	: startTime(0.0f)
	, endTime(0.0f)
{
}

FylingRepairGolem::~FylingRepairGolem()
{
}

void FylingRepairGolem::Initialize()
{
	Monster::Initialize();
}

void FylingRepairGolem::Update()
{
	if (startTime == 0.f) {
		AudioSource* as = GetComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"golem_dungeon_flyingrepair_loop", L"..\\Resources\\Sound\\SoundEffect\\FlyingRepairGolem\\golem_dungeon_flyingrepair_loop.wav"));
		as->Play();
		as->SetVolume(1);
		as->SetLoop(false);
	}
	startTime += Time::DeltaTime();
	if (startTime >= 0.5f) {
		startTime = 0.f;
	}

	AI* ai = GetComponent<AI>();
	MonDir monDir = ai->GetCurDir();
	MON_STATE monState = ai->GetCurStateName();

	sn::Animator* animator = GetComponent<sn::Animator>();

	sn::Transform* monTr = this->GetComponent <sn::Transform>();
	sn::Collider2D* collider = this->GetComponent<sn::Collider2D>();

	if (monDir != ai->GetPrevDir() || monState != ai->GetPrevStateName()) {
		switch (monState)
		{
		case MON_STATE::IDLE:
		{
			animator->PlayAnimation(L"FYLING_REPAIR_GOLEM_IDLE", true);
		}
			break;
		case MON_STATE::WALK:
			break;
		case MON_STATE::TRACE:
		{
			animator->PlayAnimation(L"FYLING_REPAIR_GOLEM_IDLE", true);
		}
		break;
		case MON_STATE::ATT:
		break;
		case MON_STATE::TARGET_ATT:
			break;
		case MON_STATE::DEAD:
			break;
		case MON_STATE::END:
			break;
		default:
			break;
		}

	}
	Monster::Update();
}

void FylingRepairGolem::LateUpdate()
{
	Monster::LateUpdate();
}

void FylingRepairGolem::Render()
{
	Monster::Render();
}

void FylingRepairGolem::OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me)
{
	Monster::OnCollisionEnter(other, me);
	if (other->GetName() == L"SecondCollider") {
		tMonInfo monInfo = GetMonsterInfo();
		monInfo.fHP -= 30.f;
		this->GetComponent<MonsterHPBar>()->PlayDamage(30.f);
		this->GetComponent<MonsterHPBar>()->SetEnable(true);
		SetMonsterInfo(monInfo);

		AudioSource* as = GetComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"golem_dungeon_golem_hit", L"..\\Resources\\Sound\\SoundEffect\\Golem\\golem_dungeon_golem_hit.wav"));
		as->Play();
		as->SetVolume(4);
		as->SetLoop(false);

		if (monInfo.fHP <= 0.f) {
			std::vector<std::vector<RoomInfo>>& vecRoomInfo = DungeonMapManager::GetInst()->GetRoomInfoArr();
			vecRoomInfo[monsterMapPos.first][monsterMapPos.second].monsterNum -= 1;

			if (vecRoomInfo[monsterMapPos.first][monsterMapPos.second].monsterNum <= 0) {
				vecRoomInfo[monsterMapPos.first][monsterMapPos.second].clear = true;
				DungeonMapManager::GetInst()->SetRoomInfoArr(vecRoomInfo);
				DungeonMapManager::GetInst()->SetDungeonClear(true);
			}
		}
	}
	if (other->GetName() == L"FisrtCollider") {
		snPlayer* player = static_cast<snPlayer*>(other->GetOwner());
		float playerHP = player->GetHP();
		playerHP -= 30.f;
		player->SetHP(playerHP);
		PlayerHP* playerHPComponent = player->GetComponent<PlayerHP>();
		playerHPComponent->PlayDamage(30.f);
	}
}

void FylingRepairGolem::OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me)
{
}

void FylingRepairGolem::OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me)
{
}
