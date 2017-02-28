#include "MFCMain.h"
#include "MFCFrame.h"
#include "resource.h"



BEGIN_MESSAGE_MAP(MFCMain, CWinApp)
	ON_COMMAND(ID_FILE_QUIT,	&MFCMain::MenuFileQuit)
	ON_COMMAND(ID_FILE_SAVETERRAIN, &MFCMain::MenuFileSaveTerrain)
	ON_COMMAND(ID_BUTTON40001,	&MFCMain::ToolBarButton1)
END_MESSAGE_MAP()

BOOL MFCMain::InitInstance()
{
	//instanciate the mfc frame
	CMyFrame *Frame = new CMyFrame();
	m_pMainWnd = Frame;

	Frame->Create(	NULL,
					_T("World Of Flim-Flam Craft Editor"),
					WS_OVERLAPPEDWINDOW,
					CRect(100, 100, 1024, 768),
					NULL,
					NULL,
					0,
					NULL
				);

	//get the rect from the MFC window so we can get its dimensions
//	m_toolHandle = Frame->GetSafeHwnd();						//handle of main window
	m_toolHandle = Frame->m_DirXView.GetSafeHwnd();				//handle of directX child window
	Frame->m_DirXView.GetWindowRect(&WindowRECT);
	m_width = WindowRECT.Width();
	m_height = WindowRECT.Height();

	Frame->ShowWindow(SW_SHOW);
	Frame->UpdateWindow();

	m_ToolSystem.onActionInitialise(m_toolHandle, 800, 600);

	return TRUE;
}

int MFCMain::Run()
{
	MSG msg;
	BOOL bGotMsg;

	PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);

	while (WM_QUIT != msg.message)
	{
		if (true)
		{
			bGotMsg = (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0);
		}
		else
		{
			bGotMsg = (GetMessage(&msg, NULL, 0U, 0U) != 0);
		}

		if (bGotMsg)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			m_ToolSystem.UpdateInput(&msg);
		}
		else
		{	
			m_ToolSystem.Tick(&msg);
		}
	}

	return (int)msg.wParam;
}

void MFCMain::MenuFileQuit()
{
	//will post message to the message thread that will exit the application normally
	PostQuitMessage(0);
}

void MFCMain::MenuFileSaveTerrain()
{
	m_ToolSystem.onActionSaveTerrain();
}

void MFCMain::ToolBarButton1()
{
	m_ToolSystem.onActionSave();
}


MFCMain::MFCMain()
{
}


MFCMain::~MFCMain()
{
}
