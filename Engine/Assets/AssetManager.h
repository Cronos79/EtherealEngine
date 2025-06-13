#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "Assets/IAsset.h"
#include "Assets/ModelAsset.h"
#include "EtherealEngine.h"

namespace Ethereal
{
	class ENGINE_API AssetManager
	{
	public:
		void Initialize();
		void Shutdown();

		bool LoadRegistry(const std::string& path);
		bool LoadModel(const std::string& name);

		template<typename T>
		std::shared_ptr<T> Get(const std::string& name)
		{
			auto it = m_Assets.find(name);
			if (it != m_Assets.end())
				return std::dynamic_pointer_cast<T>(it->second);
			return nullptr;
		}

		bool IsInitialized() const
		{
			return m_Initialized;
		}

	private:
		std::unordered_map<std::string, std::shared_ptr<IAsset>> m_Assets;
		std::unordered_map<std::string, std::string> m_Registry; // name -> path
		bool m_Initialized = false;
	};
}