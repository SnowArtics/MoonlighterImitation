#include "Monster.h"
#include "../Engine_SOURCE/AI.h"
#include "../Engine_SOURCE/snCollider2D.h"

Monster::Monster()
{
	this->AddComponent<sn::Collider2D>();
}

Monster::~Monster()
{
	if (nullptr != m_pAI) {
		delete m_pAI;
	}
}

void Monster::Update()
{
	if (nullptr != m_pAI)
		m_pAI->Update();
}
