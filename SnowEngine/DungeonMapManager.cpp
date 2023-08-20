#include "DungeonMapManager.h"
#include "snCollider2D.h"

using namespace sn;

DungeonMapManager::DungeonMapManager()
{
}

DungeonMapManager::~DungeonMapManager()
{
}

void DungeonMapManager::MakeCliffCollider(int _num, GameObject* _background)
{	
	sn::Collider2D* cdUP = _background->AddComponent<sn::Collider2D>();
	cdUP->SetSize(Vector2(cdUP->GetSize().x - 0.1f, 0.1f));
	cdUP->SetCenter(Vector2(0.0f, -2.3f));
	sn::Collider2D* cdDOWN = _background->AddComponent<sn::Collider2D>();
	cdDOWN->SetSize(Vector2(cdUP->GetSize().x - 0.1f, 0.1f));
	cdDOWN->SetCenter(Vector2(0.0f, +2.3f));
	sn::Collider2D* cdLEFT = _background->AddComponent<sn::Collider2D>();
	cdLEFT->SetSize(Vector2(0.1f, cdUP->GetSize().y - 1.f));
	cdLEFT->SetCenter(Vector2(-4.18f, 0.0f));
	sn::Collider2D* cdRIGHT = _background->AddComponent<sn::Collider2D>();
	cdRIGHT->SetSize(Vector2(0.1f, cdUP->GetSize().y - 1.f));
	cdRIGHT->SetCenter(Vector2(4.15f, 0.0f));

	switch (_num)
	{
	case 0:
	{
		sn::Collider2D* cd01 = _background->AddComponent<sn::Collider2D>();
		cd01->SetName(L"CliffCollider");
		cd01->SetSize(Vector2(0.295, 0.06f));
		cd01->SetCenter(Vector2(-2.25f, +1.85f));

		//sn::Collider2D* cd02 = _background->AddComponent<sn::Collider2D>();
		//cd02->SetName(L"CliffCollider");
		//cd02->SetSize(Vector2(0.295, 0.06f));
		//cd02->SetCenter(Vector2(-2.25f, +1.85f));
	}
		break;
	case 1:
	{

	}
	break;
	case 2:
	{

	}
	break;
	case 3:
	{

	}
	break;
	case 4:
	{

	}
	break;
	case 5:
	{

	}
	break;
	case 6:
	{

	}
	break;
	case 7:
	{

	}
	break;

	default:
		break;
	}
}
