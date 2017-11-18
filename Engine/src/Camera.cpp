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
	m_Width = window.GetWidth();
	m_Height = window.GetHeight();

	// Default position and rotation
	Position = D3DXVECTOR3(0.0f, 0.0f, -5.0f);
	Direction = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXMatrixLookAtLH(&View, &Position, &Direction, &Up);
	m_pDevice->SetTransform(D3DTS_VIEW, &View);

	D3DXMatrixPerspectiveFovLH(&Projection, 45, (m_Width / m_Height), 1.0f, 1000.0f);
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
		MovementHorizontal = -MovementSpeed * DeltaTime;
	}
	if (GetAsyncKeyState(D))
	{
		// Go right.
		MovementHorizontal = MovementSpeed * DeltaTime;
	}
	if (GetAsyncKeyState(W))
	{
		// Go forward.
		MovementForward = MovementSpeed * DeltaTime;
	}
	if (GetAsyncKeyState(S))
	{
		// Go backwards.
		MovementForward = -MovementSpeed * DeltaTime;
	}

	// Get the cursor position
	GetCursorPos(&CursorPoint);

	// Check if the cursor has moved
	if (CursorPoint.x != LastCursorPoint.x)
	{
		// Use delta x to rotate
		CamYaw += (CursorPoint.x - LastCursorPoint.x) * (MouseSensitivity / 100.0f);
	}
	if (CursorPoint.y != LastCursorPoint.y)
	{
		// Use delta y to rotate
		CamPitch += (CursorPoint.y - LastCursorPoint.y) * (MouseSensitivity / 100.0f);

		// No backflips
		if (CamPitch >= 90)
		{
			CamPitch = 90;
		} else if (CamPitch <= -90)
		{
			CamPitch = -90;
		}
	}

	D3DXMatrixRotationYawPitchRoll(&Rotation, D3DXToRadian(CamYaw), D3DXToRadian(CamPitch), 0);
	D3DXVec3TransformCoord(&Direction, &DefaultForward, &Rotation);
	D3DXVec3Normalize(&Direction, &Direction);
	
	D3DXMATRIX RotateYTempMatrix;
	D3DXMatrixRotationY(&RotateYTempMatrix, D3DXToRadian(CamYaw));

	D3DXVec3TransformCoord(&Right, &DefaultRight, &RotateYTempMatrix);
	D3DXVec3TransformCoord(&Up, &Up, &RotateYTempMatrix);
	D3DXVec3TransformCoord(&Forward, &DefaultForward, &RotateYTempMatrix);

	Position += MovementHorizontal * Right;
	Position += MovementForward * Forward;

	MovementHorizontal = 0.0f;
	MovementForward = 0.0f;

	Direction = Position + Direction;

	D3DXMatrixLookAtLH(&View, &Position, &Direction, &Up);
	m_pDevice->SetTransform(D3DTS_VIEW, &View);
	
	// Lock the cursor to the middle of the screen so it can't hit the border
	SetCursorPos(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);
}