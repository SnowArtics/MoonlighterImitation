#pragma once
#include "SnowEngine.h"
#include <snMath.h>
#include "snGameObject.h"

using namespace sn::math;
using namespace sn;

struct InventoryItem {
	Vector3 pos;
	sn::GameObject* slotItem;
	bool isEmpty;
	int itemCount;
	int itemMaxCount;
	std::wstring slotName;
	eItemType _itemType;
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
	InventoryManager();
	~InventoryManager();

public:
	static void Initiailize();
	static void Update();
	static void Render();

public:
	static bool GetInvenActive() { return bInvenActive; }

public:
	static void CreateUI();
	static void ShowUI();
	static void MoveSlot(SlotMoveDir _eSlotMoveDir);
	static bool InputItem(eItemType _itemType);
	static bool InputItemToPos(std::pair<int, int> _invenPos, eItemType _itemType);

	template<typename T>
	static std::wstring NumToWString(T& arg) {
		return std::to_wstring(arg);
	}

	template<typename T, typename... Args>
	static std::wstring NumToWString(T& firstArg, Args&... restArgs) {
		std::to_wstring(firstArg);
		IntToWString(restArgs);
	}

private:
	static std::pair<int, int> curInvenSlotPos;
	static std::vector<std::vector<Vector3>> vInventorySlotPos;
	static std::vector<std::vector<InventoryItem>> inven;

	static sn::GameObject* pInventory;
	static sn::GameObject* pInventoryLeft;
	static sn::GameObject* pInventorySlot;

	static bool bInvenActive;
};

