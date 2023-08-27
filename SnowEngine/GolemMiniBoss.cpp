#include "GolemMiniBoss.h"

#include "AI.h"
#include "snAnimator.h"
#include "snSceneManager.h"
#include "DungeonMapManager.h"
#include "MonsterHPBar.h"

#include <random>

GolemMiniBoss::GolemMiniBoss()
{
}

GolemMiniBoss::~GolemMiniBoss()
{
}

void GolemMiniBoss::Initialize()
{
	Monster::Initialize();
}

void GolemMiniBoss::Update()
{
	AI* ai = GetComponent<AI>();
	MonDir monDir = ai->GetCurDir();
	MON_STATE monState = ai->GetCurStateName();

	Transform* monTr = this->GetComponent <Transform>();
	sn::Collider2D* collider = this->GetComponent<sn::Collider2D>();

	Animator* animator = GetComponent<Animator>();

	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> distribution(1, 2);

	int randomNum = distribution(gen);

	if (monDir != ai->GetPrevDir() || monState != ai->GetPrevStateName()) {
		switch (monState)
		{
		case MON_STATE::IDLE:
			break;
		case MON_STATE::WALK:
			break;
		case MON_STATE::TRACE:
		{
			switch (monDir)
			{
			case MonDir::UP:
				animator->PlayAnimation(L"GOLEM_MOVE_UP", true);
				break;
			case MonDir::DOWN:
				animator->PlayAnimation(L"GOLEM_MOVE_DOWN", true);
				break;
			case MonDir::RIGHT:
				animator->PlayAnimation(L"GOLEM_MOVE_RIGHT", true);
				break;
			case MonDir::LEFT:
				animator->PlayAnimation(L"GOLEM_MOVE_LEFT", true);
				break;
			default:
				break;
			}
		}
		break;
		case MON_STATE::ATT:
		{
			if (randomNum == 1) {
				switch (monDir)
				{
				case MonDir::UP:
					animator->PlayAnimation(L"GOLEM_ATTACK_UP", true);
					break;
				case MonDir::DOWN:
					animator->PlayAnimation(L"GOLEM_ATTACK_DOWN", true);
					break;
				case MonDir::RIGHT:
					animator->PlayAnimation(L"GOLEM_ATTACK_RIGHT", true);
					break;
				case MonDir::LEFT:
					animator->PlayAnimation(L"GOLEM_ATTACK_LEFT", true);
					break;
				default:
					break;
				}
			}
			else if (randomNum == 2) {
				switch (monDir)
				{
				case MonDir::UP:
					animator->PlayAnimation(L"GOLEM_SMASH_UP", true);
					break;
				case MonDir::DOWN:
					animator->PlayAnimation(L"GOLEM_SMASH_DOWN", true);
					break;
				case MonDir::RIGHT:
					animator->PlayAnimation(L"GOLEM_SMASH_RIGHT", true);
					break;
				case MonDir::LEFT:
					animator->PlayAnimation(L"GOLEM_SMASH_LEFT", true);
					break;
				default:
					break;
				}
			}			
		}
		break;
		default:
			break;
		}

	}
	Monster::Update();
}

void GolemMiniBoss::LateUpdate()
{
	Monster::LateUpdate();
}

void GolemMiniBoss::Render()
{
	Monster::Render();
}

void GolemMiniBoss::OnCollisionEnter(sn::Collider2D* other)
{
}

void GolemMiniBoss::OnCollisionStay(sn::Collider2D* other)
{
}

void GolemMiniBoss::OnCollisionExit(sn::Collider2D* other)
{
}
