#include "Scene/SceneLoader.h"
#include "Scene/GameObject.h"
#include "Core/Logger.h"
#include "Core/EngineUtils.h"
#include "Assets/AssetManager.h"
#include "Core/EngineContext.h"
#include <fstream>
#include <nlohmann/json.hpp>

namespace Ethereal
{
	std::shared_ptr<Scene> SceneLoader::LoadFromFile(const std::string& path, AssetManager* assetMng)
	{
		std::ifstream file(path);
		if (!file.is_open())
		{
			EE_LOG_ERROR("Failed to open scene file: {}", path);
			return nullptr;
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
			assetMng->LoadModel(modelName);
			auto model = assetMng->Get<ModelAsset>(modelName);
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

		return scene;
	}
}