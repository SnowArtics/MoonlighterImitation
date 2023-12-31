#include "snApplication.h"
#include "snInput.h"
#include "snTime.h"
#include "snRenderer.h"
#include "snSceneManager.h"
#include "snCollisionManager.h"
#include "snFmod.h"
#include "snFontWrapper.h"
#include "snTextManager.h"
#include "InventoryManager.h"
#include "ShopManager.h"

namespace sn
{
	Application::Application()
		: graphicDevice(nullptr)
		, mHwnd(NULL)
		, mWidth(-1)
		, mHeight(-1)
	{

	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
		ChangeAIState();
		Destroy();
		ChangeScene();
	}

	void Application::Initialize()
	{
		Time::Initiailize();
		Input::Initialize();
		Fmod::Initialize();
		InventoryManager::Initiailize();
		ShopManager::Initiailize();
		FontWrapper::Initialize();

		renderer::Initialize();
		SceneManager::Initialize();
		CollisionManager::Initialize();

		//Text text(L"test", 20.f, 30.f, 20, TextColor(255.f, 255.f, 255.f, 255.f));
		//TextManager::InsertText(L"Test01", text);
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		SceneManager::Update();
		CollisionManager::Update();
		InventoryManager::Update();
		ShopManager::Update();
	}

	void Application::LateUpdate()
	{
		SceneManager::LateUpdate();
	}

	void Application::Render()
	{
		InventoryManager::Render();
		ShopManager::Render();
		Time::Render();

		graphicDevice->ClearTarget();
		graphicDevice->UpdateViewPort();
		Time::Render();
		//FontWrapper::DrawFont(L"TEXT", 10.f, 30.f, 20, FONT_RGBA(255, 0, 255, 255));
		//SceneManager::Render();
		renderer::Render();
		TextManager::Render();
		//graphicDevice->Draw();
	}

	void Application::Release()
	{
		InventoryManager::Release();
	}

	void Application::Destroy()
	{
		SceneManager::Destroy();
	}

	void Application::ChangeScene()
	{
		SceneManager::ChangeScene();
	}

	void Application::ChangeAIState()
	{
		SceneManager::ChangeAIState();
	}

	void Application::Present()
	{
		graphicDevice->Present();
	}

	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (graphicDevice == nullptr)
		{
			mHwnd = hwnd;
			mWidth = width;
			mHeight = height;

			graphicDevice = std::make_unique<sn::graphics::GraphicDevice_Dx11>();
			sn::graphics::GetDevice() = graphicDevice.get();
		}

		RECT rt = { 0, 0, (LONG)width , (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top+30, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}

}
