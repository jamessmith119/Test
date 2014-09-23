#include "Game.h"

SimpleTriangleMesh triangle;

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
		result = triangle.Initialize(graphicsEngine.GetGraphicsDevice());
	}

	return result;
}

void Game::Run()
{
	graphicsEngine.ClearScene();
	triangle.Render(graphicsEngine.GetGraphicsDeviceContext());
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