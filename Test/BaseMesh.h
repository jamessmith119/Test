#ifndef __BASEMESHHEADER__
#define __BASEMESHHEADER__

#include "GraphicsEngine.h"

struct PNTVertex
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT3 textureCoordinate;
};

//Position/Normal/Texture
static D3D11_INPUT_ELEMENT_DESC PNTVertexLayout[] =
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

class BaseMesh
{
	protected:
		ID3D11Buffer * vertexBuffer;
		ID3D11Buffer * indexBuffer;
		int vertexCount;
		int indexCount;

	public:
		BaseMesh();
		~BaseMesh();
		virtual void Render(ID3D11DeviceContext *);
};

#endif