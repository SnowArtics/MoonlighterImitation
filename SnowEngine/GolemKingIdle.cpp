#include "GolemKingIdle.h"

#include "snTime.h"
#include "snSceneManager.h"
#include <random>

GolemKingIdle::GolemKingIdle()
	:State(MON_STATE::GOLEMKING_IDLE)
	, endTime(1.6f)
	, executionTime(0.f)
	, randomNumLow(1)
	, randomNumHigh(1)
{
}

GolemKingIdle::~GolemKingIdle()
{	
}

void GolemKingIdle::Update()
{
	executionTime += Time::DeltaTime();

	//���� ���� ����
	std::random_device rd;
	std::mt19937 gen(rd());

	//std::uniform_int_distribution<> distribution(1, 1);
	std::uniform_int_distribution<> distribution(randomNumLow, randomNumHigh);

	int randomNum = distribution(gen); // randomNums�� 1�϶� �ָ� �ֵθ���, 2�϶� �����, 3�϶� �� �߻�, 4�϶� ������ �߻�

	if (executionTime >= endTime) {
		executionTime = 0.f;
		switch (randomNum)
		{
		case 1:
		{
			SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_ROCK_ATTACK);
			randomNumLow = 2;
			randomNumHigh = 4;
		}
		break;
		case 2:
		{			
			SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_ARM_LAUNCH);
			randomNumLow = 3;
		}
		break;
		case 3:
		{
			SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_AIM_PREPARE);
			randomNumLow = 1;
		}
		break;
		case 4:
		{
			SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_WAVE);
		}
		break;
		default:
			break;
		}
	}
}

void GolemKingIdle::Enter()
{
}

void GolemKingIdle::Exit()
{
}
