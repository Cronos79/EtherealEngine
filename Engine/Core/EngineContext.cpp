#include "Core/EngineContext.h"
#include "Core/Logger.h"
#include "Renderer/DX11Renderer.h"
#include "Assets/AssetManager.h"

namespace Ethereal
{
	std::unique_ptr<EngineContext> EngineContext::s_Instance;

	void EngineContext::Create()
	{
		if (!s_Instance)
			s_Instance = std::make_unique<EngineContext>();	
	}

	void EngineContext::Destroy()
	{
		s_Instance.reset();
	}

	//EngineContext& EngineContext::Get()
	//{
	//	return *s_Instance;
	//}

	void EngineContext::Init(void* windowHandle)
	{		
		EE_LOG_INFO("EngineContext initialized.");
		m_AssetManager = std::make_unique<AssetManager>();
		m_SceneManager = std::make_unique<SceneManager>();
		m_Renderer = std::make_unique<DX11Renderer>();

		m_AssetManager->Initialize();
		m_Renderer->Init(windowHandle);
	}

	void EngineContext::Shutdown()
	{
		EE_LOG_INFO("EngineContext shutting down.");
		if (m_Renderer)
		{
			m_Renderer->Shutdown();
			m_Renderer.reset();
		}
		if (m_AssetManager)
		{
			m_AssetManager->Shutdown();
			m_AssetManager.reset();
		}
		if (m_SceneManager)
		{
			m_SceneManager.reset();
		}			
	}
}