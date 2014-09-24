#include "Game.h"

SimpleTriangle triangle;
SimpleTriangleMesh mesh;

Game::Game(HWND window)
{
	mainGameWindow = window;
}

HRESULT Game::Initialize()
{
	HRESULT result = S_OK;

	//Initialize Direct3D;
	result = graphicsEngine.InitializeDevice(mainGameWindow);
	
	if(result == S_OK)
	{
		result = mesh.Initialize(graphicsEngine.GetGraphicsDevice());
		if(result == S_OK)
		{
			triangle.SetMesh(&mesh);
			gameObjects.push_back(&triangle);
		}
	}

	return result;
}

void Game::Run()
{
	graphicsEngine.ClearScene();

	for(unsigned int x = 0; x < gameObjects.size(); x++)
	{
		graphicsEngine.GetGraphicsDeviceContext()->IASetInputLayout(mesh.GetVertexLayout());
		graphicsEngine.GetGraphicsDeviceContext()->VSSetShader(mesh.GetVertexShader(), nullptr, 0);
		graphicsEngine.GetGraphicsDeviceContext()->PSSetShader(mesh.GetPixelShader(), nullptr, 0);

		gameObjects[x]->Render(graphicsEngine.GetGraphicsDeviceContext(), nullptr);
	}

	graphicsEngine.Render();
}

void Game::Shutdown()
{
	graphicsEngine.Shutdown();
}

HWND Game::GetGameWindow()
{
	return mainGameWindow;
}