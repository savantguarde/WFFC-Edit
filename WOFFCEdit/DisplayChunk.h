#pragma once
#include "pch.h"
#include "DeviceResources.h"

//geometric resoltuion - note,  hard coded.
#define TERRAINRESOLUTION 128

class DisplayChunk
{
public:
	DisplayChunk();
	~DisplayChunk();
	void RenderBatch(std::shared_ptr<DX::DeviceResources>  DevResources);
	void InitialiseBatch();
	void LoadHeightMap(std::shared_ptr<DX::DeviceResources>  DevResources, std::string *Heightmap);

	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormalTexture>>  m_batch;
	std::unique_ptr<DirectX::BasicEffect>       m_terrainEffect;
	ID3D11ShaderResourceView *					m_heightmapInitialLoading;		//heightmap texture loaded into here first and we get the static data from it.
	ID3D11ShaderResourceView *					m_heightmap;					//heightmap texture
	ID3D11ShaderResourceView *					m_texture_diffuse;				//diffuse texture
	Microsoft::WRL::ComPtr<ID3D11InputLayout>   m_terrainInputLayout;

private:
	
	DirectX::VertexPositionNormalTexture m_terrainGeometry[TERRAINRESOLUTION][TERRAINRESOLUTION];
	D3D11_TEXTURE2D_DESC m_desc;
	ID3D11Texture2D		*m_pTexture;
	ID3D11Resource		*m_pDstResource;
	D3D11_MAPPED_SUBRESOURCE m_mappedResource;



	int		m_terrainSize;				//size of terrain in metres
	float	m_textureCoordStep;			//step in texture coordinates between each vertex row / column
	float   m_terrainPositionScalingFactor;	//factor we multiply the position by to convert it from its native resolution( 0- Terrain Resolution) to full scale size in metres dictated by m_Terrainsize
	
};

