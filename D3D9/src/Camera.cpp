#include "Camera.h"

Camera::Camera(IDirect3DDevice9*& Device)
{
	m_pDevice = Device;

	// Default position and rotation
	Position = D3DXVECTOR3(0.0f, 0.0f, -5.0f);
	Direction = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXMatrixLookAtLH(&View, &Position, &Direction, &Up);
	m_pDevice->SetTransform(D3DTS_VIEW, &View);

	D3DXMatrixPerspectiveFovLH(&Projection, 45, 1.78f, 1.0f, 1000.0f);
	m_pDevice->SetTransform(D3DTS_PROJECTION, &Projection);

	// Disable lighting for now
	m_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	m_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	D3DXMatrixLookAtLH(&View, &Position, &Direction, &Up);
	m_pDevice->SetTransform(D3DTS_VIEW, &View);
}

void Camera::SetPosition(float x, float y, float z)
{
	Position = D3DXVECTOR3(-x, -y, z);
}

void Camera::SetDirection(float x, float y, float z)
{
	Direction = D3DXVECTOR3(-x, -y, z);
}