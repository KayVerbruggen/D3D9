#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class Camera
{
public:
	Camera(IDirect3DDevice9*& Device);
	~Camera();

	void Update();

	void SetPosition(float x, float y, float z);
	void SetDirection(float x, float y, float z);

private:
	IDirect3DDevice9* m_pDevice;

	D3DXMATRIX View, Projection;
	D3DXVECTOR3 Position, Direction, Up;
};