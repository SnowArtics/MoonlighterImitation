#pragma once
#include "SnowEngine.h"
#include <snMath.h>
#include "snGameObject.h"
#include "InventoryManager.h"

using namespace sn::math;
using namespace sn;

struct ShelfItem {
	int price;
	sn::GameObject* shelfItem;
};

struct PriceSelect {
	std::wstring textTitle;
	Vector3 pos;
	Vector3 texPos;
};

class ShopManager
{
public:
	static void Initiailize();
	static void Update();
	static void Render();

public:
	static void CreateShop();
	static void MoveSlot(SlotMoveDir _eSlotMoveDir);
	static void MovePriceSlot(SlotMoveDir _eSlotMoveDir);
	static void SetShopShelf();
	static void BackShopShelf();
	static void SetPrice();

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
	static std::pair<int, int> curPriceSlotPos;
	static std::vector<std::vector<InventoryItem>> shop;
	static std::vector<std::vector<PriceSelect>> price;

	static sn::GameObject* pInventoryLeft;
	static sn::GameObject* pShopRight;
	static sn::GameObject* pInventorySlot;
	static sn::GameObject* pPriceSlot;

	static ShelfItem pRightTopShelf;
	static ShelfItem pLeftTopShelf;
	static ShelfItem pLeftBottomShelf;
	static ShelfItem pRightBottomShelf;

	static int iShopInvenActive; //0 is none, 1 is ready, 2 is active
	static bool bPriceSelectActive;
};

