#include "EngineContext.h"
#include "Platform/WinInclude.h"
#include "Logger/Logger.h"

// WinMain is the entry point for Windows applications
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	Ethereal::Logger::Init();
	EE_LOG_INFO("Game starting...");

	Ethereal::EngineContext ctx;
	ctx.Hello();
	return 0;
}

int main()
{
	// call WinMain to start the application
	WinMain(GetModuleHandle(0), NULL, GetCommandLineA(), SW_SHOWDEFAULT);
}