#include "Core/RuntimeInitializer.h"
#include "EngineUtils.h"

namespace Ethereal
{
	void RuntimeInitializer::Initialize(EngineContext& engine, HWND windowHandle)
	{
		Logger::Init();
		engine.Create();
		engine.Init(windowHandle);

		auto assetManager = engine.GetAssetManager();
		assetManager->Initialize();
		if (assetManager)
		{
			// Build full path to the asset registry file using GetAssetsDirectory() returns a filesystem::path;
			auto assetRegistryPath = GetAssetsDirectory() / "asset_registry.json";
			
			if (!assetManager->LoadRegistry(assetRegistryPath.string()))
			{
				EE_LOG_ERROR("Failed to load asset registry. Asset loading may not work.");
			}
		}

		EE_LOG_INFO("Runtime systems initialized.");
	}

	void RuntimeInitializer::Shutdown(EngineContext& engine)
	{
		engine.Shutdown();
		engine.Destroy();
		EE_LOG_INFO("Runtime systems shut down.");
	}
}