#pragma once

#include <string>

namespace Ethereal
{
	struct GameConfig
	{
		std::string DefaultScene = "TestScene";

		static GameConfig LoadFromFile(const std::string& path);
	};
}