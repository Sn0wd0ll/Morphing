#include "pyramid.h"

using namespace D3D;
using namespace MyPyramid;

const float Rotation = D3DX_PI/24;


Pyramid::Pyramid(): r(3.0f), tetha(D3DX_PI/3), phi(D3DX_PI/6)
{
};

bool Pyramid::InitialObject()
{
	const float coord1 = 1.0f;
	const float coord2 = 1.41f;
	CUSTOMVERTEX Vertex[] = 
	{
		CUSTOMVERTEX( coord1,  -coord1,	 0,            RED),	
		CUSTOMVERTEX(-coord1,  -coord1,  0,          BLACK),	
		CUSTOMVERTEX(-coord1,   coord1,  0,        MAGENTA),	
		CUSTOMVERTEX( coord1,   coord1,  0,         YELLOW),		
		CUSTOMVERTEX(      0,        0,   coord2,    GREEN),		
		CUSTOMVERTEX(      0,        0,  -coord2,    WHITE)
	};
	CountVertex = sizeof(Vertex) / sizeof(Vertex[0] );
	CUSTOMINDEX Index[] = 
	{
		0, 4, 3,	3, 4, 2,
        2, 4, 1,	1, 4, 0,
		0, 3, 5,	3, 2, 5,
        2, 1, 5,	1, 0, 5
	};
	CountIndex = sizeof(Index) / sizeof(Index[0] );
	PyramidVertex.erase(PyramidVertex.begin(), PyramidVertex.end());
	PyramidIndex.erase(PyramidIndex.begin(), PyramidIndex.end());
	for (int unsigned i = 0; i<CountVertex; ++i)
	{
		PyramidVertex.push_back(Vertex[i]);
	}
	for (int unsigned i = 0; i<CountIndex; ++i)
	{
		PyramidIndex.push_back(Index[i]);
	}
	Tessellate (PyramidVertex, PyramidIndex, 0, 4, 3, 0);
	Tessellate (PyramidVertex, PyramidIndex, 3, 4, 2, 0);
	Tessellate (PyramidVertex, PyramidIndex, 2, 4, 1, 0);
	Tessellate (PyramidVertex, PyramidIndex, 1, 4, 0, 0);
	Tessellate (PyramidVertex, PyramidIndex, 0, 3, 5, 0);
	Tessellate (PyramidVertex, PyramidIndex, 3, 2, 5, 0);
	Tessellate (PyramidVertex, PyramidIndex, 2, 1, 5, 0);
	Tessellate (PyramidVertex, PyramidIndex, 1, 0, 5, 0);
	
	CountVertex = PyramidVertex.size();
	if (S_OK != device.InitialVertexBuffer(CountVertex))
	{
		return false;
	}
	void *pVB;
	if (S_OK != device.GetVB()->Lock(0, sizeof(PyramidVertex[0])*CountVertex, &pVB,0))
	{
		return false;
	}
	memcpy(pVB, &PyramidVertex[0], sizeof(PyramidVertex[0])*CountVertex);
	device.GetVB()->Unlock();

	CountIndex = PyramidIndex.size();
	if (D3D_OK != device.InitialIndexBuffer(CountIndex))
	{
		return false;
	}
	void *pIB;
	if (D3D_OK != device.GetIB()->Lock(0, sizeof(PyramidIndex[0])*CountIndex, &pIB,0))
	{
		return false;
	}
	memcpy(pIB, &PyramidIndex[0], sizeof(PyramidIndex[0])*CountIndex);
	device.GetIB()->Unlock();
	return true;
}

Pyramid::~Pyramid()
{
}

void Pyramid::Move(float x, Coords alpha)
{
	switch (alpha)
	{
	case TETHA:
		tetha+=(Rotation)*x;
		break;
	case PHI:
		phi+= (Rotation)*x;
		break;
	};
}