#include "Slime.h"
#include "AI.h"
#include "snAnimator.h"
#include "snTransform.h"
#include "snSceneManager.h"
#include "DungeonMapManager.h"

using namespace sn;

Slime::Slime()
{
}

Slime::~Slime()
{
}

void Slime::Initialize()
{
	Monster::Initialize();
}

void Slime::Update()
{
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
			break;
		case MON_STATE::WALK:
			break;
		case MON_STATE::TRACE:
		{
			//monTr->SetScale(0.5f, 0.5f, 1.0f);
			//collider->SetSize(Vector2(0.4f, 0.4f));
			animator->PlayAnimation(L"SLIME_MOVE", true);
		}
			break;
		case MON_STATE::ATT:
		{
			//monTr->SetScale(1.f, 1.f, 1.0f);
			//collider->SetSize(Vector2(0.21f, 0.21f));
			animator->PlayAnimation(L"SLIME_MOVE", true);
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

void Slime::LateUpdate()
{
	Monster::LateUpdate();
}

void Slime::Render()
{
	Monster::Render();
}

void Slime::OnCollisionEnter(sn::Collider2D* other)
{
	Monster::OnCollisionEnter(other);
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

void Slime::OnCollisionStay(sn::Collider2D* other)
{
}

void Slime::OnCollisionExit(sn::Collider2D* other)
{
}
