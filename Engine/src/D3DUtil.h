#pragma once

#include <d3d9.h>

namespace D3DColors 
{									//	 A		R		G		B
	const D3DCOLOR Red = D3DCOLOR_ARGB	(255,	255,	0,		0);
	const D3DCOLOR Green = D3DCOLOR_ARGB(255,	0,		255,	0);
	const D3DCOLOR Blue = D3DCOLOR_ARGB	(255,	0,		0,		255);
	const D3DCOLOR Purple = D3DCOLOR_ARGB(255,	150,	0,		230);
	const D3DCOLOR White = D3DCOLOR_ARGB(255,	255,	255,	255);
	const D3DCOLOR Black = D3DCOLOR_ARGB(255,	0,		0,		0);
};

struct Vertex
{
	Vertex() {}
	Vertex(float _x, float _y, float _z,  float _nx, float _ny, float _nz, float _u, float _v)
	{
		x = _x;	y = _y; z = _z; 
		nx = _nx; ny = _ny; nz = _nz;
		u = _u; v = _v;
	}
	float x, y, z;
	float nx, ny, nz;
	float u, v;

	static const DWORD FVF;
};
