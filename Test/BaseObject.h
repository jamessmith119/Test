#ifndef __BASEOBJECTHEADER__
#define __BASEOBJECTHEADER__

#include "BaseMesh.h"

class BaseObject
{
	private:
		BaseMesh * baseMesh;

	public:
		void Render(ID3D11DeviceContext *, ID3D11Buffer *); 

		BaseMesh * GetMesh();
		void SetMesh(BaseMesh * mesh);
};

#endif