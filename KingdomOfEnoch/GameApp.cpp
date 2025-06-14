#include "GameApp.h"
#include <EngineIncludes.h>
#include <Core/EngineUtils.h>
#include "Renderer/ShaderConstants.h"
#include "Core/EngineContext.h"

GameApp::GameApp()
	: Application("Kingdom of Enoch", 1280, 720)
{
}

GameApp::~GameApp()
{
}

void GameApp::OnInit()
{
	auto& engine = Ethereal::EngineContext::Get();
	//auto& engine = Ethereal::EngineContext::Get();
	using namespace DirectX;

	m_Camera.SetPosition({ 0.0f, 2.0f, -5.0f });
	m_Camera.SetTarget({ 0.0f, 0.0f, 0.0f });
	m_Camera.SetProjection(XM_PIDIV4, engine.GetAspectRatio(), 0.1f, 1000.0f); // FOV, AspectRatio, NearZ, FarZ
	GAME_LOG_INFO("GameApp Initialized!");
}

void GameApp::OnUpdate()
{
	// We will make a handle keyboard method in application for this
	//m_Camera.Update(); // If your Camera has an Update() method, like for WASD control or mouse look

	// Update renderer camera constants
	Ethereal::CameraConstants camCB;
	camCB.View = XMMatrixTranspose(m_Camera.GetView());
	camCB.Projection = XMMatrixTranspose(m_Camera.GetProj());

	auto renderer = Ethereal::EngineContext::Get().GetRenderer();
	renderer->SetCameraConstants(camCB); // You can make this method if needed
}

void GameApp::OnShutdown()
{
	GAME_LOG_INFO("GameApp Shutdown.");
}