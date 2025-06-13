#pragma once

#include <memory>
#include <string>
#include "Scene.h"
#include "EtherealEngine.h"

namespace Ethereal
{
	class ENGINE_API SceneManager
	{
	public:
		SceneManager();
		~SceneManager() = default;

		// Load scene from file and set as current
		bool LoadScene(const std::string& path, class AssetManager* assetMng);

		// Access current scene
		std::shared_ptr<Scene> GetCurrentScene() const;

	private:
		std::shared_ptr<Scene> m_CurrentScene;
	};
}