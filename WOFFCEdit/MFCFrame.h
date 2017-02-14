#pragma once
#include <afxwin.h> 
#include <afxext.h>
#include "MFCRenderFrame.h"
#include "ToolMain.h"



class CMyFrame : public CFrameWnd
{
protected:
//	DECLARE_DYNAMIC(CMainFrame)

public:

	CMenu			m_menu1;	//menu bar
	CStatusBar		m_wndStatusBar;
	CToolBar		m_toolBar;
	CChildRender	m_DirXView;

public:
	CMyFrame();
//	afx_msg LRESULT stuff(WPARAM wParam, LPARAM lParam);
//	afx_msg void activate();

private:	//overrides

			//note the afx_message keyword is linking this method to message map access.
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()	// required macro for message map functionality  One per class
};