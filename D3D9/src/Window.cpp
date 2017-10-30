#include "Window.h"

D3DXVECTOR3 m_CamPos = D3DXVECTOR3(0.0f, 0.0f, -5.0f);

enum Keys : WPARAM
{
	A = 0x41, B, C, D, E, F, G,
	H, I, J, K, L, M, N, O, P, Q,
	R, S, T, U, V, W, X, Y, Z
};

LRESULT CALLBACK WindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{

	switch (Message)
	{
	case WM_KEYDOWN:
		switch (WParam)
		{
		case D:
			m_CamPos += D3DXVECTOR3(0.05f, 0.0f, 0.0f);
			break;

		case A:
			m_CamPos -= D3DXVECTOR3(0.05f, 0.0f, 0.0f);
			break;

		case W:
			m_CamPos += D3DXVECTOR3(0.0f, 0.0f, 0.05f);
			break;

		case S:
			m_CamPos -= D3DXVECTOR3(0.0f, 0.0f, 0.05f);
			break;

		case VK_ESCAPE:
			PostQuitMessage(0);
			DestroyWindow(Window);
			break;

		default:
			break;
		}

		break;

	case WM_CLOSE:
		PostQuitMessage(0);
		DestroyWindow(Window);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(Window, Message, WParam, LParam);
	}

	return 0;
}


Window::Window(HINSTANCE hInstance, UINT ShowCmd)
{
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIconSm = 0;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = m_ClassName;
	wc.lpszMenuName = 0;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	RegisterClassEx(&wc);

	m_Width = (float)GetSystemMetrics(SM_CXSCREEN);
	m_Height = (float)GetSystemMetrics(SM_CYSCREEN);

	DWORD Style = WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX;

	m_WindowHandle = CreateWindowEx(WS_EX_APPWINDOW, m_ClassName, m_WindowTitle, Style,
		0, 0, (int)m_Width, (int)m_Height, 0, 0, hInstance, 0);

	if (m_WindowHandle == NULL)
		MessageBoxA(0, "WindowHandle is still NULL", "Error", MB_OK);

	ShowWindow(m_WindowHandle, ShowCmd);

	UpdateWindow(m_WindowHandle);

	SecureZeroMemory(&Msg, sizeof(MSG));
}

Window::~Window()
{
}

void Window::GetCamPos(D3DXVECTOR3& Position)
{
	Position = m_CamPos;
}

bool Window::CheckPeekMessage()
{
	return PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE);
}

void Window::HandleMessage()
{
	TranslateMessage(&Msg);
	DispatchMessage(&Msg);
}

MSG& Window::GetMSG()
{
	return Msg;
}

HWND& Window::GetWindowHandle()
{
	return m_WindowHandle;
}

float Window::GetWidth()
{
	return m_Width;
}

float Window::GetHeight()
{
	return m_Height;
}