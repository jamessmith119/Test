#ifndef __BASEMESHHEADER__
#define __BASEMESHHEADER__

#include "Global.h"
#include "GraphicsEngine.h"

class BaseMesh
{	
	protected:
		ID3D11Device * device;
		ID3D11Buffer * vertexBuffer;
		ID3D11Buffer * indexBuffer;
		ID3D11Buffer * constantBuffer;
		ID3D11VertexShader * vertexShader;
		ID3D11InputLayout * vertexLayout;
		ID3D11PixelShader * pixelShader;
		int vertexCount;
		int indexCount;

	public:
		BaseMesh();
		~BaseMesh();
		
		virtual void Render(ID3D11DeviceContext *);
		virtual ID3D11Buffer * GetConstantBuffer();
		virtual ID3D11InputLayout * GetVertexLayout();
		virtual ID3D11VertexShader * GetVertexShader();
		virtual ID3D11PixelShader * GetPixelShader();
};

#endif