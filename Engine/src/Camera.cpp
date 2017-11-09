#include "Camera.h"

enum Keys : WPARAM
{
	A = 0x41, B, C, D, E, F, G,
	H, I, J, K, L, M, N, O, P, Q,
	R, S, T, U, V, W, X, Y, Z
};

Camera::Camera(IDirect3DDevice9*& Device, Window& window)
{
	m_pDevice = Device;

	// Default position and rotation
	Position = D3DXVECTOR3(0.0f, 0.0f, -5.0f);
	Direction = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);;

	D3DXMatrixLookAtLH(&View, &Position, &Direction, &Up);
	m_pDevice->SetTransform(D3DTS_VIEW, &View);

	D3DXMatrixPerspectiveFovLH(&Projection, 45, (window.GetWidth() / window.GetHeight()), 1.0f, 1000.0f);
	m_pDevice->SetTransform(D3DTS_PROJECTION, &Projection);

	// Disable lighting for now
	m_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	m_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
}

Camera::~Camera()
{
}

void Camera::Update(float DeltaTime)
{
	// Check if for keys pressed
	if(GetAsyncKeyState(A))
	{
		// Go left.
		Position.x -= MovementSpeed * DeltaTime;
	}
	if (GetAsyncKeyState(D))
	{
		// Go right.
		Position.x += MovementSpeed * DeltaTime;
	}
	if (GetAsyncKeyState(W))
	{
		// Go forward.
		Position.z += MovementSpeed * DeltaTime;
	}
	if (GetAsyncKeyState(S))
	{
		// Go backwards.
		Position.z -= MovementSpeed * DeltaTime;
	}
	if (GetAsyncKeyState(VK_LSHIFT))
	{
		// Go forward.
		Position.y += MovementSpeed * DeltaTime;
	}
	if (GetAsyncKeyState(VK_LCONTROL))
	{
		// Go backwards.
		Position.y -= MovementSpeed * DeltaTime;
	}

	Direction = D3DXVECTOR3(Position.x, Position.y, Position.z + 1.0f);
	D3DXMatrixLookAtLH(&View, &Position, &Direction, &Up);
	m_pDevice->SetTransform(D3DTS_VIEW, &View);
}

void Camera::SetDirection(float x, float y, float z)
{
	Direction = D3DXVECTOR3(-x, -y, z);
}