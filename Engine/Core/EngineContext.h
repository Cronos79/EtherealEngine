#pragma once
#include "EtherealEngine.h"
#include <memory>
#include "Assets/AssetManager.h"
#include "Scene/SceneManager.h"
#include "Core/GameConfig.h"

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

		const GameConfig& GetGameConfig() const
		{
			return m_GameConfig;
		}
		void SetGameConfig(const GameConfig& config)
		{
			m_GameConfig = config;
		}

		int32_t GetWidth()
		{
			return m_Width;
		}
		void SetWidth(int32_t width)
		{
			m_Width = width;
		}
		int32_t GetHeight()
		{
			return m_Height;
		}
		void SetHeight(int32_t height)
		{
			m_Height = height;
		}

		void SetScreenSize(int32_t width, int32_t height)
		{
			m_Height = height;
			m_Width = width;
		}

		float GetAspectRatio()
		{
			return (float)m_Width / (float)m_Height;
		}

	private:
		static std::unique_ptr<EngineContext> s_Instance;

		bool m_IsRunning = true;

		std::shared_ptr<Renderer> m_Renderer;
		std::unique_ptr<AssetManager> m_AssetManager;
		std::unique_ptr<SceneManager> m_SceneManager;
		GameConfig m_GameConfig;

		int32_t m_Width = 1280;
		int32_t m_Height = 720;
	};
}