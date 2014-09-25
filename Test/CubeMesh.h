#ifndef __CUBEMESHHEADER__
#define __CUBEMESHHEADER__

#include "BaseMesh.h"

class CubeMesh : public BaseMesh
{
	private:
		HRESULT CreateVertexBuffer();
		HRESULT CreateIndexBuffer();

	public:
		HRESULT Initialize(ID3D11Device *);
};

#endif