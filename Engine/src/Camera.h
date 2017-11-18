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

private:
	IDirect3DDevice9* m_pDevice;

	D3DXMATRIX View, Projection, Rotation;
	D3DXVECTOR3 Position, Direction, Up, Right, Forward;

	D3DXVECTOR3 DefaultForward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 DefaultRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	float MovementHorizontal, MovementForward;

	float MovementSpeed = 2.0f;
	float MouseSensitivity = 4.0f;

	float CamYaw = 0.0f;
	float CamPitch = 0.0f;

	float m_Width, m_Height;

	POINT CursorPoint;
	POINT LastCursorPoint = { GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2 };
};