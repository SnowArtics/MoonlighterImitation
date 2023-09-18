#pragma once
#include "snGameObject.h"

#define SINGLE(type) public:\
						static type* GetInst()\
						{\
							static type mgr;\
							return &mgr;\
						}\
					private:\
						type();\
						~type();\

class GameObject;

struct RoomInfo {
	int		monsterNum;
	bool	clear;
	int		roomNum;
	std::wstring backgroundName;
	std::vector<sn::GameObject*> doors;
};

using namespace sn;

class DungeonMapManager
{
	SINGLE(DungeonMapManager);
public:
	void Init();
	void MakeDungeonBackgrounds(std::vector<std::wstring> _DungeonName);
	void MakeDungeonBackground(int i, int j);
	void DeleteDungeonBackground(int i, int j);
	void MakeCliffCollider(int _num, sn::GameObject* _background);
	void MakeDoors();
	void MakeDoor(int i, int j, int nextDungeonPos);
	void DeleteDoor(int i, int j);
	void MonsterSpawn();
	void MonsterSpawn(int _num, int i, int j);

public: //Get(), Set()
	std::vector<std::vector<int>> GetDungeonArr() { return arr; }
	std::pair<int, int> GetPlayerMapPos() { return playerMapPos; }
	std::vector<std::vector<RoomInfo>>& GetRoomInfoArr() { return roomInfoArr; }
	bool GetDungeonClear() { return dungeonClear; }

	void SetDungeonArr(std::vector<std::vector<int>> _arr) { arr = _arr; }
	void SetRoomInfoArr(std::vector<std::vector<RoomInfo>> _roomInfoArr) { roomInfoArr = _roomInfoArr; }
	void SetPlayerMapPos(int x, int y) { playerMapPos.first = y, playerMapPos.second = x; }
	void SetPlayerMapPos(std::pair<int, int> _playerMapPos) { playerMapPos = _playerMapPos; }
	void SetPlayerMapSpawnPos(int x, int y) { playerMapSpawnPos.first = y, playerMapSpawnPos.second = x; }
	void SetPlayerMapSpawnPos(std::pair<int, int> _playerMapPos) { playerMapSpawnPos = _playerMapPos; }
	void SetDungeonClear(bool _dungeonClear) { dungeonClear = _dungeonClear; }
	void SetDungeonName(std::vector < std::wstring> _dungeonName) { dungeonName = _dungeonName; }

private:
	std::vector<std::vector<int>>		arr;
	std::pair<int, int>					playerMapPos;
	std::pair<int, int>					playerMapSpawnPos;
	std::vector<std::vector<RoomInfo>>	roomInfoArr;
	std::vector<std::wstring>			dungeonName;
	bool								dungeonClear;
	int									dungeonCount;
};

