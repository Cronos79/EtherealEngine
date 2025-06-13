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
		auto& engine = EngineContext::Get();
		RuntimeInitializer::Shutdown(engine);
	}

	void Application::Run()
	{
		auto& engine = EngineContext::Get();
		RuntimeInitializer::Initialize(engine, m_Window.GetHandle());
	
		OnInit();

		while (m_Running && engine.IsRunning())
		{
			m_Running = m_Window.ProcessMessages();

			engine.GetRenderer()->BeginFrame();

			OnUpdate();

			engine.GetRenderer()->EndFrame();
		}

		OnShutdown();
	}
}