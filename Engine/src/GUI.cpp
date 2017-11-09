#include "GUI.h"

GUI::GUI(IDirect3DDevice9* &Device)
{
	m_Device = Device;
	HRESULT hr = D3DXCreateFont(m_Device, 40, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
								ANTIALIASED_QUALITY, FF_DONTCARE, "GeForce Bold", &m_Font);
	if (hr != S_OK)
		MessageBoxA(0, "Creating font FAILED!", "GUI Error", MB_OK);
}

GUI::~GUI()
{
	m_Font->Release();
}

void GUI::AddText(std::string Text, float PosX, float PosY)
{
	PosX = (PosX / 100) * GetSystemMetrics(SM_CXSCREEN) - (9 * Text.size());
	PosY = (PosY / 100) * GetSystemMetrics(SM_CYSCREEN) - 20;

	RECT Rect;
	SetRect(&Rect, PosX, PosY, PosX + (18 * Text.size()), PosY + 40);
	Rects.push_back(Rect);
	Texts.push_back(Text);
}

void GUI::Draw()
{
	for (int i = 0; i < Texts.size(); i++)
	{
		m_Font->DrawTextA(NULL, Texts[i].c_str(), -1, &Rects[i], DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(0, 100, 255));
	}
}
