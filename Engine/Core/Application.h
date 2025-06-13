#pragma once

#include "Core/EngineContext.h"
#include "Platform/Window.h"
#include "EtherealEngine.h"

namespace Ethereal
{
	class ENGINE_API Application
	{
	public:
		Application(const std::string& title, uint32_t width, uint32_t height);
		virtual ~Application();

		void Run();  // Game loop

	protected:
		virtual void OnInit()
		{
		}
		virtual void OnUpdate()
		{
		}
		virtual void OnShutdown()
		{
		}

	protected:
		bool m_Running = true;
		Window m_Window;
	};

	Application* CreateApplication();  // Forward declaration for GameApp
}