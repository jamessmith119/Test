#include "SimpleTriangleMesh.h"

//Building vertex and index info.
PNTVertex vertices[] =
{
	DirectX::XMFLOAT3( 0.0f, 0.5f, 0.5f ), DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f ), DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f ),
	DirectX::XMFLOAT3( 0.5f, -0.5f, 0.5f ), DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f ), DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f ),
	DirectX::XMFLOAT3( -0.5f, -0.5f, 0.5f ), DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f ), DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f )
};

SimpleTriangleMesh::SimpleTriangleMesh(ID3D11Device * graphicsDevice)
{
	device = graphicsDevice;
	vertexCount = 3;
	indexCount = sizeof(triangleIndices);	

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

	HRESULT hr = D3DCompileFromFile(L"SimpleTriangle.fx", nullptr, nullptr, "VS", "vs_4_0", dwShaderFlags, 0, &vBlob, &errorBlob);
	hr = device->CreateVertexShader(vBlob->GetBufferPointer(), vBlob->GetBufferSize(), nullptr, &vertexShader);

	UINT layout = ARRAYSIZE(PNTVertexLayout);

	// Create the input layout
	hr = device->CreateInputLayout(PNTVertexLayout, layout, vBlob->GetBufferPointer(), vBlob->GetBufferSize(), &vertexLayout);

	ID3DBlob * pBlob = nullptr;
	hr = D3DCompileFromFile(L"SimpleTriangle.fx", nullptr, nullptr, "PS", "ps_4_0", dwShaderFlags, 0, &pBlob, &errorBlob);

	// Create the pixel shader
	hr = device->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pixelShader );	
}

HRESULT SimpleTriangleMesh::Initialize()
{
	HRESULT result = S_OK;

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

void SimpleTriangleMesh::Render(ID3D11DeviceContext * context)
{
	context->IASetInputLayout(vertexLayout);
	context->VSSetShader(vertexShader, nullptr, 0);
	context->PSSetShader(pixelShader, nullptr, 0);

	BaseMesh::Render(context);
}

HRESULT SimpleTriangleMesh::CreateVertexBuffer()
{
	HRESULT result;

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

HRESULT SimpleTriangleMesh::CreateIndexBuffer()
{
	HRESULT result;

	//Fill in the index buffer description.
	bufferDescription.Usage = D3D11_USAGE_DEFAULT;
	bufferDescription.ByteWidth = sizeof(WORD) * indexCount;
	bufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDescription.CPUAccessFlags = 0;
	bufferDescription.MiscFlags = 0;

	//Fill in the index subresource data.
	bufferSubData.pSysMem = triangleIndices;
	bufferSubData.SysMemPitch = 0;
	bufferSubData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&bufferDescription, &bufferSubData, &indexBuffer);

	return result;
}