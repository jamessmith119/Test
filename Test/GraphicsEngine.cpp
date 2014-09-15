#include "GraphicsEngine.h"

D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0,
									  D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0,
									  D3D_FEATURE_LEVEL_9_3, D3D_FEATURE_LEVEL_9_2, 
									  D3D_FEATURE_LEVEL_9_1 };

GraphicsEngine::GraphicsEngine()
{
	device = nullptr;
	backBuffer = nullptr;
	renderTargetView = nullptr;

	ZeroMemory(&swapChainDescription, sizeof(swapChainDescription));
}

GraphicsEngine::~GraphicsEngine()
{
	CleanupDevice();
}

HRESULT GraphicsEngine::InitializeDevice(HWND window)
{
	HRESULT hr;
	
	//Fill out the swap chain parameters.
	swapChainDescription.BufferCount = 1;
	swapChainDescription.BufferDesc.Width = 800;
	swapChainDescription.BufferDesc.Height = 600;
	swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDescription.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDescription.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDescription.OutputWindow = window;
	swapChainDescription.SampleDesc.Count = 1;
	swapChainDescription.SampleDesc.Quality = 0;
	swapChainDescription.Windowed = TRUE;

	//Try to create the device and swap chain using Direct3D 11.1 features.
	hr = D3D11CreateDeviceAndSwapChain( nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, featureLevels, _countof(featureLevels), D3D11_SDK_VERSION, &swapChainDescription, &swapChain, &device, &featureLevelsSupported, &deviceContext);	

	if (hr == E_INVALIDARG)
	{
		//The machine does not have the 11.1 runtime.
		UINT createDeviceFlags = 0;
		#ifdef _DEBUG
			createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
		#endif

		hr = D3D11CreateDeviceAndSwapChain( nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, &featureLevels[1], _countof(featureLevels) - 1, D3D11_SDK_VERSION, &swapChainDescription, &swapChain, &device, &featureLevelsSupported, &deviceContext);
	}

	//Get a pointer to the backbuffer
	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
	if(hr == S_OK)
	{
		//Only do next steps if we have a backbuffer.
		//Create the render target view.
		device->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);

		//Bind the view.
		deviceContext->OMSetRenderTargets(1, &renderTargetView, NULL);

		//Create the viewport
		CreateViewport();
	}

	return hr;
}

void GraphicsEngine::ClearScene()
{
	deviceContext->ClearRenderTargetView(renderTargetView, DirectX::Colors::MidnightBlue);
}

void GraphicsEngine::Render()
{
    swapChain->Present(0, 0);
}

void GraphicsEngine::CleanupDevice()
{
	if(deviceContext)
	{
		deviceContext->ClearState();
	}

	if(backBuffer)
	{
		backBuffer->Release();
	}

    if(renderTargetView)
	{
		renderTargetView->Release();
	}
	
    if(swapChain)
	{
		swapChain->Release();
	}

    if(deviceContext)
	{
		deviceContext->Release();
	}

    if(device)
	{
		device->Release();
	}
}

//Properties or getter/setter section
ID3D11Device * GraphicsEngine::GetGraphicsDevice()
{
	return device;
}

ID3D11DeviceContext * GraphicsEngine::GetGraphicsDeviceContext()
{
	return deviceContext;
}

//Private methods section
void GraphicsEngine::CreateViewport()
{
	// Setup the viewport
    D3D11_VIEWPORT viewPort;
    viewPort.Width = 800;
    viewPort.Height = 600;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;
    viewPort.TopLeftX = 0;
    viewPort.TopLeftY = 0;
    deviceContext->RSSetViewports(1, &viewPort);
}