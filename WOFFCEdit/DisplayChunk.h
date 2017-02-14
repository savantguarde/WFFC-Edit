#pragma once
#include "pch.h"

class DisplayChunk
{
public:
	DisplayChunk();
	~DisplayChunk();

	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormalTexture>>  m_batch;
	std::unique_ptr<DirectX::BasicEffect>       m_terrainEffect;
	ID3D11ShaderResourceView *					m_heightmap;					//heightmap texture
	ID3D11ShaderResourceView *					m_texture_diffuse;				//diffuse texture
	Microsoft::WRL::ComPtr<ID3D11InputLayout>   m_terrainInputLayout;

private:
	
};

