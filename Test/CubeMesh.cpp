#include "CubeMesh.h"

WORD cubeIndices[] =
{
	0, 1, 2
};

CubeMesh::CubeMesh()
{
}

CubeMesh::CubeMesh(ID3D11Device * graphicsDevice)
{
	Initialize(graphicsDevice);
}

HRESULT CubeMesh::Initialize(ID3D11Device * graphicsDevice)
{
	HRESULT result = S_OK;

	device = graphicsDevice;
	vertexCount = 3;
	indexCount = sizeof(cubeIndices);	

	ID3DBlob * vBlob = nullptr;
	ID3DBlob * errorBlob = nullptr;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

	#ifdef _DEBUG
		// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
		// Setting this flag improves the shader debugging experience, but still allows 
		// the shaders to be optimized and to run exactly the way they will run in 
		// the release configuration of this program.
		dwShaderFlags |= D3DCOMPILE_DEBUG;

		// Disable optimizations to further improve shader debugging
		dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
	#endif

	result = D3DCompileFromFile(L"SimpleTriangle.fx", nullptr, nullptr, "VS", "vs_4_0", dwShaderFlags, 0, &vBlob, &errorBlob);
	if(FAILED(result = device->CreateVertexShader(vBlob->GetBufferPointer(), vBlob->GetBufferSize(), nullptr, &vertexShader)))
	{
		return E_FAIL;
	}

	UINT layout = ARRAYSIZE(PNTVertexLayout);

	// Create the input layout
	if(FAILED(result = device->CreateInputLayout(PNTVertexLayout, layout, vBlob->GetBufferPointer(), vBlob->GetBufferSize(), &vertexLayout)))
	{
		return E_FAIL;
	}

	ID3DBlob * pBlob = nullptr;
	if(FAILED(result = D3DCompileFromFile(L"SimpleTriangle.fx", nullptr, nullptr, "PS", "ps_4_0", dwShaderFlags, 0, &pBlob, &errorBlob)))
	{
		return E_FAIL;
	}

	// Create the pixel shader
	if(FAILED(result = device->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pixelShader )))
	{
		return E_FAIL;
	}

	if(FAILED(CreateVertexBuffer()))
	{
		return E_FAIL;
	}

	if(FAILED(CreateIndexBuffer()))
	{
		return E_FAIL;
	}

	return result;
}

void CubeMesh::Render(ID3D11DeviceContext * context)
{
	context->IASetInputLayout(vertexLayout);

	//Shaders should be set on Material object.
	context->VSSetShader(vertexShader, nullptr, 0);
	context->PSSetShader(pixelShader, nullptr, 0);

	BaseMesh::Render(context);
}

HRESULT CubeMesh::CreateVertexBuffer()
{
	HRESULT result;
	D3D11_BUFFER_DESC bufferDescription;
	D3D11_SUBRESOURCE_DATA bufferSubData;

	ZeroMemory(&bufferDescription, sizeof(bufferDescription));
	ZeroMemory(&bufferSubData, sizeof(bufferSubData));

	//Fill in the vertex buffer description.
	bufferDescription.Usage = D3D11_USAGE_DEFAULT;
	bufferDescription.ByteWidth = sizeof(PNTVertex) * vertexCount;
	bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDescription.CPUAccessFlags = 0;
	bufferDescription.MiscFlags = 0;

	//Fill in the vertex subresource data.
	bufferSubData.pSysMem = vertices;
	bufferSubData.SysMemPitch = 0;
	bufferSubData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&bufferDescription, &bufferSubData, &vertexBuffer);

	return result;
}

HRESULT CubeMesh::CreateIndexBuffer()
{
	HRESULT result;	
	D3D11_BUFFER_DESC bufferDescription;
	D3D11_SUBRESOURCE_DATA bufferSubData;

	ZeroMemory(&bufferDescription, sizeof(bufferDescription));
	ZeroMemory(&bufferSubData, sizeof(bufferSubData));

	//Fill in the index buffer description.
	bufferDescription.Usage = D3D11_USAGE_DEFAULT;
	bufferDescription.ByteWidth = sizeof(WORD) * indexCount;
	bufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDescription.CPUAccessFlags = 0;
	bufferDescription.MiscFlags = 0;

	//Fill in the index subresource data.
	bufferSubData.pSysMem = cubeIndices;
	bufferSubData.SysMemPitch = 0;
	bufferSubData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&bufferDescription, &bufferSubData, &indexBuffer);

	return result;
}