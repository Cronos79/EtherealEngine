#include "Scene.h"

namespace Ethereal
{

	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}

	void Scene::AddGameObject(const std::shared_ptr<GameObject>& gameObject)
	{
		m_GameObjects.push_back(gameObject);
		m_GameObjectMap[gameObject->GetID()] = gameObject;
	}

	const std::vector<std::shared_ptr<GameObject>>& Scene::GetGameObjects() const
	{
		return m_GameObjects;
	}

	std::shared_ptr<GameObject> Scene::FindGameObjectByName(const std::string& name) const
	{
		for (const auto& obj : m_GameObjects)
		{
			if (obj->GetName() == name)
				return obj;
		}
		return nullptr;
	}

	std::shared_ptr<Ethereal::GameObject> Scene::FindGameObjectByID(uint64_t id) const
	{
		auto it = m_GameObjectMap.find(id);
		if (it != m_GameObjectMap.end())
			return it->second;
		return nullptr;
	}

}