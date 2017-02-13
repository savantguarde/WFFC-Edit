#include "ToolMain.h"
#include "resource.h"
#include <vector>

//SQL CALLBACKS
//callback for loading the objects from the object table, into our sceneGraph

/*static int callbackObjectLoad(void *data, int argc, char **argv, char **azColName)
{
	std::vector<SceneObject> * newPointerToObject;								//create a new pointer to a vector of scene objects, just like our scenegraph
	newPointerToObject = static_cast<std::vector<SceneObject>*>(data);			//static cast this new pointer to the data pointer passed in here
																				//its a void pointer so we have to do this static cast.
	SceneObject newSceneObject;

	//set all object attributes from database into temp scenegraph object
	newSceneObject.ID = (int)argv[0];
//	newSceneObject.chunk_ID = argv[1];
	newSceneObject.model_path = argv[2];
	newSceneObject.tex_diffuse_path = argv[3];

	newSceneObject.posX = (float)argv[4];
	newSceneObject.posY = (float)argv[5];
	newSceneObject.posZ = (float)argv[6];
	

	//append scenegraph with the new object. 
	newPointerToObject->push_back(newSceneObject);
	return 0;
}*/


//ToolMain Class
ToolMain::ToolMain()
{
//	m_sceneGraph = new std::vector<SceneObject>;	//initialise vector of scene objects. 
	m_currentChunk = 0;		//default value
	m_sceneGraph.clear();	//clear the vector for the scenegraph

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
		newSceneObject.model_path = reinterpret_cast<const char*>(sqlite3_column_text(pResults, 2));
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

		//send completed object to scenegraph
		m_sceneGraph.push_back(newSceneObject);
	}
//	rc = sqlite3_exec(m_databaseConnection, sqlCommand, callbackObjectLoad, m_sceneGraph, &ErrMSG);
	///SQL

	//Process REsults into renderable
	m_d3dRenderer.BuildDisplayList(&m_sceneGraph, &m_chunk);

}

void ToolMain::onActionSave()
{
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

	case WM_COMMAND:
	{
		int wmId = LOWORD(msg->wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_FILE_QUIT:
			MessageBox(msg->hwnd, L"Whatever", L"Whenever", MB_OK);
			break;
	
		case ID_BUTTON40001:
			MessageBox(msg->hwnd, L"Whatever", L"Whenever", MB_OK);
			break;
		}
	}

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
