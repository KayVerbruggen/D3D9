#include "Mesh.h"

const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL| D3DFVF_TEX1;

Mesh::Mesh(IDirect3DDevice9*& Device, std::vector<Vertex> vertices, std::vector<WORD> indices, const char* TexFile)
{
	m_pDevice = Device;
	NumIndex = indices.size();

	Material.Ambient = (D3DXCOLOR)D3DColors::White;
	Material.Diffuse = (D3DXCOLOR)D3DColors::White;
	Material.Specular = (D3DXCOLOR)D3DColors::White;
	Material.Emissive = (D3DXCOLOR)D3DColors::Black;
	
	Material.Power = 5.0f;

	hr = m_pDevice->CreateVertexBuffer(vertices.size() * sizeof(Vertex), 0, Vertex::FVF, D3DPOOL_MANAGED, &m_VB, 0);
	if (hr != S_OK)
		MessageBoxA(0, "Creation of vertex buffer failed!", "Error", MB_OK);

	hr = m_pDevice->CreateIndexBuffer(indices.size() * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,
										D3DPOOL_MANAGED, &m_IB, NULL);
	if (hr != S_OK)
		MessageBoxA(0, "Creation of index buffer failed!", "Error", MB_OK);

	VOID* pVerts;
	m_VB->Lock(0, vertices.size() * sizeof(Vertex), (void**)&pVerts, 0);
	memcpy(pVerts, vertices.data(), vertices.size() * sizeof(Vertex));
	m_VB->Unlock();

	VOID* pIndices;
	hr = m_IB->Lock(0, indices.size() * sizeof(WORD), (void**)&pIndices, 0);
	memcpy(pIndices, indices.data(), indices.size() * sizeof(WORD));
	m_IB->Unlock();

	// Read file
	D3DXCreateTextureFromFile(m_pDevice, TexFile, &m_Tex);
	if (!m_Tex)
		MessageBoxA(0, "Failed to create texture!", "Errpr", MB_OK);

	// Set the default scale
	D3DXMatrixScaling(&Scale, 1.0f, 1.0f, 1.0f);

	// Set the default rotation
	D3DXMatrixRotationX(&rX, 0.0f);
	D3DXMatrixRotationY(&rY, 0.0f);
	D3DXMatrixRotationZ(&rZ, 0.0f);

	// Set the default Translation
	D3DXMatrixTranslation(&Translation, 0.0f, 0.0f, 5.0f);
}

Mesh::~Mesh()
{
	m_VB->Release();
	m_IB->Release();
	m_Tex->Release();
}

void Mesh::Draw()
{
	m_pDevice->SetTexture(0, m_Tex);
	m_pDevice->SetMaterial(&Material);

	World = Scale * rX * rY * rZ * Translation;
	m_pDevice->SetTransform(D3DTS_WORLD, &World);

	// Normalize the normals after scaling
	m_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);

	m_pDevice->SetStreamSource(0, m_VB, 0, sizeof(Vertex));
	m_pDevice->SetIndices(m_IB);
	m_pDevice->SetFVF(Vertex::FVF);
	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumIndex, 0, NumIndex / 3);
}

void Mesh::SetScale(float scaleX, float scaleY, float scaleZ)
{
	// Change the scale
	D3DXMatrixScaling(&Scale, scaleX, scaleY, scaleZ);
}

void Mesh::SetRotation(float rotX, float rotY, float rotZ)
{
	// Change the rotation
	D3DXMatrixRotationX(&rX, rotX);
	D3DXMatrixRotationY(&rY, rotY);
	D3DXMatrixRotationZ(&rZ, rotZ);
}

void Mesh::SetTranslation(float X, float Y, float Z)
{
	// Change the Translation
	D3DXMatrixTranslation(&Translation, X, Y, Z);
}