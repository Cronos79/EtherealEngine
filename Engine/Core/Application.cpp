#include "Core/Application.h"
#include "Core/Logger.h"
#include "Renderer/Renderer.h"
#include "Core/RuntimeInitializer.h"

namespace Ethereal
{
	Application::Application(const std::string& title, uint32_t width, uint32_t height)
		: m_Window(title, width, height)
	{
		
	}

	Application::~Application()
	{
		RuntimeInitializer::Shutdown(g_Engine);
	}

	void Application::Run()
	{
		RuntimeInitializer::Initialize(g_Engine, m_Window.GetHandle());
	
		OnInit();

		while (m_Running && g_Engine.IsRunning())
		{
			m_Running = m_Window.ProcessMessages();

			g_Engine.GetRenderer()->BeginFrame();

			OnUpdate();

			g_Engine.GetRenderer()->EndFrame();
		}

		OnShutdown();
	}
}