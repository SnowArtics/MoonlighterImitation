#pragma once
#include "SnowEngine.h"
#include <snMath.h>
#include "snGameObject.h"
#include "InventoryManager.h"

using namespace sn::math;
using namespace sn;

struct ShelfItem {
	int price;
	int realPrice;
	sn::GameObject* shelfItem;
	eItemType _itemType;
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
	static std::vector<Vector3> GetLoot();
	static int SearchGoods(int _pos);
	static void BuyGoods(int _pos);
	static void ShopOpen();
	static void ShopClose();
	static void CreateNPC();

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
	static ShelfItem GetLeftTopShelf() { return pLeftTopShelf; }
	static ShelfItem GetLeftBottomShelf() { return pLeftBottomShelf; }
	static ShelfItem GetRightBottomShelf() { return pRightBottomShelf; }
	static ShelfItem GetRightTopShelf() { return pRightTopShelf; }

	static int GetShopInvenActive() { return iShopInvenActive; }

private:
	static std::pair<int, int> curInvenSlotPos;
	static std::pair<int, int> curPriceSlotPos;
	static std::vector<std::vector<InventoryItem>> shop;
	static std::vector<std::vector<PriceSelect>> price;
	static std::vector<std::vector<Vector3>> loot;
	static std::vector<int> priceList;

	static sn::GameObject* pInventoryLeft;
	static sn::GameObject* pShopRight;
	static sn::GameObject* pInventorySlot;
	static sn::GameObject* pPriceSlot;

	static ShelfItem pLeftTopShelf;
	static ShelfItem pLeftBottomShelf;
	static ShelfItem pRightBottomShelf;
	static ShelfItem pRightTopShelf;

	static int iShopInvenActive; //0 is none, 1 is ready, 2 is active
	static bool bPriceSelectActive;
	static float time;
};

