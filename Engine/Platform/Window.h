#pragma once

#include "Platform/WinInclude.h"
#include <string>
#include "EtherealEngine.h"

namespace Ethereal
{
	class ENGINE_API Window
	{
	public:
		Window(const std::string& title, int width, int height);
		~Window();

		bool ProcessMessages();

		HWND GetHandle() const
		{
			return m_hwnd;
		}

	private:
		HWND m_hwnd = nullptr;
		HINSTANCE m_hInstance = nullptr;

		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}