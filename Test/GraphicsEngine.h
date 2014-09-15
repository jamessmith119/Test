#ifndef __GRAPHICSENGINEHEADER__
#define __GRAPHICSENGINEHEADER__

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

//TO-DO MOVE ME
struct PNTVertex
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT3 textureCoordinate;
};

//TO-DO MOVE ME
static D3D11_INPUT_ELEMENT_DESC PNTVertexLayout[] =
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

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

		void CreateViewport();
	public:
		GraphicsEngine();
		~GraphicsEngine();
		HRESULT InitializeDevice(HWND);
		void CleanupDevice();
		void ClearScene();
		void Render();		

		//Properties or getters/setters
		ID3D11Device * GetGraphicsDevice();
		ID3D11DeviceContext * GetGraphicsDeviceContext();
};

#endif