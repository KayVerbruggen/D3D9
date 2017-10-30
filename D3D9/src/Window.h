#pragma once

#include <Windows.h>
#include <sstream>

#include <d3dx9.h>

class Window
{
public:
	Window(HINSTANCE hInstance, UINT ShowCmd);
	~Window();

	bool CheckPeekMessage();
	void HandleMessage();
	
	void GetCamPos(D3DXVECTOR3& Position);

	// Bunch of getters
	HWND& GetWindowHandle();
	MSG& GetMSG();
	float GetWidth();
	float GetHeight();

private:
	HRESULT hr;
	
	HWND m_WindowHandle;
	WNDCLASSEX wc;
	MSG Msg;

	// Settings window
	float m_Width;
	float m_Height;
	const char* m_ClassName = "WindowClass";
	const char* m_WindowTitle = "WindowD3D9";
};