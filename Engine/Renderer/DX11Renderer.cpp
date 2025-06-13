#include "Renderer/DX11Renderer.h"
#include "Platform/WinInclude.h"
#include <dxgi.h>
#include "Core/Logger.h"
#include <stdint.h>

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
		float clearColor[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
		m_Context->ClearRenderTargetView(m_RenderTargetView.Get(), clearColor);
	}

	void DX11Renderer::EndFrame()
	{
		m_SwapChain->Present(1, 0);
	}

	void DX11Renderer::OnResize(uint32_t width, uint32_t height)
	{
		CleanupRenderTarget();
		m_SwapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
		CreateRenderTarget();
	}

	void DX11Renderer::DrawMesh(const Mesh& mesh)
	{
		if (mesh.Vertices.empty() || mesh.Indices.empty())
			return;

		// Upload if not already uploaded
		const_cast<Mesh&>(mesh).UploadToGPU(m_Device.Get());

		// Set GPU buffers
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		m_Context->IASetVertexBuffers(0, 1, mesh.VertexBuffer.GetAddressOf(), &stride, &offset);
		m_Context->IASetIndexBuffer(mesh.IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// TODO: Bind shaders and materials

		m_Context->DrawIndexed(static_cast<UINT>(mesh.Indices.size()), 0, 0);
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