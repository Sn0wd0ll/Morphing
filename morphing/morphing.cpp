#include "pyramid.h"
using namespace MyPyramid;
using namespace D3D;

CUSTOMVERTEX AddVertex(TesselateVertex Vertex, int i1, int i2)
{
	DWORD color = D3DCOLOR_XRGB(rand()%256, rand()%256, rand()%256);
	return CUSTOMVERTEX ((Vertex[i1].x+Vertex[i2].x)/2,
						(Vertex[i1].y+Vertex[i2].y)/2,
						(Vertex[i1].z+Vertex[i2].z)/2,
						 color);
}

void Pyramid::Tessellate(TesselateVertex &Vertex, TesselateIndex &Index, int i1, int i2, int i3, int tesselate_level)
{
	if (tesselate_level < TesselateLevel)
	{
		int newIndex = Vertex.size()-1;
		Vertex.push_back(AddVertex(Vertex, i1, i3));
		Vertex.push_back(AddVertex(Vertex, i1, i2));
		Vertex.push_back(AddVertex(Vertex, i2, i3));
		
		tesselate_level++;
		Tessellate(Vertex, Index, i1, newIndex + 2, newIndex + 1, tesselate_level);
 		Tessellate(Vertex, Index, i2, newIndex + 3, newIndex + 2, tesselate_level);
 		Tessellate(Vertex, Index, i3, newIndex + 1, newIndex + 3, tesselate_level);
 		Tessellate(Vertex, Index, newIndex + 1, newIndex + 2, newIndex + 3, tesselate_level);
	}
	else
	{
		Index.push_back(i1);
		Index.push_back(i2);
		Index.push_back(i3);
	}
}

bool Pyramid::Draw(TesselateVertex &Vertex)
{
	if (NULL == device.GetDirect3D())
		return false;
	void *pVB;
	if (S_OK != device.GetVB()->Lock(0, sizeof(Vertex[0])*CountVertex, &pVB,0))
	{
		return false;
	}
	memcpy(pVB, &Vertex[0], sizeof(Vertex[0])*CountVertex);
	device.GetVB()->Unlock();
	device.Get3DDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 100, 150), 1.0f, 0);
	device.Get3DDevice()->BeginScene();
	if (S_OK == device.matrix.SetMatrix(r, tetha, phi))
	{
		device.Get3DDevice()->SetStreamSource(0, device.GetVB(), 0, sizeof(CUSTOMVERTEX));
		device.Get3DDevice()->SetIndices(device.GetIB());
		device.Get3DDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, CountVertex, 0, CountIndex/3); 
	}

	device.Get3DDevice()->EndScene();
	device.Get3DDevice()->Present(NULL, NULL, NULL, NULL);
	return true;
}
