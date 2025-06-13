#pragma once

#include "Core/EngineContext.h"
#include "Core/Logger.h"
#include "Platform/Window.h"
#include "EtherealEngine.h"

namespace Ethereal
{
	class ENGINE_API RuntimeInitializer
	{
	public:
		static void Initialize(EngineContext& engine, HWND windowHandle);
		static void Shutdown(EngineContext& engine);
	};
}