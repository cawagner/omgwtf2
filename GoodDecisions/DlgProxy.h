
// DlgProxy.h: header file
//

#pragma once

class CMainUIDlg;


// CMainUIDlgAutoProxy command target

class CMainUIDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CMainUIDlgAutoProxy)

	CMainUIDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CMainUIDlg* m_pDialog;

// Operations
public:

// Overrides
	public:
	virtual void OnFinalRelease();

// Implementation
protected:
	virtual ~CMainUIDlgAutoProxy();

	// Generated message map functions

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CMainUIDlgAutoProxy)

	// Generated OLE dispatch map functions

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

