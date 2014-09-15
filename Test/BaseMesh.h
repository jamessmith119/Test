#ifndef __BASEMESHHEADER__
#define __BASEMESHHEADER__

#include "GraphicsEngine.h"

class BaseMesh
{
	protected:
		ID3D11Buffer * vertexBuffer;
		ID3D11Buffer * indexBuffer;
		D3D11_BUFFER_DESC bufferDescription;
		D3D11_SUBRESOURCE_DATA bufferSubData;
		int vertexCount;
		int indexCount;

	public:
		BaseMesh();
		~BaseMesh();
		virtual void Render(ID3D11DeviceContext *);
};

#endif