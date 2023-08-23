#include "Monster.h"
#include "../Engine_SOURCE/AI.h"
#include "../Engine_SOURCE/snCollider2D.h"
#include <snMeshRenderer.h>
#include "snTime.h"

using namespace sn;

Monster::Monster()
	:m_tInfo{}
	, monsterMapPos({ -1,-1 })
	, time(0.f)
	,hitTime(0.f)
	, deadTime(0.f)
{
}

Monster::~Monster()
{
}

void Monster::Initialize()
{
	GameObject::Initialize();
}

void Monster::Update()
{
	if (m_tInfo.fHP <= 0.f) {
		SetState(eState::Dead);
		return;
	}

	//0 is normal, 1 is hit, 2 is dead
	int monsterState = this->GetComponent<MeshRenderer>()->GetMonsterCB().state;

	if (monsterState == 1) {
		hitTime += Time::DeltaTime();
		if (hitTime > 0.3f) {
			hitTime = 0.f;
			MeshRenderer* meshRenderer = this->GetComponent<MeshRenderer>();
			renderer::MonsterCB monsterCB = {};
			monsterCB.state = 0;
			meshRenderer->SetMonsterCB(monsterCB);
		}
	}
	else if (monsterState == 2) {
		deadTime += Time::DeltaTime();
		if (deadTime > 1.f) {
			deadTime = 0.f;
		}
	}

	GameObject::Update();
}

void Monster::LateUpdate()
{
	GameObject::LateUpdate();
}

void Monster::Render()
{
	GameObject::Render();
}

void Monster::OnCollisionEnter(sn::Collider2D* other)
{
	if (other->GetName() == L"SecondCollider") {
		MeshRenderer* meshRenderer = this->GetComponent<MeshRenderer>();
		renderer::MonsterCB monsterCB = {};
		monsterCB.state = 1;
		meshRenderer->SetMonsterCB(monsterCB);
	}
}

void Monster::OnCollisionStay(sn::Collider2D* other)
{
}

void Monster::OnCollisionExit(sn::Collider2D* other)
{
	//if (other->GetName() == L"SecondCollider") {		
	//	MeshRenderer* meshRenderer = this->GetComponent<MeshRenderer>();
	//	renderer::MonsterCB monsterCB = {};
	//	monsterCB.state = 0;
	//	meshRenderer->SetMonsterCB(monsterCB);
	//}
}
