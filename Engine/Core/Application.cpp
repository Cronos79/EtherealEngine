#include "Core/Application.h"
#include "Core/Logger.h"
#include "Renderer/Renderer.h"
#include "Core/RuntimeInitializer.h"
#include "Core/Transform.h"
#include <DirectXMath.h>
#include "Renderer/RendererCommon.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui.h"

namespace Ethereal
{
	Application::Application(const std::string& title, uint32_t width, uint32_t height)
		: m_Window(title, width, height)
	{
		m_TEMPHeight = height;
		m_TEMPWidth = width;
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
		engine.SetWidth(m_TEMPWidth);
		engine.SetHeight(m_TEMPHeight);

		const std::string& sceneName = Ethereal::EngineContext::Get().GetGameConfig().DefaultScene;
		engine.GetAssetManager()->LoadSceneFromFile(sceneName);

		auto renderer = Ethereal::EngineContext::Get().GetRenderer();

		if (!Ethereal::EngineContext::Get().GetSceneManager()->LoadScene(sceneName, engine.GetAssetManager()))
		{
			GAME_LOG_ERROR("Failed to load scene: {}", sceneName);
			return;
		}

		OnInit();

		while (m_Running && engine.IsRunning())
		{
			m_Running = m_Window.ProcessMessages();
			if (!m_Running)
			{
				ImGui_ImplWin32_Shutdown();
				ImGui_ImplDX11_Shutdown();				
				ImGui::DestroyContext();
				OnShutdown();
				return;
			}

			renderer->BeginFrame();

			OnUpdate();

			for (const auto& gameObject : engine.GetSceneManager()->GetCurrentScene()->GetGameObjects())
			{
				auto model = gameObject->GetModel();
				if (model)
				{
					auto meshes = model->GetMeshes();
					auto materials = model->GetMaterials();

					for (size_t i = 0; i < meshes.size(); ++i)
					{
						const Mesh& mesh = meshes[i];
						Material* material = materials.size() > i ? materials[i].get() : nullptr;
						DirectX::XMMATRIX world = gameObject->GetTransform().GetWorldMatrix();

						Renderable r = { &mesh, material, world };
						renderer->DrawRenderable(r);
					}
				}
			}			

			renderer->EndFrame();
		}
		
		OnShutdown();
	}
}