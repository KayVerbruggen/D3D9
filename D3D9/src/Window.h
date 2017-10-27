#pragma once

#include <Windows.h>
#include <sstream>

class Window
{
public:
	Window(HINSTANCE hInstance, UINT ShowCmd);
	~Window();

	bool CheckPeekMessage();
	void HandleMessage();

	void OutputFPS(float DeltaTime);
	
	// Bunch of getters
	HWND& GetWindowHandle();
	MSG& GetMSG();
	int GetWidth();
	int GetHeight();

private:
	HRESULT hr;
	
	HWND m_WindowHandle;
	WNDCLASSEX wc;
	MSG Msg;

	// Settings window
	int m_Width = 1280;
	int m_Height = 720;
	const char* m_ClassName = "WindowClass";
	const char* m_WindowTitle = "WindowD3D9";
};