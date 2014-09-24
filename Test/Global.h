#ifndef __GLOBALHEADER__
#define __GLOBALHEADER__

#include <d3d11.h>
#include <DirectXColors.h>

//Position/Normal/Texture
static D3D11_INPUT_ELEMENT_DESC PNTVertexLayout[] = 
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

struct PNTVertex
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT3 textureCoordinate;
};

//Building vertex and index info.
static PNTVertex vertices[] =
{
	DirectX::XMFLOAT3( 0.0f, 0.5f, 0.5f ), DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f ), DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f ),
	DirectX::XMFLOAT3( 0.5f, -0.5f, 0.5f ), DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f ), DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f ),
	DirectX::XMFLOAT3( -0.5f, -0.5f, 0.5f ), DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f ), DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f )
};

#endif