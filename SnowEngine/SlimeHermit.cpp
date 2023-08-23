#include "SlimeHermit.h"

#include "AI.h"
#include "snAnimator.h"
#include "snSceneManager.h"
#include "DungeonMapManager.h"

SlimeHermit::SlimeHermit()
{
}

SlimeHermit::~SlimeHermit()
{
}

void SlimeHermit::Initialize()
{
	Monster::Initialize();
}

void SlimeHermit::Update()
{
	AI* ai = GetComponent<AI>();
	MonDir monDir = ai->GetCurDir();
	MON_STATE monState = ai->GetCurStateName();

	Transform* monTr = this->GetComponent <Transform>();
	sn::Collider2D* collider = this->GetComponent<sn::Collider2D>();

	Animator* animator = GetComponent<Animator>();

	if (monDir != ai->GetPrevDir() || monState != ai->GetPrevStateName()) {
		switch (monState)
		{
		case MON_STATE::IDLE:
			break;
		case MON_STATE::WALK:
			break;
		case MON_STATE::TRACE:
		{
			monTr->SetScale(1.5f, 1.5f, 1.5f);
			collider->SetSize(Vector2(0.4f, 0.4f));
			switch (monDir)
			{
			case MonDir::UP:
				animator->PlayAnimation(L"SLIME_HERMIT_WALK_UP", true);
				break;
			case MonDir::DOWN:
				animator->PlayAnimation(L"SLIME_HERMIT_WALK_DOWN", true);
				break;
			case MonDir::RIGHT:
				animator->PlayAnimation(L"SLIME_HERMIT_WALK_RIGHT", true);
				break;
			case MonDir::LEFT:
				animator->PlayAnimation(L"SLIME_HERMIT_WALK_LEFT", true);
				break;
			default:
				break;
			}
		}
		break;
		case MON_STATE::ATT:
		{
			monTr->SetScale(3.0f, 3.0f, 3.0f);
			collider->SetSize(Vector2(0.2f, 0.2f));
			switch (monDir)
			{
			case MonDir::UP:
				collider->SetSize(Vector2(0.2f, 0.4f));
				animator->PlayAnimation(L"SLIME_HERMIT_ATT_UP", true);
				break;
			case MonDir::DOWN:
				collider->SetSize(Vector2(0.2f, 0.4f));
				animator->PlayAnimation(L"SLIME_HERMIT_ATT_DOWN", true);
				break;
			case MonDir::RIGHT:
				collider->SetSize(Vector2(0.4f, 0.2f));
				animator->PlayAnimation(L"SLIME_HERMIT_ATT_RIGHT", true);
				break;
			case MonDir::LEFT:
				collider->SetSize(Vector2(0.4f, 0.2f));
				animator->PlayAnimation(L"SLIME_HERMIT_ATT_LEFT", true);
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

void SlimeHermit::LateUpdate()
{
	Monster::LateUpdate();
}

void SlimeHermit::Render()
{
	Monster::Render();
}

void SlimeHermit::OnCollisionEnter(sn::Collider2D* other)
{
	if (other->GetName() == L"SecondCollider") {
		tMonInfo monInfo = GetMonsterInfo();
		monInfo.fHP -= 30.f;
		SetMonsterInfo(monInfo);

		std::vector<std::vector<RoomInfo>> vecRoomInfo = DungeonMapManager::GetInst()->GetRoomInfoArr();

		if (monInfo.fHP <= 0.f) {
			vecRoomInfo[monsterMapPos.first][monsterMapPos.second].monsterNum -= 1;

			if (vecRoomInfo[monsterMapPos.first][monsterMapPos.second].monsterNum <= 0) {
				vecRoomInfo[monsterMapPos.first][monsterMapPos.second].clear = true;
				DungeonMapManager::GetInst()->SetRoomInfoArr(vecRoomInfo);
				DungeonMapManager::GetInst()->SetDungeonClear(true);
			}
		}
	}
}

void SlimeHermit::OnCollisionStay(sn::Collider2D* other)
{
}

void SlimeHermit::OnCollisionExit(sn::Collider2D* other)
{
}
