#include "Golem.h"

#include "AI.h"
#include "snAnimator.h"
#include "snSceneManager.h"
#include "snDungeon.h"

Golem::Golem()
{
}

Golem::~Golem()
{
}

void Golem::Initialize()
{
	Monster::Initialize();
}

void Golem::Update()
{
	AI* ai = GetComponent<AI>();
	MonDir monDir = ai->GetCurDir();
	MON_STATE monState = ai->GetCurStateName();

	Animator* animator = GetComponent<Animator>();

	if (monState != ai->GetPrevStateName())
		int a = 0;

	if (monDir != ai->GetPrevDir() || monState != ai->GetPrevStateName()) {
		switch (monState)
		{
		case MON_STATE::IDLE:
			break;
		case MON_STATE::WALK:
			break;
		case MON_STATE::TRACE:
		{
			switch (monDir)
			{
			case MonDir::UP:
				animator->PlayAnimation(L"GOLEM_MOVE_UP", true);
				break;
			case MonDir::DOWN:
				animator->PlayAnimation(L"GOLEM_MOVE_DOWN", true);
				break;
			case MonDir::RIGHT:
				animator->PlayAnimation(L"GOLEM_MOVE_RIGHT", true);
				break;
			case MonDir::LEFT:
				animator->PlayAnimation(L"GOLEM_MOVE_LEFT", true);
				break;
			default:
				break;
			}
		}
		break;
		case MON_STATE::ATT:
		{
			switch (monDir)
			{
			case MonDir::UP:
				animator->PlayAnimation(L"GOLEM_ATTACK_UP", true);
				break;
			case MonDir::DOWN:
				animator->PlayAnimation(L"GOLEM_ATTACK_DOWN", true);
				break;
			case MonDir::RIGHT:
				animator->PlayAnimation(L"GOLEM_ATTACK_RIGHT", true);
				break;
			case MonDir::LEFT:
				animator->PlayAnimation(L"GOLEM_ATTACK_LEFT", true);
				break;
			default:
				break;
			}
		}
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

void Golem::LateUpdate()
{
	Monster::LateUpdate();
}

void Golem::Render()
{
	Monster::Render();
}

void Golem::OnCollisionEnter(sn::Collider2D* other)
{
	if (other->GetName() == L"SecondCollider") {
		tMonInfo monInfo = GetMonsterInfo();
		monInfo.fHP -= 30.f;
		SetMonsterInfo(monInfo);

		Dungeon* dungeonScene = static_cast<Dungeon*>(SceneManager::GetActiveScene());
		std::vector<std::vector<RoomInfo>> vecRoomInfo = dungeonScene->GetRoomInfoArr();

		if (monInfo.fHP <= 0.f) {
			vecRoomInfo[monsterMapPos.first][monsterMapPos.second].monsterNum -= 1;

			if (vecRoomInfo[monsterMapPos.first][monsterMapPos.second].monsterNum <= 0) {
				vecRoomInfo[monsterMapPos.first][monsterMapPos.second].clear = true;
				dungeonScene->SetRoomInfoArr(vecRoomInfo);
				dungeonScene->SetDungeonClear(true);
			}
		}
	}
}

void Golem::OnCollisionStay(sn::Collider2D* other)
{
}

void Golem::OnCollisionExit(sn::Collider2D* other)
{
}
