#include "Model.h"

const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL| D3DFVF_TEX1;

Model::Model(IDirect3DDevice9*& Device, Loader& modelLoader, std::string ModelFile, std::string TexFile)
{
	modelLoader.LoadModel(ModelFile, vertices, indices);

	m_Tex = modelLoader.LoadTexture(TexFile);
	m_pDevice = Device;
	NumIndex = indices.size();

	Material.Ambient = (D3DXCOLOR)D3DColors::White;
	Material.Diffuse = (D3DXCOLOR)D3DColors::White;
	Material.Specular = (D3DXCOLOR)D3DColors::White;
	Material.Emissive = (D3DXCOLOR)D3DColors::Black;
	
	Material.Power = 5.0f;

	// Create Buffers
	hr = m_pDevice->CreateVertexBuffer(vertices.size() * sizeof(Vertex), 0, Vertex::FVF, D3DPOOL_MANAGED, &m_VB, 0);
	if (hr != S_OK)
		MessageBoxA(0, "Creation of vertex buffer failed!", "Error", MB_OK);

	hr = m_pDevice->CreateIndexBuffer(indices.size() * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,
										D3DPOOL_MANAGED, &m_IB, NULL);
	if (hr != S_OK)
		MessageBoxA(0, "Creation of index buffer failed!", "Error", MB_OK);

	// Copy data to vertex buffer
	VOID* pVerts;
	m_VB->Lock(0, vertices.size() * sizeof(Vertex), (void**)&pVerts, 0);
	memcpy(pVerts, vertices.data(), vertices.size() * sizeof(Vertex));
	m_VB->Unlock();

	// Copy data to index buffer
	VOID* pIndices;
	m_IB->Lock(0, indices.size() * sizeof(WORD), (void**)&pIndices, 0);
	memcpy(pIndices, indices.data(), indices.size() * sizeof(WORD));
	m_IB->Unlock();

	// Set the default scale
	D3DXMatrixScaling(&Scale, 1.0f, 1.0f, 1.0f);

	// Set the default rotation
	D3DXMatrixRotationX(&rX, 0.0f);
	D3DXMatrixRotationY(&rY, 0.0f);
	D3DXMatrixRotationZ(&rZ, 0.0f);

	// Set the default Translation
	D3DXMatrixTranslation(&Translation, 0.0f, 0.0f, 0.0f);
}

Model::~Model()
{
	m_VB->Release();
	m_IB->Release();
	m_Tex->Release();
}

void Model::Draw()
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

void Model::SetScale(float scaleX, float scaleY, float scaleZ)
{
	// Change the scale
	D3DXMatrixScaling(&Scale, scaleX, scaleY, scaleZ);
}

void Model::SetRotation(float rotX, float rotY, float rotZ)
{
	// Change the rotation
	D3DXMatrixRotationX(&rX, rotX);
	D3DXMatrixRotationY(&rY, rotY);
	D3DXMatrixRotationZ(&rZ, rotZ);
}

void Model::SetTranslation(float X, float Y, float Z)
{
	// Change the Translation
	D3DXMatrixTranslation(&Translation, X, Y, Z);
}