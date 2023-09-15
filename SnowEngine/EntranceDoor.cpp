#include "EntranceDoor.h"
#include "snGameObject.h"
#include "snTime.h"
#include "snCollider2D.h"
#include "snAnimator.h"
#include "snSceneManager.h"
#include "snMeshRenderer.h"
#include "snResources.h"
#include "snInput.h"

EntranceDoor::EntranceDoor()
	:time(0.0f)
	, doorState(0)
	, enterUI(nullptr)
{	
}

EntranceDoor::~EntranceDoor()
{
}

void EntranceDoor::Initialize()
{
}

void EntranceDoor::Update()
{
	if (doorState == 0) {
		time += Time::DeltaTime();
		if (time >= 0.7f) {
			doorState = 1;
		}
	}
	else if (doorState == 1 && Input::GetKeyDown(eKeyCode::J)) {		
		doorState = 3;
	}
	else if (doorState == 3) {
		if (time == 0.f) {
			SceneManager::GetActiveScene()->GetPlayer()->SetEnable(false);
			Animator* at = GetOwner()->GetComponent<Animator>();
			at->PlayAnimation(L"Door_Entrance", false);
		}
		else if (time >= 2.5f) {
			SceneManager::SetChangeScene(L"DungeonScene01");
		}
		time += Time::DeltaTime();
	}
	else {
		time = 0.f;
	}
}

void EntranceDoor::LateUpdate()
{
}

void EntranceDoor::Render()
{
}

void EntranceDoor::OnCollisionEnter(sn::Collider2D* other)
{
	if (other->GetName() == L"FisrtCollider") {
		doorState = 0;
		
		Animator* at = GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"Door_Open", false);
	}
}

void EntranceDoor::OnCollisionStay(sn::Collider2D* other)
{
	if (other->GetName() == L"FisrtCollider") {
		enterUI->SetEnable(true);
		if (doorState == 1) {
			Animator* at = GetOwner()->GetComponent<Animator>();
			at->PlayAnimation(L"Door_Cycle", true);
		}		
	}
}

void EntranceDoor::OnCollisionExit(sn::Collider2D* other)
{
	if (other->GetName() == L"FisrtCollider") {
		doorState = 2;
		Animator* at = GetOwner()->GetComponent<Animator>();
		at->PlayAnimation(L"Door_Close", false);
		enterUI->SetEnable(false);
	}
}

void EntranceDoor::Init()
{
	enterUI = new sn::GameObject;
	SceneManager::GetActiveScene()->AddGameObject(eLayerType::InteractionUI, enterUI);

	MeshRenderer* mr = enterUI->AddComponent<MeshRenderer>();
	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	mr->SetMaterial(Resources::Find<Material>(L"InteractionJKeyMaterial"));

	Vector3 ownerVec3 = GetOwner()->GetComponent<Transform>()->GetPosition();

	Transform* tr = enterUI->GetComponent<Transform>();
	tr->SetPosition(Vector3(ownerVec3.x, ownerVec3.y+1.0f, ownerVec3.z - 2.0f));
	tr->SetScale(Vector3(0.5f,0.5f,1.0f));

	enterUI->SetEnable(false);
}
