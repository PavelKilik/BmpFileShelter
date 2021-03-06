
// BmpFileShelterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BmpFileShelter.h"
#include "BmpFileShelterDlg.h"
#include "afxdialogex.h"
#include "CBmpFileShelterHelper.h"
#include "CMyImage.h"
#include "CMyFileEncryptor.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBmpFileShelterDlg dialog



CBmpFileShelterDlg::CBmpFileShelterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BMPFILESHELTER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBmpFileShelterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_KEY, ctrlKey);
	DDX_Control(pDX, IDC_EDIT_SOURCE_IMAGE, ctrlSourceImage);
	DDX_Control(pDX, IDC_EDIT_BMP_HIDE, ctrlBmpHide);
	DDX_Control(pDX, IDC_EDIT_FILE_HIDE, ctrlFileHide);
	DDX_Control(pDX, IDC_EDIT_BMP_EXTRACT, ctrlBmpExtract);
	DDX_Control(pDX, IDC_EDIT_FILE_EXTRACT, ctrlFileExtract);
}

BEGIN_MESSAGE_MAP(CBmpFileShelterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SHOW_HIDE_KEY, &CBmpFileShelterDlg::OnBnClickedButtonShowHideKey)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_BMP_HIDE, &CBmpFileShelterDlg::OnBnClickedButtonSelectBmpHide)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_HIDE, &CBmpFileShelterDlg::OnBnClickedButtonSelectFileHide)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_BMP_EXTRACT, &CBmpFileShelterDlg::OnBnClickedButtonSelectBmpExtract)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE_EXTRACT, &CBmpFileShelterDlg::OnBnClickedButtonSelectFileExtract)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_SOURCE_IMAGE, &CBmpFileShelterDlg::OnBnClickedButtonSelectSourceImage)
	ON_BN_CLICKED(IDC_BUTTON_HIDE, &CBmpFileShelterDlg::OnBnClickedButtonHide)
	ON_BN_CLICKED(IDC_BUTTON_EXTRACT, &CBmpFileShelterDlg::OnBnClickedButtonExtract)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CBmpFileShelterDlg::OnBnClickedButtonExit)
END_MESSAGE_MAP()


// CBmpFileShelterDlg message handlers

void CBmpFileShelterDlg::OnOK()
{
}

void CBmpFileShelterDlg::OnCancel()
{
}

BOOL CBmpFileShelterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	aPasswordChar = ctrlKey.GetPasswordChar();

	//ctrlKey.SetWindowTextW(L"/ä,ö,ü,Ä,Ö,Ü,ß/家蚕（学名：Bombyx mori）是鳞翅目的昆虫，丝绸的主要原料来源，在人类经济生活及文化歷史上占有重要地位。/");
	//ctrlSourceImage.SetWindowText(L"K:\\Pictures\\010.jpg");
	//ctrlFileHide.SetWindowText(L"K:\\Pictures\\010.txt");
	//ctrlBmpHide.SetWindowText(L"K:\\Pictures\\011.bmp");
	//ctrlBmpExtract.SetWindowText(L"K:\\Pictures\\011.bmp");
	//ctrlFileExtract.SetWindowText(L"K:\\Pictures\\011.txt");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBmpFileShelterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
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

void CBmpFileShelterDlg::OnPaint()
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
HCURSOR CBmpFileShelterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBmpFileShelterDlg::ErrorMessage(int strMessageID)
{
	CString errMsg;
	errMsg.LoadStringW(strMessageID);
	ErrorMessage(errMsg);
}

void CBmpFileShelterDlg::ErrorMessage(LPCTSTR strMessage)
{
	MessageBox(strMessage, L"Error", MB_OK | MB_ICONERROR);
}

