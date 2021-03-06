
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
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	WCHAR aPasswordChar;

public:
	CEdit ctrlKey;
	afx_msg void OnBnClickedButtonShowHideKey();
	afx_msg void OnBnClickedButtonSelectBmpHide();
	afx_msg void OnBnClickedButtonSelectFileHide();
	afx_msg void OnBnClickedButtonSelectBmpExtract();
	afx_msg void OnBnClickedButtonSelectFileExtract();
	afx_msg void OnBnClickedButtonSelectSourceImage();
	afx_msg void OnBnClickedButtonHide();
	afx_msg void OnBnClickedButtonExtract();
	CEdit ctrlSourceImage;
	CEdit ctrlBmpHide;
	CEdit ctrlFileHide;
	CEdit ctrlBmpExtract;
	CEdit ctrlFileExtract;
	void ErrorMessage(int strMessageID);
	void ErrorMessage(LPCTSTR strMessage);
	bool CheckKeyAndFileNamesHideSection(CString & key, CString & sourceImagePath, CString & fileHide, CString & bmpFilePath);
	bool CheckKeyAndFileNamesExtractSection(CString & key, CString & etractFromBmpFilePath, CString & extractFilePath);
	afx_msg void OnBnClickedButtonExit();
};
