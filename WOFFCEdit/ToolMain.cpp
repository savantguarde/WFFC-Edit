#include "ToolMain.h"
#include "resource.h"
#include <vector>

//ToolMain Class
ToolMain::ToolMain()
{
//	m_sceneGraph = new std::vector<SceneObject>;	//initialise vector of scene objects. 
	m_currentChunk = 0;		//default value
	m_sceneGraph.clear();	//clear the vector for the scenegraph
	m_databaseConnection = NULL;

	//zero input commands
	m_toolInputCommands.forward		= false;
	m_toolInputCommands.back		= false;
	m_toolInputCommands.left		= false;
	m_toolInputCommands.right		= false;
	
}


ToolMain::~ToolMain()
{
	sqlite3_close(m_databaseConnection);		//close the database connection
}


void ToolMain::onActionInitialise(HWND handle, int width, int height)
{
	//window size, handle etc for directX
	m_width		= width;
	m_height	= height;
	m_d3dRenderer.GetDefaultSize(m_width, m_height);
	m_d3dRenderer.Initialize(handle, m_width, m_height);

	//database connection establish
	int rc;
	rc = sqlite3_open("database/test.db", &m_databaseConnection);

	if (rc) 
	{
		TRACE("Can't open database");
		//if the database cant open. Perhaps a more catastrophic error would be better here
	}
	else 
	{
		TRACE("Opened database successfully");
	}

	onActionLoad();
}

void ToolMain::onActionLoad()
{
	//load current chunk and objects into lists
	if (!m_sceneGraph.empty())		//is the vector empty
	{
		m_sceneGraph.clear();		//if not, empty it
	}

	//SQL
	int rc;
	char *sqlCommand;
	char *ErrMSG = 0;
	sqlite3_stmt *pResults;								//results of the query

	//prepare SQL Text
	sqlCommand = "SELECT * from Objects";				//sql command which will return all records from the objects table.

	//Send Command and fill result object
	rc = sqlite3_prepare_v2(m_databaseConnection, sqlCommand, -1, &pResults, 0 );

	
	//loop for each row in results until there are no more rows.  ie for every row in the results. We create and object
	while (sqlite3_step(pResults) == SQLITE_ROW)
	{	
		SceneObject newSceneObject;
		newSceneObject.ID = sqlite3_column_int(pResults, 0);
		newSceneObject.chunk_ID = sqlite3_column_int(pResults, 1);
		newSceneObject.model_path		= reinterpret_cast<const char*>(sqlite3_column_text(pResults, 2));
		newSceneObject.tex_diffuse_path = reinterpret_cast<const char*>(sqlite3_column_text(pResults, 3));
		newSceneObject.posX = sqlite3_column_double(pResults, 4);
		newSceneObject.posY = sqlite3_column_double(pResults, 5);
		newSceneObject.posZ = sqlite3_column_double(pResults, 6);
		newSceneObject.rotX = sqlite3_column_double(pResults, 7);
		newSceneObject.rotY = sqlite3_column_double(pResults, 8);
		newSceneObject.rotZ = sqlite3_column_double(pResults, 9);
		newSceneObject.scaX = sqlite3_column_double(pResults, 10);
		newSceneObject.scaY = sqlite3_column_double(pResults, 11);
		newSceneObject.scaZ = sqlite3_column_double(pResults, 12);
		newSceneObject.render = sqlite3_column_double(pResults, 13);
		newSceneObject.collision = sqlite3_column_double(pResults, 14);
		newSceneObject.collision_mesh = reinterpret_cast<const char*>(sqlite3_column_text(pResults, 15));
		newSceneObject.collectable = sqlite3_column_double(pResults, 16);
		newSceneObject.destructable = sqlite3_column_double(pResults, 17);
		newSceneObject.health_amount = sqlite3_column_double(pResults, 18);
		newSceneObject.editor_render = sqlite3_column_double(pResults, 19);
		newSceneObject.editor_texture_vis = sqlite3_column_double(pResults, 20);
		newSceneObject.editor_normals_vis = sqlite3_column_double(pResults, 21);
		newSceneObject.editor_collision_vis = sqlite3_column_double(pResults, 22);
		newSceneObject.editor_pivot_vis = sqlite3_column_double(pResults, 23);
		newSceneObject.pivotX = sqlite3_column_double(pResults, 24);
		newSceneObject.pivotY = sqlite3_column_double(pResults, 25);
		newSceneObject.pivotZ = sqlite3_column_double(pResults, 26);
		newSceneObject.snapToGround = sqlite3_column_double(pResults, 27);
		newSceneObject.AINode = sqlite3_column_double(pResults, 28);
		newSceneObject.audio_path = reinterpret_cast<const char*>(sqlite3_column_text(pResults, 29));
		newSceneObject.volume = sqlite3_column_double(pResults, 30);
		newSceneObject.pitch = sqlite3_column_double(pResults, 31);
		newSceneObject.pan = sqlite3_column_double(pResults, 32);
		newSceneObject.one_shot = sqlite3_column_double(pResults, 33);
		newSceneObject.play_on_init = sqlite3_column_double(pResults, 34);
		newSceneObject.play_in_editor = sqlite3_column_double(pResults, 35);
		newSceneObject.min_dist = sqlite3_column_double(pResults, 36);
		newSceneObject.max_dist = sqlite3_column_double(pResults, 37);
		newSceneObject.camera = sqlite3_column_double(pResults, 38);
		newSceneObject.path_node = sqlite3_column_double(pResults, 39);
		newSceneObject.path_node_start = sqlite3_column_double(pResults, 40);
		newSceneObject.path_node_end = sqlite3_column_double(pResults, 41);
		newSceneObject.parent_id = sqlite3_column_double(pResults, 42);
		
	
		

		bool camera;
		bool path_node;
		bool path_node_start;
		bool path_node_end;
		int parent_id;

		//send completed object to scenegraph
		m_sceneGraph.push_back(newSceneObject);
	}

	//Process REsults into renderable
	m_d3dRenderer.BuildDisplayList(&m_sceneGraph, &m_chunk);
	//build the renderable chunk 
	m_d3dRenderer.BuildDisplayChunk(&m_chunk);

}

