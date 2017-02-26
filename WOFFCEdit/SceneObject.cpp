#include "SceneObject.h"



SceneObject::SceneObject()
{
	ID = 0;
	chunk_ID =0 ;
	model_path ="";
	tex_diffuse_path = "";
	posX = 0.0f;	posY = 0.0f;	posZ = 0.0f;
	rotX = 0.0f;	rotY = 0.0f;	rotZ = 0.0f;
	scaX = 0.0f;	scaY = 0.0f;	scaZ = 0.0f;
	render = true;
	collision = false;
	collision_mesh ="";
	collectable = false;
	destructable = false;
	health_amount = 0;
	editor_render = true;  
	editor_texture_vis = true;
	editor_normals_vis = false;
	editor_collision_vis = false;
	editor_pivot_vis = true;
	pivotX = 0.0f; pivotY = 0.0f; pivotZ = 0.0f;
	snapToGround = false;
	AINode = false;
	audio_path = "";
	float volume =0.0f;
	float pitch = 0.0f;
	float pan = 0.0f;
	bool one_shot = false;
	bool play_on_init = false;
	bool play_in_editor = false;
	int min_dist = 0;
	int max_dist = 0;
	bool camera = false;
	bool path_node = false;
	bool path_node_start = false;
	bool path_node_end = false;
	int parent_id =0;
}


SceneObject::~SceneObject()
{
}
