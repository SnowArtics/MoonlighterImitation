#pragma once
#include "SnowEngine.h"
#include <snMath.h>
#include "snGameObject.h"

using namespace sn::math;
using namespace sn;

struct InventoryItem {
	Vector3 pos;
};

enum SlotMoveDir {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class InventoryManager
{
public:
	static void Initiailize();
	static void Update();
	static void Render();

public:
	static void CreateUI();
	static void ShowUI();
	static void MoveSlot(SlotMoveDir _eSlotMoveDir);

private:
	static std::pair<int, int> curInvenSlotPos;
	static std::vector<std::vector<Vector3>> vInventorySlotPos;
	static std::vector<std::vector<InventoryItem>> inven;

	static sn::GameObject* pInventory;
	static sn::GameObject* pInventorySlot;

	static bool bInvenActive;
};

