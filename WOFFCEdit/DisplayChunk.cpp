#include "DisplayChunk.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

DisplayChunk::DisplayChunk()
{
	//terrain size in meters. note that this is hard coded here, we COULD get it from the terrain chunk along with the other info from the tool if we want to be more flexible.
	m_terrainSize = 512;
}


DisplayChunk::~DisplayChunk()
{
}

void DisplayChunk::RenderBatch()
{

	m_batch->Begin();

	VertexPositionNormalTexture v1(Vector3(-64.0f, 0.0f, 64.0f),	Vector3(0.0f, 1.0f, 0.0f),	Vector2(0.0f, 0.0f));
	VertexPositionNormalTexture v2(Vector3(-64.0f, 0.0f, -64.0f),	Vector3(0.0f, 1.0f, 0.0f),	Vector2(0.0f, 1.0f));
	VertexPositionNormalTexture v3(Vector3(64.0f, 0.0f, 64.0f),		Vector3(0.0f, 1.0f, 0.0f),	Vector2(1.0f, 0.0f));
	VertexPositionNormalTexture v4(Vector3(64.0f, 0.0f, -64.0f),	Vector3(0.0f, 1.0f, 0.0f),	Vector2(1.0f, 1.0f));

	m_batch->DrawTriangle(v1, v2, v3);

	m_batch->End();
}

void DisplayChunk::InitialiseBatch()
{
	//build geometry for our terrain array
	//iterate through all the vertices of our required resolution terrain.
	for (size_t i = 0; i < TERRAINRESOLUTION; i++)
	{
		for (size_t j = 0; j < TERRAINRESOLUTION; j++)
		{
			m_terrainGeometry[i][j].position =			Vector3(i-(0.5*TERRAINRESOLUTION), 0.0f, j-(0.5*TERRAINRESOLUTION));	//This will create a terrain going from -64->64.  rather than 0->128.  So the center of the terrain is on the origin
			m_terrainGeometry[i][j].normal =			Vector3(0.0f, 1.0f, 0.0f);						//standard y =up
			m_terrainGeometry[i][j].textureCoordinate =	Vector2((float)1/i, (float)1/j);				//Spread tex coords so that its distributed evenly across the terrain from 0-1
		}
	}
}
