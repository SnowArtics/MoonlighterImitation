#include "MiniSlime.h"
#include "snSceneManager.h"
#include "DungeonMapManager.h"

MiniSlime::MiniSlime()
{
}

MiniSlime::~MiniSlime()
{
}

void MiniSlime::Initialize()
{
	Monster::Initialize();
}

void MiniSlime::Update()
{
	Monster::Update();
}

void MiniSlime::LateUpdate()
{
	Monster::LateUpdate();
}

void MiniSlime::Render()
{
	Monster::Render();
}

void MiniSlime::OnCollisionEnter(sn::Collider2D* other)
{
	Monster::OnCollisionEnter(other);
	if (other->GetName() == L"SecondCollider") {
		tMonInfo monInfo = GetMonsterInfo();
		monInfo.fHP -= 30.f;
		this->GetComponent<MonsterHPBar>()->PlayDamage(30.f);
		this->GetComponent<MonsterHPBar>()->SetEnable(true);
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

void MiniSlime::OnCollisionStay(sn::Collider2D* other)
{
}

void MiniSlime::OnCollisionExit(sn::Collider2D* other)
{
}
