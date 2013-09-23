
// MainUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MainUI.h"
#include "MainUIDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"
#include "DecisionHistory.h"
#include "EngineBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDecisionHistory m_history;
CEngineBox m_engineBox;
CDecisionEngine* m_lpDengine = NULL;

CMenu *m_pop;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMainUIDlg dialog


IMPLEMENT_DYNAMIC(CMainUIDlg, CDialogEx);

CMainUIDlg::CMainUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainUIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
	m_history.Load();
}

CMainUIDlg::~CMainUIDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CMainUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC2, m_tbcMin);
	DDX_Control(pDX, IDC_STATIC3, m_tbcMax);
	DDX_Control(pDX, IDC_LIST1, lpclbDecisions);
}

BEGIN_MESSAGE_MAP(CMainUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_INITMENUPOPUP()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMainUIDlg::OnBnClickedButton1)
	ON_COMMAND(ID_HELP_ABOUT, &CMainUIDlg::OnHelpAbout)
	ON_COMMAND(ID_EDIT_UNDO, &CMainUIDlg::OnEditUndo)
	//ON_COMMAND(ID_EDIT_UNDOA, &CMainUIDlg::OnEditUndoa)
	ON_COMMAND(ID_EDIT_CLEAR, &CMainUIDlg::OnEditClear)
	ON_COMMAND_RANGE(60000, 60100, &CMainUIDlg::OnEngineSelect)
	ON_COMMAND(ID_FILE_EXIT, &CMainUIDlg::OnFileExit)
END_MESSAGE_MAP()


// CMainUIDlg message handlers

void CMainUIDlg::OnInitMenuPopup(CMenu *pcmPopupMenu, UINT nIndex,BOOL bSysMenu)
{
	// NOTE: might not need to do this
	//CCmdUI state;
	//state.m_pMenu = pcmPopupMenu;

	//AfxGetThreadState()->m_hTrackingMenu == pcmPopupMenu->m_hMenu;
	//state.m_pParentMenu
 //   if (bSysMenu)
	//{

	//}
	////pcmPopupMenu->EnableMenuItem(
}

BOOL CMainUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// NOTE: not sure what's going on it never seems to add this to the Help Menu?
	// Just added another one to the resources, using it instead. Afraid to remove this not sure why Visual
	// Studio added it

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	CMenu* menu = new CMenu();
	menu->CreatePopupMenu();

	m_engineBox.LoadEngines();
	m_engineBox.BeginEnumerateEngines();
	int i = 0;

	// n stands for engine
	while (auto n = m_engineBox.GetNextEngine())
	{
		if (m_lpDengine == NULL)
		{
			m_lpDengine = n;
		}
		menu->AppendMenu(MF_STRING, 60000 + ++i, n->GetName());
	}
	GetMenu()->InsertMenu(2, MF_POPUP, (UINT_PTR)menu->m_hMenu, "Engines");
	CheckMenuItem(GetMenu()->GetSafeHmenu(), 60001, MF_CHECKED  );

	BOOL* bools;
	int cnt;
	if ((cnt = m_history.GetDecisions(&bools)) > 0)
	{
		GetMenu()->EnableMenuItem(ID_EDIT_UNDO, MF_ENABLED);
	}

	//GetDlgItem(IDC_STATIC2)

	//m_tbcMin.SetWindowText();
