#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "Window.h"

class Camera
{
public:
	Camera(IDirect3DDevice9*& Device, Window& window);
	~Camera();

	void Update(float DeltaTime);
	void SetDirection(float x, float y, float z);

private:
	IDirect3DDevice9* m_pDevice;

	D3DXMATRIX View, Projection;
	D3DXVECTOR3 Position, Direction, Up;

	float MovementSpeed = 2.0f;
};