#ifndef __BASEMESHHEADER__
#define __BASEMESHHEADER__

#include "Global.h"
#include "GraphicsEngine.h"

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