bool CBmpFileShelterDlg::CheckKeyAndFileNamesHideSection(CString & key, CString & sourceImagePath, CString & fileHide, CString & bmpFilePath)
{
	ctrlKey.GetWindowText(key);
	ctrlSourceImage.GetWindowText(sourceImagePath);
	ctrlFileHide.GetWindowText(fileHide);
	ctrlBmpHide.GetWindowText(bmpFilePath);

	CString errMsg;

	if (key.GetLength() < CMyFileEncryptor::MinKeySize)
	{
		ctrlKey.SetFocus();
		CString errMsg;
		errMsg.Format(IDS_STRING_ERR_KEY_SIZE, CMyFileEncryptor::MinKeySize);
		ErrorMessage(errMsg);
		return false;
	}

	if (!CBmpFileShelterHelper::CheckImageExtension(sourceImagePath))
	{
		ctrlSourceImage.SetFocus();
		errMsg.LoadString(IDS_STRING_ERR_IMAGE_FILE_PATH);
		ErrorMessage(errMsg);
		return false;
	}

	if (!CBmpFileShelterHelper::CheckImageExtension(bmpFilePath, true))
	{
		ctrlBmpHide.SetFocus();
		errMsg.LoadString(IDS_STRING_ERR_BMP_FILE_PATH);
		ErrorMessage(errMsg);
		return false;
	}

	if (fileHide.GetLength() < 1)
	{
		ctrlBmpHide.SetFocus();
		errMsg.LoadString(IDS_STRING_ERR_HIDE_FILE_PATH);
		ErrorMessage(errMsg);
		return false;
	}

	return true;
}

bool CBmpFileShelterDlg::CheckKeyAndFileNamesExtractSection(CString & key, CString & etractFromBmpFilePath, CString & extractFilePath)
{
	ctrlKey.GetWindowText(key);
	ctrlBmpExtract.GetWindowText(etractFromBmpFilePath);
	ctrlFileExtract.GetWindowText(extractFilePath);

	CString errMsg;

	if (key.GetLength() < CMyFileEncryptor::MinKeySize)
	{
		ctrlKey.SetFocus();
		CString errMsg;
		errMsg.Format(IDS_STRING_ERR_KEY_SIZE, CMyFileEncryptor::MinKeySize);
		ErrorMessage(errMsg);
		return false;
	}

	if (!CBmpFileShelterHelper::CheckImageExtension(etractFromBmpFilePath, true))
	{
		ctrlBmpExtract.SetFocus();
		errMsg.LoadString(IDS_STRING_ERR_BMP_FILE_PATH);
		ErrorMessage(errMsg);
		return false;
	}

	if (extractFilePath.GetLength() < 1)
	{
		ctrlFileExtract.SetFocus();
		errMsg.LoadString(IDS_STRING_ERR_TARGET_FILE_PATH);
		ErrorMessage(errMsg);
		return false;
	}

	return true;
}

void CBmpFileShelterDlg::OnBnClickedButtonShowHideKey()
{
	if (ctrlKey.GetPasswordChar() == 0)
	{
		ctrlKey.SetPasswordChar(aPasswordChar);
	}
	else
	{
		ctrlKey.SetPasswordChar(0);
	}
	ctrlKey.RedrawWindow();
}

