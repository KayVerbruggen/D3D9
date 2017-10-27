#include "Window.h"

LRESULT CALLBACK WindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
	switch (Message)
	{
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

	DWORD Style = WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX;

	m_WindowHandle = CreateWindowEx(WS_EX_APPWINDOW, m_ClassName, m_WindowTitle, Style,
		0, 0, m_Width, m_Height, 0, 0, hInstance, 0);

	if (m_WindowHandle == NULL)
		MessageBoxA(0, "WindowHandle is still NULL", "Error", MB_OK);

	ShowWindow(m_WindowHandle, ShowCmd);

	UpdateWindow(m_WindowHandle);

	SecureZeroMemory(&Msg, sizeof(MSG));
}

Window::~Window()
{
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

void Window::OutputFPS(float DeltaTime)
{
	static int Frames = 0;
	static float Time = 0.0f;

	Frames++;
	Time += DeltaTime;

	if (Time >= 1.0f)
	{
		std::stringstream stream;
		stream << m_WindowTitle << "        FPS: " << Frames;

		SetWindowText(m_WindowHandle, stream.str().c_str());

		Frames = 0;
		Time = 0.0f;
	}
}

MSG& Window::GetMSG()
{
	return Msg;
}

HWND& Window::GetWindowHandle()
{
	return m_WindowHandle;
}

int Window::GetWidth()
{
	return m_Width;
}

int Window::GetHeight()
{
	return m_Height;
}