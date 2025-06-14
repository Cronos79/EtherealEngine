#include "Assets/AssetManager.h"
#include "Core/Logger.h"
#include <memory>
#include <nlohmann/json.hpp>
#include <fstream>
#include "Core/EngineUtils.h"
#include "Scene/Scene.h"

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

	bool AssetManager::LoadTexture(const std::string& name, ID3D11Device* device)
	{
		if (m_Assets.find(name) != m_Assets.end())
		{
			EE_LOG_INFO("Texture '{}' is already loaded.", name);
			return true;
		}

		auto it = m_Registry.find(name);
		if (it == m_Registry.end())
		{
			EE_LOG_ERROR("Texture '{}' not found in registry.", name);
			return false;
		}

		std::filesystem::path fullPath = GetAssetsDirectory();
		fullPath /= it->second;

		auto texture = std::make_shared<TextureAsset>();
		if (!texture->LoadFromFile(device, fullPath.string()))
		{
			EE_LOG_ERROR("Failed to load texture '{}': {}", name, fullPath.string());
			return false;
		}

		m_Assets[name] = texture;
		EE_LOG_INFO("Texture '{}' loaded successfully from '{}'", name, fullPath.string());
		return true;
	}

	bool AssetManager::LoadSceneFromFile(const std::string& name)
	{
		auto it = m_Registry.find(name);
		if (it == m_Registry.end())
		{
			EE_LOG_ERROR("Scene '{}' not found in registry.", name);
			return false;
		}

		std::filesystem::path fullPath = GetAssetsDirectory();
		fullPath /= it->second;

		std::ifstream file(fullPath);
		if (!file.is_open())
		{
			EE_LOG_ERROR("Failed to open scene file: {}", fullPath.string());
			return false;
		}

		nlohmann::json json;
		file >> json;

		auto scene = std::make_shared<Scene>();

		for (auto& obj : json["game_objects"])
		{
			std::string name = obj["name"];
			auto gameObject = std::make_shared<GameObject>(name);

			// Model
			std::string modelName = obj["model"];
			LoadModel(modelName);
			auto model = Get<ModelAsset>(modelName);
			if (model)
			{
				gameObject->SetModel(model);
			}
			else
			{
				EE_LOG_WARN("Model '{}' not found for GameObject '{}'", modelName, name);
			}

			// Transform
			DirectX::XMFLOAT3 pos = { obj["position"][0], obj["position"][1], obj["position"][2] };
			DirectX::XMFLOAT3 rot = { obj["rotation"][0], obj["rotation"][1], obj["rotation"][2] };
			DirectX::XMFLOAT3 scale = { obj["scale"][0], obj["scale"][1], obj["scale"][2] };

			gameObject->SetPosition(pos);
			gameObject->SetRotation(rot);
			gameObject->SetScale(scale);

			scene->AddGameObject(gameObject);
		}

		m_Assets[name] = scene;

		return true;
	}

}