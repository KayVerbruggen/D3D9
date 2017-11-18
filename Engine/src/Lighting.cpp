#include "Lighting.h"



Lighting::Lighting(IDirect3DDevice9*& Device)
{
	m_pDevice = Device;
}

Lighting::~Lighting()
{
}

void Lighting::CreateDirectional(D3DXVECTOR3 Position, D3DXVECTOR3 Direction)
{
	D3DLIGHT9 Light;
	Light.Type = D3DLIGHT_DIRECTIONAL;
	Light.Position = Position;
	Light.Direction = Direction;
	
	Light.Ambient = White * 0.4f;
	Light.Diffuse = White;
	Light.Specular = White * 0.6f;

	m_pDevice->SetLight(Index, &Light);
	m_pDevice->LightEnable(Index, true);

	Index++;
}

void Lighting::CreateSpot(D3DXVECTOR3 Position, D3DXVECTOR3 Direction)
{
	D3DLIGHT9 Light;
	Light.Type = D3DLIGHT_SPOT;
	Light.Position = Position;
	Light.Direction = Direction;
	Light.Range = 2.5f;

	Light.Falloff = 0.5f;
	Light.Attenuation0 = 0.1f;

	// Inner cone
	Light.Theta = 0.5f;
	// Outer cone
	Light.Phi = 1.8f;

	Light.Ambient = White * 0.4f;
	Light.Diffuse = White;
	Light.Specular = White * 0.6f;

	m_pDevice->SetLight(Index, &Light);
	m_pDevice->LightEnable(Index, true);

	Index++;
}

void Lighting::CreatePoint(D3DXVECTOR3 Position, D3DXVECTOR3 Direction)
{
	D3DLIGHT9 Light;
	Light.Type = D3DLIGHT_POINT;
	Light.Position = Position;
	Light.Direction = Direction;
	Light.Ambient = White * 0.4f;
	Light.Diffuse = White;
	Light.Specular = White * 0.6f;

	m_pDevice->SetLight(Index, &Light);
	m_pDevice->LightEnable(Index, true);

	Index++;
}

void Lighting::EnablePixelFog(DWORD Color, DWORD Mode)
{
	float Start = 0.5f;
	float End = 35.0f;
	float Density = 0.1f;

	// Enable fog blending.
	m_pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	// Set the fog color.
	m_pDevice->SetRenderState(D3DRS_FOGCOLOR, Color);

	// Set fog parameters.
	if (Mode == D3DFOG_LINEAR)
	{
		m_pDevice->SetRenderState(D3DRS_FOGTABLEMODE, Mode);
		m_pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&Start));
		m_pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD *)(&End));
	}
	else
	{
		m_pDevice->SetRenderState(D3DRS_FOGTABLEMODE, Mode);
		m_pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD *)(&Density));
	}
}
