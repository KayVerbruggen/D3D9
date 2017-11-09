#pragma once

#include <string>
#include <vector>
#include <d3dx9.h>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "D3DUtil.h"

class Loader
{
public:
	Loader(IDirect3DDevice9*& Device);
	~Loader();

	void LoadModel(std::string FileName, std::vector<Vertex> &OutVertices, std::vector<WORD> &OutIndices);
	IDirect3DTexture9*& LoadTexture(std::string TexFile);

private:
	Assimp::Importer importer;
	IDirect3DDevice9* m_pDevice;

	std::vector<IDirect3DTexture9*> textures;
	std::vector<std::string> loadedTex;

	std::vector<std::string> loadedMesh;
	std::vector< std::vector<Vertex> > loadedVertices;
	std::vector< std::vector<WORD> > loadedIndices;

	std::vector<Vertex> ProcessVertices(aiMesh* mesh);
	std::vector<WORD> ProcessIndices(aiMesh* mesh);
};

