#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <string>

class GUI
{
public:
	GUI(IDirect3DDevice9* &Device);
	~GUI();

	void AddText(std::string Text, float PosX, float PosY);
	void Draw();

private:
	IDirect3DDevice9* m_Device;

	ID3DXFont* m_Font;

	std::vector<RECT> Rects;
	std::vector<std::string> Texts;
};

