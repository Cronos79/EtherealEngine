#pragma once
#include "EtherealEngine.h"
#include <stdint.h>

namespace Ethereal
{
	class ENGINE_API Renderer
	{
	public:
		virtual ~Renderer() = default;

		virtual void Init(void* windowHandle) = 0;
		virtual void Shutdown() = 0;

		virtual void BeginFrame() = 0;
		virtual void EndFrame() = 0;

		// Optional: resize, set viewport, clear color, etc.
		virtual void OnResize(uint32_t width, uint32_t height) = 0;
	};
}