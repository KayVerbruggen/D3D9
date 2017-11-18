#pragma once

#include <string>
#include <vector>
#include "D3DUtil.h"
#include <d3dx9.h>

class Terrain
{
public:
	Terrain(IDirect3DDevice9*& Device, std::string TexFile);
	~Terrain();

	void Draw();

private:
	HRESULT hr;

	IDirect3DDevice9* m_pDevice;
	IDirect3DVertexBuffer9* m_VB;
	IDirect3DIndexBuffer9* m_IB;
	IDirect3DTexture9* m_Tex;

	float rotX;
	float rotY;
	float rotZ;

	D3DXMATRIX Scale, rX, rY, rZ, Translation, World;
};