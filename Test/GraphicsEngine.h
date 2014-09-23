#ifndef __GRAPHICSENGINEHEADER__
#define __GRAPHICSENGINEHEADER__

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

class GraphicsEngine
{
	private:
		ID3D11Device * device;
		ID3D11DeviceContext * deviceContext;
		IDXGISwapChain * swapChain;
		DXGI_SWAP_CHAIN_DESC swapChainDescription;
		ID3D11RenderTargetView * renderTargetView;
		ID3D11Texture2D * backBuffer;
		D3D_FEATURE_LEVEL featureLevelsSupported;
		IDXGIAdapter * adapter; 

		void CreateViewport();
	public:
		GraphicsEngine();
		~GraphicsEngine();
		HRESULT InitializeDevice(HWND);
		void Shutdown();
		void ClearScene();
		void Render();		

		//Properties or getters/setters
		ID3D11Device * GetGraphicsDevice();
		ID3D11DeviceContext * GetGraphicsDeviceContext();
		IDXGIAdapter * GetDefaultGraphicsAdapter();
};

#endif