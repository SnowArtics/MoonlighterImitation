#pragma once
#include "SnowEngine.h"
#include <snMath.h>

using namespace sn::math;
using namespace sn;

struct InventoryItem {
	Vector3 pos;
	std::pair<int, int> curInvenPos;
};

class InventoryManager
{
public:
	static void Initiailize();
	static void Update();
	static void Render();

public:
	static void CreateUI();

private:
	static std::pair<int, int> curInvenPos;
	static std::vector<std::vector<InventoryItem>> inven;
};

