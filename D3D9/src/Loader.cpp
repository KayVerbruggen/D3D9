#include "Loader.h"

Loader::Loader(IDirect3DDevice9*& Device)
{
	m_pDevice = Device;
}

Loader::~Loader()
{
}

// TODO: Make this work with multiple meshes.
void Loader::LoadModel(std::string FileName, std::vector<Vertex> &OutVertices, std::vector<WORD> &OutIndices)
{
	// Go to the res directory.
	FileName = "res/" + FileName;

	if (!loadedMesh.empty())
	{
		for (unsigned int i = 0; i < loadedMesh.size(); i++)
		{
			if (FileName == loadedMesh[i])
			{
				OutVertices = loadedVertices[i];
				OutIndices = loadedIndices[i];
				goto end;
			}
		}
	}

	// Read the file and save it as a scene.
	const aiScene* scene = importer.ReadFile(FileName,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_FlipUVs |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	aiMesh* mesh = scene->mMeshes[0];

	OutVertices = ProcessVertices(mesh);
	OutIndices = ProcessIndices(mesh);

end:
	loadedMesh.push_back(FileName);
	loadedVertices.push_back(OutVertices);
	loadedIndices.push_back(OutIndices);
}

IDirect3DTexture9*& Loader::LoadTexture(std::string TexFile)
{
	TexFile = "res/" + TexFile;
	
	if (!loadedTex.empty())
	{
		for (unsigned int i = 0; i < loadedTex.size(); i++)
		{
			if (TexFile == loadedTex[i])
			{
				return textures[i];
			}
		}
	}

	IDirect3DTexture9* m_Tex;

	// Read file
	D3DXCreateTextureFromFile(m_pDevice, TexFile.c_str(), &m_Tex);
	if (!m_Tex)
		MessageBoxA(0, "Failed to create texture!", "Error", MB_OK);
	
	textures.push_back(m_Tex);
	loadedTex.push_back(TexFile);

	return m_Tex;
}

std::vector<Vertex> Loader::ProcessVertices(aiMesh* mesh)
{
	// Empty vectors, will be filled when the file is read.
	std::vector<Vertex> Vertices;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		// Add the positions to the vertex.
		aiVector3D pos = mesh->mVertices[i];
		vertex.x = pos.y;
		vertex.y = pos.z;
		vertex.z = pos.x;

		// Add normals.
		aiVector3D normals = mesh->mNormals[i];
		vertex.nx = normals.y;
		vertex.ny = normals.z;
		vertex.nz = normals.x;

		if (mesh->mTextureCoords[0])
		{
			// Add texure coordinates.
			vertex.u = mesh->mTextureCoords[0][i].x;
			vertex.v = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			vertex.u = 0;
			vertex.v = 0;
		}


		Vertices.push_back(vertex);
	}
	return Vertices;
}

std::vector<WORD> Loader::ProcessIndices(aiMesh* mesh)
{
	// Empty vectors, will be filled when the file is read.
	std::vector<WORD> Indices;

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			Indices.push_back(face.mIndices[j]);
	}

	return Indices;
}