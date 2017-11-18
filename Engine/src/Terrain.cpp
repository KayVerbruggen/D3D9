#include "Terrain.h"

Terrain::Terrain(IDirect3DDevice9*& Device, std::string TexFile)
{
	m_pDevice = Device;
	TexFile = "res/" + TexFile;

	//Create the vertex buffer
	std::vector<Vertex> vertices =
	{
		// Bottom Face
		Vertex(-1.0f,-1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 100.0f, 100.0f),
		Vertex(1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,   0.0f, 100.0f),
		Vertex(1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 0.0f,   0.0f,   0.0f),
		Vertex(-1.0f,-1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 100.0f,   0.0f)
	};

	std::vector<WORD> indices = 
	{
		0, 2, 1,
		0, 3, 2
	};

	// Create Buffers
	hr = m_pDevice->CreateVertexBuffer(vertices.size() * sizeof(Vertex), 0, Vertex::FVF, D3DPOOL_MANAGED, &m_VB, 0);
	if (hr != S_OK)
		MessageBox(0, "Creation of vertex buffer failed!", "Terrain Error", MB_OK);

	hr = m_pDevice->CreateIndexBuffer(indices.size() * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,
		D3DPOOL_MANAGED, &m_IB, NULL);
	if (hr != S_OK)
		MessageBox(0, "Creation of index buffer failed!", "Terrain Error", MB_OK);

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

	hr = D3DXCreateTextureFromFile(m_pDevice, TexFile.c_str(), &m_Tex);
	if (hr != S_OK)
		MessageBox(0, "Failed to create Texture", "Terrain Error", MB_OK);

	// Set the default scale
	D3DXMatrixScaling(&Scale, 100.0f, 1.0f, 100.0f);

	// Set the default Translation
	D3DXMatrixTranslation(&Translation, 0.0f, 0.0f, 0.0f);
}

Terrain::~Terrain()
{
}

void Terrain::Draw()
{
	m_pDevice->SetTexture(0, m_Tex);

	World = Scale * Translation;
	m_pDevice->SetTransform(D3DTS_WORLD, &World);

	// Normalize the normals after scaling
	m_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);

	m_pDevice->SetStreamSource(0, m_VB, 0, sizeof(Vertex));
	m_pDevice->SetIndices(m_IB);
	m_pDevice->SetFVF(Vertex::FVF);
	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 6, 0, 2);
}