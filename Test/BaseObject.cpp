#include "BaseObject.h"

BaseMesh * BaseObject::GetMesh()
{
	return baseMesh;
}

void BaseObject::SetMesh(BaseMesh * mesh)
{
	baseMesh = mesh;
}

void BaseObject::Render(ID3D11DeviceContext * context, ID3D11Buffer * buffer)
{
	baseMesh->Render(context);
}