#define BIG "                    "
	char big[] = BIG;
	sprintf(big, "%d", cnt);
	m_tbcMin.SetWindowText(big);

	// not sure why it's saying it's full one too soon but for now we'll just say there's one fewer decision
	// available -- shouldn't matter too much
	sprintf(big, "%d", sizeof(DECISION_STORAGE_TYPE) * 8 - 1);
	m_tbcMax.SetWindowTextA(big);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMainUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// just learned about auto; showing John how it works
	// gonna switch everything to it for the next version of the program
	auto ulSelected = (nID & 0xFFF0);
	if (ulSelected == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMainUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMainUIDlg::OnQueryDragIcon()
{
	return (HCURSOR)(m_hIcon);
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CMainUIDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CMainUIDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CMainUIDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CMainUIDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}



void CMainUIDlg::OnBnClickedButton1()
{
	if (m_history.IsHostoryFull() == FALSE)
	{
		if (m_history.PushDecision(TRUE) == TRUE)
		{
			BOOL decision = (*m_lpDengine).GetDecision();

			// TODO: Add your control notification handler code here
			if (decision == TRUE)
			{
				MessageBox("YES, definitely!", "Decision being made...", MB_OK);
				lpclbDecisions.InsertString(0, "Yes");
			}
			else
			{
				MessageBox("NO, bad idea!", "Decision being made...", MB_OK);
				lpclbDecisions.InsertString(0, "No");
			}
			m_history.Save();

			GetMenu()->EnableMenuItem(ID_EDIT_UNDO, MF_ENABLED);

			int cnt;
			char txt[] = BIG;
			m_tbcMin.GetWindowText(txt, sizeof(txt));
			sscanf(txt, "%d", &cnt);
			++cnt;
			sprintf(txt, "%d", cnt);
			m_tbcMin.SetWindowText(txt);
		}
	}
	else
	{
		// TODO: Add your control notification handler code here
		MessageBox("Not enough room for decision! You'll need to undo some decisions to make room, or clear your log.", "Decision failure", MB_ICONHAND);
	}
}


void CMainUIDlg::OnHelpAbout()
{
	// HACK: gotta be a cleaner way to do this
	OnSysCommand(IDM_ABOUTBOX, 0);
}


void CMainUIDlg::OnEditUndo()
{
	BOOL y;
	if (m_history.PopDecision(&y))
	{
		MessageBox("Decision undone!", "Success", MB_ICONWARNING);
		m_history.Save();

		int cnt;
		char txt[] = BIG;
		m_tbcMin.GetWindowText(txt, sizeof(txt));
		sscanf(txt, "%d", &cnt);
		--cnt;
		sprintf(txt, "%d", cnt);
		m_tbcMin.SetWindowText(txt);

		lpclbDecisions.DeleteString(0);

		BOOL *y;
		if (m_history.GetDecisions(&y) == 0) {
			CMenu *menu = GetMenu();
			menu->EnableMenuItem(ID_EDIT_UNDO, MF_DISABLED);
		}
	}
	else
	{
		MessageBox("No histroy to undo!", "Failure", MB_ICONHAND);
		CMenu *menu = GetMenu();
		menu->EnableMenuItem(ID_EDIT_UNDO, MF_DISABLED);
	}
	// TODO: Add your command handler code here
}


void CMainUIDlg::OnEditUndoa()
{
	// looks like we'll need to do this to make shortcut keys work in our app
// http://support.microsoft.com/kb/100770
	OnEditUndo();
}

void CMainUIDlg::OnEngineSelect(UINT iEngine)
{
	for (int i = 60000; i < 60100; ++i)
	{
		CheckMenuItem(GetMenu()->GetSafeHmenu(), i , MF_UNCHECKED  );
	}

	m_lpDengine = m_engineBox * (iEngine - 60001);
	//CheckMenuItem(GetMenu()->GetSubMenu(2)->GetSafeHmenu(), iEngine, MF_CHECKED  );
	CheckMenuItem(GetMenu()->GetSafeHmenu(), iEngine, MF_CHECKED  );
	( ( CWnd* ) GetDlgItem( IDC_ENGINENAM ) )->SetWindowText( m_lpDengine->GetName() );
	( ( CWnd* ) GetDlgItem( IDC_ENGINED2 ) )->SetWindowText(m_lpDengine->GetDescription() );
}

void CMainUIDlg::OnEditClear()
{
	// doesn't seem to work...
	//m_history.ClearDecisions();

	BOOL y;
	while (m_history.PopDecision(&y))
	{
		m_history.Save();
		int cnt;
		char txt[] = BIG;
		m_tbcMin.GetWindowText(txt, sizeof(txt));
		sscanf(txt, "%d", &cnt);
		--cnt;
		sprintf(txt, "%d", cnt);
		m_tbcMin.SetWindowText(txt);

		lpclbDecisions.DeleteString(0);
	}

	CMenu *menu = GetMenu();
	menu->EnableMenuItem(ID_EDIT_UNDO, MF_DISABLED);
	m_history.Save();
}


void CMainUIDlg::OnFileExit()
{
	exit(0);
}
