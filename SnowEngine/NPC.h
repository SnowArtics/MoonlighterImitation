#pragma once
#include "Monster.h"
#include "snGameObject.h"

using namespace sn;

class NPC :
    public Monster
{
public:
    NPC();
    ~NPC();

public:
    virtual void Initialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void Render();

public:
    virtual void OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me);
    virtual void OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me);
    virtual void OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me);

public:
    void GetLootByShopScene();
    int GetLootProgress() { return lootProgress; }
    std::vector<Vector3> GetLoot() { return loot; }
    GameObject* GetThinkBox() { return thinkBox; }
    GameObject* GetThink() { return think; }
    int GetBuyGold() { return buyGold; }

    void SetLootProgress(int _lootProgress) { lootProgress = _lootProgress; }
    void SetBuyGold(int _buyGold) { buyGold = _buyGold; }

private:
    bool deadFlag;
    std::vector<Vector3> loot;
    int lootProgress;

    sn::GameObject* thinkBox;
    sn::GameObject* think;
    
    int buyGold;
};

