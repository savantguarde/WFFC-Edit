// SelectDialogue.cpp : implementation file
//

#include "stdafx.h"
#include "SelectDialogue.h"

// SelectDialogue dialog

IMPLEMENT_DYNAMIC(SelectDialogue, CDialogEx)

SelectDialogue::SelectDialogue(CWnd* pParent, std::vector<SceneObject>* SceneGraph)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	m_sceneGraph = SceneGraph;
}

SelectDialogue::~SelectDialogue()
{
}


void SelectDialogue::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listBox);
}

BOOL SelectDialogue::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//roll through all the objects in the scene graph and put an entry for each in the listbox
	int numSceneObjects = m_sceneGraph->size();
	for (size_t i = 0; i < numSceneObjects; i++)
	{
		//easily possible to make the data string presented more complex. showing other columns.
		std::wstring listBoxEntry = std::to_wstring(m_sceneGraph->at(i).ID);
		m_listBox.AddString(listBoxEntry.c_str());
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(SelectDialogue, CDialogEx)
	
	ON_BN_CLICKED(IDOK, &SelectDialogue::OnBnClickedOk)
END_MESSAGE_MAP()


// SelectDialogue message handlers

INT_PTR CALLBACK SelectProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{	
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hwndDlg, wParam);
			return TRUE;
			

		case IDCANCEL:
			EndDialog(hwndDlg, wParam);
			return TRUE;
			break;
		}
	}
	
	return INT_PTR();
}


void SelectDialogue::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
