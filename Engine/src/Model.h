#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <string>

#include "D3DUtil.h"
#include "Loader.h"

class Model
{
public:
	Model(IDirect3DDevice9*& Device, Loader& modelLoader, std::string ModelFile, std::string TexFile);
	~Model();

	void Draw();

	void SetScale(float scaleX, float scaleY, float scaleZ);
	void SetRotation(float rotX, float rotY, float rotZ);
	void SetTranslation(float X, float Y, float Z);

private:
	HRESULT hr;

	IDirect3DDevice9* m_pDevice;
	IDirect3DVertexBuffer9* m_VB;
	IDirect3DIndexBuffer9* m_IB;
	IDirect3DTexture9* m_Tex;
	D3DMATERIAL9 Material;

	D3DXMATRIX World;

	std::vector<Vertex> vertices;
	std::vector<WORD> indices;

	float rotX;
	float rotY;
	float rotZ;

	D3DXMATRIX Scale, rX, rY, rZ, Translation;

	int NumIndex;
};