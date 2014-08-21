
// CodeWarehouseCrackerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CodeWarehouseCracker.h"
#include "CodeWarehouseCrackerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCodeWarehouseCrackerDlg dialog




CCodeWarehouseCrackerDlg::CCodeWarehouseCrackerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCodeWarehouseCrackerDlg::IDD, pParent)
	, m_strExePath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCodeWarehouseCrackerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCodeWarehouseCrackerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CCodeWarehouseCrackerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CCodeWarehouseCrackerDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CCodeWarehouseCrackerDlg message handlers

BOOL CCodeWarehouseCrackerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	m_strExePath = TEXT("C:\\Program Files\\Code Warehouse\\CodeWarehouse.exe");
	SetDlgItemText(IDC_EDIT1, m_strExePath);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCodeWarehouseCrackerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCodeWarehouseCrackerDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCodeWarehouseCrackerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCodeWarehouseCrackerDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CFileDialog fileDlg(TRUE,_T("exe"),_T("CodeWarehouse"),OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST,TEXT("Execute files(*.exe, *.ocx, *.dll, *.com, *.bat)|*.exe; *.ocx; *.dll; *.com; *.bat|All Files(*.*)|*.*||"),NULL); 
	if (IDOK == fileDlg.DoModal()) {
		m_strExePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT1,m_strExePath);
	}
}

void CCodeWarehouseCrackerDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//MessageBox(m_strExePath);
	CFile dstFile;
	CFileException ex;

	// open the source file for reading
	if (!dstFile.Open(m_strExePath,
		CFile::modeReadWrite | CFile::typeBinary, &ex))
	{
		// complain if an error happened
		// no need to delete the ex object

		TCHAR szError[1024];
		ex.GetErrorMessage(szError, 1024);
		CString errorMsg;
		errorMsg.Format(_T("Couldn't open source file: %s"), szError);
		MessageBox(errorMsg, _T("Error"));
	}
	else
	{
		long blockSize = 0x18677L; /* random access*/
		byte *pBuffer = new byte[blockSize];
		dstFile.Read(pBuffer, blockSize);
		pBuffer[blockSize-1] = 0x17;
		dstFile.SeekToBegin();
		dstFile.Write(pBuffer, blockSize);
		delete[] pBuffer;
		dstFile.Close();
		MessageBox(TEXT("Successfully Patched!"), TEXT("Patch"));
	}

}
