#pragma once
#include "SnowEngine.h"
#include <snMath.h>
#include "snGameObject.h"
#include "InventoryManager.h"

using namespace sn::math;
using namespace sn;

class ShopManager
{
public:
	static void Initiailize();
	static void Update();
	static void Render();

public:
	static void CreateShop();
	static void MoveSlot(SlotMoveDir _eSlotMoveDir);

	template<typename T>
	static std::wstring NumToWString(T& arg) {
		return std::to_wstring(arg);
	}

	template<typename T, typename... Args>
	static std::wstring NumToWString(T& firstArg, Args&... restArgs) {
		std::to_wstring(firstArg);
		IntToWString(restArgs);
	}

public:
	static void SetShopInvenActive(int _iShopInvenActive) { iShopInvenActive = _iShopInvenActive; }

	static int GetShopInvenActive() { return iShopInvenActive; }

private:
	static std::pair<int, int> curInvenSlotPos;
	static std::vector<std::vector<InventoryItem>> shop;

	static sn::GameObject* pInventoryLeft;
	static sn::GameObject* pShopRight;
	static sn::GameObject* pInventorySlot;

	static sn::GameObject* pRightTopShelf;
	static sn::GameObject* pLeftTopShelf;
	static sn::GameObject* pLeftBottomShelf;
	static sn::GameObject* pRightBottomShelf;

	static int iShopInvenActive; //0 is none, 1 is ready, 2 is active
};

