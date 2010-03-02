#include "directx9.h"
#include "pyramid.h"
using namespace D3D;
using namespace MyPyramid;
Shader::Shader()
{
	pVShader				= NULL;
	pCode					= NULL;
	pDeclaration			= NULL;
}

Shader::~Shader()
{
	if (pVShader != NULL)
		pVShader->Release();
	if (pVDeclaration != NULL)
		pVDeclaration->Release();
}

HRESULT Shader::InitialShader()
{
	D3DCAPS9 Caps;
	device->Get3DDevice()->GetDeviceCaps(&Caps);
	if (Caps.VertexShaderVersion < D3DVS_VERSION(1,1))
	{
		return E_FAIL;
	}
	D3DVERTEXELEMENT9 Declaration[] = 
	{
		{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
		D3DDECL_END()
	};
	if (D3D_OK != device->Get3DDevice()->CreateVertexDeclaration(Declaration, &pVDeclaration))
	{
		return E_FAIL;
	}
	if (D3D_OK != D3DXAssembleShaderFromFile(SHADER_FILE, NULL, NULL, 0, &pCode, NULL))
	{	
		return E_FAIL;
	}
	if (D3D_OK != device->Get3DDevice()->CreateVertexShader((DWORD*)(pCode->GetBufferPointer()), &pVShader))
	{	
		return E_FAIL;
	}
	pCode->Release();
	return S_OK;
}

HRESULT Shader::SetShader()
{
	if (D3D_OK != device->Get3DDevice()->SetVertexDeclaration(pVDeclaration))
	{
		return E_FAIL;
	}
	if (D3D_OK != device->Get3DDevice()->SetVertexShader(pVShader))
	{	
		return E_FAIL;
	}
	return S_OK;
}