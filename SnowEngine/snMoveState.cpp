#include "snMoveState.h"
#include "..\Engine_SOURCE\snGameObject.h"
#include "..\Engine_SOURCE\snTransform.h"
#include "..\Engine_SOURCE\snTime.h"
#include "..\Engine_SOURCE\snInput.h"
#include "snTime.h"
#include <snAudioSource.h>
#include "snResources.h"
#include "snRigidBody.h"

MoveState::MoveState()
	:PlayerState(PLAYER_STATE::MOVE)
	, soundStartTime(0.0f)
	, soundEndTime(0.21f)
{
}

MoveState::~MoveState()
{
}

void MoveState::Update()
{
	if (soundStartTime == 0.f) {
		AudioSource* as = GetPlayerFSM()->GetOwner()->GetComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"will_step_golem_dungeon", L"..\\Resources\\Sound\\SoundEffect\\Will\\will_step_golem_dungeon.wav"));
		as->Play();
		as->SetVolume(1);
		as->SetLoop(false);
	}

	soundStartTime += Time::DeltaTime();

	if (soundStartTime >= 0.5f) {
		soundStartTime = 0.f;
	}

	Transform* tr = GetPlayerFSM()->GetOwner()->GetComponent<Transform>();
	Vector3 pos = tr->GetPosition();

	RigidBody* rb = GetPlayerFSM()->GetOwner()->GetComponent<RigidBody>();
	Vector3 velocity = rb->GetVelocity();

	std::vector<PLAYER_DIR>& actionDir = GetPlayerFSM()->GetActionDir();

	actionDir.clear();

	if(Input::GetKey(eKeyCode::A)&& Input::GetKey(eKeyCode::D))
		GetPlayerFSM()->ChangeState(PLAYER_STATE::IDLE);

	if (Input::GetKey(eKeyCode::W) && Input::GetKey(eKeyCode::S))
		GetPlayerFSM()->ChangeState(PLAYER_STATE::IDLE);

	Vector2 move = Vector2(0.f, 0.f);

	if (Input::GetKey(eKeyCode::A)&&GetPlayerFSM()->GetCanMove(PLAYER_DIR::LEFT))
	{
		//pos.x -= 2.3f * Time::DeltaTime();
		//tr->SetPosition(pos);
		move.x -= 1.0f;
		GetPlayerFSM()->SetDirection(PLAYER_DIR::LEFT);
		actionDir.push_back(PLAYER_DIR::LEFT);

	}
	if (Input::GetKey(eKeyCode::D) && GetPlayerFSM()->GetCanMove(PLAYER_DIR::RIGHT))
	{
		//pos.x += 2.3f * Time::DeltaTime();
		//tr->SetPosition(pos);
		move.x += 1.0f;
		GetPlayerFSM()->SetDirection(PLAYER_DIR::RIGHT);
		actionDir.push_back(PLAYER_DIR::RIGHT);
	}
	if (Input::GetKey(eKeyCode::S) && GetPlayerFSM()->GetCanMove(PLAYER_DIR::DOWN))
	{
		//pos.y -= 2.3f * Time::DeltaTime();
		//tr->SetPosition(pos);
		move.y -= 1.0f;
		GetPlayerFSM()->SetDirection(PLAYER_DIR::DOWN);
		actionDir.push_back(PLAYER_DIR::DOWN);		
	}
	if (Input::GetKey(eKeyCode::W) && GetPlayerFSM()->GetCanMove(PLAYER_DIR::UP))
	{
		//pos.y += 2.3f * Time::DeltaTime();
		//tr->SetPosition(pos);
		move.y += 1.0f;
		GetPlayerFSM()->SetDirection(PLAYER_DIR::UP);
		actionDir.push_back(PLAYER_DIR::UP);		
	}

	move.Normalize();
	pos.x += move.x * 2.3f * Time::DeltaTime();
	pos.y += move.y * 2.3f * Time::DeltaTime();

	velocity.x = move.x * 2.3f;
	velocity.y = move.y * 2.3f;

	//tr->SetPosition(pos);
	rb->SetVelocity(velocity);

	if (!(Input::GetKey(eKeyCode::A))
		&& !(Input::GetKey(eKeyCode::D))
		&& !(Input::GetKey(eKeyCode::S))
		&& !(Input::GetKey(eKeyCode::W)) ) {
		GetPlayerFSM()->ChangeState(PLAYER_STATE::IDLE);
	}

	if (Input::GetKeyDown(eKeyCode::SPACE) && GetPlayerFSM()->IsKeyPresent(PLAYER_STATE::ROLL)) {
		GetPlayerFSM()->ChangeState(PLAYER_STATE::ROLL);
		return;
	}

	if (Input::GetKeyDown(eKeyCode::J) && GetPlayerFSM()->GetWeaponType() == WEAPON_TYPE::SHORT_SWORD&&GetPlayerFSM()->IsKeyPresent(PLAYER_STATE::ATTSWORD1))
		GetPlayerFSM()->ChangeState(PLAYER_STATE::ATTSWORD1);
	if (Input::GetKeyDown(eKeyCode::J) && GetPlayerFSM()->GetWeaponType() == WEAPON_TYPE::BOW&& GetPlayerFSM()->IsKeyPresent(PLAYER_STATE::ATTBOW))
		GetPlayerFSM()->ChangeState(PLAYER_STATE::ATTBOW);
}

void MoveState::Enter()
{
}

void MoveState::Exit()
{
}
