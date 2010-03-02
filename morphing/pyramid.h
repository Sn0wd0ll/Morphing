#pragma once
#include "directx9.h"
#include <stdlib.h>
#include <vector>
using namespace D3D;
using namespace std;
namespace MyPyramid
{
	enum Coords
	{
		R = 0,
		TETHA = 1,
		PHI = 2
	};
	const unsigned TesselateLevel = 4;
	
	typedef vector<CUSTOMVERTEX> TesselateVertex;
	typedef vector<CUSTOMINDEX> TesselateIndex;

	class Pyramid
	{
	public:
		Pyramid();
		~Pyramid();
		Graphics device;
		bool InitialObject();
		void Tessellate(TesselateVertex &Vertex, TesselateIndex &Index, int i1, int i2, int i3, int tesselate_level);
		bool Draw(TesselateVertex &Vertex);
		void Move(float x, Coords alpha);
		TesselateVertex PyramidVertex;
		TesselateIndex PyramidIndex;
		unsigned CountIndex;
		unsigned CountVertex;
	private:
		float r, tetha, phi;
		float Rate;
	};
}
