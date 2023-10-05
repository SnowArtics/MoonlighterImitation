#include "TitleDoor.h"

#include "snGameObject.h"
#include "snSceneManager.h"
#include "snMesh.h"
#include "snMeshRenderer.h"
#include "snResources.h"
#include "snInput.h"
#include "snTime.h"
#include <random>
#include "snTransform.h"
#include <snAudioSource.h>
#include <snAudioClip.h>
#include "snTextManager.h"

using namespace sn;

TitleDoor::TitleDoor()
	: startTime(0.0f)
	, endTime(0.0f)
	, doorOpenTrigger(false)
	, BGMTrigger(false)
	, TextTrigger(false)
	, TextAlbedo(0.f)
{
	{
		//왼쪽 문
		GameObject* Background = new GameObject();
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Background, Background);
		MeshRenderer* mr = Background->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"TitleLeftDoorMeterial"));
		Background->GetComponent<Transform>()->SetPosition(Vector3(-2.4f, 0.0f, -0.2f));
		//Background->GetComponent<Transform>()->SetScale(Vector3(6.7f, 4.0f, 2.0f));
		Background->GetComponent<Transform>()->SetScale(Vector3(4.861878453038f, 5.5f, 2.0f));

		leftDoor = Background;
	}

	{
		//오른쪽 문
		GameObject* Background = new GameObject();
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Background, Background);
		MeshRenderer* mr = Background->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"TitleRightDoorMeterial"));
		Background->GetComponent<Transform>()->SetPosition(Vector3(2.4f, 0.0f, -0.2f));
		//Background->GetComponent<Transform>()->SetScale(Vector3(6.7f, 4.0f, 2.0f));
		Background->GetComponent<Transform>()->SetScale(Vector3(4.861878453038f, 5.5f, 2.0f));

		rightDoor = Background;
	}

	{
	//가운데 선
		GameObject* Background = new GameObject();
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Background, Background);
		MeshRenderer* mr = Background->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"TitleMiddleLineMeterial"));
		Background->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -0.2f));
		//Background->GetComponent<Transform>()->SetScale(Vector3(0.01342281879f, 1.f, 2.0f));
		Background->GetComponent<Transform>()->SetScale(Vector3(0.02684563758f, 5.5f, 2.0f));

		middleLine = Background;
	}
}

TitleDoor::~TitleDoor()
{
}

void TitleDoor::Initialize()
{
}

void TitleDoor::Update()
{
	if (Input::GetKeyDown(eKeyCode::J) && !doorOpenTrigger) {
		doorOpenTrigger = true;
		middleLine->SetState(sn::GameObject::eState::Dead);
		middleLine = nullptr;

		AudioSource* as = GetOwner()->AddComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"main_menu_door_open", L"..\\Resources\\Sound\\SoundEffect\\Title\\main_menu_door_open.wav"));
		as->SetLoop(false);
		as->Play();
	}

	if (doorOpenTrigger) {
		startTime += Time::DeltaTime();
	}

	if (doorOpenTrigger && startTime > 0.001f && startTime <= 0.25f) {
		////랜덤 패턴 시작
		//std::random_device rd;
		//std::mt19937 gen(rd());

		//std::uniform_real_distribution<> distribution(-1.0f, 1.0f);

		//float randomNum = distribution(gen); // randomNums이 1일때 주먹 휘두르기, 2일때 충격파, 3일때 손 발사, 4일때 레이저 발사

		//Transform* leftTr = leftDoor->GetComponent<Transform>();
		//Vector3 leftPos = leftTr->GetPosition();

		//leftPos.x = leftPos.x * randomNum * 2.0f;
		//leftPos.y = -leftPos.y * randomNum * 2.0f;

		//leftTr->SetPosition(leftPos);

		//Transform* rightTr = rightDoor->GetComponent<Transform>();
		//Vector3 rightPos = rightTr->GetPosition();

		//rightPos.x = rightPos.x * randomNum * .1f;
		//rightPos.y = -rightPos.y * randomNum * .1f;

		//rightTr->SetPosition(rightPos);

		Transform* leftTr = leftDoor->GetComponent<Transform>();
		Vector3 leftPos = leftTr->GetPosition();

		leftPos.x -= 3.0f * Time::DeltaTime();

		leftTr->SetPosition(leftPos);

		Transform* rightTr = rightDoor->GetComponent<Transform>();
		Vector3 rightPos = rightTr->GetPosition();

		rightPos.x += 3.0f * Time::DeltaTime();

		rightTr->SetPosition(rightPos);
	}
	else if (doorOpenTrigger && startTime > 0.5f && startTime <= 1.f) {
		Transform* leftTr = leftDoor->GetComponent<Transform>();
		Vector3 leftPos = leftTr->GetPosition();

		leftPos.x -= 5.0f * Time::DeltaTime();

		leftTr->SetPosition(leftPos);

		Transform* rightTr = rightDoor->GetComponent<Transform>();
		Vector3 rightPos = rightTr->GetPosition();

		rightPos.x += 5.0f * Time::DeltaTime();

		rightTr->SetPosition(rightPos);

		BGMTrigger = true;
	}

	if (startTime > 1.f && BGMTrigger) {
		{
			AudioSource* as = leftDoor->AddComponent<AudioSource>();
			as->SetClip(Resources::Load<AudioClip>(L"Beyond the Gates", L"..\\Resources\\Sound\\BGM\\Moonlighter OST - 01 - Beyond the Gates_256k.mp3"));
			as->SetLoop(true);
			as->Play();
		}

		{
			AudioSource* as = rightDoor->AddComponent<AudioSource>();
			as->SetClip(Resources::Load<AudioClip>(L"main_menu_door_opened_loop", L"..\\Resources\\Sound\\SoundEffect\\Title\\main_menu_door_opened_loop.wav"));
			as->SetLoop(true);
			as->Play();
		}

		BGMTrigger = false;
	}

	if (startTime > 1.5f && !TextTrigger && TextAlbedo == 0.0f) {
		Text text(L"시작하려면 아무키나 누르세요.", 735.f, 910.f, 40, TextColor(255.f, 255.f, 255.f, 255.f));
		TextManager::InsertText(L"TitleText", text);
		TextTrigger = true;
	}
	else if (TextTrigger == true) {
		TextAlbedo += 150.f * Time::DeltaTime();
		if (TextAlbedo >= 255.f) {
			TextAlbedo = 255.f;
			TextTrigger = false;
		}
		TextColor textColor(255.f, 255.f, 255.f, TextAlbedo);
		TextManager::ChangeColor(L"TitleText", textColor);
	}

	if (TextAlbedo >= 255.f && Input::GetKeyDown(eKeyCode::J)) {
		SceneManager::SetChangeScene(L"DungeonEntrance");
		TextManager::DeleteText(L"TitleText");
	}
}

void TitleDoor::LateUpdate()
{
}

void TitleDoor::Render()
{
}
