#pragma once
#include "d3d9.h"
#include "d3dx9.h"
#include <tchar.h>

namespace D3D
{
	enum {TIME = 0,
		  RADIUS = 1,
		  MATRIX = 2 };

	const DWORD RED = D3DCOLOR_XRGB(255, 0, 0);
	const DWORD BLACK = D3DCOLOR_XRGB(0, 0, 0);
	const DWORD MAGENTA = D3DCOLOR_XRGB(255, 0, 255);
	const DWORD YELLOW = D3DCOLOR_XRGB(255, 255, 0);
	const DWORD GREEN = D3DCOLOR_XRGB(0, 255, 0);
	const DWORD WHITE = D3DCOLOR_XRGB(255, 255, 255);
	const DWORD CYAN = D3DCOLOR_XRGB(0, 255, 255);	
	const DWORD BLUE = D3DCOLOR_XRGB(0, 0, 255);

	class Graphics;
	struct CUSTOMVERTEX		
	{
		float x, y, z;
		DWORD color;

		CUSTOMVERTEX(float x = 0.0f, float y = 0.0f, float z = 0.0f, DWORD color = RED):
										x(x), y(y), z(z), color(color)
		{}
	};
	typedef unsigned short CUSTOMINDEX;

	class Matrix
	{
	public:
		Matrix();
		~Matrix();
		Graphics *device;
		HRESULT SetMatrix(float r, float tetha, float phi);
	private:
		D3DXVECTOR3		at;
		D3DXVECTOR3		eye;
		D3DXVECTOR3		up;
		D3DXMATRIX ViewMatrix;
		D3DXMATRIX ProjMatrix;
		D3DXMATRIX WorldMatrix;
	};

	class Shader 
	{
	public:
		Shader();
		~Shader();
		Graphics *device;
		HRESULT InitialShader();
		HRESULT SetShader();
	private:
		LPDIRECT3DVERTEXDECLARATION9	pDeclaration;
		IDirect3DVertexShader9			*pVShader;
		ID3DXBuffer						*pCode;
		IDirect3DVertexDeclaration9		*pVDeclaration;
	};

	class Graphics
	{
	public:
		Graphics();
		~Graphics();
		Matrix matrix;
		Shader shader;
		HRESULT InitialDirect3D(HWND hwnd);
		HRESULT InitialVertexBuffer(unsigned int CountVertex);
		HRESULT InitialIndexBuffer(unsigned int CountIndex);

		inline LPDIRECT3D9 GetDirect3D()       {return pDirect3D;}
		inline LPDIRECT3DDEVICE9 Get3DDevice() {return pDirect3DDevice;}
		inline LPDIRECT3DVERTEXBUFFER9 GetVB() {return pVertexBuffer;}
		inline LPDIRECT3DINDEXBUFFER9 GetIB()  {return pIndexBuffer;}
	private:
		LPDIRECT3D9						pDirect3D;
		LPDIRECT3DDEVICE9				pDirect3DDevice;
		LPDIRECT3DVERTEXBUFFER9			pVertexBuffer;
		LPDIRECT3DINDEXBUFFER9			pIndexBuffer;
	};

	const TCHAR SHADER_FILE[] = _T("shader.vsh");
}
