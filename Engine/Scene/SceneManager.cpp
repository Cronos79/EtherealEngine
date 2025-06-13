#include "Scene/SceneManager.h"
#include "Scene/SceneLoader.h"
#include "Core/Logger.h"
#include "Assets/AssetManager.h"

namespace Ethereal
{
	SceneManager::SceneManager()
	{
		EE_LOG_INFO("SceneManager created.");
	}

	bool SceneManager::LoadScene(const std::string& path, AssetManager* assetMng)
	{
		auto scene = SceneLoader::LoadFromFile(path, assetMng);
		if (!scene)
		{
			EE_LOG_ERROR("Failed to load scene: {}", path);
			return false;
		}

		m_CurrentScene = scene;
		EE_LOG_INFO("Scene loaded successfully: {}", path);
		return true;
	}

	std::shared_ptr<Scene> SceneManager::GetCurrentScene() const
	{
		return m_CurrentScene;
	}
}