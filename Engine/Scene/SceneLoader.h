#pragma once

#include <memory>
#include <string>
#include "Scene.h"
#include "EtherealEngine.h"

namespace Ethereal
{
	class ENGINE_API SceneLoader
	{
	public:
		static std::shared_ptr<Scene> LoadFromFile(const std::string& path, class AssetManager* assetMng);
	};
}