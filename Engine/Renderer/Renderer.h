#pragma once
#include "EtherealEngine.h"
#include <stdint.h>
#include <d3d11.h> // #NOTE: Need to have a macro if / when we add other renderers
#include "ShaderConstants.h"

namespace Ethereal
{
	class Mesh;
	struct Renderable;

	class ENGINE_API Renderer
	{
	public:
		virtual ~Renderer() = default;

		virtual void Init(void* windowHandle) = 0;
		virtual void Shutdown() = 0;

		virtual void BeginFrame() = 0;
		virtual void DrawRenderable(const Renderable& renderable) = 0;
		virtual void EndFrame() = 0;

		virtual void SetCameraConstants(const CameraConstants& camera) = 0;

		// Optional: resize, set viewport, clear color, etc.
		virtual void OnResize(uint32_t width, uint32_t height) = 0;

		virtual ID3D11Device* GetD3D11Device() const
		{
			return nullptr;
		}
		virtual ID3D11DeviceContext* GetD3D11Context() const
		{
			return nullptr;
		}
	};
}