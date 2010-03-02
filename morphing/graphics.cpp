#include "directx9.h"

using namespace D3D;

Graphics::Graphics()
{
	shader.device			= this;
	matrix.device			= this;
	pDirect3D				= NULL;
	pDirect3DDevice			= NULL;
	pVertexBuffer			= NULL;
	pIndexBuffer			= NULL;
}

Graphics::~Graphics()
{
	if (NULL != pDirect3DDevice)
	{
		pDirect3DDevice->Release();
	}
	if (NULL != pDirect3D)
	{
		pDirect3D->Release();
	}
	if (NULL != pVertexBuffer)
	{
		pVertexBuffer->Release();
	}
	if (NULL != pIndexBuffer)
	{
		pIndexBuffer->Release();
	}
}

HRESULT Graphics::InitialDirect3D(HWND hwnd)
{
	if (NULL == (pDirect3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}
	D3DDISPLAYMODE Display;
	if (FAILED (pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &Display)))
	{
		return E_FAIL;
	}
	D3DPRESENT_PARAMETERS Direct3DParametr;
	ZeroMemory(&Direct3DParametr, sizeof(Direct3DParametr));
	Direct3DParametr.Windowed = TRUE;
	Direct3DParametr.SwapEffect = D3DSWAPEFFECT_DISCARD;
	Direct3DParametr.BackBufferFormat = Display.Format;
	Direct3DParametr.EnableAutoDepthStencil = TRUE;
	Direct3DParametr.hDeviceWindow = hwnd;
	Direct3DParametr.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED (pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, 
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &Direct3DParametr, &pDirect3DDevice)))
	{
		return E_FAIL;
	}
	//pDirect3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	return S_OK;
}

HRESULT Graphics::InitialVertexBuffer(unsigned int CountVertex)
{
	if (FAILED(pDirect3DDevice->CreateVertexBuffer(CountVertex*sizeof(CUSTOMVERTEX), 0, 0,
			D3DPOOL_MANAGED,&pVertexBuffer, NULL)))
	{
		return E_FAIL;
	}
	return S_OK;	
}

HRESULT Graphics::InitialIndexBuffer(unsigned int CountIndex)
{
	if (FAILED(pDirect3DDevice->CreateIndexBuffer(CountIndex*sizeof(CUSTOMINDEX), 0, D3DFMT_INDEX16,
		D3DPOOL_MANAGED,&pIndexBuffer, NULL)))
	{
		return E_FAIL;
	}
	return S_OK;
}