void CBmpFileShelterDlg::OnBnClickedButtonSelectSourceImage()
{
	static TCHAR BASED_CODE szFilter[] = _T("Image files (*.bmp;*.jpg;*.jpeg;*.png)|*.bmp;*.jpg;*.jpeg;*.png|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, szFilter);
	if (dlg.DoModal() == IDOK)
	{
		ctrlSourceImage.SetWindowTextW(dlg.GetPathName());
	}
}

void CBmpFileShelterDlg::OnBnClickedButtonSelectBmpHide()
{
	static TCHAR BASED_CODE szFilter[] = _T("Bmp file (*.bmp)|*.bmp|All Files (*.*)|*.*||");
	CFileDialog dlg(FALSE, NULL, NULL, OFN_OVERWRITEPROMPT, szFilter);
	if (dlg.DoModal() == IDOK)
	{
		ctrlBmpHide.SetWindowTextW(dlg.GetPathName());
	}
}


void CBmpFileShelterDlg::OnBnClickedButtonSelectFileHide()
{
	static TCHAR BASED_CODE szFilter[] = _T("All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, szFilter);
	if (dlg.DoModal() == IDOK)
	{
		ctrlFileHide.SetWindowTextW(dlg.GetPathName());
	}
}


void CBmpFileShelterDlg::OnBnClickedButtonSelectBmpExtract()
{
	static TCHAR BASED_CODE szFilter[] = _T("Bmp file (*.bmp)|*.bmp|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, szFilter);
	if (dlg.DoModal() == IDOK)
	{
		ctrlBmpExtract.SetWindowTextW(dlg.GetPathName());
	}
}


void CBmpFileShelterDlg::OnBnClickedButtonSelectFileExtract()
{
	static TCHAR BASED_CODE szFilter[] = _T("All Files (*.*)|*.*||");
	CFileDialog dlg(FALSE, NULL, NULL, OFN_OVERWRITEPROMPT, szFilter);
	if (dlg.DoModal() == IDOK)
	{
		ctrlFileExtract.SetWindowTextW(dlg.GetPathName());
	}
}


void CBmpFileShelterDlg::OnBnClickedButtonHide()
{
	CString key;
	CString sourceImagePath;
	CString fileHidePath;
	CString hideIntoBmpFilePath;

	if (!CheckKeyAndFileNamesHideSection(key, sourceImagePath, fileHidePath, hideIntoBmpFilePath))
	{
		return;
	}

	CMyImage sourceImage;
	CWaitCursor waitCur;
	HRESULT hr = sourceImage.Load(sourceImagePath);
	if (hr == S_OK)
	{
		int bmpCapacity = sourceImage.GetCapacity();
		CString errorString;
		CMyFileEncryptor mfe;
		int encryptedSize;
		byte * pB = mfe.Encrypt(fileHidePath, key, bmpCapacity, encryptedSize, errorString);
		if (pB != nullptr)
		{
			sourceImage.HideByteArrayIntoBitmap(pB, encryptedSize);
			hr = sourceImage.Save(hideIntoBmpFilePath);
			if (hr == S_OK)
			{
				MessageBox(L"OK");
			}
			else
			{
				ErrorMessage(IDS_STRING_ERR_CREATE_BMP);
			}
		}
		else
		{
			ErrorMessage(errorString);
		}
	}
	else
	{
		ErrorMessage(IDS_STRING_ERR_SOURCE_IMAGE_READING);
		ctrlSourceImage.SetFocus();
	}
}


void CBmpFileShelterDlg::OnBnClickedButtonExtract()
{
	CString key;
	CString etractFromBmpFilePath;
	CString extractedFilePath;

	if (!CheckKeyAndFileNamesExtractSection(key, etractFromBmpFilePath, extractedFilePath))
	{
		return;
	}

	CMyImage sourceImage;
	CWaitCursor waitCur;
	HRESULT hr = sourceImage.Load(etractFromBmpFilePath);
	if (hr == S_OK)
	{
		int arrSize;
		byte *pB = sourceImage.ExtractByteArrayFromBitmap(arrSize);
		if (pB != nullptr)
		{
			CString errString;
			CMyFileEncryptor mfe;
			if (!mfe.Decrypt(extractedFilePath, key, pB, arrSize, errString))
			{
				ErrorMessage(errString);
			}
			else
			{
				MessageBox(L"OK");
			}
			delete pB;
		}
	}
	else
	{
		ErrorMessage(IDS_STRING_ERR_SOURCE_IMAGE_READING);
		ctrlSourceImage.SetFocus();
	}
}


void CBmpFileShelterDlg::OnBnClickedButtonExit()
{
	this->EndDialog(IDCANCEL);
}
