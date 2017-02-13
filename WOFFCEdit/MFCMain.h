#pragma once

#include <afxwin.h> 
#include <afxext.h>
#include <afx.h>
#include "pch.h"
#include "Game.h"
#include "ToolMain.h"
#include "resource.h"


class MFCMain : public CWinApp 
{
public:
	MFCMain();
	~MFCMain();
	BOOL InitInstance();
	int  Run();
//	int  OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
//	int  OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
//	afx_msg LRESULT OnMyCommand(WPARAM wParam, LPARAM lParam);

private:

	HWND m_toolHandle;	//Handle to the MFC window
	ToolMain m_ToolSystem;	//Instance of Tool System that we interface to. 
	CRect WindowRECT;	//Window area rectangle. 
	
	int m_width;		
	int m_height;
	DECLARE_MESSAGE_MAP()	// required macro for message map functionality  One per class
};
