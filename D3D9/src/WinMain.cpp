#include "Window.h"
#include "Renderer.h"
#include "Model.h"
#include "Camera.h"
#include "Lighting.h"
#include "Loader.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR CmdLine, int ShowCmd)
{
	// Create all objects
	Window window(hInstance, ShowCmd);
	Renderer renderer(window);
	IDirect3DDevice9* Device = renderer.GetDevice();
	Loader loader(Device);

	Model barrel(Device, loader, "barrel.fbx", "TextureAtlas.png");
	Model barrel2(Device, loader, "barrel.fbx", "TextureAtlas.png");
	barrel2.SetTranslation(2.5f, 0.0f, 0.0f);
	Model barrel3(Device, loader, "barrel.fbx", "TextureAtlas.png");
	barrel3.SetTranslation(-2.5f, 0.0f, 0.0f);

	Camera camera(Device);
	Lighting lighting(Device);

	// Create lights
	lighting.CreateDirectional(D3DXVECTOR3(-2.0f, 100.0f, 5.0f), D3DXVECTOR3(1.0f, -1.0f, 0.0f));

	// System for getting DeltaTime and FPS
	__int64 CountsPerSecond;
	QueryPerformanceFrequency((LARGE_INTEGER*)&CountsPerSecond);
	float SecondsPerCount = 1.0f / CountsPerSecond;

	__int64 PrevTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&PrevTime);

	// Variables for rotating the cube
	float rotX = 0.0f;
	float rotY = 0.0f;
	float rotZ = 0.0f;

	float camX = 0.0f;
	float camY = 0.0f;
	float camZ = -5.0f;

	while (window.GetMSG().message != WM_QUIT)
	{
		if (window.CheckPeekMessage())
		{
			window.HandleMessage();
		}
		else
		{
			// Capture current time
			__int64 CurrentTime = 0;
			QueryPerformanceCounter((LARGE_INTEGER*)&CurrentTime);
			
			// Calculate delta time
			float DeltaTime = (CurrentTime - PrevTime) * SecondsPerCount;

			// Calculate and output the FPS
			window.OutputFPS(DeltaTime);

			// Set and update camera
			camera.SetPosition(camX, camY, camZ);
			camera.Update();

			// Rotate cube
			rotY += 0.5f * DeltaTime;
			barrel.SetRotation(rotX, rotY, rotZ);
			barrel2.SetRotation(rotX, rotY, rotZ);
			barrel3.SetRotation(rotX, rotY, rotZ);

			// Rendering here.
			renderer.BeginFrame();

			barrel.Draw();
			barrel2.Draw();
			barrel3.Draw();

			renderer.EndFrame();

			// Set previous time to current
			PrevTime = CurrentTime;

		}
	}
	
	return 0;
}