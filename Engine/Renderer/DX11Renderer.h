#pragma once
#include "Renderer/Renderer.h"
#include <d3d11.h>
#include <wrl/client.h>
#include "EtherealEngine.h"
#include <stdint.h>
#include "Assets/Mesh.h"

namespace Ethereal
{
	class ENGINE_API DX11Renderer : public Renderer
	{
	public:
		DX11Renderer();
		~DX11Renderer() override;

		void Init(void* windowHandle) override;
		void Shutdown() override;

		void BeginFrame() override;
		void EndFrame() override;

		void OnResize(uint32_t width, uint32_t height) override;

		void DrawMesh(const Mesh& mesh);

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_Context;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;

		void CreateRenderTarget();
		void CleanupRenderTarget();
	};
}