#include "Core/GameConfig.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include "Core/Logger.h"

namespace Ethereal
{
	GameConfig GameConfig::LoadFromFile(const std::string& path)
	{
		GameConfig config;

		std::ifstream file(path);
		if (!file.is_open())
		{
			EE_LOG_WARN("Could not open GameConfig file: {}", path);
			return config;
		}

		nlohmann::json json;
		file >> json;

		config.DefaultScene = json.value("DefaultScene", "TestScene");

		EE_LOG_INFO("GameConfig loaded: DefaultScene = '{}'", config.DefaultScene);

		return config;
	}
}