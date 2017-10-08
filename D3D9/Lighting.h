#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "Renderer.h"

class Lighting
{
public:
	Lighting(IDirect3DDevice9*& m_pDevice);
	~Lighting();

	void CreateDirectional(D3DXVECTOR3 Position, D3DXVECTOR3 Direction);

private:
	D3DXCOLOR White = D3DCOLOR_ARGB(255, 255, 255, 255);

	IDirect3DDevice9* m_pDevice;
	DWORD Index = 0;
};
