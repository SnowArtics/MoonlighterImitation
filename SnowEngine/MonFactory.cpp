#include "MonFactory.h"
#include "Monster.h"
#include "../Engine_SOURCE/snTransform.h"
#include "snAnimator.h"
#include "snResources.h"
#include "snCollider2D.h"
#include "snMesh.h"
#include "snMeshRenderer.h"
#include "snMaterial.h"
#include "snRigidBody.h"
#include "AI.h"
#include "MonsterIdle.h"
#include "MonsterTrace.h"
#include "MonsterAttack.h"
#include "SlimeAttack.h"
#include "TurretAttack.h"
#include "TurretBrokenAttack.h"

#include "Golem.h"
#include "Slime.h"
#include "MiniSlime.h"
#include "FylingRepairGolem.h"
#include "GolemTurret.h"
#include "GolemTurretBroken.h"
#include "SlimeHermit.h"
#include "MonsterHPBar.h"
#include "GolemMiniBoss.h"
#include "MiniBossHPBar.h"
#include "GolemCorruptedMiniBoss.h"
#include "MiniBossAttack.h"
#include "MiniBossTrace.h"
#include "MiniBossSmash.h"
#include "MiniBossTeleportAttack.h"
#include "MiniBossIdle.h"
#include "GolemKing.h"
#include "GolemKingUp.h"
#include "GolemKingIdle.h"
#include "GolemKingRockAttack.h"
#include "GolemKingAimAttack.h"
#include "GolemKingArmAttack.h"
#include "GolemKingWave.h"
#include "GolemKingArmIdle.h"
#include "GolemKingArmRecover.h"
#include "GolemKingAimCycle.h"
#include "GolemKingAimEnd.h"
#include "GolemKingAimShoot.h"
#include "GolemKingDeath.h"
#include "GolemKingDeath01.h"
#include "DroppingItem.h"

using namespace sn;

