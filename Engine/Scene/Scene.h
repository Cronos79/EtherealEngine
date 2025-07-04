#pragma once

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "GameObject.h"
#include "EtherealEngine.h"
#include "Assets/IAsset.h"

namespace Ethereal
{
	class ENGINE_API Scene : public IAsset
	{
	public:
		Scene();
		virtual ~Scene() override;

		std::string GetSceneName()
		{
			return m_SceneName;
		}
		void SetSceneName(std::string sceneName)
		{
			m_SceneName = sceneName;
		}

		// Add a GameObject to the scene
		void AddGameObject(const std::shared_ptr<GameObject>& gameObject);

		// Get all GameObjects
		const std::vector<std::shared_ptr<GameObject>>& GetGameObjects() const;

		// Optional: Get by name
		std::shared_ptr<GameObject> FindGameObjectByName(const std::string& name) const;

		std::shared_ptr<GameObject> FindGameObjectByID(uint64_t id) const;

	private:
		std::vector<std::shared_ptr<GameObject>> m_GameObjects;
		std::unordered_map<uint64_t, std::shared_ptr<GameObject>> m_GameObjectMap;
		std::string m_SceneName = "Unknown";
	};
}