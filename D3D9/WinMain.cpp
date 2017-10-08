#include "Window.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Camera.h"
#include "Lighting.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR CmdLine, int ShowCmd)
{

	std::vector<Vertex> vertices =
	{
		// Front
		Vertex(-1.0f, 1.0f, -1.0f,	0.0f, 0.0f, -1.0f,	0.0f, 0.0f),
		Vertex(1.0f, 1.0f, -1.0f,	0.0f, 0.0f, -1.0f,	1.0f, 0.0f),
		Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f,	0.0f, 1.0f),
		Vertex(1.0f, -1.0f, -1.0f,	0.0f, 0.0f, -1.0f,	1.0f, 1.0f),
											  
		// Back						
		Vertex(1.0f, 1.0f, 1.0f,	 0.0f, 0.0f, 1.0f,	0.0f, 0.0f),
		Vertex(-1.0f, 1.0f, 1.0f,	 0.0f, 0.0f, 1.0f,	1.0f, 0.0f),
		Vertex(1.0f, -1.0f, 1.0f,	 0.0f, 0.0f, 1.0f,	0.0f, 1.0f),
		Vertex(-1.0f, -1.0f, 1.0f,	 0.0f, 0.0f, 1.0f,	1.0f, 1.0f),
										
		// Left							
		Vertex(-1.0f, 1.0f, 1.0f,	 -1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
		Vertex(-1.0f, 1.0f, -1.0f,	 -1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
		Vertex(-1.0f, -1.0f, 1.0f,	 -1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
		Vertex(-1.0f, -1.0f, -1.0f,	 -1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
											
		// Right							
		Vertex(1.0f, 1.0f, -1.0f,	 1.0f, 0.0f, 0.0f,	0.0f, 0.0f),
		Vertex(1.0f, 1.0f, 1.0f,	 1.0f, 0.0f, 0.0f,	1.0f, 0.0f),
		Vertex(1.0f, -1.0f, -1.0f,	 1.0f, 0.0f, 0.0f,	0.0f, 1.0f),
		Vertex(1.0f, -1.0f, 1.0f,	 1.0f, 0.0f, 0.0f,	1.0f, 1.0f),
										  
		// Top							  
		Vertex(-1.0f, 1.0f, 1.0f,	 0.0f, 1.0f, 0.0f,	0.0f, 0.0f),
		Vertex(1.0f, 1.0f, 1.0f,	 0.0f, 1.0f, 0.0f,	1.0f, 0.0f),
		Vertex(-1.0f, 1.0f, -1.0f,	 0.0f, 1.0f, 0.0f,	0.0f, 1.0f),
		Vertex(1.0f, 1.0f, -1.0f,	 0.0f, 1.0f, 0.0f,	1.0f, 1.0f),
											   
		// Bottom							  
		Vertex(1.0f, -1.0f, 1.0f,	 0.0f, -1.0f, 0.0f, 0.0f, 0.0f),
		Vertex(-1.0f, -1.0f, 1.0f,	 0.0f, -1.0f, 0.0f, 1.0f, 0.0f),
		Vertex(1.0f, -1.0f, -1.0f,	 0.0f, -1.0f, 0.0f, 0.0f, 1.0f),
		Vertex(-1.0f, -1.0f, -1.0f,	 0.0f, -1.0f, 0.0f, 1.0f, 1.0f),
	};

	std::vector<WORD> indices =
	{
		// Front face
		0, 1, 2,
		2, 1, 3,

		// Back face
		4, 5, 6,
		6, 5, 7,

		// Left face
		8, 9, 10,
		10, 9, 11,

		// Right face
		12, 13, 14,
		14, 13, 15,

		// Top
		16, 17, 18,
		18, 17, 19,

		// Bottom
		20, 21, 22,
		22, 21, 23
	};

	// Create all objects
	Window window(hInstance, ShowCmd);
	Renderer renderer(window);
	Mesh mesh(renderer.GetDevice(), vertices, indices, "img.png");
	Camera camera(renderer.GetDevice());
	Lighting lighting(renderer.GetDevice());

	// Create lights
	lighting.CreateDirectional(D3DXVECTOR3(-2.0f, 0.0f, 5.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f));

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
			mesh.SetRotation(rotX, rotY, rotZ);

			// Rendering here.
			renderer.BeginFrame();

			mesh.Draw();

			renderer.EndFrame();

			// Set previous time to current
			PrevTime = CurrentTime;
		}
	}
	return 0;
}