void ToolMain::onActionSave()
{
	MessageBox(NULL, L"Save", L"Save", MB_OK);
}

void ToolMain::Tick(MSG *msg)
{
	//do we have a selection
	//do we have a mode
	//are we clicking / dragging /releasing
	//has something changed
		//update Scenegraph
		//add to scenegraph
		//resend scenegraph to Direct X renderer

	//Renderer Update Call
	m_d3dRenderer.Tick(&m_toolInputCommands);
}

void ToolMain::UpdateInput(MSG * msg)
{

	switch (msg->message)
	{
		//Global inputs,  mouse position and keys etc
	case WM_KEYDOWN:
		m_keyArray[msg->wParam] = true;
		break;

	case WM_KEYUP:
		m_keyArray[msg->wParam] = false;
		break;

	case WM_MOUSEMOVE:
		break;

	}
	//here we update all the actual app functionality that we want.  This information will either be used int toolmain, or sent down to the renderer (Camera movement etc
	//WASD movement
	if (m_keyArray['W'])
	{
		m_toolInputCommands.forward = true;
	}
	else m_toolInputCommands.forward = false;
	
	if (m_keyArray['S'])
	{
		m_toolInputCommands.back = true;
	}
	else m_toolInputCommands.back = false;
	if (m_keyArray['A'])
	{
		m_toolInputCommands.left = true;
	}
	else m_toolInputCommands.left = false;

	if (m_keyArray['D'])
	{
		m_toolInputCommands.right = true;
	}
	else m_toolInputCommands.right = false;
	//rotation
	if (m_keyArray['E'])
	{
		m_toolInputCommands.rotRight = true;
	}
	else m_toolInputCommands.rotRight = false;
	if (m_keyArray['Q'])
	{
		m_toolInputCommands.rotLeft = true;
	}
	else m_toolInputCommands.rotLeft = false;

	//WASD
}
