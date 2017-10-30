#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "Window.h"

class Camera
{
public:
	Camera(IDirect3DDevice9*& Device, Window& window);
	~Camera();

	void Update(Window& m_Window);
	void SetDirection(float x, float y, float z);

private:
	IDirect3DDevice9* m_pDevice;

	D3DXMATRIX View, Projection;
	D3DXVECTOR3 Position, Direction, Up;
};