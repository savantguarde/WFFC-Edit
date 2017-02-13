#pragma once
#include <afxwin.h> 
#include <afxext.h>


// CChildView window

class CChildRender : public CWnd
{
	// Construction
public:
	CChildRender();

	// Attributes
public:

	// Operations
public:

	// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// Implementation
public:
	virtual ~CChildRender();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};

