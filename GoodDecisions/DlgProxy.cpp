
// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "MainUI.h"
#include "DlgProxy.h"
#include "MainUIDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainUIDlgAutoProxy

IMPLEMENT_DYNCREATE(CMainUIDlgAutoProxy, CCmdTarget)

CMainUIDlgAutoProxy::CMainUIDlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CMainUIDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CMainUIDlg)))
		{
			m_pDialog = reinterpret_cast<CMainUIDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CMainUIDlgAutoProxy::~CMainUIDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CMainUIDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CMainUIDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMainUIDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// Note: we add support for IID_IMainUI to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {A999E970-850C-484C-926C-B720F4DF4CD3}
static const IID IID_IMainUI =
{ 0xA999E970, 0x850C, 0x484C, { 0x92, 0x6C, 0xB7, 0x20, 0xF4, 0xDF, 0x4C, 0xD3 } };

BEGIN_INTERFACE_MAP(CMainUIDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CMainUIDlgAutoProxy, IID_IMainUI, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {6DA093B9-25B0-41AD-888E-F3C7C3ED7879}
IMPLEMENT_OLECREATE2(CMainUIDlgAutoProxy, "MainUI.Application", 0x6da093b9, 0x25b0, 0x41ad, 0x88, 0x8e, 0xf3, 0xc7, 0xc3, 0xed, 0x78, 0x79)


// CMainUIDlgAutoProxy message handlers
