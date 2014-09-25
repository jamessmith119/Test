#include "Game.h"

SimpleTriangle triangle;
SimpleTriangleMesh triangleMesh;
Cube cube;
CubeMesh cubeMesh;

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
		//result = triangleMesh.Initialize(graphicsEngine.GetGraphicsDevice());
		result = cubeMesh.Initialize(graphicsEngine.GetGraphicsDevice());
		if(result == S_OK)
		{
			//triangle.SetMesh(&mesh);
			//gameObjects.push_back(triangle);

			cube.SetMesh(&cubeMesh);
			gameObjects.push_back(cube);

			//XMVECTOR Eye = XMVectorSet( 0.0f, 1.0f, -5.0f, 0.0f );
			//XMVECTOR At = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
			//XMVECTOR Up = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
			//g_View = XMMatrixLookAtLH( Eye, At, Up );

			//// Initialize the projection matrix
			//g_Projection = XMMatrixPerspectiveFovLH( XM_PIDIV2, width / (FLOAT)height, 0.01f, 100.0f );

			camera.SetEye(DirectX::XMFLOAT3(0.0f, 1.0f, -5.0f));
			//camera.SetProjection();
		}
	}

	return result;
}

void Game::Run()
{
	graphicsEngine.ClearScene();

	for (std::vector<BaseObject>::iterator objectIterator = gameObjects.begin() ; objectIterator != gameObjects.end(); objectIterator++)
	{
		ID3D11Buffer * g = objectIterator->GetMesh()->GetConstantBuffer();
		graphicsEngine.GetGraphicsDeviceContext()->IASetInputLayout(objectIterator->GetMesh()->GetVertexLayout());
		graphicsEngine.GetGraphicsDeviceContext()->VSSetShader(objectIterator->GetMesh()->GetVertexShader(), nullptr, 0);

		ConstantBuffer cb;
		cb.mWorld = DirectX::XMMatrixTranspose(DirectX::XMMatrixIdentity());
		cb.mView = DirectX::XMMatrixTranspose(camera.View());
		cb.mProjection = DirectX::XMMatrixTranspose(camera.Projection());
		graphicsEngine.GetGraphicsDeviceContext()->UpdateSubresource(g, 0, nullptr, &cb, 0, 0);

		graphicsEngine.GetGraphicsDeviceContext()->VSSetConstantBuffers(0, 1, &g);
		graphicsEngine.GetGraphicsDeviceContext()->PSSetShader(objectIterator->GetMesh()->GetPixelShader(), nullptr, 0);

		objectIterator->Render(graphicsEngine.GetGraphicsDeviceContext(), nullptr);
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