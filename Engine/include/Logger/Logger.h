#pragma once
#include "EtherealEngine.h"
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Ethereal
{
	class ENGINE_API Logger
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger()
		{
			return s_CoreLogger;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
	};
}

// Logging macros
#define EE_LOG_TRACE(...)    ::Ethereal::Logger::GetCoreLogger()->trace("[{}:{}]\n {}", __FILE__, __LINE__, __VA_ARGS__)
#define EE_LOG_INFO(...)     ::Ethereal::Logger::GetCoreLogger()->info("[{}:{}]\n {}", __FILE__, __LINE__, __VA_ARGS__)
#define EE_LOG_WARN(...)     ::Ethereal::Logger::GetCoreLogger()->warn("[{}:{}]\n {}", __FILE__, __LINE__, __VA_ARGS__)
#define EE_LOG_ERROR(...)    ::Ethereal::Logger::GetCoreLogger()->error("[{}:{}]\n {}", __FILE__, __LINE__, __VA_ARGS__)
#define EE_LOG_CRITICAL(...) ::Ethereal::Logger::GetCoreLogger()->critical("[{}:{}]\n {}", __FILE__, __LINE__, __VA_ARGS__)