#ifndef __SIMPLETRIANGLEMESHHEADER__
#define __SIMPLETRIANGLEMESHHEADER__

#include "BaseMesh.h"

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
		SimpleTriangleMesh();
		SimpleTriangleMesh(ID3D11Device *);
		virtual void Render(ID3D11DeviceContext *);
		HRESULT Initialize(ID3D11Device *);
};

#endif