#include "GolemKingIdle.h"

#include "snTime.h"
#include "snSceneManager.h"
#include <random>

GolemKingIdle::GolemKingIdle()
	:State(MON_STATE::GOLEMKING_IDLE)
	, endTime(1.6f)
	, executionTime(0.f)
{
}

GolemKingIdle::~GolemKingIdle()
{	
}

void GolemKingIdle::Update()
{
	executionTime += Time::DeltaTime();

	//랜덤 패턴 시작
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> distribution(2, 2);

	int randomNum = distribution(gen); // randomNums이 1일때 주먹 휘두르기, 2일때 충격파, 3일때 손 발사, 4일때 레이저 발사

	if (executionTime >= endTime) {
		executionTime = 0.f;
		switch (randomNum)
		{
		case 1:
		{
			SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_ROCK_ATTACK);
		}
		break;
		case 2:
		{
			SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_WAVE);
		}
		break;
		case 3:
		{
			SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_ARM_ATTACK);
		}
		break;
		case 4:
		{
			SceneManager::ChangeMonsterState(GetAI(), MON_STATE::GOLEMKING_AIM_ATTACK);
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
