#include "GameApp.h"
#include <EngineIncludes.h>
#include <Core/EngineUtils.h>

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
	auto sceneManager = engine.GetSceneManager();
	engine.GetAssetManager()->LoadSceneFromFile("TestScene");

	if (!sceneManager->LoadScene("TestScene", engine.GetAssetManager()))
	{
		GAME_LOG_ERROR("Failed to load scene: TestScene");
		return;
	}
	GAME_LOG_INFO("GameApp Initialized!");
}

void GameApp::OnUpdate()
{
	// TODO: game logic here
}

void GameApp::OnShutdown()
{
	GAME_LOG_INFO("GameApp Shutdown.");
}