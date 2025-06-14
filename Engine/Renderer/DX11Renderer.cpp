#include "Renderer/DX11Renderer.h"
#include "Platform/WinInclude.h"
#include <dxgi.h>
#include "Core/Logger.h"
#include <stdint.h>
#include "Assets/AssetManager.h"
#include "Core/EngineContext.h"

namespace Ethereal
{
	DX11Renderer::DX11Renderer()
	{
	}
	DX11Renderer::~DX11Renderer()
	{
		Shutdown();
	}

	void DX11Renderer::Init(void* windowHandle)
	{
		HWND hwnd = static_cast<HWND>(windowHandle);

		DXGI_SWAP_CHAIN_DESC scDesc = {};
		scDesc.BufferCount = 1;
		scDesc.BufferDesc.Width = 0;
		scDesc.BufferDesc.Height = 0;
		scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scDesc.OutputWindow = hwnd;
		scDesc.SampleDesc.Count = 1;
		scDesc.Windowed = TRUE;
		scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		UINT createDeviceFlags = 0;
#if defined(_DEBUG)
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_FEATURE_LEVEL featureLevel;
		const D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };

		HRESULT hr = D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			createDeviceFlags,
			featureLevels,
			1,
			D3D11_SDK_VERSION,
			&scDesc,
			m_SwapChain.GetAddressOf(),
			m_Device.GetAddressOf(),
			&featureLevel,
			m_Context.GetAddressOf()
		);

		if (FAILED(hr))
		{
			spdlog::error("Failed to initialize D3D11 device and swap chain.");
			return;
		}

		CreateRenderTarget();

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;
		//io.ConfigViewportsNoDefaultParent = true;
		//io.ConfigDockingAlwaysTabBar = true;
		//io.ConfigDockingTransparentPayload = true;
		//io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;     // FIXME-DPI: Experimental. THIS CURRENTLY DOESN'T WORK AS EXPECTED. DON'T USE IN USER APP!
		//io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports; // FIXME-DPI: Experimental.

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer backends
		ImGui_ImplWin32_Init(hwnd);
		ImGui_ImplDX11_Init(m_Device.Get(), m_Context.Get());

		m_IsInit = true;
	}

	void DX11Renderer::Shutdown()
	{	
		CleanupRenderTarget();
		m_SwapChain.Reset();
		m_Context.Reset();
		m_Device.Reset();
	}

	void DX11Renderer::BeginFrame()
	{
		if (!m_IsInit) return;
		if (!m_RenderTargetView)
		{
			EE_LOG_ERROR("RTV is null");
			return;
		}
		float clearColor[4] = { 0.01f, 0.01f, 0.01f, 1.0f };
		m_Context->ClearRenderTargetView(m_RenderTargetView.Get(), clearColor);

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void DX11Renderer::EndFrame()
	{
		if (!m_IsInit) return;
		if (!m_RenderTargetView)
		{
			EE_LOG_ERROR("RTV is null");
			return;
		}

		bool show_demo_window = true;
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}

		m_SwapChain->Present(1, 0);
	}

	void DX11Renderer::OnResize(uint32_t width, uint32_t height)
	{
		CleanupRenderTarget();
		m_SwapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
		CreateRenderTarget();
	}

	void DX11Renderer::DrawRenderable(const Renderable& renderable)
	{
		const Mesh* mesh = renderable.mesh;
		const Material* material = renderable.material;
		if (!mesh || !material || mesh->Vertices.empty() || mesh->Indices.empty())
			return;

		// Upload if not already uploaded
		const_cast<Mesh*>(mesh)->UploadToGPU(m_Device.Get());

		// Set GPU buffers
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		m_Context->IASetVertexBuffers(0, 1, mesh->VertexBuffer.GetAddressOf(), &stride, &offset);
		m_Context->IASetIndexBuffer(mesh->IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		auto vs = material->GetVertexShaderAsset();
		auto ps = material->GetPixelShaderAsset();

		if (!vs || !ps)
		{
			EE_LOG_ERROR("Missing shader(s) in material");
			return;
		}

		m_Context->IASetInputLayout(vs->GetInputLayout());
		m_Context->VSSetShader(vs->GetVertexShader(), nullptr, 0);
		m_Context->PSSetShader(ps->GetPixelShader(), nullptr, 0);

		// TODO: Upload world matrix to constant buffer here

		m_Context->DrawIndexed(static_cast<UINT>(mesh->Indices.size()), 0, 0);
	}

	void DX11Renderer::SetCameraConstants(const CameraConstants& camera)
	{
		// Update GPU constant buffer
		//m_Context->UpdateSubresource(m_CameraConstantBuffer.Get(), 0, nullptr, &camera, 0, 0); // #TODO: This is broken camera will not work
	}

	void DX11Renderer::CreateRenderTarget()
	{
		Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
		m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
		m_Device->CreateRenderTargetView(backBuffer.Get(), nullptr, m_RenderTargetView.GetAddressOf());
		m_Context->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), nullptr);
	}

	void DX11Renderer::CleanupRenderTarget()
	{
		m_RenderTargetView.Reset();
	}
}