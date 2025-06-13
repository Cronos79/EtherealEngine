#pragma once
#include "EtherealEngine.h"
#include <memory>
#include "Assets/AssetManager.h"
#include "Scene/SceneManager.h"

namespace Ethereal
{
	class Renderer; // Forward declare your renderer 

	class ENGINE_API EngineContext
	{
	public:
		static void Create();
		static void Destroy();
		static EngineContext& Get();

		void Init(void* windowHandle);
		void Shutdown();

		// Accessors
		bool IsRunning() const
		{
			return m_IsRunning;
		}
		void SetRunning(bool running)
		{
			m_IsRunning = running;
		}
		Renderer* GetRenderer()
		{
			return m_Renderer.get();
		}
		AssetManager* GetAssetManager() const
		{
			return m_AssetManager.get();
		}
		SceneManager* GetSceneManager() const
		{
			return m_SceneManager.get();
		}

	private:
		static std::unique_ptr<EngineContext> s_Instance;

		bool m_IsRunning = true;

		std::shared_ptr<Renderer> m_Renderer;
		std::unique_ptr<AssetManager> m_AssetManager;
		std::unique_ptr<SceneManager> m_SceneManager;
	};
}