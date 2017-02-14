#include "MFCFrame.h"
#include "resource.h"



BEGIN_MESSAGE_MAP(CMyFrame, CFrameWnd)
	ON_WM_CREATE()
//	ON_COMMAND(ID_BUTTON40001, CMyFrame.m_ToolSystem.OnActionSave)
//	ON_COMMAND(ID_BUTTON40001, &CMyFrame::activate)
//	ON_MESSAGE(WM_COMMAND, stuff)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};
//FRAME CLASS

/*
LRESULT CMyFrame::stuff(WPARAM wParam, LPARAM lParam)
{
	if (wParam == ID_BUTTON40001)
	{
		float temp = 0;
	}
	return 0L;
}

void CMyFrame::activate()
{
	float temp = 0;
}*/

//frame initialiser
CMyFrame::CMyFrame()
{
}

//oncretae, called after init but before window is shown. 
int CMyFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1) return -1;

	// create a view to occupy the client area of the frame //This is where DirectX is rendered
	if (!m_DirXView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	m_menu1.LoadMenuW(IDR_MENU1);
	SetMenu(&m_menu1);
	
	if (!m_toolBar.CreateEx(this, TBSTYLE_TRANSPARENT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_toolBar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));



	return 0;
}