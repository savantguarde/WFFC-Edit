#pragma once

#include <string>


//This object should accurately and totally reflect the information stored in the object table


class SceneObject
{
public:
	SceneObject();
	~SceneObject();

	int ID;
	int chunk_ID;
	std::string model_path;
	std::string tex_diffuse_path;
	float posX, posY, posZ;
	float rotX, rotY, rotZ;
	float scaX, scaY, scaZ;
	bool render, collision;
	std::string collision_mesh;
	bool collectable, destructable;
	int health_amount;
	bool editor_render, editor_texture_vis;
	bool editor_normals_vis, editor_collision_vis, editor_pivot_vis;
	float pivotX, pivotY, pivotZ;
	bool snapToGround;
	bool AINode;
	std::string audio_path;
	float volume;
	float pitch;
	float pan;
	bool one_shot;
	bool play_on_init;
	bool play_in_editor;
	int min_dist;
	int max_dist;
	bool camera;
	bool path_node;
	bool path_node_start;
	bool path_node_end;
	int parent_id;
};

