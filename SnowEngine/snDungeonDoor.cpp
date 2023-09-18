#include "snDungeonDoor.h"

#include "snGameObject.h"
#include "snTransform.h"
#include "snSceneManager.h"
#include "snDungeon.h"
#include "snCollider2D.h"
#include "snAnimator.h"
#include "DungeonMapManager.h"

bool DungeonDoor::monsterSpawnFlag = true;
bool DungeonDoor::dungeonBackgroundSpawnFlag = true;

namespace sn {
	sn::DungeonDoor::DungeonDoor(DoorType _doorType, std::pair<int, int> _doorMapPos)
		: doorType(_doorType)
		, doorMapPos(_doorMapPos)
		, prevPlayerMapPos({ -1,-1 })
		, curPlayerMapPos({ -1,-1 })
		, doorOpen(false)
	{
	}

	sn::DungeonDoor::~DungeonDoor()
	{
	}

	void sn::DungeonDoor::Initialize()
	{

	}

	void sn::DungeonDoor::Update()
	{
		Dungeon* dungeonScene = static_cast<Dungeon*>(SceneManager::GetActiveScene());
		prevPlayerMapPos = curPlayerMapPos;
		curPlayerMapPos = DungeonMapManager::GetInst()->GetPlayerMapPos();

		Collider2D* collider = GetOwner()->GetComponent<Collider2D>();

		Animator* animator = GetOwner()->GetComponent <Animator>();

		if (prevPlayerMapPos != curPlayerMapPos && dungeonBackgroundSpawnFlag) {
			dungeonBackgroundSpawnFlag = false;
			if (!(prevPlayerMapPos.first == -1 || prevPlayerMapPos.second == -1)) {
				DungeonMapManager::GetInst()->MakeDungeonBackground(curPlayerMapPos.first, curPlayerMapPos.second);
				DungeonMapManager::GetInst()->DeleteDungeonBackground(prevPlayerMapPos.first, prevPlayerMapPos.second);
				
				int prevPlayerPos = 0;
				if (prevPlayerMapPos.first < curPlayerMapPos.first)
					prevPlayerPos = 0x02;
				else if(prevPlayerMapPos.first > curPlayerMapPos.first)
					prevPlayerPos = 0x01;
				else if (prevPlayerMapPos.second < curPlayerMapPos.second)
					prevPlayerPos = 0x08;
				else if (prevPlayerMapPos.second > curPlayerMapPos.second)
					prevPlayerPos = 0x04;
				DungeonMapManager::GetInst()->MakeDoor(curPlayerMapPos.first, curPlayerMapPos.second, prevPlayerPos);
				DungeonMapManager::GetInst()->DeleteDoor(prevPlayerMapPos.first, prevPlayerMapPos.second);
			}
		}
		else if (prevPlayerMapPos == curPlayerMapPos) {
			dungeonBackgroundSpawnFlag = true;
		}

		std::vector<std::vector<RoomInfo>>& vecRoomInfo = DungeonMapManager::GetInst()->GetRoomInfoArr();

		if (prevPlayerMapPos != curPlayerMapPos && vecRoomInfo[curPlayerMapPos.first][curPlayerMapPos.second].clear == false) {
			collider->SetEnable(false);
			animator->PlayAnimation(L"CLOSE_DOOR", false);
			DungeonMapManager::GetInst()->SetDungeonClear(false);
			if (monsterSpawnFlag) {				
				DungeonMapManager::GetInst()->MonsterSpawn(vecRoomInfo[curPlayerMapPos.first][curPlayerMapPos.second].roomNum, curPlayerMapPos.first, curPlayerMapPos.second);
				monsterSpawnFlag = false;
			}
		}		

		if (DungeonMapManager::GetInst()->GetDungeonClear() == true) {
			if (collider->GetEnable() == false) {
				doorOpen = true;
			}
		}

		if (doorOpen == true) {			
			animator->PlayAnimation(L"OPEN_DOOR", false);
			collider->SetEnable(true);
			doorOpen = false;
			monsterSpawnFlag = true;
		}
	}

	void sn::DungeonDoor::LateUpdate()
	{
	}

	void sn::DungeonDoor::Render()
	{
	}

	void sn::DungeonDoor::OnCollisionEnter(Collider2D* other)
	{
		GameObject* otherObject = other->GetOwner();

		if (GetOwner()->GetName() == L"NextDungeonDoor") {
			if (SceneManager::GetActiveScene()->GetName() == L"DungeonScene01") {
				SceneManager::SetChangeScene(L"DungeonScene02");
			}
			else if (SceneManager::GetActiveScene()->GetName() == L"DungeonScene02") {
				SceneManager::SetChangeScene(L"DungeonScene03");
			}
		}else if (otherObject->GetName() == L"Player") {
			Transform* tr = otherObject->GetComponent<Transform>();
			Vector3 playerPos = tr->GetPosition();
			Dungeon* curScene = static_cast<Dungeon*>(SceneManager::GetActiveScene());
			std::pair<int, int> playerMapPos = DungeonMapManager::GetInst()->GetPlayerMapPos();

			switch (doorType)
			{
			case DoorType::UP:
				tr->SetPosition(Vector3(playerPos.x, playerPos.y + 2.f, playerPos.z));
				DungeonMapManager::GetInst()->SetPlayerMapPos(playerMapPos.second, playerMapPos.first -1);
				break;
			case DoorType::DOWN:
				tr->SetPosition(Vector3(playerPos.x, playerPos.y - 2.f, playerPos.z));
				DungeonMapManager::GetInst()->SetPlayerMapPos(playerMapPos.second, playerMapPos.first + 1);
				break;
			case DoorType::LEFT:
				tr->SetPosition(Vector3(playerPos.x-3.0f, playerPos.y, playerPos.z));
				DungeonMapManager::GetInst()->SetPlayerMapPos(playerMapPos.second -1 , playerMapPos.first);
				break;
			case DoorType::RIGHT:
				tr->SetPosition(Vector3(playerPos.x + 3.0f, playerPos.y, playerPos.z));
				DungeonMapManager::GetInst()->SetPlayerMapPos(playerMapPos.second + 1, playerMapPos.first);
				break;
			default:
				break;
			}
		}
	}

	void sn::DungeonDoor::OnCollisionStay(Collider2D* other)
	{
	}

	void sn::DungeonDoor::OnCollisionExit(Collider2D* other)
	{
	}
}