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