Monster* MonFactory::CreateMonster(MonType _eType, sn::math::Vector2 _vPos)
{
    Monster* pMon = nullptr;

	switch (_eType)
	{
	case MonType::GOLEM:
	{
		pMon = new Golem;
		pMon->SetName(L"GOLEM");
		Transform* tr = pMon->GetComponent<Transform>();
		tr->SetPosition(Vector3(_vPos.x, _vPos.y, 0.0f));

		tMonInfo info = {};
		info.fAtt = 20.f;
		info.fAttRange = 0.75f;
		info.fRecogRange = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 0.5f;
		info.fAttTime = 1.3f;
		info.fAttDelay = 0.f;
		info.fUnStiffness = 5.f;

		pMon->SetMonInfo(info);

		MeshRenderer* mr = pMon->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> atlas
			= Resources::Load<Texture>(L"Monster_Golem_Move", L"..\\Resources\\Texture\\Dungeon\\Enemy\\GolemMove.png");
		Animator* at = pMon->AddComponent<Animator>();

		at->Create(L"GOLEM_MOVE_LEFT", atlas, Vector2(0.0f, 0.0f), Vector2(190.0f, 190.0f), 8);
		at->Create(L"GOLEM_MOVE_RIGHT", atlas, Vector2(0.0f, 190.0f), Vector2(190.0f, 190.0f), 8);
		at->Create(L"GOLEM_MOVE_UP", atlas, Vector2(0.0f, 380.0f), Vector2(190.0f, 190.0f), 8);
		at->Create(L"GOLEM_MOVE_DOWN", atlas, Vector2(0.0f, 570.0f), Vector2(190.0f, 190.0f), 8);

		atlas
			= Resources::Load<Texture>(L"Monster_Golem_Attack", L"..\\Resources\\Texture\\Dungeon\\Enemy\\GolemAttack.png");

		at->Create(L"GOLEM_ATTACK_LEFT", atlas, Vector2(0.0f, 0.0f), Vector2(190.0f, 190.0f), 13, 180.f, 0.1f, Vector2(0.0f,0.01f));
		at->Create(L"GOLEM_ATTACK_RIGHT", atlas, Vector2(0.0f, 190.0f), Vector2(190.0f, 190.0f), 13, 180.f, 0.1f, Vector2(0.0f, 0.01f));
		at->Create(L"GOLEM_ATTACK_UP", atlas, Vector2(0.0f, 380.0f), Vector2(190.0f, 190.0f), 13, 180.f, 0.1f, Vector2(0.0f, 0.01f));
		at->Create(L"GOLEM_ATTACK_DOWN", atlas, Vector2(0.0f, 570.0f), Vector2(190.0f, 190.0f), 13, 180.f, 0.1f, Vector2(0.0f, 0.01f));

		at->PlayAnimation(L"GOLEM_MOVE_UP", true);

		sn::Collider2D* collider = pMon->AddComponent<sn::Collider2D>();
		collider->SetSize(Vector2(0.4f,0.4f));
		collider->SetCenter(Vector2(0.0f, -0.1f));

		sn::Collider2D* collider2 = pMon->AddComponent<sn::Collider2D>();
		collider2->SetName(L"Second_Collider");
		collider2->SetEnable(false);

		RigidBody* rigidBody = pMon->AddComponent<RigidBody>();

		AI* ai = pMon->AddComponent<AI>(pMon);
		ai->AddState(new MonsterIdle);
		ai->AddState(new MonsterTrace);
		ai->AddState(new TurretBrokenAttack);
		//ai->AddState(new MonsterAttack);
		ai->SetCurState(MON_STATE::IDLE);

		MonsterHPBar* monsterHPBar = pMon->AddComponent<MonsterHPBar>();
		monsterHPBar->CreateHpBar();

		std::vector<eItemType> eItems;
		eItems.push_back(eItemType::Crystal_Energy);
		eItems.push_back(eItemType::Golem_Pieces);
		eItems.push_back(eItemType::Fabric);
		eItems.push_back(eItemType::Fabric);
		DroppingItem* di = pMon->AddComponent<DroppingItem>(eItems);
	}
		break;
	case MonType::SLIME:
	{
		pMon = new Slime;
		Transform* tr = pMon->GetComponent<Transform>();
		tr->SetPosition(Vector3(_vPos.x, _vPos.y, 0.0f));
		tr->SetScale(Vector3(0.5f, 0.5f, 0.0f));

		tMonInfo info = {};
		info.fAtt = 15.f;
		info.fAttRange = 2.5f; //-1이면 Trace상태에서 벗어나지 않음.
		info.fRecogRange = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 0.75f;
		info.fAttTime = 1.2f;
		info.fAttDelay = 1.f;
		info.fUnStiffness = 10.f;

		pMon->SetMonInfo(info);

		MeshRenderer* mr = pMon->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		RigidBody* rigidBody = pMon->AddComponent<RigidBody>();

		std::shared_ptr<Texture> atlas
			= Resources::Load<Texture>(L"Slime_Attack", L"..\\Resources\\Texture\\Dungeon\\Enemy\\Slime\\slimeAttack.png");
		Animator* at = pMon->AddComponent<Animator>();

		at->Create(L"SLIME_ATTACK", atlas, Vector2(0.0f, 0.0f), Vector2(41.0f, 44.0f), 8);

		atlas = Resources::Load<Texture>(L"Slime_Move", L"..\\Resources\\Texture\\Dungeon\\Enemy\\Slime\\slimeMove.png");

		at->Create(L"SLIME_MOVE", atlas, Vector2(0.0f, 0.0f), Vector2(80.0f, 75.0f), 8);

		atlas = Resources::Load<Texture>(L"Slime_Jump", L"..\\Resources\\Texture\\Dungeon\\Enemy\\Slime\\slimeJump.png");

		at->Create(L"SLIME_JUMP", atlas, Vector2(0.0f, 0.0f), Vector2(80.0f, 180.0f), 12, 240.f, 0.1f, Vector2(0.0f, -0.25f));

		at->PlayAnimation(L"SLIME_MOVE", true);

		sn::Collider2D* collider = pMon->AddComponent<sn::Collider2D>();
		collider->SetSize(Vector2(0.2f, 0.2f));
		collider->SetCenter(Vector2(0.0f, 0.0f));

		AI* ai = pMon->AddComponent<AI>(pMon);
		ai->AddState(new MonsterTrace);
		ai->AddState(new MonsterIdle);
		ai->AddState(new SlimeAttack);
		ai->SetCurState(MON_STATE::IDLE);

		MonsterHPBar* monsterHPBar = pMon->AddComponent<MonsterHPBar>();
		monsterHPBar->CreateHpBar();

		std::vector<eItemType> eItems;
		eItems.push_back(eItemType::Slime_Jelly);
		eItems.push_back(eItemType::Slime_Jelly);
		eItems.push_back(eItemType::Slime_Jelly);
		DroppingItem* di = pMon->AddComponent<DroppingItem>(eItems);
	}
		break;

	case MonType::BABYSLIME:
	{
		pMon = new MiniSlime;
		Transform* tr = pMon->GetComponent<Transform>();
		tr->SetPosition(Vector3(_vPos.x, _vPos.y, 0.0f));
		tr->SetScale(Vector3(0.5f, 0.5f,0.0f));

		RigidBody* rigidBody = pMon->AddComponent<RigidBody>();

		tMonInfo info = {};
		info.fAtt = 15.f;
		info.fAttRange = -1.f; //-1이면 Trace상태에서 벗어나지 않음.
		info.fRecogRange = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 0.75f;
		info.fAttTime = -1.f;
		info.fAttDelay = 0.f;
		info.fUnStiffness = 10.f;

		pMon->SetMonInfo(info);

		MeshRenderer* mr = pMon->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> atlas
			= Resources::Load<Texture>(L"BabySlime", L"..\\Resources\\Texture\\Dungeon\\Enemy\\BabySlime\\BabySlime.png");
		Animator* at = pMon->AddComponent<Animator>();

		at->Create(L"BABY_SLIME_MOVE", atlas, Vector2(0.0f, 0.0f), Vector2(36.0f, 29.0f), 5);

		at->PlayAnimation(L"BABY_SLIME_MOVE", true);

		sn::Collider2D* collider = pMon->AddComponent<sn::Collider2D>();
		collider->SetSize(Vector2(0.2f, 0.2f));
		collider->SetCenter(Vector2(0.0f, 0.0f));

		AI* ai = pMon->AddComponent<AI>(pMon);
		ai->AddState(new MonsterTrace);
		ai->AddState(new MonsterIdle);
		ai->SetCurState(MON_STATE::IDLE);

		MonsterHPBar* monsterHPBar = pMon->AddComponent<MonsterHPBar>();
		monsterHPBar->CreateHpBar();

		std::vector<eItemType> eItems;
		eItems.push_back(eItemType::Slime_Jelly);
		DroppingItem* di = pMon->AddComponent<DroppingItem>(eItems);
	}
	break;
	case MonType::FYLINGREPAIRGOLEM:
	{
		pMon = new FylingRepairGolem;
		Transform* tr = pMon->GetComponent<Transform>();
		tr->SetPosition(Vector3(_vPos.x, _vPos.y, 0.0f));
		tr->SetScale(Vector3(2.5f, 2.5f, 2.5f));

		RigidBody* rigidBody = pMon->AddComponent<RigidBody>();

		tMonInfo info = {};
		info.fAtt = 15.f;
		info.fAttRange = -1.f; //-1이면 Trace상태에서 벗어나지 않음.
		info.fRecogRange = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 0.75f;
		info.fAttTime = -1.f;
		info.fAttDelay = 0.f;
		info.fUnStiffness = 10.f;

		pMon->SetMonInfo(info);

		MeshRenderer* mr = pMon->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> atlas
			= Resources::Load<Texture>(L"FylingRepairGolem", L"..\\Resources\\Texture\\Dungeon\\Enemy\\FylingRepairGolem\\FylingRepairGolem.png");
		Animator* at = pMon->AddComponent<Animator>();

		at->Create(L"FYLING_REPAIR_GOLEM_IDLE", atlas, Vector2(0.0f, 0.0f), Vector2(18.0f, 29.0f), 3,120.f,0.1f);
		at->Create(L"FYLING_REPAIR_GOLEM_FARM", atlas, Vector2(0.0f, 29.0f), Vector2(18.0f, 29.0f), 12, 120.f, 0.1f);
		at->Create(L"FYLING_REPAIR_GOLEM_MOVE", atlas, Vector2(0.0f, 58.0f), Vector2(18.0f, 29.0f), 6, 120.f, 0.1f);

		at->PlayAnimation(L"FYLING_REPAIR_GOLEM_IDLE", true);

		sn::Collider2D* collider = pMon->AddComponent<sn::Collider2D>();
		collider->SetSize(Vector2(0.1f, 0.1f));
		collider->SetCenter(Vector2(0.0f, 0.0f));

		AI* ai = pMon->AddComponent<AI>(pMon);
		ai->AddState(new MonsterTrace);
		ai->AddState(new MonsterIdle);
		ai->SetCurState(MON_STATE::IDLE);

		MonsterHPBar* monsterHPBar = pMon->AddComponent<MonsterHPBar>();
		monsterHPBar->CreateHpBar();

		std::vector<eItemType> eItems;
		eItems.push_back(eItemType::Broken_Sword);
		eItems.push_back(eItemType::Golem_Pieces);
		DroppingItem* di = pMon->AddComponent<DroppingItem>(eItems);
	}
		break;
	case MonType::GOLEMTURRET:
	{
		pMon = new GolemTurret;
		Transform* tr = pMon->GetComponent<Transform>();
		tr->SetPosition(Vector3(_vPos.x, _vPos.y, 0.0f));
		tr->SetScale(Vector3(1.7f, 1.7f, 2.0f));

		RigidBody* rigidBody = pMon->AddComponent<RigidBody>();

		tMonInfo info = {};
		info.fAtt = 15.f;
		info.fAttRange = 2.f; //-1이면 Trace상태에서 벗어나지 않음.
		info.fRecogRange = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 1.f;
		info.fAttTime = 2.16f;
		info.fAttDelay = 1.5f;
		info.fUnStiffness = 10.f;

		pMon->SetMonInfo(info);

		MeshRenderer* mr = pMon->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> atlas
			= Resources::Load<Texture>(L"GolemTurretWalk", L"..\\Resources\\Texture\\Dungeon\\Enemy\\GolemTurret\\golemturret_walk.png");
		Animator* at = pMon->AddComponent<Animator>();

		at->Create(L"GOLEM_TURRET_WALK_DOWN", atlas, Vector2(0.0f, 0.0f), Vector2(64.f, 64.f), 6, 120.f, 0.1f);
		at->Create(L"GOLEM_TURRET_WALK_LEFT", atlas, Vector2(0.0f, 64.f), Vector2(64.f, 64.f), 6, 120.f, 0.1f);
		at->Create(L"GOLEM_TURRET_WALK_RIGHT", atlas, Vector2(0.0f, 128.f), Vector2(64.f, 64.f), 6, 120.f, 0.1f);
		at->Create(L"GOLEM_TURRET_WALK_UP", atlas, Vector2(0.0f, 192.f), Vector2(64.f, 64.f), 6, 120.f, 0.1f);

		atlas = Resources::Load<Texture>(L"GolemTurretShoot", L"..\\Resources\\Texture\\Dungeon\\Enemy\\GolemTurret\\golemturret_shot.png");

		at->Create(L"GOLEM_TURRET_SHOT_DOWN", atlas, Vector2(0.0f, 0.0f), Vector2(64.f, 64.f), 18, 120.f, 0.12f);
		at->Create(L"GOLEM_TURRET_SHOT_LEFT", atlas, Vector2(0.0f, 64.f), Vector2(64.f, 64.f), 18, 120.f, 0.12f);
		at->Create(L"GOLEM_TURRET_SHOT_RIGHT", atlas, Vector2(0.0f, 128.f), Vector2(64.f, 64.f), 18, 120.f, 0.12f);
		at->Create(L"GOLEM_TURRET_SHOT_UP", atlas, Vector2(0.0f, 192.f), Vector2(64.f, 64.f), 18, 120.f, 0.12f);

		at->PlayAnimation(L"GOLEM_TURRET_WALK_DOWN", true);

		sn::Collider2D* collider = pMon->AddComponent<sn::Collider2D>();
		collider->SetSize(Vector2(0.2f, 0.2f));

		AI* ai = pMon->AddComponent<AI>(pMon);
		ai->AddState(new MonsterTrace);
		ai->AddState(new MonsterIdle);
		ai->AddState(new TurretAttack);
		ai->SetCurState(MON_STATE::IDLE);

		MonsterHPBar* monsterHPBar = pMon->AddComponent<MonsterHPBar>();
		monsterHPBar->CreateHpBar();

		std::vector<eItemType> eItems;
		eItems.push_back(eItemType::Broken_Sword);
		eItems.push_back(eItemType::Golem_Pieces);
		eItems.push_back(eItemType::Crystal_Energy);
		DroppingItem* di = pMon->AddComponent<DroppingItem>(eItems);
	}
		break;
	case MonType::GOLEMTURRETBROKEN:
	{
		pMon = new GolemTurretBroken;
		Transform* tr = pMon->GetComponent<Transform>();
		tr->SetPosition(Vector3(_vPos.x, _vPos.y, 0.0f));
		tr->SetScale(Vector3(1.7f, 1.7f, 2.0f));

		tMonInfo info = {};
		info.fAtt = 15.f;
		info.fAttRange = 10.f; //-1이면 Trace상태에서 벗어나지 않음.
		info.fRecogRange = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 0.f;
		info.fAttTime = 1.8f;
		info.fAttDelay = 1.f;

		pMon->SetMonInfo(info);

		MeshRenderer* mr = pMon->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> atlas
			= Resources::Load<Texture>(L"GolemTurretBroken", L"..\\Resources\\Texture\\Dungeon\\Enemy\\GolemTurretBroken\\GolemTurretBroken.png");
		Animator* at = pMon->AddComponent<Animator>();

		at->Create(L"GOLEM_TURRET_BROKEN_DOWN", atlas, Vector2(0.0f, 0.0f), Vector2(33.0f, 40.0f), 1, 120.f, 0.1f);
		at->Create(L"GOLEM_TURRET_BROKEN_LEFT", atlas, Vector2(0.0f, 40.0f), Vector2(33.0f, 40.0f), 1, 120.f, 0.1f);
		at->Create(L"GOLEM_TURRET_BROKEN_RIGHT", atlas, Vector2(0.0f, 80.0f), Vector2(33.0f, 40.0f), 1, 120.f, 0.1f);
		at->Create(L"GOLEM_TURRET_BROKEN_UP", atlas, Vector2(0.0f, 120.0f), Vector2(33.0f, 40.0f), 1, 120.f, 0.1f);

		at->Create(L"GOLEM_TURRET_BROKEN_SHOT_DOWN",atlas, Vector2(33.0f, 0.0f), Vector2(33.0f, 40.0f), 10, 120.f, 0.06f);
		at->Create(L"GOLEM_TURRET_BROKEN_SHOT_LEFT", atlas, Vector2(33.0f, 40.0f), Vector2(33.0f, 40.0f), 10, 120.f, 0.06f);
		at->Create(L"GOLEM_TURRET_BROKEN_SHOT_RIGHT", atlas, Vector2(33.0f, 80.0f), Vector2(33.0f, 40.0f), 10, 120.f, 0.06f);
		at->Create(L"GOLEM_TURRET_BROKEN_SHOT_UP", atlas, Vector2(33.0f, 120.0f), Vector2(33.0f, 40.0f), 10, 120.f, 0.06f);

		at->PlayAnimation(L"GOLEM_TURRET_BROKEN_SHOT_LEFT", true);

		sn::Collider2D* collider = pMon->AddComponent<sn::Collider2D>();
		collider->SetSize(Vector2(0.2f, 0.2f));

		AI* ai = pMon->AddComponent<AI>(pMon);
		ai->AddState(new MonsterTrace);
		ai->AddState(new MonsterIdle);
		ai->AddState(new TurretBrokenAttack);
		ai->SetCurState(MON_STATE::IDLE);

		MonsterHPBar* monsterHPBar = pMon->AddComponent<MonsterHPBar>();
		monsterHPBar->CreateHpBar();

		std::vector<eItemType> eItems;
		eItems.push_back(eItemType::Fabric);
		eItems.push_back(eItemType::Crystal_Energy);
		DroppingItem* di = pMon->AddComponent<DroppingItem>(eItems);
	}
	break;
	case MonType::GOLEMMINIBOSS:
	{
		pMon = new GolemMiniBoss;
		pMon->SetName(L"Golem Warrior");
		Transform* tr = pMon->GetComponent<Transform>();
		tr->SetPosition(Vector3(_vPos.x, _vPos.y, 0.0f));
		tr->SetScale(3.0f, 3.0f, 3.0f);

		tMonInfo info = {};
		info.fAtt = 20.f;
		info.fAttRange = 1.5f;
		info.fRecogRange = 300.f;
		info.fHP = 300.f;
		info.fSpeed = 0.5f;
		info.fAttTime = 1.5f;
		info.fAttDelay = 1.f;

		pMon->SetMonInfo(info);

		MeshRenderer* mr = pMon->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> atlas
			= Resources::Load<Texture>(L"Golem_Mini_Boss", L"..\\Resources\\Texture\\Dungeon\\Enemy\\GolemMiniBoss\\Golem_MiniBoss.png");
		Animator* at = pMon->AddComponent<Animator>();

		at->Create(L"GOLEM_MOVE_DOWN", atlas, Vector2(0.0f, 0.0f), Vector2(248.f, 225.f), 8,240.f);
		at->Create(L"GOLEM_MOVE_LEFT", atlas, Vector2(0.0f, 225.f), Vector2(248.f, 225.f), 8, 240.f);
		at->Create(L"GOLEM_MOVE_RIGHT", atlas, Vector2(0.0f, 450.f), Vector2(248.f, 225.f), 8, 240.f);
		at->Create(L"GOLEM_MOVE_UP", atlas, Vector2(0.0f, 675.0f), Vector2(248.f, 225.f), 8, 240.f);

		at->Create(L"GOLEM_SMASH_DOWN", atlas, Vector2(0.0f, 900.f), Vector2(248.f, 225.f), 15, 240.f,0.1f);
		at->Create(L"GOLEM_SMASH_LEFT", atlas, Vector2(0.0f, 1125.0f), Vector2(248.f, 225.f), 15, 240.f, 0.1f);
		at->Create(L"GOLEM_SMASH_RIGHT", atlas, Vector2(0.0f, 1350.0f), Vector2(248.f, 225.f), 15, 240.f, 0.1f);
		at->Create(L"GOLEM_SMASH_UP", atlas, Vector2(0.0f, 1575.0f), Vector2(248.f, 225.f), 15, 240.f, 0.1f);

		at->Create(L"GOLEM_ATTACK_DOWN", atlas, Vector2(0.0f, 1800.f), Vector2(248.f, 225.f), 15, 240.f, 0.1f);
		at->Create(L"GOLEM_ATTACK_LEFT", atlas, Vector2(0.0f, 2025.0f), Vector2(248.f, 225.f), 15, 240.f, 0.1f);
		at->Create(L"GOLEM_ATTACK_RIGHT", atlas, Vector2(0.0f, 2250.0f), Vector2(248.f, 225.f), 15, 240.f, 0.1f);
		at->Create(L"GOLEM_ATTACK_UP", atlas, Vector2(0.0f, 2475.f), Vector2(248.f, 225.f), 15, 240.f, 0.1f);

		at->PlayAnimation(L"GOLEM_MOVE_UP", true);

		sn::Collider2D* collider = pMon->AddComponent<sn::Collider2D>();
		collider->SetSize(Vector2(0.2f, 0.25f));
		collider->SetCenter(Vector2(0.0f, -0.1f));
		
		sn::Collider2D* collider2 = pMon->AddComponent<sn::Collider2D>();
		collider2->SetEnable(false);
		collider2->SetName(L"Mini_Boss_Second_Collider");

		sn::Collider2D* collider3 = pMon->AddComponent<sn::Collider2D>();
		collider3->SetEnable(false);
		collider3->SetName(L"Mini_Boss_Third_Collider");

		AI* ai = pMon->AddComponent<AI>(pMon);
		ai->AddState(new MonsterIdle);
		ai->AddState(new MonsterTrace);
		ai->AddState(new TurretBrokenAttack);
		ai->SetCurState(MON_STATE::IDLE);

		pMon->AddComponent<MiniBossHPBar>();

		std::vector<eItemType> eItems;
		eItems.push_back(eItemType::Crystal_Energy);
		eItems.push_back(eItemType::Crystal_Energy);
		eItems.push_back(eItemType::Golem_Core);
		eItems.push_back(eItemType::Golem_Core);
		eItems.push_back(eItemType::Reinforced_Steel);
		eItems.push_back(eItemType::Reinforced_Steel);
		eItems.push_back(eItemType::Reinforced_Steel);
		eItems.push_back(eItemType::Broken_Sword);
		eItems.push_back(eItemType::Broken_Sword);
		DroppingItem* di = pMon->AddComponent<DroppingItem>(eItems);
	}
	break;
	case MonType::GOLEMCORRUPTMINIBOSS:
	{
		pMon = new GolemCorruptedMiniBoss;
		pMon->SetName(L"Golem Corrupted Warrior");
		Transform* tr = pMon->GetComponent<Transform>();
		tr->SetPosition(Vector3(_vPos.x, _vPos.y, 0.0f));
		tr->SetScale(3.0f, 3.0f, 3.0f);

		tMonInfo info = {};
		info.fAtt = 20.f;
		info.fAttRange = 1.5f;
		info.fRecogRange = 300.f;
		info.fHP = 300.f;
		info.fSpeed = 0.5f;
		info.fAttTime = 1.5f;
		info.fAttDelay = 1.f;

		pMon->SetMonInfo(info);

		MeshRenderer* mr = pMon->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteTeleportAnimaionMaterial"));

		std::shared_ptr<Texture> atlas
			= Resources::Load<Texture>(L"Golem_Mini_Boss", L"..\\Resources\\Texture\\Dungeon\\Enemy\\GolemMiniBoss\\Golem_MiniBoss.png");
		Animator* at = pMon->AddComponent<Animator>();

		at->Create(L"GOLEM_MOVE_DOWN", atlas, Vector2(0.0f, 0.0f), Vector2(248.f, 225.f), 8, 240.f);
		at->Create(L"GOLEM_MOVE_LEFT", atlas, Vector2(0.0f, 225.f), Vector2(248.f, 225.f), 8, 240.f);
		at->Create(L"GOLEM_MOVE_RIGHT", atlas, Vector2(0.0f, 450.f), Vector2(248.f, 225.f), 8, 240.f);
		at->Create(L"GOLEM_MOVE_UP", atlas, Vector2(0.0f, 675.0f), Vector2(248.f, 225.f), 8, 240.f);

		at->Create(L"GOLEM_SMASH_DOWN", atlas, Vector2(0.0f, 900.f), Vector2(248.f, 225.f), 15, 240.f, 0.1f);
		at->Create(L"GOLEM_SMASH_LEFT", atlas, Vector2(0.0f, 1125.0f), Vector2(248.f, 225.f), 15, 240.f, 0.1f);
		at->Create(L"GOLEM_SMASH_RIGHT", atlas, Vector2(0.0f, 1350.0f), Vector2(248.f, 225.f), 15, 240.f, 0.1f);
		at->Create(L"GOLEM_SMASH_UP", atlas, Vector2(0.0f, 1575.0f), Vector2(248.f, 225.f), 15, 240.f, 0.1f);

		at->Create(L"GOLEM_TELEPORT_ATTACK_PREV_DOWN", atlas, Vector2(0.0f, 1800.f), Vector2(248.f, 225.f), 5, 240.f, 0.1f);
		at->Create(L"GOLEM_TELEPORT_ATTACK_PREV_LEFT", atlas, Vector2(0.0f, 2025.0f), Vector2(248.f, 225.f), 5, 240.f, 0.1f);
		at->Create(L"GOLEM_TELEPORT_ATTACK_PREV_RIGHT", atlas, Vector2(0.0f, 2250.0f), Vector2(248.f, 225.f), 5, 240.f, 0.1f);
		at->Create(L"GOLEM_TELEPORT_ATTACK_PREV_UP", atlas, Vector2(0.0f, 2475.f), Vector2(248.f, 225.f), 5, 240.f, 0.1f);
		
		at->Create(L"GOLEM_TELEPORT_ATTACK_DOWN", atlas, Vector2(992.f, 1800.f), Vector2(248.f, 225.f), 10, 240.f, 0.1f);
		at->Create(L"GOLEM_TELEPORT_ATTACK_LEFT", atlas, Vector2(992.f, 2025.0f), Vector2(248.f, 225.f), 10, 240.f, 0.1f);
		at->Create(L"GOLEM_TELEPORT_ATTACK_RIGHT", atlas, Vector2(992.f, 2250.0f), Vector2(248.f, 225.f), 10, 240.f, 0.1f);
		at->Create(L"GOLEM_TELEPORT_ATTACK_UP", atlas, Vector2(992.f, 2475.f), Vector2(248.f, 225.f), 10, 240.f, 0.1f);

		at->Create(L"GOLEM_ATTACK_DOWN", atlas, Vector2(0.0f, 1800.f), Vector2(248.f, 225.f), 15, 240.f, 0.1f);
		at->Create(L"GOLEM_ATTACK_LEFT", atlas, Vector2(0.0f, 2025.0f), Vector2(248.f, 225.f), 15, 240.f, 0.1f);
		at->Create(L"GOLEM_ATTACK_RIGHT", atlas, Vector2(0.0f, 2250.0f), Vector2(248.f, 225.f), 15, 240.f, 0.1f);
		at->Create(L"GOLEM_ATTACK_UP", atlas, Vector2(0.0f, 2475.f), Vector2(248.f, 225.f), 15, 240.f, 0.1f);

		at->PlayAnimation(L"GOLEM_MOVE_UP", true);

		sn::Collider2D* collider = pMon->AddComponent<sn::Collider2D>();
		collider->SetSize(Vector2(0.2f, 0.25f));
		collider->SetCenter(Vector2(0.0f, -0.1f));

		sn::Collider2D* collider2 = pMon->AddComponent<sn::Collider2D>();
		collider2->SetEnable(false);
		collider2->SetName(L"Mini_Boss_Second_Collider");

		sn::Collider2D* collider3 = pMon->AddComponent<sn::Collider2D>();
		collider3->SetEnable(false);
		collider3->SetName(L"Mini_Boss_Third_Collider");

		AI* ai = pMon->AddComponent<AI>(pMon);
		ai->AddState(new MiniBossIdle);
		ai->AddState(new MiniBossTrace);
		ai->AddState(new MiniBossAttack);
		ai->AddState(new MiniBossSmash);
		ai->AddState(new MiniBossTeleportAttack);
		ai->SetCurState(MON_STATE::MINIBOSS_IDLE);

		pMon->AddComponent<MiniBossHPBar>();

		std::vector<eItemType> eItems;
		eItems.push_back(eItemType::Crystal_Energy);
		eItems.push_back(eItemType::Crystal_Energy);
		eItems.push_back(eItemType::Golem_Core);
		eItems.push_back(eItemType::Golem_Core);
		eItems.push_back(eItemType::Reinforced_Steel);
		eItems.push_back(eItemType::Reinforced_Steel);
		eItems.push_back(eItemType::Reinforced_Steel);
		eItems.push_back(eItemType::Golem_King_Design);
		eItems.push_back(eItemType::Golem_King_Design);
		eItems.push_back(eItemType::Broken_Sword);
		eItems.push_back(eItemType::Broken_Sword);
		DroppingItem* di = pMon->AddComponent<DroppingItem>(eItems);
	}
	break;
	case MonType::SLIMEHERMIT:
	{
		pMon = new SlimeHermit;
		pMon->SetName(L"SlimeHermit");
		Transform* tr = pMon->GetComponent<Transform>();
		tr->SetPosition(Vector3(_vPos.x, _vPos.y, 0.0f));

		tMonInfo info = {};
		info.fAtt = 20.f;
		info.fAttRange = 0.75f;
		info.fRecogRange = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 0.5f;
		info.fAttTime = 7.8f;
		info.fAttDelay = 0.f;

		pMon->SetMonInfo(info);

		MeshRenderer* mr = pMon->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> atlas
			= Resources::Load<Texture>(L"Slime_Hermit_Move", L"..\\Resources\\Texture\\Dungeon\\Enemy\\SlimeHermit\\Slime_Hermit.png");
		Animator* at = pMon->AddComponent<Animator>();

		at->Create(L"SLIME_HERMIT_WALK_UP", atlas, Vector2(0.0f, 0.0f), Vector2(200.f, 220.0f), 11);
		at->Create(L"SLIME_HERMIT_WALK_RIGHT", atlas, Vector2(0.0f, 220.0f), Vector2(200.f, 220.0f), 11);
		at->Create(L"SLIME_HERMIT_WALK_LEFT", atlas, Vector2(0.0f, 440.0f), Vector2(200.f, 220.0f), 11);
		at->Create(L"SLIME_HERMIT_WALK_DOWN", atlas, Vector2(0.0f, 660.0f), Vector2(200.f, 220.0f), 11);

		at->Create(L"SLIME_HERMIT_ATT_UP", atlas, Vector2(0.0f, 880.0f), Vector2(200.f, 220.0f), 52, 240.f,0.15f);
		at->Create(L"SLIME_HERMIT_ATT_RIGHT", atlas, Vector2(0.0f, 1100.0f), Vector2(200.f, 220.0f), 52, 240.f, 0.15f);
		at->Create(L"SLIME_HERMIT_ATT_LEFT", atlas, Vector2(0.0f, 1320.0f), Vector2(200.f, 220.0f), 52, 240.f, 0.15f);
		at->Create(L"SLIME_HERMIT_ATT_DOWN", atlas, Vector2(0.0f, 1540.0f), Vector2(200.f, 220.0f), 52, 240.f, 0.15f);

		sn::Collider2D* collider = pMon->AddComponent<sn::Collider2D>();
		collider->SetSize(Vector2(0.4f, 0.4f));

		AI* ai = pMon->AddComponent<AI>(pMon);
		ai->AddState(new MonsterIdle);
		ai->AddState(new MonsterTrace);
		ai->AddState(new TurretBrokenAttack);
		ai->SetCurState(MON_STATE::IDLE);

		MonsterHPBar* monsterHPBar = pMon->AddComponent<MonsterHPBar>();
		monsterHPBar->CreateHpBar();
	}
	break;

	case MonType::GOLEMKING:
	{
		pMon = new GolemKing;
		pMon->SetName(L"GolemKing");
		Transform* tr = pMon->GetComponent<Transform>();
		tr->SetPosition(Vector3(_vPos.x, _vPos.y, 0.0f));
		tr->SetScale(5.5f, 5.5f, 3.0f);

		tMonInfo info = {};
		info.fAtt = 30.f;
		info.fAttRange = 1.5f;
		info.fRecogRange = 300.f;
		info.fHP = 1000.f;
		info.fSpeed = 0.5f;
		info.fAttTime = 1.5f;
		info.fAttDelay = 1.f;

		pMon->SetMonInfo(info);

		MeshRenderer* mr = pMon->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> atlas
			= Resources::Load<Texture>(L"GolemKing", L"..\\Resources\\Texture\\Dungeon\\Enemy\\GolemKing\\Boss1.png");
		Animator* at = pMon->AddComponent<Animator>();

		at->Create(L"GOLEMKING_UP", atlas, Vector2(0.0f, 0.0f), Vector2(350.f, 350.f), 32, 360.f);
		at->Create(L"GOLEMKING_IDLE", atlas, Vector2(0.0f, 350.f), Vector2(350.f, 350.f), 16, 360.f);
		at->Create(L"GOLEMKING_ROCK_ATTACK", atlas, Vector2(0.0f, 700.f), Vector2(350.f, 350.f), 43, 360.f, 0.07f);
		at->Create(L"GOLEMKING_ARM_LAUNCH", atlas, Vector2(0.0f, 1050.f), Vector2(350.f, 350.f), 20, 360.f);
		at->Create(L"GOLEMKING_NO_ARM_IDLE", atlas, Vector2(0.0f, 1400.f), Vector2(350.f, 350.f), 16, 360.f);
		at->Create(L"GOLEMKING_ARM_RECOVER", atlas, Vector2(0.0f, 1750.f), Vector2(350.f, 350.f), 11, 360.f);
		at->Create(L"GOLEMKING_AIM_PREPARE", atlas, Vector2(0.0f, 2100.f), Vector2(350.f, 350.f), 16, 360.f);
		at->Create(L"GOLEMKING_AIM_CYCLE_1", atlas, Vector2(0.0f, 2450.f), Vector2(350.f, 350.f), 16, 360.f);
		at->Create(L"GOLEMKING_AIM_CYCLE_2", atlas, Vector2(0.0f, 2800.f), Vector2(350.f, 350.f), 16, 360.f);
		at->Create(L"GOLEMKING_AIM_END", atlas, Vector2(0.0f, 3150.f), Vector2(350.f, 350.f), 32, 360.f);

		atlas = Resources::Load<Texture>(L"GolemKing_Shoot", L"..\\Resources\\Texture\\Dungeon\\Enemy\\GolemKing\\FistShoot.png");

		at->Create(L"GOLEMKING_AIM_SHOOT", atlas, Vector2(0.0f, 700.f), Vector2(350.f, 350.f), 16, 360.f);


		atlas = Resources::Load<Texture>(L"dead1", L"..\\Resources\\Texture\\Dungeon\\Enemy\\GolemKing\\dead1.png");

		at->Create(L"GOLEMKING_DEATH", atlas, Vector2(0.0f, 0.f), Vector2(308.f, 350.f), 41, 360.f, 0.1f, Vector2(0.f,0.0f));

		atlas = Resources::Load<Texture>(L"dead2", L"..\\Resources\\Texture\\Dungeon\\Enemy\\GolemKing\\dead2.png");

		at->Create(L"GOLEMKING_DEATH01", atlas, Vector2(0.0f, 0.f), Vector2(350.f, 350.f), 41, 360.f, 0.1f, Vector2(0.f,0.0f));

		at->PlayAnimation(L"GOLEMKING_IDLE", true);

		sn::Collider2D* collider = pMon->AddComponent<sn::Collider2D>();
		collider->SetName(L"GolemKing_First_Collider");
		collider->SetSize(Vector2(0.4f, 0.4f));
		collider->SetCenter(Vector2(-0.1f, -0.3f));

		sn::Collider2D* collider2 = pMon->AddComponent<sn::Collider2D>();
		collider2->SetName(L"GolemKing_Rock_Attack_Collider");
		collider2->SetSize(Vector2(0.3f, 0.1f));
		collider2->SetCenter(Vector2(0.3f, -1.9f));
		collider2->SetEnable(false);

		sn::Collider2D* collider3 = pMon->AddComponent<sn::Collider2D>();
		collider3->SetName(L"GolemKing_Wave_Collider");
		collider3->SetSize(Vector2(0.5f, 0.4f));
		collider3->SetCenter(Vector2(-0.5f, -1.3f));
		collider3->SetEnable(false);

		AI* ai = pMon->AddComponent<AI>(pMon);
		ai->AddState(new GolemKingUp);
		ai->AddState(new GolemKingIdle);
		ai->AddState(new GolemKingRockAttack);
		ai->AddState(new GolemKingArmAttack);
		ai->AddState(new GolemKingArmIdle);
		ai->AddState(new GolemKingArmRecover);
		ai->AddState(new GolemKingAimAttack);
		ai->AddState(new GolemKingWave);
		ai->AddState(new GolemKingAimCycle);
		ai->AddState(new GolemKingAimShoot);
		ai->AddState(new GolemKingAimEnd);
		ai->AddState(new GolemKingDeath);
		ai->AddState(new GolemKingDeath01);
		ai->SetCurState(MON_STATE::GOLEMKING_UP);

		pMon->AddComponent<MiniBossHPBar>();

		std::vector<eItemType> eItems;
		eItems.push_back(eItemType::Slime_Jelly);
		eItems.push_back(eItemType::Slime_Jelly);
		eItems.push_back(eItemType::Golem_Pieces);
		eItems.push_back(eItemType::Golem_Core);
		DroppingItem* di = pMon->AddComponent<DroppingItem>(eItems);
	}
	break;
	default:
		break;
	}

    return pMon;
}
