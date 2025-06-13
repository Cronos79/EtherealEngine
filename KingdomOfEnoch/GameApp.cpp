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
	auto sceneManager = g_Engine.GetSceneManager();
	std::string scenePath = (GetAssetsDirectory() / "Scenes/TestScene.json").string();

	if (!sceneManager->LoadScene(scenePath, g_Engine.GetAssetManager()))
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