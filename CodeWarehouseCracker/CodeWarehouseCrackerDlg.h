
// CodeWarehouseCrackerDlg.h : header file
//

#pragma once


// CCodeWarehouseCrackerDlg dialog
class CCodeWarehouseCrackerDlg : public CDialog
{
// Construction
public:
	CCodeWarehouseCrackerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CODEWAREHOUSECRACKER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
private:
	CString m_strExePath;
public:
	afx_msg void OnBnClickedOk();
};
