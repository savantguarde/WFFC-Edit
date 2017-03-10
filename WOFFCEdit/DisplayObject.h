#pragma once
#include "pch.h"


class DisplayObject
{
public:
	DisplayObject();
	~DisplayObject();

	std::shared_ptr<DirectX::Model>						m_model;							//main Mesh
	ID3D11ShaderResourceView *							m_texture_diffuse;					//diffuse texture


	int m_ID;
	DirectX::SimpleMath::Vector3			m_position;
	DirectX::SimpleMath::Vector3			m_orientation;
	DirectX::SimpleMath::Vector3			m_scale;
	bool									m_render;
	bool									m_wireframe;
};

