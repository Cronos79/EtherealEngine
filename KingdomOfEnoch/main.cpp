#include "GameApp.h"

Ethereal::Application* Ethereal::CreateApplication()
{
	return new GameApp();
}

// WinMain is the entry point for Windows applications
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{	
	auto app = Ethereal::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

int main()
{
	// call WinMain to start the application
	WinMain(GetModuleHandle(0), NULL, GetCommandLineA(), SW_SHOWDEFAULT);
}