#include "Platform/Window.h"
#include <stdexcept>
#include "imgui/imgui_impl_win32.h"


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Ethereal
{
	Window::Window(const std::string& title, int width, int height)
	{
		m_hInstance = GetModuleHandle(nullptr);

		WNDCLASS wc = {};
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = m_hInstance;
		wc.lpszClassName = "EtherealWindowClass";
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

		RegisterClass(&wc);

		RECT rect = { 0, 0, width, height };
		auto style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
		AdjustWindowRect(&rect, style, FALSE);

		m_hwnd = CreateWindowEx(
			0,
			wc.lpszClassName,
			title.c_str(),
			style,
			CW_USEDEFAULT, CW_USEDEFAULT,
			rect.right - rect.left, rect.bottom - rect.top,
			nullptr, nullptr, m_hInstance, nullptr
		);

		if (!m_hwnd)
			throw std::runtime_error("Failed to create window");

		ShowWindow(m_hwnd, SW_SHOW);
	}

	Window::~Window()
	{		
		if (m_hwnd)
			DestroyWindow(m_hwnd);
	}

	bool Window::ProcessMessages()
	{
		MSG msg = {};
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				return false;
		}
		return true;
	}

	LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
			return true;

		switch (uMsg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}