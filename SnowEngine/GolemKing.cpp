#include "GolemKing.h"

#include "AI.h"
#include "snAnimator.h"

GolemKing::GolemKing()
{
}

GolemKing::~GolemKing()
{
}

void GolemKing::Initialize()
{
	Monster::Initialize();
}

void GolemKing::Update()
{
	AI* ai = GetComponent<AI>();
	MON_STATE monState = ai->GetCurStateName();

	Animator* animator = GetComponent<Animator>();

	if (monState != ai->GetPrevStateName()) {
		switch (monState)
		{
		case MON_STATE::GOLEMKING_UP:
		{
			animator->PlayAnimation(L"GOLEMKING_UP", false);
		}
		break;
		case MON_STATE::GOLEMKING_IDLE:
		{
			animator->PlayAnimation(L"GOLEMKING_IDLE", true);
		}
			break;
		case MON_STATE::GOLEMKING_ROCK_ATTACK:
		{
			animator->PlayAnimation(L"GOLEMKING_ROCK_ATTACK", false);
		}
		break;
		case MON_STATE::GOLEMKING_ARM_ATTACK:
		{
			animator->PlayAnimation(L"GOLEMKING_ARM_LAUNCH", false);
		}
		break;
		case MON_STATE::GOLEMKING_AIM_ATTACK:
		{
			animator->PlayAnimation(L"GOLEMKING_AIM_PREPARE", false);
		}
		break;
		case MON_STATE::DEAD:
			break;
		default:
			break;
		}


	}

	Monster::Update();
}

void GolemKing::LateUpdate()
{
	Monster::LateUpdate();
}

void GolemKing::Render()
{
	Monster::Render();
}

void GolemKing::OnCollisionEnter(sn::Collider2D* other, sn::Collider2D* me)
{
}

void GolemKing::OnCollisionStay(sn::Collider2D* other, sn::Collider2D* me)
{
}

void GolemKing::OnCollisionExit(sn::Collider2D* other, sn::Collider2D* me)
{
}
