#pragma once
#include "Renderer/Renderer.h"
#include <d3d11.h>
#include <wrl/client.h>
#include "EtherealEngine.h"
#include <stdint.h>
#include "Assets/Mesh.h"
#include "Renderer/RendererCommon.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

namespace Ethereal
{
	class ENGINE_API DX11Renderer : public Renderer
	{
	public:
		DX11Renderer();
		~DX11Renderer() override;

		ID3D11Device* GetD3D11Device() const override
		{
			return m_Device.Get();
		}
		ID3D11DeviceContext* GetD3D11Context() const override
		{
			return m_Context.Get();
		}

		void Init(void* windowHandle) override;
		void Shutdown() override;

		void BeginFrame() override;
		void EndFrame() override;

		void OnResize(uint32_t width, uint32_t height) override;

		void DrawRenderable(const Renderable& renderable);

		void SetCameraConstants(const CameraConstants& camera) override;

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_Context;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;

		void CreateRenderTarget();
		void CleanupRenderTarget();

	private:
		bool m_IsInit = false;
	};
}