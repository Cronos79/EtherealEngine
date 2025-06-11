#include "Logger/Logger.h"

namespace Ethereal
{
	std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;

	void Logger::Init()
	{
		std::vector<spdlog::sink_ptr> sinks;

#ifdef _DEBUG
		// Console sink (colored)
		auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		consoleSink->set_pattern("[%Y-%m-%d %T] [%l] %n: %v");
		sinks.push_back(consoleSink);
#endif

		// File sink
		auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("Ethereal.log", true);
		fileSink->set_pattern("[%Y-%m-%d %T] [%l] %n: %v");
		sinks.push_back(fileSink);

		s_CoreLogger = std::make_shared<spdlog::logger>("Ethereal", sinks.begin(), sinks.end());
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::warn);

		spdlog::register_logger(s_CoreLogger);
	}
}