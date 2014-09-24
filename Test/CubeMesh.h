#ifndef __CUBEMESHHEADER__
#define __CUBEMESHHEADER__

#include "BaseMesh.h"

class CubeMesh : public BaseMesh
{
	private:
		ID3D11Device * device;
		ID3D11VertexShader * vertexShader;
		ID3D11InputLayout * vertexLayout;
		ID3D11PixelShader * pixelShader;

		HRESULT CreateVertexBuffer();
		HRESULT CreateIndexBuffer();

	public:
		CubeMesh();
		CubeMesh(ID3D11Device *);
		virtual void Render(ID3D11DeviceContext *);
		HRESULT Initialize(ID3D11Device *);
};

#endif