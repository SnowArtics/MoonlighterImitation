#include "snRollState.h"
#include "..\Engine_SOURCE\snGameObject.h"
#include "..\Engine_SOURCE\snTransform.h"
#include "..\Engine_SOURCE\snTime.h"
#include "..\Engine_SOURCE\snInput.h"
#include "snCollider2D.h"
#include <snAudioSource.h>
#include "snResources.h"

RollState::RollState()
	: PlayerState(PLAYER_STATE::ROLL)
	, time(0.f)
{
}

RollState::~RollState()
{
}

void RollState::Update()
{
	if (time == 0.f) {
		AudioSource* as = GetPlayerFSM()->GetOwner()->GetComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"will_roll", L"..\\Resources\\Sound\\SoundEffect\\Will\\will_roll.wav"));
		as->Play();
		as->SetVolume(3);
		as->SetLoop(false);
	}

	time += Time::DeltaTime();

	sn::Collider2D* collider = GetPlayerFSM()->GetOwner()->GetComponent<sn::Collider2D>();
	collider->SetEnable(false);

	std::vector<PLAYER_DIR>& actionDir = GetPlayerFSM()->GetActionDir();
	Transform* tr = GetPlayerFSM()->GetOwner()->GetComponent<Transform>();
	Vector3 pos = tr->GetPosition();

	if (actionDir.size() == 0) {
		switch (GetPlayerFSM()->GetDirection())
		{
		case PLAYER_DIR::UP:
			pos.y += 2.0f * Time::DeltaTime();
			GetPlayerFSM()->SetDirection(PLAYER_DIR::UP);
			tr->SetPosition(pos);
			break;
		case PLAYER_DIR::DOWN:
			pos.y -= 2.0f * Time::DeltaTime();
			GetPlayerFSM()->SetDirection(PLAYER_DIR::DOWN);
			tr->SetPosition(pos);
			break;
		case PLAYER_DIR::RIGHT:
			pos.x += 2.0f * Time::DeltaTime();
			GetPlayerFSM()->SetDirection(PLAYER_DIR::RIGHT);
			tr->SetPosition(pos);
			break;
		case PLAYER_DIR::LEFT:
			pos.x -= 2.0f * Time::DeltaTime();
			GetPlayerFSM()->SetDirection(PLAYER_DIR::LEFT);
			tr->SetPosition(pos);
			break;
		default:
			break;
		}
	}

	for (int i = 0; i < actionDir.size(); i++) {
		switch (actionDir[i])
		{
		case PLAYER_DIR::UP:
			pos.y += 2.0f * Time::DeltaTime();
			GetPlayerFSM()->SetDirection(PLAYER_DIR::UP);
			tr->SetPosition(pos);
			break;
		case PLAYER_DIR::DOWN:
			pos.y -= 2.0f * Time::DeltaTime();
			GetPlayerFSM()->SetDirection(PLAYER_DIR::DOWN);
			tr->SetPosition(pos);
			break;
		case PLAYER_DIR::RIGHT:
			pos.x += 2.0f * Time::DeltaTime();
			GetPlayerFSM()->SetDirection(PLAYER_DIR::RIGHT);
			tr->SetPosition(pos);
			break;
		case PLAYER_DIR::LEFT:
			pos.x -= 2.0f * Time::DeltaTime();
			GetPlayerFSM()->SetDirection(PLAYER_DIR::LEFT);
			tr->SetPosition(pos);
			break;
		default:
			break;
		}
	}

	if (time > 0.48f) {
		GetPlayerFSM()->ChangeState(PLAYER_STATE::MOVE);
		collider->SetEnable(true);
	}
}

void RollState::Enter()
{
}

void RollState::Exit()
{
	time = 0.f;
}
