#ifndef __SIMPLETRIANGLEMESHHEADER__
#define __SIMPLETRIANGLEMESHHEADER__

#include "BaseMesh.h"

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
		HRESULT Initialize(ID3D11Device *);

		ID3D11VertexShader * GetVertexShader();
		ID3D11InputLayout * GetVertexLayout();
		ID3D11PixelShader * GetPixelShader();
};

#endif