#include "Assets/AssetManager.h"
#include "Core/Logger.h"
#include <memory>
#include <nlohmann/json.hpp>
#include <fstream>
#include "Core/EngineUtils.h"

namespace Ethereal
{
	void AssetManager::Initialize()
	{
		m_Initialized = true;
		EE_LOG_INFO("AssetManager initialized.");
	}

	void AssetManager::Shutdown()
	{
		m_Assets.clear();
		EE_LOG_INFO("AssetManager shutdown.");
	}

	bool AssetManager::LoadRegistry(const std::string& path)
	{
		std::ifstream file(path);
		if (!file.is_open())
		{
			EE_LOG_ERROR("Failed to open asset registry: {}", path);
			return false;
		}

		nlohmann::json json;
		file >> json;

		for (auto& [key, value] : json.items())
		{
			m_Registry[key] = value;
			EE_LOG_INFO("Registered asset: '{}' -> '{}'", key, value.get<std::string>());
		}
		return true;
	}

	bool AssetManager::LoadModel(const std::string& name)
	{
		// Check if the model is already loaded
		if (m_Assets.find(name) != m_Assets.end())
		{
			EE_LOG_INFO("Model '{}' is already loaded.", name);
			return true;
		}

		auto it = m_Registry.find(name);
		if (it == m_Registry.end())
		{
			EE_LOG_ERROR("Asset '{}' not found in registry.", name);
			return false;
		}

		std::filesystem::path fullPath = GetAssetsDirectory();
		fullPath /= it->second;

		auto model = std::make_shared<ModelAsset>();
		if (!model->LoadFromFile(fullPath.string()))
		{
			EE_LOG_ERROR("Failed to load model '{}': {}", name, fullPath.string());
			return false;
		}

		m_Assets[name] = model;
		EE_LOG_INFO("Model '{}' loaded successfully from '{}'", name, fullPath.string());
		return true;
	}
}