
// MainUIDlg.h : header file
//

#pragma once
#include "afxwin.h"

class CMainUIDlgAutoProxy;


// CMainUIDlg dialog
class CMainUIDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainUIDlg);
	friend class CMainUIDlgAutoProxy;

// Construction
public:
	CMainUIDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CMainUIDlg();

// Dialog Data
	enum { IDD = IDD_MAINUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	CMainUIDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex,BOOL fSysMenu);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnHelpAbout();
	afx_msg void OnEditUndo();
	afx_msg void OnEditUndoa();
	afx_msg void OnEditClear();
	void CMainUIDlg::OnEngineSelect(UINT iEngine);
	CStatic m_tbcMin;
	CStatic m_tbcMax;
	CListBox lpclbDecisions;
	afx_msg void OnFileExit();
};
