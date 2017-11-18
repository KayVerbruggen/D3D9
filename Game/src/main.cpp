#include "Window.h"
#include "Renderer.h"
#include "Model.h"
#include "Camera.h"
#include "Lighting.h"
#include "Loader.h"
#include "GUI.h"
#include "Time.hpp"
#include "Terrain.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR CmdLine, int ShowCmd)
{
	std::vector<Model> models;

	// Create all objects
	Window window(hInstance, ShowCmd);
	Renderer renderer(window);
	IDirect3DDevice9* Device = renderer.GetDevice();

	Loader loader(Device);
	GUI gui(Device);
	gui.AddText("Dit is een demo", 50.0f, 5.0f);

	Model barrel(Device, loader, "barrel.fbx", "TextureAtlas.png");
	Model tree(Device, loader, "tree.fbx", "TextureAtlas.png");
	tree.SetTranslation(2.5f, -1.0f, 0.0f);
	Model barrel2(Device, loader, "barrel.fbx", "TextureAtlas.png");
	barrel2.SetTranslation(-2.5f, 0.0f, 0.0f);

	Terrain terrain(Device, "grass.png");
	Camera camera(Device, window);
	Lighting lighting(Device);

	// Create lights
	lighting.CreateDirectional(D3DXVECTOR3(-2.0f, 100.0f, 5.0f), D3DXVECTOR3(1.0f, -1.0f, 0.0f));
	// lighting.EnablePixelFog((DWORD)D3DCOLOR_RGBA(255, 255, 255, 5), D3DFOG_EXP);

	StartTimer();

	// Variables for rotating the cube
	float rotX = 0.0f;
	float rotY = 0.0f;
	float rotZ = 0.0f;

	while (window.GetMSG().message != WM_QUIT)
	{
		window.HandleMessage();
		UpdateTimer();
		camera.Update(DeltaTime);

		// Rotate cube
		rotY += 0.5f * DeltaTime;
		barrel.SetRotation(rotX, rotY, rotZ);
		barrel2.SetRotation(rotX, rotY, rotZ);
		tree.SetRotation(rotX, rotY, rotZ);

		// Rendering here.
		renderer.BeginFrame();

		terrain.Draw();
		gui.Draw();

		barrel.Draw();
		barrel2.Draw();
		tree.Draw();

		renderer.EndFrame();

		SetPrevTime();
	}

	return 0;
}