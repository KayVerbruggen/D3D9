#include "Renderer.h"

Renderer::Renderer(Window& window)
{
	m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_pD3D9)
		MessageBox(0, "Creating D3D9 failed!", "Error", MB_OK);

	// Fill out parameters for presenting the back buffer
	ZeroMemory(&m_PresentParams, sizeof(D3DPRESENT_PARAMETERS));

	// Window information
	m_PresentParams.BackBufferWidth = (UINT)window.GetWidth();
	m_PresentParams.BackBufferHeight = (UINT)window.GetHeight();
	m_PresentParams.hDeviceWindow = window.GetWindowHandle();
	m_PresentParams.Windowed = m_Windowed;

	// Backbuffer
	m_PresentParams.BackBufferFormat = D3DFMT_A8R8G8B8;
	m_PresentParams.BackBufferCount = 1;

	// MSAA
	DWORD MSAA_QualityLevels;
	hr = m_pD3D9->CheckDeviceMultiSampleType(	D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_A8R8G8B8,
												m_Windowed, D3DMULTISAMPLE_8_SAMPLES, &MSAA_QualityLevels);

	if (hr != S_OK)
		MessageBox(0, "Failed to get MSAA quality!", "Error", MB_OK);

	m_PresentParams.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;
	m_PresentParams.MultiSampleQuality = MSAA_QualityLevels - 1;
	
	// Depth stencil
	m_PresentParams.EnableAutoDepthStencil = true;
	m_PresentParams.AutoDepthStencilFormat = D3DFMT_D24S8;

	m_PresentParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_PresentParams.Flags = 0;
	m_PresentParams.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	m_PresentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;

	hr = m_pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window.GetWindowHandle(),
							D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_PresentParams, &m_pDevice);

	if (hr != S_OK)
		MessageBox(0, "Creating D3D9 Device failed!", "Error", MB_OK);

	// Make viewport
	D3DVIEWPORT9 Viewport;
	ZeroMemory(&Viewport, sizeof(D3DVIEWPORT9));

	Viewport.X = 0;
	Viewport.Y = 0;
	Viewport.Width = (DWORD)window.GetWidth();
	Viewport.Height = (DWORD)window.GetHeight();
	Viewport.MinZ = 0.0f;
	Viewport.MaxZ = 1.0f;

	// Set the viewport
	m_pDevice->SetViewport(&Viewport);

	// Enable back face culling
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

Renderer::~Renderer()
{
	m_pD3D9->Release();
	m_pDevice->Release();
}

void Renderer::BeginFrame()
{
	m_pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 150, 125), 1.0f, 0);
	m_pDevice->BeginScene();

	// Wireframe mode just for fun.
	if (GetAsyncKeyState(VK_TAB))
		m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	else
		m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void Renderer::EndFrame()
{
	m_pDevice->EndScene();
	m_pDevice->Present(0, 0, 0, 0);
}

IDirect3DDevice9*& Renderer::GetDevice()
{
	return m_pDevice;
}