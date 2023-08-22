#include "MonFactory.h"
#include "Monster.h"
#include "../Engine_SOURCE/snTransform.h"
#include "snAnimator.h"
#include "snResources.h"
#include "snCollider2D.h"
#include "snMesh.h"
#include "snMeshRenderer.h"
#include "snMaterial.h"
#include "AI.h"
#include "MonsterIdle.h"
#include "MonsterTrace.h"
#include "MonsterAttack.h"
#include "SlimeAttack.h"
#include "TurretAttack.h"

#include "Golem.h"
#include "Slime.h"
#include "MiniSlime.h"
#include "FylingRepairGolem.h"
#include "GolemTurretBroken.h"

using namespace sn;

Monster* MonFactory::CreateMonster(MonType _eType, sn::math::Vector2 _vPos)
{
    Monster* pMon = nullptr;

	switch (_eType)
	{
	case MonType::GOLEM:
	{
		pMon = new Golem;
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

		AI* ai = pMon->AddComponent<AI>(pMon);
		ai->AddState(new MonsterIdle);
		ai->AddState(new MonsterTrace);
		ai->AddState(new MonsterAttack);
		ai->SetCurState(MON_STATE::IDLE);
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
		info.fAttRange = 1.5f; //-1이면 Trace상태에서 벗어나지 않음.
		info.fRecogRange = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 0.75f;
		info.fAttTime = 1.2f;
		info.fAttDelay = 1.f;

		pMon->SetMonInfo(info);

		MeshRenderer* mr = pMon->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

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
	}
		break;

	case MonType::BABYSLIME:
	{
		pMon = new MiniSlime;
		Transform* tr = pMon->GetComponent<Transform>();
		tr->SetPosition(Vector3(_vPos.x, _vPos.y, 0.0f));
		tr->SetScale(Vector3(0.5f, 0.5f,0.0f));

		tMonInfo info = {};
		info.fAtt = 15.f;
		info.fAttRange = -1.f; //-1이면 Trace상태에서 벗어나지 않음.
		info.fRecogRange = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 0.75f;
		info.fAttTime = -1.f;
		info.fAttDelay = 0.f;

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
	}
	break;
	case MonType::FYLINGREPAIRGOLEM:
	{
		pMon = new FylingRepairGolem;
		Transform* tr = pMon->GetComponent<Transform>();
		tr->SetPosition(Vector3(_vPos.x, _vPos.y, 0.0f));
		tr->SetScale(Vector3(2.5f, 2.5f, 2.5f));

		tMonInfo info = {};
		info.fAtt = 15.f;
		info.fAttRange = -1.f; //-1이면 Trace상태에서 벗어나지 않음.
		info.fRecogRange = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 0.75f;
		info.fAttTime = -1.f;
		info.fAttDelay = 0.f;

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
	}
		break;
	case MonType::GOLEMTURRET:
	{

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
		info.fAttTime = 2.4f;
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

		at->Create(L"GOLEM_TURRET_BROKEN_SHOT_DOWN",atlas, Vector2(33.0f, 0.0f), Vector2(33.0f, 40.0f), 10, 120.f, 0.08f);
		at->Create(L"GOLEM_TURRET_BROKEN_SHOT_LEFT", atlas, Vector2(33.0f, 40.0f), Vector2(33.0f, 40.0f), 10, 120.f, 0.08f);
		at->Create(L"GOLEM_TURRET_BROKEN_SHOT_RIGHT", atlas, Vector2(33.0f, 80.0f), Vector2(33.0f, 40.0f), 10, 120.f, 0.08f);
		at->Create(L"GOLEM_TURRET_BROKEN_SHOT_UP", atlas, Vector2(33.0f, 120.0f), Vector2(33.0f, 40.0f), 10, 120.f, 0.08f);

		at->PlayAnimation(L"GOLEM_TURRET_BROKEN_SHOT_LEFT", true);

		sn::Collider2D* collider = pMon->AddComponent<sn::Collider2D>();
		collider->SetSize(Vector2(0.2f, 0.2f));

		AI* ai = pMon->AddComponent<AI>(pMon);
		ai->AddState(new MonsterTrace);
		ai->AddState(new MonsterIdle);
		ai->AddState(new TurretAttack);
		ai->SetCurState(MON_STATE::IDLE);
	}
	break;
	case MonType::GOLEMMINIBOSS:
	{

	}
	break;
	case MonType::GOLEMCORRUPTMINIBOSS:
	{

	}
	break;
	case MonType::SLIMEHERMIT:
	{

	}
	break;
	default:
		break;
	}

    return pMon;
}
