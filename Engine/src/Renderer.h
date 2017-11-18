#pragma once

#include <d3d9.h>

#include "Window.h"

class Renderer
{
public:
	Renderer(Window& window);
	~Renderer();

	void BeginFrame();
	void EndFrame();

	IDirect3DDevice9*& GetDevice();

private:
	HRESULT hr;

	IDirect3D9* m_pD3D9;
	IDirect3DDevice9* m_pDevice;
	D3DPRESENT_PARAMETERS m_PresentParams;

	bool m_Windowed = true;
};