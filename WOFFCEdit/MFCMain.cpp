#include "MFCMain.h"
#include "MFCFrame.h"
#include "resource.h"



BEGIN_MESSAGE_MAP(MFCMain, CWinApp)
	//ON_MESSAGE(WM_COMMAND, OnMyCommand)
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
/*
int MFCMain::OnCmdMsg(UINT nID, int nCode, void * pExtra, AFX_CMDHANDLERINFO * pHandlerInfo)
{
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_OPEN, 0);
	return 0;


LRESULT MFCMain::OnMyCommand(WPARAM wParam, LPARAM lParam)
{
	// ... Handle message here
	int commandId = LOWORD(wParam);

	switch (commandId) {
	case ID_BUTTON40001:
		MessageBox(0, L"Hello there!", L"ID_HELLO_COMMAND", MB_OK);
		break;
		// ... other commands here
	}

	return 0L;
}
*/

MFCMain::MFCMain()
{
}


MFCMain::~MFCMain()
{
}
