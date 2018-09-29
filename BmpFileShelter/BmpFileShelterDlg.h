
// BmpFileShelterDlg.h : header file
//

#pragma once


// CBmpFileShelterDlg dialog
class CBmpFileShelterDlg : public CDialogEx
{
// Construction
public:
	CBmpFileShelterDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BMPFILESHELTER_DIALOG };
#endif

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

	WCHAR aPasswordChar;

public:
	CEdit ctrlKey;
	afx_msg void OnBnClickedButtonShowHideKey();
};
