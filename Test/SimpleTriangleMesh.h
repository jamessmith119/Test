#ifndef __SIMPLETRIANGLEMESHHEADER__
#define __SIMPLETRIANGLEMESHHEADER__

#include "BaseMesh.h"

class SimpleTriangleMesh : public BaseMesh
{
	private:
		HRESULT CreateVertexBuffer();
		HRESULT CreateIndexBuffer();

	public:
		HRESULT Initialize(ID3D11Device *);
};

#endif