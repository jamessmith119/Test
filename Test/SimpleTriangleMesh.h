#ifndef __SIMPLETRIANGLEMESHHEADER__
#define __SIMPLETRIANGLEMESHHEADER__

#include "BaseMesh.h"

//Building vertex and index info.
const PNTVertex vertices[] =
{
	DirectX::XMFLOAT3( 0.0f, 0.5f, 0.5f ), DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f ), DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f ),
	DirectX::XMFLOAT3( 0.5f, -0.5f, 0.5f ), DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f ), DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f ),
	DirectX::XMFLOAT3( -0.5f, -0.5f, 0.5f ), DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f ), DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f )
};

const WORD triangleIndices[] =
{
	0, 1, 2
};

class SimpleTriangleMesh : public BaseMesh
{
	private:
		ID3D11Device * device;
		ID3D11VertexShader * vertexShader;
		ID3D11InputLayout * vertexLayout;
		ID3D11PixelShader * pixelShader;

		HRESULT CreateVertexBuffer();
		HRESULT CreateIndexBuffer();
	public:
		SimpleTriangleMesh(ID3D11Device *);
		virtual void Render(ID3D11DeviceContext *);
		HRESULT Initialize();
};

#endif