#include "Scene/SceneManager.h"
#include "Core/Logger.h"
#include "Assets/AssetManager.h"

namespace Ethereal
{
	SceneManager::SceneManager()
	{
		EE_LOG_INFO("SceneManager created.");
	}

	bool SceneManager::LoadScene(const std::string& name, AssetManager* assetMng)
	{
		auto scene = assetMng->Get<Scene>(name);
		if (!scene)
		{
			EE_LOG_ERROR("Failed to load scene: {}", name);
			return false;
		}

		m_CurrentScene = scene;
		EE_LOG_INFO("Scene loaded successfully: {}", name);
		return true;
	}

	std::shared_ptr<Scene> SceneManager::GetCurrentScene() const
	{
		return m_CurrentScene;
	}
}