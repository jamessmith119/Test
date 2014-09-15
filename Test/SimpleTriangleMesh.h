#ifndef __SIMPLETRIANGLEMESHHEADER__
#define __SIMPLETRIANGLEMESHHEADER__

#include "BaseMesh.h"

class SimpleTriangleMesh : public BaseMesh
{
	private:
		ID3D11VertexShader * vertexShader;
		ID3D11InputLayout * vertexLayout;
		ID3D11PixelShader * pixelShader;
	public:
		SimpleTriangleMesh(ID3D11Device *);
		virtual void Render(ID3D11DeviceContext *);
};

#endif