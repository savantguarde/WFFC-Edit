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
	volume =0.0f;
	pitch = 0.0f;
	pan = 0.0f;
	one_shot = false;
	play_on_init = false;
	play_in_editor = false;
	min_dist = 0;
	max_dist = 0;
	camera = false;
	path_node = false;
	path_node_start = false;
	path_node_end = false;
	parent_id =0;
	editor_wireframe=false;
	name ="";
	light_type = 1;
	light_diffuse_r = 1;	light_diffuse_g = 1;	light_diffuse_b = 1;
	light_specular_r = 1;	light_specular_g = 1;	light_specular_b = 1;
	light_spot_cutoff = 1;
	light_constant = 1;
	light_linear = 1;
	light_quadratic = 1;
}


SceneObject::~SceneObject()
{
}
