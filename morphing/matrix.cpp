#include "directx9.h"
#include <time.h>
using namespace D3D;

const float PERIOD			= 1.0f;
const float RATE			= 2.0f*D3DX_PI/PERIOD;
const float SphereRadius	= 1.41f;
const float SPEED			= 50.0f;
Matrix::Matrix():at(0, 0, 0), eye(3, 3, 3), up(0, 1, 0)
{
}

Matrix::~Matrix()
{
}

HRESULT Matrix::SetMatrix(float r, float tetha, float phi)
{
	eye.x = r*sin(tetha)*cos(phi);
	eye.y = r*sin(tetha)*sin(phi);
	eye.z = r*cos(tetha);
	D3DXVECTOR3 x;
	D3DXVECTOR3 y;
	D3DXVECTOR3 z;
	z = at - eye;
	D3DXVec3Normalize(&z, &z);
	D3DXVec3Cross(&x, &up, &z);
	D3DXVec3Normalize(&x, &x);

	D3DXVec3Cross(&y, &z, &x);

	D3DXMATRIX ViewMatrix (x.x, x.y, x.z, -D3DXVec3Dot(&eye, &x),
						   y.x, y.y, y.z, -D3DXVec3Dot(&eye, &y),
						   z.x, z.y, z.z, -D3DXVec3Dot(&eye, &z),
						   0,   0,   0,   1);
    const float M = 1.0f;
    const float F = 20.0f;
    float a = F/(F - M);
    float b = -M * a;
	D3DXMATRIX ProjMatrix (M, 0,  0,  0,
					       0, M,  0,  0,
					       0, 0,  a,  b,
					       0, 0,  1,  0);

	D3DXMATRIX WorldMatrix = ProjMatrix * ViewMatrix;
	if( D3D_OK != device->Get3DDevice()->SetVertexShaderConstantF(MATRIX, static_cast<float*>(WorldMatrix), 4))
	{
		return E_FAIL;
	}
	float time = static_cast<float>(clock()*SPEED)/static_cast<float>(CLOCKS_PER_SEC);
    float t = (sin(D3DXToRadian(RATE*time)) + 1.0f)/2.0f; 
	D3DXVECTOR4 v(t, 0.0f, 0.0f, 0.0f);
	if( D3D_OK != device->Get3DDevice()->SetVertexShaderConstantF(TIME, v, 1))
	{
		return E_FAIL;
	}
	v.x = SphereRadius;
	if( D3D_OK != device->Get3DDevice()->SetVertexShaderConstantF(RADIUS, v, 1))
	{
		return E_FAIL;
	}
	device->shader.SetShader();
	
	return S_OK;
}
